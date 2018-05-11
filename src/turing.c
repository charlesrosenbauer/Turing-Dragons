#include "turing.h"
#include "funcs.h"
#include "stdlib.h"
#include "stdio.h"










void randomMachine(MACHINE* m, uint8_t cardct){
  for(int i = 0; i < cardct; i++){
    m->cards[i].code0 = randByte() % 4;
    m->cards[i].goto0 = randByte() % cardct+1;
    m->cards[i].code1 = randByte() % 4;
    m->cards[i].goto1 = randByte() % cardct+1;
  }
  m->cardct = cardct;
  m->index  = 0;
}










void makeTape(TAPE* t, uint64_t size){
  t->size = size;
  t->tape = malloc((size / 8)+1);
}










void clearTape(TAPE* t){
  for(int i = 0; i < (t->size/8); i++)
    t->tape[i] = 0;
}









TERMCODE runMachine(MACHINE* m, TAPE* t, int limit){

  TERMCODE ret;
  ret.termct = 0;
  ret.maxIx  = 0;
  ret.minIx  = t->size+1;

  int state = 0;
  for(int i = 0; i < limit; i++){
    int indexbyte = m->index / 8;
    int indexbit  = m->index % 8;

    uint8_t* tapebyte  = &(t->tape[indexbyte]);
    int tapebit = (*tapebyte) >> indexbit;
    int mask    = 1 >> indexbit;

    if(tapebit){
      switch(m->cards[state].code1){
        case 0: (*tapebyte) &= ~mask; m->index--; break; // Write 0, move Left
        case 1: (*tapebyte) |=  mask; m->index--; break; // Write 1, move Left
        case 2: (*tapebyte) &= ~mask; m->index++; break; // Write 0, move Right
        case 3: (*tapebyte) |=  mask; m->index++; break; // Write 1, move Right
      }
      state = m->cards[state].goto1;
    }else{
      switch(m->cards[state].code0){
        case 0: (*tapebyte) &= ~mask; m->index--; break; // Write 0, move Left
        case 1: (*tapebyte) |=  mask; m->index--; break; // Write 1, move Left
        case 2: (*tapebyte) &= ~mask; m->index++; break; // Write 0, move Right
        case 3: (*tapebyte) |=  mask; m->index++; break; // Write 1, move Right
      }
      state = m->cards[state].goto0;
    }

    if(state == m->cardct){
      ret.termct = i;
      return ret;
    }

    if((m->index < 0) || (m->index >= t->size)){
      ret.termct = -i;
      return ret;
    }

    ret.maxIx = (ret.maxIx < m->index)? m->index : ret.maxIx;
    ret.minIx = (ret.minIx > m->index)? m->index : ret.minIx;
  }
  return ret;
}
