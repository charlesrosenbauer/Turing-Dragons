#ifndef __TURING_HEADER__
#define __TURING_HEADER__


#include "stdint.h"










typedef int64_t TERMCODE;


typedef struct{
  uint8_t* tape;
  uint64_t size;
}TAPE;


typedef struct{
  // If 0
  uint8_t code0;
  uint8_t goto0;

  // If 1
  uint8_t code1;
  uint8_t goto1;
}CARD;


typedef struct{
  CARD cards[255];  // 255 cards is the limit for now.
  uint8_t cardct;
  uint64_t index;
}MACHINE;










void randomMachine(MACHINE*, uint8_t);
void clearTape(TAPE*);
TERMCODE runMachine(MACHINE*, TAPE*, int);








#endif
