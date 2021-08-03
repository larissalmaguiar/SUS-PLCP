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
    char *Text = (char *)malloc((n+1) * sizeof(char));
    char *line = malloc(n+1);
    while (fgets(line, n+1, ent) != NULL)
    {
        if (line[0] != '>')
        {
            int tam = strlen(line);
            line[tam-1] = '\0';
            strcat(Text, line);
       }
    }
    n = strlen(Text) + 1;
    //================================
    //DECLARAÇÃO DE VETORES
    //================================
    uint_t *SA = (uint_t *)malloc((n + 1) * sizeof(uint_t));
    int_t *LCP = NULL;
    int *ISA = NULL;
    int *PHI = NULL;
    int *PLCP = NULL;
    int *SUS = NULL;
    int *SUS1 = NULL;
    int *SUS2 = NULL;
    int *SUS3 = NULL;
    #if DEBUG
      printf("Text = %s$\n\n", Text);
    #endif
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

    //================================
    //COMPUTING SA
    //================================
    if(time) time_start(&t_start, &c_start);
    printf("## SACAK ##\n");
    sacak((unsigned char *)Text, (uint_t *)SA, n);
    if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start));
    //================================
    
    if(time) time_start(&t_start, &c_start);
    switch (alg){
      case 0: printf("## SUS_T ##\n");
          LCP = (int_t *)malloc((n + 1) * sizeof(int_t));
          sacak_lcp ((unsigned char *)Text, (uint_t *)SA, (int_t *)LCP, n);
          SUS = (int *)malloc((n) * sizeof(int));
          SUS_T(SUS, n, LCP, SA);
          break;
      case 1: printf("## SUS_1 ##\n");
          ISA = (int *)malloc((n + 1) * sizeof(int));
          PHI = (int *)malloc((n + 1) * sizeof(int));
          PLCP = (int *)malloc((n + 1) * sizeof(int));
          SUS1 = (int *)malloc((n) * sizeof(int));
          for(int i=0; i<n; i++) SUS1[i]=0;
          SUS_1(SUS1, PHI, n, PLCP, Text, ISA, SA);
          break;
      case 2: printf("## SUS_2 ##\n");
          ISA = (int *)malloc((n + 1) * sizeof(int));
          PHI = (int *)malloc((n + 1) * sizeof(int));
          PLCP = (int *)malloc((n + 1) * sizeof(int));
          SUS2 = (int *)malloc((n) * sizeof(int));
          SUS_2(SUS2, n, PLCP, PHI, ISA, Text, SA);
          break;
      case 3: printf("## PLCP_SUS ##\n");
          ISA = (int *)malloc((n + 1) * sizeof(int));
          PHI = (int *)malloc((n + 1) * sizeof(int));
          PLCP = (int *)malloc((n + 1) * sizeof(int));
          SUS3 = (int *)malloc((n+1) * sizeof(int));
          PLCPSUS(PLCP, PHI, Text, n, ISA, SA, SUS3);
          break;
      case 4: printf("## SUS_C ##\n");
          LCP = (int_t *)malloc((n + 1) * sizeof(int_t));
          sacak_lcp ((unsigned char *)Text, (uint_t *)SA, (int_t *)LCP, n);
          ISA = (int *)malloc((n + 1) * sizeof(int));
          SUS_C(ISA, SA, LCP, n, Text);
      default:
          break;
    }
    if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start));

    if (alg != 0 && alg!=4)
    {
        if (comp == 1)
        {
            LCP = (int_t *)malloc((n + 1) * sizeof(int_t));
            sacak_lcp ((unsigned char *)Text, (uint_t *)SA, (int_t *)LCP, n);
            SUS = (int *)malloc((n) * sizeof(int));
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
    free(SUS3);
    free(ISA);
    free(PHI);
    free(PLCP);
    fclose(ent);
    free(Text);
    free(line);
    return 0;
}
