#ifndef __FUNCS_HEADER__
#define __FUNCS_HEADER__

#include "stdint.h"










static uint32_t randState;
static uint16_t randMul;
static uint16_t randAcc;

void seedrand(uint64_t);
uint8_t randByte();




#endif
