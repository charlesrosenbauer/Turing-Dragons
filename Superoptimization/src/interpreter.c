#include "interpreter.h"
#include "stdio.h"
#include "string.h"










void runProgram(PROGRAM* p, IOSPACE* io, BITMODE b){
  for(int i = 0; i < 1024; i++){
    if(b == MODE8){
      uint8_t belt [40];
      int ip = 0;
      int bp = 3;

      belt[0] = (io->inputs[i]      ) & 0xFF;
      belt[1] = (io->inputs[i] >>  8) & 0xFF;
      belt[2] = (io->inputs[i] >> 16) & 0xFF;
      belt[3] = (io->inputs[i] >> 24) & 0xFF;

      while(ip < p->length){
        uint8_t ins =  p->code[ip];
        uint8_t op  =  ins >> 4;
        uint8_t a   =  ins &  3;
        uint8_t b   = (ins >> 2) & 3;
        uint8_t imm =  ins & 15;

        switch(op){
          case  0: belt[bp+1] = belt[bp-a] +  belt[bp-b]; break;
          case  1: belt[bp+1] = belt[bp-a] -  belt[bp-b]; break;
          case  2: belt[bp+1] = belt[bp-a] &  belt[bp-b]; break;
          case  3: belt[bp+1] = belt[bp-a] |  belt[bp-b]; break;
          case  4: belt[bp+1] = belt[bp-a] ^  belt[bp-b]; break;
          case  5: belt[bp+1] = belt[bp-a] >> belt[bp-b]; break;
          case  6: belt[bp+1] = belt[bp-a] << belt[bp-b]; break;
          case  7: belt[bp+1] = imm;                      break;
          case  8: belt[bp+1] = belt[bp-a] != belt[bp-b]; break;
          case  9: belt[bp+1] = belt[bp-b] & (belt[bp-a] - belt[bp-b]); break;
          case 10: belt[bp+1] = belt[bp-a] >  belt[bp-b]; break;
          case 11: belt[bp+1] = belt[bp-a] <  belt[bp-b]; break;
          case 12: belt[bp+1] = belt[bp-a] *  belt[bp-b]; break;
          case 13: belt[bp+1] = belt[bp-a] & ~belt[bp-b]; break;
          case 14: bp += imm; break;
          case 15: bp += (belt[bp-a])? belt[bp-b]: 0; break;
        }
        bp++;
        ip++;
      }

      if(bp > 40) bp = 40;

      io->outputs[i] = 0;
      io->outputs[i] |= ((uint64_t)belt[bp-3]) << 24;
      io->outputs[i] |= ((uint64_t)belt[bp-2]) << 16;
      io->outputs[i] |= ((uint64_t)belt[bp-1]) <<  8;
      io->outputs[i] |= ((uint64_t)belt[bp  ]);

    }else{
      uint16_t belt [40];
      int ip = 0;
      int bp = 3;

      belt[0] = (io->inputs[i]      ) & 0xFF;
      belt[1] = (io->inputs[i] >>  8) & 0xFF;
      belt[2] = (io->inputs[i] >> 16) & 0xFF;
      belt[3] = (io->inputs[i] >> 24) & 0xFF;

      while(ip < p->length){
        uint8_t ins =  p->code[ip];
        uint8_t op  =  ins >> 4;
        uint8_t a   =  ins &  3;
        uint8_t b   = (ins >> 2) & 3;
        uint8_t imm =  ins & 15;

        switch(op){
          case  0: belt[bp+1] = belt[bp-a] +  belt[bp-b]; break;
          case  1: belt[bp+1] = belt[bp-a] -  belt[bp-b]; break;
          case  2: belt[bp+1] = belt[bp-a] &  belt[bp-b]; break;
          case  3: belt[bp+1] = belt[bp-a] |  belt[bp-b]; break;
          case  4: belt[bp+1] = belt[bp-a] ^  belt[bp-b]; break;
          case  5: belt[bp+1] = belt[bp-a] >> belt[bp-b]; break;
          case  6: belt[bp+1] = belt[bp-a] << belt[bp-b]; break;
          case  7: belt[bp+1] = imm;                      break;
          case  8: belt[bp+1] = belt[bp-a] != belt[bp-b]; break;
          case  9: belt[bp+1] = belt[bp-b] & (belt[bp-a] - belt[bp-b]); break;
          case 10: belt[bp+1] = belt[bp-a] >  belt[bp-b]; break;
          case 11: belt[bp+1] = belt[bp-a] <  belt[bp-b]; break;
          case 12: belt[bp+1] = belt[bp-a] *  belt[bp-b]; break;
          case 13: belt[bp+1] = belt[bp-a] & ~belt[bp-b]; break;
          case 14: bp += imm; break;
          case 15: bp += (belt[bp-a])? belt[bp-b]: 0; break;
        }
        bp++;
        ip++;
      }

      if(bp > 40) bp = 40;

      io->outputs[i] = 0;
      io->outputs[i] |= ((uint64_t)belt[bp-3]) << 24;
      io->outputs[i] |= ((uint64_t)belt[bp-2]) << 16;
      io->outputs[i] |= ((uint64_t)belt[bp-1]) <<  8;
      io->outputs[i] |= ((uint64_t)belt[bp  ]);
    }
  }
}










