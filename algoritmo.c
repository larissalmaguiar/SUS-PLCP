
//================================
//BIBLIOTECAS
//================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//================================
//TADS
//================================
#include "sacak-lcp.h"
#include "sus.h"
//#include "kseq.h"

#define lcp(i) ((i < n) ? (LCP[i]) : (0))
#define PHI(i) ((ISA[i]<n-1) ? (phi[i]) : (i))



int main()
{
    //================================
    //ENTRADA
    //================================
    FILE *ent;
    ent = fopen("teste1.txt", "r");
    fseek(ent, 0, SEEK_END);
    int n = ftell(ent);

    rewind(ent);

    char *Text = (char *)malloc((n + 1) * sizeof(char));
    fgets(Text, n, ent);
    Text[n - 1] = '\0';

    
    //================================
    //DECLARAÇÃO DE VETORES
    //================================
    uint_t *SA = (uint_t *)malloc((n) * sizeof(uint_t));
    int_t *LCP = (int_t *)malloc((n) * sizeof(int_t));
    int *SUS = (int *)malloc((n) * sizeof(int));
    int *ISA = (int *)malloc((n) * sizeof(int));
    int *phi = (int *)malloc((n) * sizeof(int));
    int *PLCP = (int *)malloc((n+1) * sizeof(int));
    int *SUS1 = (int *)malloc((n) * sizeof(int));
    int *SUS2 = (int *)malloc((n) * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        SA[i] = 0;
        LCP[i] = 0;
    }
    //================================
    //CHAMADA DE FUNÇÃO
    //================================
    sacak_lcp((unsigned char *)Text, (uint_t *)SA, LCP, n);

    //================================
    //INICIALIZAÇÃO E CONSTRUÇÃO
    //================================
    inicializacao(SUS1, SUS, ISA, phi, SA, n);
    construcaoPLCP(PLCP, phi, Text, n, SUS2);
    //================================
    //SUS VERSÃO 1
    //================================
    SUS_1(SUS, phi, n, PLCP, ISA);
    //================================
    //SUS VERSÃO 2
    //================================
    SUS_2(SUS2, phi, n, PLCP);
    //================================
    //SUS TRADICIONAL
    //================================
    SUS_tradicional(SUS1, SA, n, LCP);
    //================================
    //IMPRESSÃO
    //================================
    printf("Text = %s$\n\n", Text);
    if (iguais(SUS, SUS1,SUS2, n))
        printf("OS VETORES SÃO EQUIVALENTES :)\n");
    printf("\n");
    printf("i\tSA\tISA\tPLCP\tPHI\tSUST\tSUS1\tSUS2\tsuffixes\n");
    for (int i = 0; i < n; ++i)
    {

        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t", i, SA[i], ISA[SA[i]], PLCP[SA[i]], phi[SA[i]], SUS1[SA[i]], SUS[SA[i]], SUS2[SA[i]]);
        
        for (int j = SA[i]; j < n - 1; ++j)
        {
            printf("%c", Text[j]);
        }
        printf("$\n");
    }

    free(SA);
    free(LCP);
    fclose(ent);
    free(Text);
    return 0;
}
