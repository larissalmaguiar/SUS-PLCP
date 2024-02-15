
#include "sus.h"

#define lcp(i) ((i < n) ? (LCP[i]) : (0))

void print(uint_t *A, int *B, unsigned char *T, int n)
{
    printf("i\tA\tB\tSuffixes\n");
    for (int i = 0; i < n; ++i)
    {
        printf("%d\t%d\t%d\t", i, A[i], B[i]);
        for (int j = A[i]; j < n; ++j)
        {
          if(T[j]==0) printf("#");
          else if (T[j]==1){
            printf("$");
            break;
          }
          else printf("%c", T[j]-1);
        }
        printf("\n");
    }
}

void print_sus(uint_t *A, int *B, unsigned char *T, int n)
{
    printf("i\tA\tB\tSuffixes\n");
    for (int i = 0; i <=n; ++i)
    {
        printf("%d\t%d\t%d\t", i, A[i], B[A[i]]);
        for (int j = A[i]; j < n; ++j)
        {
          if(T[j]==0) printf("#");
          else if (T[j]==1){
            printf("$");
            break;
          }
          else printf("%c", T[j]-1);
        }
        printf("\n");
    }
}
bool equal(int *v1, int *v2, int tam)
{
    
    for (int i = 0; i <tam; i++)
    {
        if (v1[i] != v2[i])
        {
            printf("SUS and SUST are different in %d SUS: %d \t SUS_T: %d\n", i, v1[i], v2[i]);
            return false;
        }
    }
    return true;
}