void printProgram(PROGRAM* p){

  printf("PROGRAM:\n");
  for(int i = 0; i < p->length; i++){
    uint8_t ins =  p->code[i];
    uint8_t op  =  ins >> 4;
    uint8_t a   =  ins &  3;
    uint8_t b   = (ins >> 2) & 3;
    uint8_t imm =  ins & 15;

    switch(op){
      case  0: printf("  add  b%i b%i\n", a, b); break;
      case  1: printf("  sub  b%i b%i\n", a, b); break;
      case  2: printf("  and  b%i b%i\n", a, b); break;
      case  3: printf("  or   b%i b%i\n", a, b); break;
      case  4: printf("  xor  b%i b%i\n", a, b); break;
      case  5: printf("  shr  b%i b%i\n", a, b); break;
      case  6: printf("  shl  b%i b%i\n", a, b); break;
      case  7: printf("  cst  #%i    \n", imm ); break;
      case  8: printf("  neq  b%i b%i\n", a, b); break;
      case  9: printf("  mskc b%i b%i\n", a, b); break;
      case 10: printf("  gt   b%i b%i\n", a, b); break;
      case 11: printf("  ls   b%i b%i\n", a, b); break;
      case 12: printf("  mul  b%i b%i\n", a, b); break;
      case 13: printf("  andn b%i b%i\n", a, b); break;
      case 14: printf("  br   +%i    \n",  imm); break;
      case 15: printf("  j    b%i +%i\n", a, b); break;
    }
  }
}










void formatInt(char* c, int x){
  c[7] = '\0';
  if(x == 0){
    for(int i = 0; i < 6; i++)
      c[i] = ' ';
    c[6] = '0';
    return;
  }

  for(int i = 0; i < 7; i++){
    int digits = x % 10;
    if(x != 0)
      c[6-i] = '0' + digits;
    else
      c[6-i] = ' ';
    x /= 10;
  }
}










void printIOSpace(IOSPACE* io, BITMODE b){
  if(b == MODE8){
    for(int i = 0; i < 1024; i++){
      char a[8], b[8], c[8], d[8], is[8];
      formatInt(a, (io->outputs[i]      ) & 0xFF);
      formatInt(b, (io->outputs[i] >>  8) & 0xFF);
      formatInt(c, (io->outputs[i] >> 16) & 0xFF);
      formatInt(d, (io->outputs[i] >> 24) & 0xFF);
      formatInt(is,i);
      printf("|%s>%s,%s,%s,%s|", is, a, b, c, d);
      if(i % 6 == 5) printf("\n");
    }
  }else{
    for(int i = 0; i < 1024; i++){
      char a[8], b[8], c[8], d[8], is[8];
      formatInt(a, (io->outputs[i]      ) & 0xFFFF);
      formatInt(b, (io->outputs[i] >> 16) & 0xFFFF);
      formatInt(c, (io->outputs[i] >> 32) & 0xFFFF);
      formatInt(d, (io->outputs[i] >> 48) & 0xFFFF);
      formatInt(is,i);
      printf("|%s>%s,%s,%s,%s|", is, a, b, c, d);
      if(i % 6 == 5) printf("\n");
    }
  }
}
