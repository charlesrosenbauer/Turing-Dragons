#include "spacetable.h"
#include "stdlib.h"
#include "util.h"
#include "stdio.h"










// Later, use preprocessing to switch between this and a few alt versions.
// Also, we need multiple different subspace algos.
int getSubspace(uint64_t x){
  uint64_t m0 = 0x8000000000000000;
  uint64_t m1 = 0x7FFFFFFFFFFFFFF0;
  uint64_t m2 = 0x000000000000000E;
  uint64_t m3 = 0x0000000000000001;
  int v0 = ((x & m0) != 0) << 3;
  int v1 = ((x & m1) != 0) << 2;
  int v2 = ((x & m2) != 0) << 1;
  int v3 = ((x & m3) != 0);
  return v0 | v1 | v2 | v3;
}










uint64_t makeSubspace(uint64_t rval, int space){
  uint64_t m0 = 0x8000000000000000;
  uint64_t m1 = 0x7FFFFFFFFFFFFFF0;
  uint64_t m2 = 0x000000000000000E;
  uint64_t m3 = 0x0000000000000001;
  uint64_t mk = 0;
  mk |= (space & 0x8)? m0 : 0;
  mk |= (space & 0x4)? m1 : 0;
  mk |= (space & 0x2)? m2 : 0;
  mk |= (space & 0x1)? m3 : 0;
  return rval & mk;
}










SPACETABLE_1P* generateTable1P(uint64_t(*f)(uint64_t)){
  SPACETABLE_1P* rettable = malloc(sizeof(SPACETABLE_1P));

  for(int i = 0; i < TABLEDIM; i++){

    rettable->elems[i] = 0;

    for(int j = 0; j < 256; j++){
      uint64_t a = makeSubspace(rnum8(), i);

      uint64_t q = f(a);

      rettable->elems[i] |= (1 << getSubspace(q));
    }
  }

  return rettable;
}










SPACETABLE_2P* generateTable2P(uint64_t(*f)(uint64_t, uint64_t)){
  SPACETABLE_2P* rettable = malloc(sizeof(SPACETABLE_2P));

  for(int i = 0; i < TABLEDIM; i++){
    for(int j = 0; j < TABLEDIM; j++){

      rettable->elems[i][j] = 0;

      for(int k = 0; k < 256; k++){
        uint64_t a = makeSubspace(rnum8(), i);
        uint64_t b = makeSubspace(rnum8(), j);

        uint64_t q = f(a, b);

        rettable->elems[i][j] |= (1 << getSubspace(q));
      }
    }
  }

  return rettable;
}










SPACETABLE_3P* generateTable3P(uint64_t(*f)(uint64_t, uint64_t, uint64_t)){
  SPACETABLE_3P* rettable = malloc(sizeof(SPACETABLE_3P));

  for(int i = 0; i < TABLEDIM; i++){
    for(int j = 0; j < TABLEDIM; j++){
      for(int k = 0; k < TABLEDIM; k++){

        rettable->elems[i][j][k] = 0;

        for(int l = 0; l < 256; l++){
          uint64_t a = makeSubspace(rnum8(), i);
          uint64_t b = makeSubspace(rnum8(), j);
          uint64_t c = makeSubspace(rnum8(), k);

          uint64_t q = f(a, b, c);

          rettable->elems[i][j][k] |= (1 << getSubspace(q));
        }
      }
    }
  }

  return rettable;
}










uint64_t addu64(uint64_t a, uint64_t b){
  return a + b;
}

uint64_t subu64(uint64_t a, uint64_t b){
  return a - b;
}

uint64_t mulu64(uint64_t a, uint64_t b){
  return a * b;
}

uint64_t divu64(uint64_t a, uint64_t b){
  return (b != 0)? a / b : 0;
}

uint64_t modu64(uint64_t a, uint64_t b){
  return (b != 0)? a % b : 0;
}

uint64_t xoru64(uint64_t a, uint64_t b){
  return a ^ b;
}

uint64_t andu64(uint64_t a, uint64_t b){
  return a & b;
}

uint64_t oru64(uint64_t a, uint64_t b){
  return a | b;
}

uint64_t shlu64(uint64_t a, uint64_t b){
  return a << b;
}

uint64_t shru64(uint64_t a, uint64_t b){
  return a >> b;
}

uint64_t lsu64(uint64_t a, uint64_t b){
  return a < b;
}

uint64_t gtu64(uint64_t a, uint64_t b){
  return a > b;
}

uint64_t neu64(uint64_t a, uint64_t b){
  return a != b;
}

uint64_t andnzu64(uint64_t a, uint64_t b){
  return (a & b) != 0;
}

