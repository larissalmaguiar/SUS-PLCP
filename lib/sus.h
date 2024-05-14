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
//#include "../external/sacak-lcp.h"
#include "utils.h"

#define lcp(i) ((i < n) ? (LCP[i]) : (0))



bool equal(int_t *v1, int_t *v2, int_t tam);
void buildPLCP(int_t *PLCP, int_t *PHI, unsigned char *T, int_t n); //9n bytes
void SUS_T(unsigned char *T, int_t *SUS, int_t n, int_t *LCP, uint_t *SA);
//void SUS_11(int_t *SUS, int n, int *PLCP, int *PHI,unsigned char *T );
void SUS_1(int_t sa_last, int_t n, int_t *PLCP, int_t *PHI, unsigned char *T);
void SUS1_13(int_t *SUS, int_t n, int_t *PLCP, int_t *PHI, unsigned char *T);
void SUS_2(int_t sa_last, int_t n, int_t *PLCP, int_t *PHI, unsigned char *T);
void SUS2_13(int_t *SUS, int_t n, int_t *PLCP, int_t *PHI, unsigned char *T);
void isa(int_t *ISA, int_t n, uint_t *SA);
void phi (int_t *PHI, int_t n, int_t *ISA, uint_t *SA);
void buildPHI(int_t *PHI, int_t n, uint_t *SA);
void print(uint_t *SA, int_t *SUS, unsigned char *T, int_t n);
void print_sus(uint_t *SA, int_t *SUS, unsigned char *T, int_t n);
void PLCPSUS(int_t *PLCP, int_t *PHI, unsigned char *T, int_t n, uint_t *SA, int_t *SUS);
void SUS_C(int_t *ISA, uint_t *SA, int_t *LCP, int_t n, unsigned char *T);
void sus_cr (int_t *LCP, int_t *ISA, int_t n, int_t k, unsigned char *T);
void lcp_plcp(int_t *LCP, int_t *PLCP, uint_t *SA, int_t n);
#endif


