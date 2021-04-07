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
//#include "kseq.h"

#define lcp(i) ((i < n) ? (LCP[i]) : (0))
#define PHI(i) ((ISA[i]<n-1) ? (phi[i]) : (i))


bool iguais(int *v1, int *v2, int *v3, int tam);
void inicializacao (int *SUS1, int *SUS, int *ISA, int *phi, uint_t SA[], int n);
void construcaoPLCP(int *PLCP, int phi[], char Text[], int n, int *SUS2);
void SUS_tradicional(int *SUS, uint_t SA[], int n, int_t LCP[]);
void SUS_1(int *SUS, int phi[], int n, int PLCP[], int ISA[]);
void SUS_2(int *SUS2, int phi[], int n, int PLCP[]);
#endif