#ifndef __SPACETABLE_HEADER__
#define __SPACETABLE_HEADER__


#include "stdint.h"










static const int TABLEDIM = 16;
typedef uint16_t TABLEELEM;

typedef struct{
  TABLEELEM elems [TABLEDIM];
}SPACETABLE_1P;

typedef struct{
  TABLEELEM elems [TABLEDIM][TABLEDIM];
}SPACETABLE_2P;

typedef struct{
  TABLEELEM elems [TABLEDIM][TABLEDIM][TABLEDIM];
}SPACETABLE_3P;










typedef struct{
  SPACETABLE_1P*   unops;
  SPACETABLE_2P*  binops;
  SPACETABLE_3P* trinops;

  int bs, ts;
}SPACETABLE_ISA;










SPACETABLE_1P*  generateTable1P (uint64_t(uint64_t));
SPACETABLE_2P*  generateTable2P (uint64_t(uint64_t, uint64_t));
SPACETABLE_3P*  generateTable3P (uint64_t(uint64_t, uint64_t, uint64_t));
SPACETABLE_ISA* generateTableISA();
int getSubspace      (uint64_t);
uint64_t makeSubspace(uint64_t, int);

void printTable_1P(SPACETABLE_1P*);
void printTable_2P(SPACETABLE_2P*);
void printTable_3P(SPACETABLE_3P*);


#endif