uint64_t msiu64(uint64_t a, uint64_t b){
  return a & (b - a);
}

uint64_t andnu64(uint64_t a, uint64_t b){
  return a & ~b;
}

int64_t addi64(int64_t a, int64_t b){
  return a + b;
}

int64_t subi64(int64_t a, int64_t b){
  return a - b;
}

int64_t muli64(int64_t a, int64_t b){
  return a * b;
}

int64_t divi64(int64_t a, int64_t b){
  return (b != 0)? a / b : 0;
}

int64_t modi64(int64_t a, int64_t b){
  return (b != 0)? a % b : 0;
}

int64_t lsi64(int64_t a, int64_t b){
  return a < b;
}

int64_t gti64(int64_t a, int64_t b){
  return a > b;
}










uint64_t incu64(uint64_t a){
  return a++;
}

uint64_t decu64(uint64_t a){
  return a--;
}

uint64_t notu64(uint64_t a){
  return ~a;
}

uint64_t nzu64(uint64_t a){
  return a != 0;
}








SPACETABLE_ISA* generateTableISA(){
  SPACETABLE_ISA* ret = malloc(sizeof(SPACETABLE_ISA));
  ret->unops  = malloc(sizeof(SPACETABLE_1P) *  4);
  ret->binops = malloc(sizeof(SPACETABLE_2P) * 23);
  ret->trinops= malloc(sizeof(SPACETABLE_3P) *  1);

  ret->us = 4;
  ret->bs = 23;
  ret->ts = 0;

  ret->binops[ 0] = *generateTable2P(addu64);
  ret->binops[ 1] = *generateTable2P(subu64);
  ret->binops[ 2] = *generateTable2P(mulu64);
  ret->binops[ 3] = *generateTable2P(divu64);
  ret->binops[ 4] = *generateTable2P(modu64);
  ret->binops[ 5] = *generateTable2P(xoru64);
  ret->binops[ 6] = *generateTable2P(oru64 );
  ret->binops[ 7] = *generateTable2P(andu64);
  ret->binops[ 8] = *generateTable2P(shlu64);
  ret->binops[ 9] = *generateTable2P(shru64);
  ret->binops[10] = *generateTable2P(lsu64);
  ret->binops[11] = *generateTable2P(gtu64);
  ret->binops[12] = *generateTable2P(neu64);
  ret->binops[13] = *generateTable2P(andnzu64);
  ret->binops[14] = *generateTable2P(msiu64);
  ret->binops[15] = *generateTable2P(andnu64);
  ret->binops[16] = *generateTable2P(addi64);
  ret->binops[17] = *generateTable2P(subi64);
  ret->binops[18] = *generateTable2P(muli64);
  ret->binops[19] = *generateTable2P(divi64);
  ret->binops[20] = *generateTable2P(modi64);
  ret->binops[21] = *generateTable2P(lsi64);
  ret->binops[22] = *generateTable2P(gti64);

  ret->  unops[0] = *generateTable1P(incu64);
  ret->  unops[1] = *generateTable1P(decu64);
  ret->  unops[2] = *generateTable1P(notu64);
  ret->  unops[3] = *generateTable1P(nzu64);

  return ret;
}











void printTable_1P(SPACETABLE_1P* table){
  for(int i = 0; i < TABLEDIM; i++){
    char numtext[64];
    for(int j = 0; j < sizeof(TABLEELEM) * 8; j++)
      numtext[j] = ((1 << j) & table->elems[i])? '#' : '_';
    numtext[sizeof(TABLEELEM) * 8] = '\0';

    printf("%s\n", numtext);
  }
}










void printTable_2P(SPACETABLE_2P* table){
  for(int i = 0; i < TABLEDIM; i++){
    for(int j = 0; j < TABLEDIM; j++){
      char numtext[64];
      for(int k = 0; k < sizeof(TABLEELEM) * 8; k++)
        numtext[k] = ((1 << k) & table->elems[i][j])? '#' : '_';
      numtext[sizeof(TABLEELEM) * 8] = '\0';

      printf("%s ", numtext);
    }
    printf("\n");
  }
}










void printTable_3P(SPACETABLE_3P* table){
  for(int i = 0; i < TABLEDIM; i++){
    for(int j = 0; j < TABLEDIM; j++){
      for(int k = 0; k < TABLEDIM; k++){
        char numtext[64];
        for(int l = 0; l < sizeof(TABLEELEM) * 8; l++)
          numtext[l] = ((1 << l) & table->elems[i][j][k])? '#' : '_';
        numtext[sizeof(TABLEELEM) * 8] = '\0';

        printf("%s ", numtext);
      }
      printf("\n");
    }
    printf("\n");
  }
}
