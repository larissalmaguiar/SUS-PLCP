#define DEBUG 0
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
#include "external/sacak-lcp.h"
#include "lib/sus.h"
#include "external/malloc_count/malloc_count.h"  

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
    #if DEBUG
      printf("Text = %s$\n\n", Text);
    #endif
    //================================
    //CONSTRUÇÃO DO SA E LCP
    //================================
    sacak_lcp((unsigned char *)Text, (uint_t *)SA, LCP, n);
    //================================
    //INICIALIZAÇÃO E CONSTRUÇÃO
    //================================
    time_t t_start=0;
    clock_t c_start=0;
    //================================
    //ESCOLHA DE SUS
    //================================
    int c, alg = 0, comp = 0, pri = 0, time=0;
    while ((c = getopt(argc, argv, "A:kpct")) != -1)
    {
        switch (c)
        {
        case 'A':
            alg=(int)atoi(optarg);
            break;
        case 'p':
            pri = 1;
            break;
        case 'c':
            comp = 1;
            break;
        case 't':
            time=1;
            break;
        default:
            break;
        }
    }
    
    if(time) time_start(&t_start, &c_start);
    switch (alg){
      case 0: printf("## SUS_T ##\n");
          SUS_T(SUS, n, LCP, SA);
          break;
      case 1: printf("## SUS_1 ##\n");
          SUS_1(SUS1, PHI, n, PLCP, Text, ISA, SA);
          break;
      case 2: printf("## SUS_2 ##\n");
          SUS_2(SUS2, n, PLCP, PHI, ISA, Text, SA);
          break;
      case 3: printf("## PLCP_SUS ##\n");
          PLCPSUS(PLCP, PHI, Text, n, ISA, SA, SUS3);
          break;
      case 4: printf("## SUS_C ##\n");
          SUS_C(ISA, SA, LCP, n, Text);
      default:
          break;
    }
    if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start));

    if (alg != 0 && alg!=4)
    {
        if (comp == 1)
        {
            SUS_T(SUS, n, LCP, SA);
            switch (alg)
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
    if (pri == 1 && alg!=4)
    {
        switch (alg)
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
