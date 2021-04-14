
#include "sus.h"


#define lcp(i) ((i < n) ? (LCP[i]) : (0))



bool iguais(int *v1, int *v2, int tam) 
{
    int i;
    for(i=0; i < tam; i++) 
    {
        if (v1[i] != v2[i]) 
        {
            printf("Os vetores não são iguais na posição: %d :(\n", i);
            return false;
        }
    }

    return true;
}
void inicializacao (int *SUS1, int *SUS, int *ISA, int *phi, uint_t SA[], int n)
{
    SA[n]=n;
    ISA[n]=n;
    for (int i = 0; i < n; i++)
    {
        SUS[i] = 0;
        SUS1[i] = 0;
        ISA[SA[i]] = i;
    }
    for (int i = 0; i <=n; i++)
    {
        if (ISA[i] != 0)
            phi[i] = SA[ISA[i] - 1];
        else
            phi[i]=-1;
    }
}

void construcaoPLCP(int *PLCP, int phi[], char Text[], int n, int *SUS2)
{
    int l=0, k=0;
    for (int i = 0; i <= n; i++)
    {
        k = phi[i];
        if (k != n)
        {
            while (Text[k + l] == Text[i + l])
            {
                l++;
            }
            PLCP[i] = l;
            SUS2[k]=PLCP[i];
            l = max((l - 1), 0);
        }
        else
            PLCP[i] = 0;
        
    }
}
void SUS_2(int *SUS2, int phi[], int n, int PLCP[])
{
    int cur;
    //for(int i=0; i<n; i++) SUS2[phi[i]]=PLCP[i];
        for(int i=0; i<n; i++)
        {
            cur=max(PLCP[i], SUS2[i]) +1;
            if(n-i-1>=cur)
            {
                SUS2[i]=cur;
            }
            else SUS2[i]=0;
        
        }
}
void SUS_tradicional(int *SUS, uint_t SA[], int n, int_t LCP[])
{
     for (int i = 1; i < n; i++)
    {
        int cur = 1 + max(lcp(i), lcp(i + 1));
        if (n - SA[i] - 1 >= cur)
            SUS[SA[i]] = cur;
    }
}
void SUS_1(int *SUS, int phi[], int n, int PLCP[], int ISA[])
{
    int k, cur;
    for (int i = 0; i <= n; i++)
    {
       k = phi[i];
        if(k!=-1)
        {
            cur = 1 + max(PLCP[i], PLCP[k]);
            if (n - k - 1 >= cur)
                SUS[k] = cur;
        }
        
    }
}
