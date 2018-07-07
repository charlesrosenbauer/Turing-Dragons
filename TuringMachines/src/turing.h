#ifndef __TURING_HEADER__
#define __TURING_HEADER__


#include "stdint.h"










typedef struct{
   int64_t termct;
  uint64_t maxIx;
  uint64_t minIx;
}TERMCODE;


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
}CARD_2S;


typedef struct{
  CARD_2S cards[255];  // 255 cards is the limit for now.
  uint8_t cardct;
  uint64_t index;
}MACHINE_2S;    // Turing Machine with 2 Symbols - Not actually Universal as far as I'm aware.










typedef struct{
  // If 0
  uint8_t code0;
  uint8_t goto0;

  // If 1
  uint8_t code1;
  uint8_t goto1;

  // If 2
  uint8_t code2;
  uint8_t goto2;
}CARD_3S;


typedef struct{
  CARD_3S cards[255];  // 255 cards is the limit for now.
  uint8_t cardct;
  uint64_t index;
}MACHINE_3S;










void makeTape (TAPE*, uint64_t);
void clearTape(TAPE*);
void  randomMachine_2S(MACHINE_2S*, uint8_t);
TERMCODE runMachine_2S(MACHINE_2S*, TAPE*, int);

void  randomMachine_3S(MACHINE_3S*, uint8_t);
TERMCODE runMachine_3S(MACHINE_3S*, TAPE*, int);








#endif
