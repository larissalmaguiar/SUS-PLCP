
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


#define lcp(i) ((i < n) ? (LCP[i]) : (0))



int main(int argc, char *argv[])
{
    //================================
    //ENTRADA
    //================================
    FILE *ent;
    ent = fopen(argv[1], "r");
    fseek(ent, 0, SEEK_END);
    int n = ftell(ent);
    rewind(ent);
    char *Text = (char *)malloc((n) * sizeof(char));
    char *line= malloc(n);
    while (fgets(line, n, ent) !=NULL)
    {
       if(line[0]!='>')
       {
           int tam=strlen(line);
           line[tam-1]='\0';
           strcat(Text, line);
       }
    }
    n=strlen(Text)+1;
    //================================
    //DECLARAÇÃO DE VETORES
    //================================
    uint_t *SA = (uint_t *)malloc((n+1) * sizeof(uint_t));
    int_t *LCP = (int_t *)malloc((n+1) * sizeof(int_t));
    int *ISA = (int *)malloc((n+1) * sizeof(int));
    int *PHI = (int *)malloc((n+1) * sizeof(int));
    int *PLCP = (int *)malloc((n+1) * sizeof(int));
    int *SUS = (int *)malloc((n) * sizeof(int));
    int *SUS1 = (int *)malloc((n) * sizeof(int));
    int *SUS2 = (int *)malloc((n) * sizeof(int));
    printf("Text = %s$\n\n", Text);
    //================================
    //CONSTRUÇÃO DO SA E LCP
    //================================
    sacak_lcp((unsigned char *)Text, (uint_t *)SA, LCP, n);
    //================================
    //INICIALIZAÇÃO E CONSTRUÇÃO 
    //================================
    initialize(SUS1, SUS, ISA, PHI, SA, n);
    buildPLCP(PLCP, PHI, Text, n, SUS2);
    //================================
    //SUS TRADICIONAL 
    //================================
    int opt=atoi(argv[2]);
    switch (opt)
    {
        case 0:
            SUS_T(SUS, n, LCP, SA);
        break;
        case 1:
            SUS_1(SUS1, PHI, n, PLCP);
        break;
        case 2:
            SUS_2(SUS2, n, PLCP, PHI);
        break;

    }
    int op;
    printf("compare SUS with SUST?\n 1-Yes 2- No: ");
    scanf("%d",&op);
    if(op==1)
    {
        SUS_T(SUS, n, LCP, SA);
        if(opt==2){
            if (equal(SUS,SUS2, n)) printf("SUS and SUST are equal :)\n");
        }
        else 
            if(equal(SUS,SUS1, n)) printf("SUS and SUST are equal :)\n");
    }
    printf("Print SUS?\n 1-Yes 2- No: ");
    scanf("%d",&op);
    if(op==1)
    {
        if(opt==2)
            print(SA, SUS2, Text, n);
        else if(opt==1)
           print(SA, SUS1, Text, n);
        else if(opt==0)
             print(SA, SUS, Text, n);
    }
    //================================
    //LIBERAÇÃO DOS VETORES
    //================================
    free(SA);
    free(LCP);
    free(SUS);
    free(SUS1);
    free(SUS2);
    free(ISA);
    free(PHI);
    free(PLCP);
    fclose(ent);
    free(Text);
    free(line);
    return 0;
}
