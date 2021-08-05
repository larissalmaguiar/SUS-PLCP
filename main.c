#define DEBUG 0
#define MAX 10000 //longest FASTA line

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

int main(int argc, char *argv[]){

  time_t t_start=0;
  clock_t c_start=0;

  extern char *optarg;
  extern int optind, opterr, optopt;
  char *c_file=NULL;

  int c, alg = 0, comp = 0, pri = 0, time=0;
  while ((c = getopt(argc, argv, "A:kpct")) != -1){
    switch (c){
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
  free(optarg);

  if(optind+1==argc) {
    c_file=argv[optind++];
  }

  //TODO: colocar em uma função

  //================================
  //PREPROCESSING FASTA
  //================================

  FILE *ent;
  ent = fopen(c_file, "r");
  fseek(ent, 0, SEEK_END);
  size_t n = ftell(ent);
  rewind(ent);

  //TODO: verificar se o malloc não é diferente de NULL
  char *Text = (char *)malloc((n+1) * sizeof(char));

  //  char *line = malloc(n+1); ?? aloca 2 vezes o espaço ??
  char *line = malloc(MAX);

  if(time) time_start(&t_start, &c_start);
  printf("## PREPROCESSING ##\n");
  while (fgets(line, MAX, ent) != NULL){
    if (line[0] != '>'){
      size_t tam = strlen(line);
      line[tam-1] = '\0';
      strcat(Text, line);
    }
  }
  //TODO: fechar depois de usar o arquivo, ok?
  free(line);
  fclose(ent);
  if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start));

  n = strlen(Text) + 1;

  //================================
  //DECLARAÇÃO DE VETORES
  //================================
  uint_t *SA = NULL;
  int_t *LCP = NULL;
  int *ISA = NULL;
  int *PHI = NULL;
  int *PLCP = NULL;
  int *SUS = NULL;
#if DEBUG
  printf("Text = %s$\n\n", Text);
#endif

  //================================
  //COMPUTING SA
  //================================
  SA = (uint_t *)malloc((n + 1) * sizeof(uint_t));
  SUS = (int *)malloc((n+1) * sizeof(int));

  if(alg == 0 || alg == 4){

    LCP = (int_t *)malloc((n + 1) * sizeof(int_t));
    if(time) time_start(&t_start, &c_start);
    printf("## SACAK_lcp ##\n");
    sacak_lcp ((unsigned char *)Text, (uint_t *)SA, (int_t *)LCP, n);
    if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start));

    if(alg == 4){
      ISA = (int *)malloc((n + 1) * sizeof(int));
    }
  }
  if(alg == 1 || alg == 2 || alg == 3){

    if(time) time_start(&t_start, &c_start);
    printf("## SACAK ##\n");
    sacak((unsigned char *)Text, (uint_t *)SA, n);
    if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start));

    ISA = (int *)malloc((n + 1) * sizeof(int));
    PHI = (int *)malloc((n + 1) * sizeof(int));
    PLCP = (int *)malloc((n + 1) * sizeof(int));
  }

  //================================

  if(time) time_start(&t_start, &c_start);
  switch (alg){
    case 0: printf("## SUS_T ##\n");
            SUS_T(SUS, n, LCP, SA);
            break;
    case 1: printf("## SUS_1 ##\n");
            for(int i=0; i<n; i++) SUS[i]=0;
            SUS_1(SUS, PHI, n, PLCP, Text, ISA, SA);
            break;
    case 2: printf("## SUS_2 ##\n");
            SUS_2(SUS, n, PLCP, PHI, ISA, Text, SA);
            break;
    case 3: printf("## PLCP_SUS ##\n");
            PLCPSUS(PLCP, PHI, Text, n, ISA, SA, SUS);
            break;
    case 4: printf("## SUS_C ##\n");
            SUS_C(ISA, SA, LCP, n, Text);
    default:
            break;
  }
  if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start));

  if (pri == 1 && alg!=4){
    switch (alg){
      case 0:
        print(SA, SUS, Text, n);
        break;
      case 1:
        print(SA, SUS, Text, n);
        break;
      case 2:
        print(SA, SUS, Text, n);
        break;
      case 3:
        print(SA, SUS, Text, n);
        break;
      default:
        break;
    }
  }

  if(alg == 1 || alg == 2 || alg == 3){
    free(ISA);
    free(PHI);
    free(PLCP);
  }

  //VALIDATION
  if (alg != 0 && alg!=4){
    if (comp == 1){

      if(LCP==NULL){ //TODO: calcular apenas o LCP
        LCP = (int_t *)malloc((n + 1) * sizeof(int_t));
        sacak_lcp ((unsigned char *)Text, (uint_t *)SA, (int_t *)LCP, n);
      }

      int *SUS_aux = (int *)malloc((n) * sizeof(int));
      SUS_T(SUS_aux, n, LCP, SA);

      switch (alg){
        case 1:
          if (equal(SUS, SUS_aux, n))
            printf("SUS and SUST are equal :)\n");
          break;
        case 2:
          if (equal(SUS, SUS_aux, n))
            printf("SUS and SUST are equal :)\n");
          break;
        case 3:
          if (equal(SUS, SUS_aux, n))
            printf("SUS and SUST are equal :)\n");
          break;
        default:
          break;
      }
    }
  }

  //TODO: verificar
  if(alg == 0 || alg == 4 || comp == 1){
    free(LCP);
  }
  free(SA);
  free(SUS);
  free(Text);

  return 0;
}
