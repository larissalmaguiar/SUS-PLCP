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
#include "../external/sacak-lcp.h"


#define lcp(i) ((i < n) ? (LCP[i]) : (0))



bool equal(int *v1, int *v2, int tam);
void time_start(time_t *t_time, clock_t *c_clock);
double time_stop(time_t t_time, clock_t c_clock);
void buildPLCP(int *PLCP, int *PHI, char *Text, int n, int *ISA, uint_t *SA);
void SUS_T(int *SUS, int n, int_t *LCP, uint_t *SA);
void SUS_1(int *SUS, int *PHI, int n, int *PLCP, char *Text, int *ISA, uint_t *SA);
void SUS_2(int *SUS2, int n, int *PLCP, int *PHI, int *ISA, char *Text, uint_t *SA);
void isa(int *ISA, int n, uint_t *SA);
void phi (int *PHI, int n, int *ISA, uint_t *SA);
void print(uint_t *SA, int *SUS, char *Text, int n);
void PLCPSUS(int *PLCP, int *PHI, char *Text, int n, int *ISA, uint_t *SA, int *SUS);
void SUS_C(int *ISA, uint_t *SA, int_t *LCP, int n, char *Text);
void sus_cr (int_t *LCP, int *ISA, int n, int k, char *Text);
#endif
