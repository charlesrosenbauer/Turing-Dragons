#include "spacetable.h"
#include "stdlib.h"
#include "util.h"










// Later, use preprocessing to switch between this and a few alt versions.
// Also, we need multiple different subspace algos.
int getSubspace(uint64_t x){
  uint64_t m0 = 0xFFFFFFFF00000000;
  uint64_t m1 = 0x00000000FFFF0000;
  uint64_t m2 = 0x000000000000FFF0;
  uint64_t m3 = 0x000000000000000F;
  int v0 = ((x & m0) != 0) << 3;
  int v1 = ((x & m1) != 0) << 2;
  int v2 = ((x & m2) != 0) << 1;
  int v3 = ((x & m3) != 0);
  return v0 | v1 | v2 | v3;
}










uint64_t makeSubspace(uint64_t rval, int space){
  uint64_t m0 = 0xFFFFFFFF00000000;
  uint64_t m1 = 0x00000000FFFF0000;
  uint64_t m2 = 0x000000000000FFF0;
  uint64_t m3 = 0x000000000000000F;
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

    for(int j = 0; j < 128; j++){
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

      for(int k = 0; k < 128; k++){
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

        for(int l = 0; l < 128; l++){
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









/*
SPACETABLE_ISA* generateTableISA(){

}*/
