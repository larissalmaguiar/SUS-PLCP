
#include "sus.h"

#define lcp(i) ((i < n) ? (LCP[i]) : (0))

void print(uint_t *SA, int *SUS, unsigned char *T, int n)
{
    printf("i\tSA\tSUS\tSuffixies\n");
    for (int i = 0; i < n; ++i)
    {
        printf("%d\t%d\t%d\t", i, SA[i], SUS[SA[i]]);
        for (int j = SA[i]; j < n; ++j)
        {
             printf("%c", T[j]);
        }
        printf("$\n");
    }
}


bool equal(int *v1, int *v2, int tam)
{
    int i;
    for (i = 0; i < tam; i++)
    {
        if (v1[i] != v2[i])
        {
            printf("SUS and SUST are different in %d :(\n", i);
            return false;
        }
    }
    return true;
}

void isa(int *ISA, int n, uint_t *SA)
{
    for (int i = 0; i < n; i++) ISA[SA[i]] = i;
    SA[n] = n;
    ISA[n] = n;
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
void buildPLCP(int *PLCP, int *PHI, unsigned char *T, int n, int *ISA, uint_t *SA)
{
    int l = 0, k = 0;
    phi(PHI, n, ISA, SA);
    for (int i = 0; i <= n; i++)
    {
        k = PHI[i];
        if (k != n)
        {
            while (T[k + l] == T[i + l])
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
void SUS_2(int *SUS2, int n, int *PLCP, int *PHI, int *ISA, unsigned char *T, uint_t *SA)
{
    int cur;
    buildPLCP(PLCP, PHI, T, n, ISA, SA);
    for (int i = 0; i <= n; i++)
    {
        if (PHI[i] != n) SUS2[PHI[i]] = PLCP[i];
    }
    for (int i = 0; i < n; i++)
    {
        cur = max(PLCP[i], SUS2[i]) + 1;
        if (n - i - 1 >= cur)
            SUS2[i] = cur;
        else
            SUS2[i] = 0;
    }
}
void PLCPSUS(int *PLCP, int *PHI, unsigned char *T, int n, int *ISA, uint_t *SA, int *SUS)
{
    int l = 0, k = 0, cur=0;
    phi(PHI, n, ISA, SA);
    for (int i = 0; i < n; i++)
    {
        PLCP[i] = SUS[i] = -1;
    }
    PLCP[n] = 0;
    for (int i = 0; i <= n; i++)
    {
        // printf("i: %d\n", i);
        k = PHI[i];
        if (k != n)
        {
            while (T[k + l] == T[i + l])
            {
                l++;
            }
            PLCP[i] = l;
            l = max((l - 1), 0);
            SUS[k] = PLCP[i];
            if (PLCP[i]!= -1 && SUS[i]!= -1)
            {
                // printf("Sufixo (i): %d\tPLCP(i): %d\tPLCP(k): %d\n", i, PLCP[i], SUS[i]);
                cur = max(PLCP[i], SUS[i]) + 1;
                if (n - i - 1 >= cur) SUS[i] = cur;
                else SUS[i]=0;  
            }
            if (PLCP[k]!= -1 && SUS[k]!= -1)
            {
                // printf("Sufixo (k): %d\tPLCP(k): %d\tPLCP(phi(k)): %d\n", k, PLCP[k], SUS[k]);
                cur = max(PLCP[k], SUS[k]) + 1;
                if (n - k - 1 >= cur) SUS[k] = cur;
                else SUS[k]=0;
            }
        }
        else
            PLCP[i] = 0;
        // printf("i\tSUS\tPLCP\n");
        // for (int i = 0; i < n; ++i) printf("%d\t%d\t%d\n", i, SUS[i], PLCP[i]);
    }
}
void SUS_T(int *SUS, int n, int_t *LCP, uint_t *SA)
{
    for (int i = 1; i < n; i++)
    {
        int cur = 1 + max(lcp(i), lcp(i + 1));
        if (n - SA[i] - 1 >= cur)
            SUS[SA[i]] = cur;
        // else SUS[SA[i]]=0;
    }
}
void SUS_1(int *SUS, int *PHI, int n, int *PLCP, unsigned char *T, int *ISA, uint_t *SA)
{
    int k, cur;
    buildPLCP(PLCP, PHI, T, n, ISA, SA);
    for (int i = 0; i <= n; i++)
    {
        k = PHI[i];
        cur = 1 + max(PLCP[i], PLCP[k]);
        if (n - k - 1 >= cur)
            SUS[k] = cur;
        // else SUS[k]=0;
    }
}


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
