#ifndef SUS_K_H
#define SUS_K_H
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


#define lcp(i) ((i < n) ? (LCP[i]) : (0))



bool equal(int *v1, int *v2, int tam);
void initialize(int *SUS, int *SUS1, int *ISA, int *phi, uint_t SA[], int n);
void buildPLCP(int *PLCP, int *phi, char *Text, int n);
void SUS_T(int *SUS, int n, int_t *LCP, uint_t *SA);
void SUS_1(int *SUS, int *PHI, int n, int *PLCP);
void SUS_2(int *SUS2, int n, int *PLCP, int *phi);
void print(uint_t *SA, int *SUS, char *Text, int n);
#endif
