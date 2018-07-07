#ifndef __INTERPRET_HEADER__
#define __INTERPRET_HEADER__


#include "stdint.h"










typedef uint8_t BYTECODE;










/*
  Programs are short belt machines. The belt is 4 entries long.
*/
typedef struct{
  BYTECODE code [32];
  int length;
}PROGRAM;










/*
  Programs can be 8 or 16-bit.
  inputs and outputs are just the first/last 4 values put into their belts.
*/
static const int IOSIZE = 4096;
typedef struct{
  uint64_t inputs [IOSIZE];
  uint64_t outputs[IOSIZE];
}IOSPACE;










typedef enum{
  MODE8,
  MODE16
}BITMODE;










void runProgram(PROGRAM*, IOSPACE*, BITMODE);
int  cmpProgram(PROGRAM*, IOSPACE*, BITMODE);
void printProgram(PROGRAM*);
void printIOSpace(IOSPACE*, BITMODE);


#endif
