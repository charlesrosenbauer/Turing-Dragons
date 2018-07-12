#ifndef __SPACETABLE_HEADER__
#define __SPACETABLE_HEADER__


#include "stdint.h"










static const int TABLEDIM = 16;
typedef uint16_t TABLEELEM;
typedef struct{
  TABLEELEM elems [TABLEDIM][TABLEDIM];
}SPACETABLE_2P;

typedef struct{
  TABLEELEM elems [TABLEDIM][TABLEDIM][TABLEDIM];
}SPACETABLE_3P;










void generateTable2P (uint64_t(uint64_t, uint64_t));
void generateTable3P (uint64_t(uint64_t, uint64_t, uint64_t));
int getSubspace      (uint64_t);
uint64_t makeSubspace(uint64_t, int);



#endif
