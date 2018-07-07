#include "funcs.h"










void seedrand(uint64_t seed){
  randMul  = ((seed >>  0) & 0xFFFF    ) | 1;
  randAcc  = ((seed >> 16) & 0xFFFF    ) | 1;
  randState= ((seed >> 32) & 0xFFFFFFFF) | 1;
}










inline uint8_t randByte(){
  randState = (randState * randMul) + randAcc;
  return (randState >> 16) & 0xFF;
}