void lcp_plcp(int_t *LCP, int *PLCP, uint_t *SA, int n)
{
    for(int i=0; i<=n; i++) LCP[i]=PLCP[SA[i]];
}
void isa(int *ISA, int n, uint_t *SA)
{
    SA[n] = n;
    for (int i = 0; i <= n; i++) ISA[SA[i]] = i;
}
void phi(int *PHI, int n, int *ISA, uint_t *SA)
{
    isa(ISA, n, SA);
    for (int i = 0; i <= n; i++)
    {
        if (ISA[i] != 0)
            PHI[i] = SA[ISA[i] - 1];
        else
            PHI[i] = n;
    }
}
void buildPHI(int *PHI, int n, uint_t *SA)
{
  PHI[SA[0]] = n;
  SA[n] = n;
  int i;
  for(i = 1; i<=n; i++)
    PHI[SA[i]] = SA[i-1];

}
void buildPLCP(int *PLCP, int *PHI, unsigned char *T, int n)//9n bytes
{
    int l = 0, k = 0;
    for (int i = 0; i <= n; i++)
    {
        k = PHI[i];
        if (k != n)
        {
            while (T[k + l] == T[i + l] && T[k+l]!=1)
            {
                l++;
            }
            PLCP[i] = l;
            l = max((l - 1), 0);
        }
        else
            PLCP[i] = 0;
    }
    PLCP[n] = 0;
}
/*
void SUS_2(int *SUS, int n, int *PLCP, int *PHI, unsigned char *T)
{
    n--;
    int p, cur, i;
    for (i = 0; i <= n; i++)
    {
        p=PHI[i];
        if (p!=n) SUS[p] = PLCP[i];
    }
    for (i = 0; i <= n; i++)
    {
        cur = max(PLCP[i], SUS[i]);
        if (n - i >= cur && T[i+cur]!= 1 && T[i+cur]!=0)
            SUS[i] = cur+1;
        else
            SUS[i] = 0;
    }
}
*/
void SUS_2(int sa_last, int n, int *PLCP, int *PHI, unsigned char *T)
{
    int cur, i, k, aux, cont=0;  
    PHI[n]=sa_last; 
    k=PHI[0];// sufixo que antecede o sufixo j
    aux=0;
    i=0;
    while(cont<=n)
    {
        aux=PHI[k]; //quem está sendo atualizado e o próximo a ser inicializado?
        PHI[k]= PLCP[i]; //na primeira iteração isso é o plcp de 0
        i=k;
        k=aux;
        //printf("%d\t", aux);
        cont++; 
    }
    for (i = 0; i <= n; i++)
    {
        cur = max(PLCP[i], PHI[i]);
        if (n - i >= cur && T[i+cur]!= 1 && T[i+cur]!=0)
            PHI[i] = cur+1;
        else
            PHI[i] = 0;
    }
}
void PLCPSUS(int *PLCP, int *PHI, unsigned char *T, int n, uint_t *SA, int *SUS)
{
    int l = 0, k = 0, cur=0;
    phi(PHI, n, SUS, SA);//SUS usado como vetor ISA
    for (int i = 0; i <= n; i++) SUS[i]=PLCP[i]=-1;
    PLCP[n] = 0;
    for (int i = 0; i <= n; i++)
    {
        k = PHI[i];
        if (k != n)
        {
            while ( T[k+l]!=1 && T[k + l] == T[i + l] )
            {
                l++;
            }
            PLCP[i] = l;
            SUS[k] = l;
            l = max((l - 1), 0);
            
            if (SUS[i]!= -1)
            {
                cur = max(PLCP[i], SUS[i]) ;
                if (n - i >= cur && T[i+cur] != 1) SUS[i] = cur+1;
                else SUS[i]=0;  
            }
            if (PLCP[k]!= -1)
            {
                cur = max(PLCP[k], SUS[k]);
                if (n - k  >= cur && T[k+cur] != 1) SUS[k] = cur+1;
                else SUS[k]=0;
            }
        }
        else PLCP[i] = 0;
    }
}
//checked :)
void SUS_T(unsigned char *T, int *SUS, int n, int_t *LCP, uint_t *SA)
{
    //SUS[SA[0]]=0; // O sufixo em SA[0] não é atualizado no loop, pq?
    for (int i = 0; i < n; i++)
    {
        int cur = max(lcp(i), lcp(i + 1))+1;
        if (T[SA[i]+cur-1] != 1 && T[SA[i]+cur-1]!=0 && cur+SA[i]<=n-1) //separator == 1
            SUS[SA[i]] = cur;
        else SUS[SA[i]]=0;
    }
}
/*
void SUS_11(int *SUS, int n, int *PLCP, int *PHI, unsigned char *T)
{

    int k, cur;    
    for (int i = 0; i <= n; i++)
    {
        k = PHI[i]; // sufixo que antecede o sufixo i 
        cur = 1 + max(PLCP[i], PLCP[k]); // tamanho da subcadeia 
        if (n - k - 1 >= cur && T[k+cur-1] != 1)
            SUS[k] = cur;
        else SUS[k]=0;
    }

    for(int i =0; i<=n; i++) printf("SUS[%d]: %d\n", i, SUS[i]);
}
//*/
///*
void SUS_1(int sa_last, int n, int *PLCP, int *PHI, unsigned char *T)
{

    int k, cur, aux, i, cont=0, plcp_ant;  
    PHI[n]=sa_last; 
    //for(int i =0; i<=n; i++) printf("PHI[%d]: %d\n", i, PHI[i]);
    k=PHI[0];// sufixo que antecede o sufixo i 
    aux=PLCP[k];
    //printf("SUS\n\n");
    while(cont<=n)
    {
        i=PHI[k];
        cur =  max(PLCP[i], aux); // tamanho da subcadeia 
        aux=PLCP[i];
        if (n - i >= cur && T[i+cur] != 1 && T[i+cur]!=0)
            PLCP[i] = cur+1;
        else PLCP[i]=0;
        k=i; // na segunda iteração o k vira i, então a comparação entre os plcps passa a ser de plcp[k] e aux que é o plcp[i] da iteração anterior, em que k=i
        cont++; 
    }
}
//*/
void sus_cr(int_t *LCP, int *ISA, int n, int k, unsigned char *T)
{
    int  tam=n, L=0;
    for(int i=0; i<=k; i++)
    {
        L=max(LCP[ISA[i]], LCP[ISA[i]+1]);
        if(i+L<n-1)
        {
            if(max(L+1, k-i+1)<tam) tam=max(L+1, k-i+1);
            else break; 
        }
    }
    printf("K: %d\t Length: %d\n", k, tam);
    for(int i=0; i<=k; i++)
    {
        L=max(LCP[ISA[i]], LCP[ISA[i]+1]);
        if(i+L<n-1)
        {
            if(max(L+1, k-i+1)==tam)
            {
                /* ???
                char sp[n];
                strcpy(sp, T+i);
                sp[tam]='\0';
                printf("%s\n", sp);
                */
            }
        }
    }
}
void SUS_C(int *ISA,uint_t *SA, int_t *LCP, int n, unsigned char *T)
{
    isa(ISA, n, SA);
    for(int i=0; i<n-1; i++)
    {
        sus_cr (LCP, ISA, n, i, T);
    }
}
