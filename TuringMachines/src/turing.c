#include "turing.h"
#include "funcs.h"
#include "stdlib.h"
#include "stdio.h"










void randomMachine_2S(MACHINE_2S* m, uint8_t cardct){
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
  t->tape = malloc(size);
}










void clearTape(TAPE* t){
  for(int i = 0; i < t->size; i++)
    t->tape[i] = 0;
}









TERMCODE runMachine_2S(MACHINE_2S* m, TAPE* t, int limit){

  TERMCODE ret;
  ret.termct = 0;
  ret.maxIx  = 0;
  ret.minIx  = (t->size*8)+1;

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

    if((m->index < 0) || (m->index >= (t->size*8))){
      ret.termct = -i;
      return ret;
    }

    ret.maxIx = (ret.maxIx < m->index)? m->index : ret.maxIx;
    ret.minIx = (ret.minIx > m->index)? m->index : ret.minIx;
  }
  return ret;
}










void randomMachine_3S(MACHINE_3S* m, uint8_t cardct){
  for(int i = 0; i < cardct; i++){
    m->cards[i].code0 = randByte() % 6;
    m->cards[i].goto0 = randByte() % cardct+1;
    m->cards[i].code1 = randByte() % 6;
    m->cards[i].goto1 = randByte() % cardct+1;
    m->cards[i].code2 = randByte() % 6;
    m->cards[i].goto2 = randByte() % cardct+1;
  }
  m->cardct = cardct;
  m->index  = 0;
}










TERMCODE runMachine_3S(MACHINE_3S* m, TAPE* t, int limit){

  TERMCODE ret;
  ret.termct = 0;
  ret.maxIx  = 0;
  ret.minIx  = (t->size*4)+1;

  int state = 0;
  for(int i = 0; i < limit; i++){
    int indexbyte = m->index / 4;
    int indexbit  = (m->index % 4) * 2;

    uint8_t* tapebyte  = &(t->tape[indexbyte]);
    int tapesym = (*tapebyte) >> indexbit;
    int mask    = 3 >> indexbit;
    int maskb   = 2 >> indexbit;

    if(tapesym == 0){
      switch(m->cards[state].code0){
        case 0: (*tapebyte) &= ~mask;                           m->index--; break; // Write 0, move Left
        case 1: (*tapebyte) |=  mask;                           m->index--; break; // Write 1, move Left
        case 2: (*tapebyte)  = ((*tapebyte) & (~mask)) | maskb; m->index--; break; // Write 2, move Left
        case 3: (*tapebyte) &= ~mask;                           m->index++; break; // Write 0, move Right
        case 4: (*tapebyte) |=  mask;                           m->index++; break; // Write 1, move Right
        case 5: (*tapebyte)  = ((*tapebyte) & (~mask)) | maskb; m->index++; break; // Write 2, move Right
      }
      state = m->cards[state].goto0;
    }else if(tapesym == 3){
      switch(m->cards[state].code1){
        case 0: (*tapebyte) &= ~mask;                           m->index--; break; // Write 0, move Left
        case 1: (*tapebyte) |=  mask;                           m->index--; break; // Write 1, move Left
        case 2: (*tapebyte)  = ((*tapebyte) & (~mask)) | maskb; m->index--; break; // Write 2, move Left
        case 3: (*tapebyte) &= ~mask;                           m->index++; break; // Write 0, move Right
        case 4: (*tapebyte) |=  mask;                           m->index++; break; // Write 1, move Right
        case 5: (*tapebyte)  = ((*tapebyte) & (~mask)) | maskb; m->index++; break; // Write 2, move Right
      }
      state = m->cards[state].goto1;
    }else{
      switch(m->cards[state].code2){
        case 0: (*tapebyte) &= ~mask;                           m->index--; break; // Write 0, move Left
        case 1: (*tapebyte) |=  mask;                           m->index--; break; // Write 1, move Left
        case 2: (*tapebyte)  = ((*tapebyte) & (~mask)) | maskb; m->index--; break; // Write 2, move Left
        case 3: (*tapebyte) &= ~mask;                           m->index++; break; // Write 0, move Right
        case 4: (*tapebyte) |=  mask;                           m->index++; break; // Write 1, move Right
        case 5: (*tapebyte)  = ((*tapebyte) & (~mask)) | maskb; m->index++; break; // Write 2, move Right
      }
      state = m->cards[state].goto2;
    }


    if(state == m->cardct){
      ret.termct = i;
      return ret;
    }

    if((m->index < 0) || (m->index >= (t->size*4))){
      ret.termct = -i;
      return ret;
    }

    ret.maxIx = (ret.maxIx < m->index)? m->index : ret.maxIx;
    ret.minIx = (ret.minIx > m->index)? m->index : ret.minIx;
  }
  return ret;
}
