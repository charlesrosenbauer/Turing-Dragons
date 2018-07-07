#include "interpreter.h"
#include "stdio.h"
#include "stdint.h"










long rseed = 3156937611;

uint8_t rnum(){
  rseed = (rseed * 123571389)  + 1385179671;
  return (rseed / 256) % 256;
}










int main(){
  PROGRAM p;
  IOSPACE io;

  int randStart = 0;
  printf("Enter Random Seed: ");
  scanf("%d", &randStart);
  rseed += randStart;

  for(int i = 0; i < 32; i++)
    p.code[i] = rnum();
  p.length = 8;

  printProgram(&p);

  for(int i = 0; i < 1024; i++){
    io.inputs[i] = i;
  }

  runProgram(&p, &io, MODE8);

  printIOSpace(&io, MODE8);
}
