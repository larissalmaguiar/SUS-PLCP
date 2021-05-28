
#include "sus.h"

#define lcp(i) ((i < n) ? (LCP[i]) : (0))

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
/*void initialize(int *SUS, int *SUS1, int *ISA, int *phi, uint_t *SA, int n)
{
    SA[n] = n;
    ISA[n] = n;
    for (int i = 0; i < n; i++)
    {
        SUS[i] = 0;
        SUS1[i] = 0;
        ISA[SA[i]] = i;
    }
    for (int i = 0; i <= n; i++)
    {
        if (ISA[i] != 0)
            phi[i] = SA[ISA[i] - 1];
        else
            phi[i] = n;
    }
}*/
void isa(int *ISA, int n, uint_t *SA)
{
    SA[n] = n;
    ISA[n] = n;
    for (int i = 0; i < n; i++) ISA[SA[i]] = i;
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
void buildPLCP(int *PLCP, int *PHI, char *Text, int n, int *ISA, uint_t *SA)
{
    int l = 0, k = 0;
    phi(PHI, n, ISA, SA);
    for (int i = 0; i <= n; i++)
    {
        k = PHI[i];
        if (k != n)
        {
            while (Text[k + l] == Text[i + l])
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
void SUS_2(int *SUS2, int n, int *PLCP, int *PHI, int *ISA, char *Text, uint_t *SA)
{
    int cur;
    buildPLCP(PLCP, PHI, Text, n, ISA, SA);
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
void PLCPSUS(int *PLCP, int *PHI, char *Text, int n, int *ISA, uint_t *SA, int *SUS)
{
    int l = 0, k = 0;
    phi(PHI, n, ISA, SA);
    for (int i = 0; i < n; i++)
    {
        PLCP[i] = SUS[i] = -1;
    }
    PLCP[n] = 0;
    for (int i = 0; i <= n; i++)
    {
        k = PHI[i];
        if (k != n)
        {
            while (Text[k + l] == Text[i + l])
            {
                l++;
            }
            PLCP[i] = l;
            l = max((l - 1), 0);
            SUS[k] = PLCP[i];
            if (PLCP[i]!= -1 && SUS[i]!= -1)
            {
                int cur = max(PLCP[i], SUS[i]) + 1;
                if (n - i - 1 >= cur) SUS[i] = cur;
                else SUS[i]=0;
            }
            if (PLCP[k]!= -1 && SUS[k]!= -1)
            {
                int cur = max(PLCP[k], SUS[k]) + 1;
                if (n - k - 1 >= cur) SUS[k] = cur;
                else SUS[k]=0;
            }
        }
        else
            PLCP[i] = 0;
    }
}
void SUS_T(int *SUS, int n, int_t *LCP, uint_t *SA)
{
    for (int i = 1; i < n; i++)
    {
        int cur = 1 + max(lcp(i), lcp(i + 1));
        if (n - SA[i] - 1 >= cur)
            SUS[SA[i]] = cur;
    }
}
void SUS_1(int *SUS, int *PHI, int n, int *PLCP, char *Text, int *ISA, uint_t *SA)
{
    int k, cur;
    buildPLCP(PLCP, PHI, Text, n, ISA, SA);
    for (int i = 0; i <= n; i++)
    {
        k = PHI[i];
        cur = 1 + max(PLCP[i], PLCP[k]);
        if (n - k - 1 >= cur)
            SUS[k] = cur;
    }
}
void print(uint_t *SA, int *SUS, char *Text, int n)
{
    printf("i\tSA\tSUS\tsuffixes\n");
    for (int i = 0; i < n; ++i)
    {
        printf("%d\t%d\t%d\t", i, SA[i], SUS[SA[i]]);
        for (int j = SA[i]; j < n; ++j)
        {
            printf("%c", Text[j]);
        }
        printf("$\n");
    }
}
