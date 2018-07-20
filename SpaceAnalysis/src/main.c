#include "spacetable.h"
#include "stdio.h"










int main(){
  SPACETABLE_ISA* isa = generateTableISA();

  printf("Generated\n");

  for(int i = 0; i < isa->bs; i++){
    printf("binop %i\n", i);
    printTable_2P(&isa->binops[i]);
  }

  printf("\n\n");

  for(int i = 0; i < isa->us; i++){
    printf("unop %i\n", i);
    printTable_1P(&isa->unops[i]);
  }
}
