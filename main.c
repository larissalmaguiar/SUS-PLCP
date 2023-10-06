/*
 * plcp-sus
 *
 * Authors: Larissa M. Aguiar and Felipe A. Louza
 * contact: louza@ufu.br
 * 16/08/2021
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "external/sacak-lcp.h"
#include "lib/sus.h"
#include "lib/file.h"
#include "lib/utils.h"
#include "external/malloc_count/malloc_count.h"  

#define lcp(i) ((i < n) ? (LCP[i]) : (0))


/*************************************/

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

  if(time) time_start(&t_start, &c_start);
  printf("## PREPROCESSING ##\n");

  int k=0;
  size_t n=0;
  unsigned char **R = (unsigned char**) file_load_multiple(c_file, &k, &n);

  //concatenate all string
  unsigned char *T = cat_char(R, k, &n);

  #if DEBUG
    printf("R:\n");
    for(int i=0; i<k && i<10; i++)
      printf("%" PRIdN ") %s (%zu)\n", i, R[i], strlen((char*)R[i]));
    printf("####\n");
    for(size_t i=0; i<n; i++) printf("[%d]", T[i]);
    printf("\n");
  #endif

  printf("k = %d\n", k);
  printf("N = %zu bytes\n", n);
  printf("sizeof(int) = %zu bytes\n", sizeof(int_t)); 

  //free memory
  for(int i=0; i<k; i++)
    free(R[i]);
  free(R);

  if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start));


  //================================
  //DECLARAÇÃO DE VETORES
  //================================
  uint_t *SA = NULL;
  int_t *LCP = NULL;
  int_t *LCP1 = NULL;
  //int *ISA = NULL;
  int *PHI = NULL;
  int *PLCP = NULL;
  int *SUS = NULL;
#if DEBUG
  printf("T = %s$\n\n", T);
#endif

  //================================
  //COMPUTING SA
  //================================
  SA = (uint_t *)malloc((n + 1) * sizeof(uint_t));
  SUS = (int *)malloc((n+1) * sizeof(int));
 

  if(alg == 0 || alg == 5){
    LCP = (int_t *)malloc((n + 1) * sizeof(int_t));
    if(time) time_start(&t_start, &c_start);
    printf("## SACAK_lcp ##\n");
    sacak_lcp ((unsigned char *)T, (uint_t *)SA, (int_t *)LCP, n);
    if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start));

    /**
    if(alg == 5){
      ISA = (int *)malloc((n + 1) * sizeof(int));
    }
    **/
  }
  if(alg == 1 || alg == 2){
    if(time) time_start(&t_start, &c_start);
    printf("## SACAK ##\n");
    sacak((unsigned char *)T, (uint_t *)SA, n);
    if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start));

    PHI = (int *)malloc((n + 1) * sizeof(int));

    if(time) time_start(&t_start, &c_start);
    printf("## PHI ##\n");
    buildPHI(PHI, n, SA);//8n bytes 
    if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start)); 

    //PLCP = (int *)malloc((n + 1) * sizeof(int));
    PLCP = (int*) SA;

    if(time) time_start(&t_start, &c_start);
    printf("## PLCP ##\n");
    buildPLCP(PLCP, PHI, T, n);//
    if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start)); 
  }
  if(alg == 3){
    if(time) time_start(&t_start, &c_start);
    printf("## SACAK ##\n");
    sacak((unsigned char *)T, (uint_t *)SA, n);
    if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start));

    PHI = (int *)malloc((n + 1) * sizeof(int));
    PLCP = (int *)malloc((n + 1) * sizeof(int));
  }
  if(alg==4)
  {
    if(time) time_start(&t_start, &c_start);
    printf("## SACAK ##\n");
    sacak((unsigned char *)T, (uint_t *)SA, n);
    if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start));
    PHI = (int *)malloc((n + 1) * sizeof(int));

    if(time) time_start(&t_start, &c_start);
    printf("## PHI ##\n");
    buildPHI(PHI, n, SA);// vetor SUS é usado no lugar de ISA
    if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start)); 

    PLCP= (int *)malloc((n + 1) * sizeof(int));

    if(time) time_start(&t_start, &c_start);
    printf("## LCP ##\n");
    buildPLCP(PLCP, PHI, T, n);// vetor SUS é usado no lugar de ISA

    LCP1 = (int_t *)malloc((n + 1) * sizeof(int_t));
    lcp_plcp(LCP1, PLCP, SUS, n); 
    if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start));

    free (PLCP);
  }
  
  //================================

  if(time) time_start(&t_start, &c_start);
  switch (alg){
    case 0: printf("## SUS_T ##\n");
            SUS_T(SUS, n, LCP, SA);
            break;
    case 1: printf("## SUS_1 ##\n");
            for(int i=0; i<n; i++) SUS[i]=0;
            SUS_1(SUS, n, PLCP, PHI);//13n bytes
            break;
    case 2: printf("## SUS_2 ##\n");
            SUS_2(SUS, n, PLCP, PHI);//13n bytes
            break;
    case 3: printf("## PLCP_SUS ##\n");
            PLCPSUS(PLCP, PHI, T, n, SA, SUS);
            break;
    case 4: printf("## SUS_T2 ##\n");
            SUS_T(SUS, n, LCP1, SA);
            break;
    /**
    case 5: printf("## SUS_C ##\n");
            SUS_C(ISA, SA, LCP, n, T);
            break;
    **/
    default:
            break;
  }
  if(time) fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start));

  if (pri == 1 && alg!=5){ 
        print(SA, SUS, T, n);
  }

  if(alg == 1 || alg == 2 || alg == 3){
    free(PHI);
    if(alg==3) free(PLCP);
  }
  if(alg==4) free(LCP1);

  //VALIDATION

  if (alg != 0 && alg!=5)
  {
    if (comp == 1){
      if(LCP==NULL){ //TODO: calcular apenas o LCP
        LCP = (int_t *)malloc((n + 1) * sizeof(int_t));
        sacak_lcp ((unsigned char *)T, (uint_t *)SA, (int_t *)LCP, n);
      }
      int *SUS_aux = (int *)malloc((n+1) * sizeof(int));
      SUS_T(SUS_aux, n, LCP, SA);
        if (equal(SUS, SUS_aux, n))
          printf("SUS and SUST are equal :)\n");  
      }
  }
  //TODO: verificar

  if(alg == 0 || alg == 5|| comp == 1){
    free(LCP);
  }
  free(SA);
  free(SUS);
  free(T);

  return 0;
}

