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
void buildPLCP(int *PLCP, int *PHI, unsigned char *T, int n, int *ISA, uint_t *SA);
void SUS_T(int *SUS, int n, int_t *LCP, uint_t *SA);
void SUS_1(int *SUS, int *PHI, int n, int *PLCP, unsigned char *T,uint_t *SA);
void SUS_2(int *SUS2, int n, int *PLCP, int *PHI, unsigned char *T, uint_t *SA);
void isa(int *ISA, int n, uint_t *SA);
void phi (int *PHI, int n, int *ISA, uint_t *SA);
void print(uint_t *SA, int *SUS, unsigned char *T, int n);
void PLCPSUS(int *PLCP, int *PHI, unsigned char *T, int n, uint_t *SA, int *SUS);
void SUS_C(int *ISA, uint_t *SA, int_t *LCP, int n, unsigned char *T);
void sus_cr (int_t *LCP, int *ISA, int n, int k, unsigned char *T);
void lcp_plcp(int_t *LCP, int *PLCP, int *ISA, int n);
#endif
