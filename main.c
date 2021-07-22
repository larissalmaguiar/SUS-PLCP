
//================================
//BIBLIOTECAS
//================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
//================================
//TADS
//================================
#include "sacak-lcp.h"
#include "sus.h"

#define lcp(i) ((i < n) ? (LCP[i]) : (0))

int main(int argc, char *argv[])
{
    //================================
    //LEITURA DO ARQUIVO
    //================================
    FILE *ent;
    ent = fopen(argv[1], "r");
    fseek(ent, 0, SEEK_END);
    int n = ftell(ent);
    rewind(ent);
    //================================
    //TRATAMENTO DE ARQUIVO FASTA
    //================================
    char *Text = (char *)malloc((n) * sizeof(char));
    char *line = malloc(n);
    while (fgets(line, n, ent) != NULL)
    {
        if (line[0] != '>')
        {
            int tam = strlen(line);
            line[tam - 1] = '\0';
            strcat(Text, line);
       }
    }
    n = strlen(Text) + 1;
    //================================
    //DECLARAÇÃO DE VETORES
    //================================
    uint_t *SA = (uint_t *)malloc((n + 1) * sizeof(uint_t));
    int_t *LCP = (int_t *)malloc((n + 1) * sizeof(int_t));
    int *ISA = (int *)malloc((n + 1) * sizeof(int));
    int *PHI = (int *)malloc((n + 1) * sizeof(int));
    int *PLCP = (int *)malloc((n + 1) * sizeof(int));
    int *SUS = (int *)malloc((n) * sizeof(int));
    int *SUS1 = (int *)malloc((n) * sizeof(int));
    int *SUS2 = (int *)malloc((n) * sizeof(int));
    int *SUS3 = (int *)malloc((n) * sizeof(int));
    printf("Text = %s$\n\n", Text);
    //================================
    //CONSTRUÇÃO DO SA E LCP
    //================================
    sacak_lcp((unsigned char *)Text, (uint_t *)SA, LCP, n);
    //================================
    //INICIALIZAÇÃO E CONSTRUÇÃO
    //================================
        time_t t_start=0;
        clock_t c_start=0;
        double time=0.0;
    //================================
    //ESCOLHA DE SUS
    //================================
    int c, type = 0, comp = 0, pri = 0, t=0;
    while ((c = getopt(argc, argv, "0123kpct")) != -1)
    {
        switch (c)
        {
        case '0':
            type=0;
            break;
         case '1':
            type=1;
            break;
         case '2':
            type=2;
            break;
         case '3':
            type=3;
            break;
        case'k':
            type=4;
            break;
        case 'p':
            pri = 1;
            break;
        case 'c':
            comp = 1;
            break;
        case 't':
            t=1;
            break;
        default:
            break;
        }
    }
    switch (type)
    {
    case 0:
        time_start(&t_start, &c_start);
        SUS_T(SUS, n, LCP, SA);
        time = time_stop(t_start, c_start);
        break;
    case 1:
        time_start(&t_start, &c_start);
        SUS_1(SUS1, PHI, n, PLCP, Text, ISA, SA);
        time =time_stop(t_start, c_start);
        break;
    case 2:
        time_start(&t_start, &c_start);
        SUS_2(SUS2, n, PLCP, PHI, ISA, Text, SA);
        time = time_stop(t_start, c_start);
        break;
    case 3:
        time_start(&t_start, &c_start);
        PLCPSUS(PLCP, PHI, Text, n, ISA, SA, SUS3);
        time = time_stop(t_start, c_start);
        break;
    case 4:
        SUS_C(ISA, SA, LCP, n, Text);
    default:
        break;
    }
    if (type != 0 && type!=4)
    {
        if (comp == 1)
        {
            SUS_T(SUS, n, LCP, SA);
            switch (type)
            {
            case 1:
                if (equal(SUS, SUS1, n))
                    printf("SUS and SUST are equal :)\n");
                break;
            case 2:
                if (equal(SUS, SUS2, n))
                    printf("SUS and SUST are equal :)\n");
                break;
            case 3:
                if (equal(SUS, SUS3, n))
                    printf("SUS and SUST are equal :)\n");
                break;
            default:
                break;
            }
        }
    }
    if (pri == 1 && type!=4)
    {
        switch (type)
        {
        case 0:
            print(SA, SUS, Text, n);
            break;
        case 1:
            print(SA, SUS1, Text, n);
            break;
        case 2:
            print(SA, SUS2, Text, n);
            break;
        case 3:
            print(SA, SUS3, Text, n);
            break;
        default:
            break;
        }
    }
    if(t==1 && type!=4)
        printf("TIME: %.15lf\n", time);
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
