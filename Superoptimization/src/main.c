#include "interpreter.h"
#include "stdio.h"
#include "stdint.h"










long rseed = 3156937611;

uint8_t rnum(){
  rseed = (rseed * 123571389)  + 1385179671;
  return (rseed / 256) % 256;
}










uint64_t rpar(){
  uint64_t x = 0;
  for(int i = 0; i < 8; i++){
    x |= rnum(); x <<= 8;
  }
  return x;
}










int main(){
  PROGRAM p;
  IOSPACE io;

  int randStart = 0;
  printf("Enter Random Seed: ");
  scanf("%d", &randStart);
  rseed += randStart;

  for(int j = 0; j < 32; j++)
    p.code[j] = rnum();
  p.length = rnum() % 16;
  p.length = (p.length > 6)? p.length : 6;

  for(int i = 0; i < IOSIZE; i++){
    io.inputs[i] = rpar();
  }

  runProgram(&p, &io, MODE8);

  printf("Program run.\n");

  int mi = -1, mn = 64;
  PROGRAM best;
  for(int i = 0; i < 65536; i++){

    // Random 16-op program
    PROGRAM pnew;
    for(int j = 0; j < 32; j++)
      pnew.code[j] = rnum();
    pnew.length = rnum() % 6;
    pnew.length = (pnew.length > 2)? pnew.length : 2;

    int n = cmpProgram(&pnew, &io, MODE8);
    if(n < mn){
      mn = n;
      mi = i;
      best = pnew;
    }
  }
  printProgram(&p);
  printf("\n\n");

  printProgram(&best);

  printf("\n\nScore: %i\n", 64 - mn);

  //printIOSpace(&io, MODE8);
}
