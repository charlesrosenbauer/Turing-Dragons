#include "interpreter.h"
#include "stdio.h"
#include "string.h"
#include "util.h"










void runProgram(PROGRAM* p, IOSPACE* io, BITMODE b){
  for(int i = 0; i < IOSIZE; i++){
    if(b == MODE8){
      uint8_t belt [64];
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
          case 14: ip += imm; break;
          case 15: ip += (belt[bp-a])? belt[bp-b]: 0; break;
        }
        bp++;
        ip++;
      }

      if(bp >= 64) bp = 63;

      io->outputs[i] = 0;
      io->outputs[i] |= ((uint64_t)belt[bp-3]) << 24;
      io->outputs[i] |= ((uint64_t)belt[bp-2]) << 16;
      io->outputs[i] |= ((uint64_t)belt[bp-1]) <<  8;
      io->outputs[i] |= ((uint64_t)belt[bp  ]);

    }else{
      uint16_t belt [64];
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
          case 14: ip += imm; break;
          case 15: ip += (belt[bp-a])? belt[bp-b]: 0; break;
        }
        bp++;
        ip++;
      }

      if(bp >= 64) bp = 63;

      io->outputs[i] = 0;
      io->outputs[i] |= ((uint64_t)belt[bp-3]) << 24;
      io->outputs[i] |= ((uint64_t)belt[bp-2]) << 16;
      io->outputs[i] |= ((uint64_t)belt[bp-1]) <<  8;
      io->outputs[i] |= ((uint64_t)belt[bp  ]);
    }
  }
}










void runAdvProgram(ADVANCEDPROGRAM* p, IOSPACE* io, uint64_t outmask){
  for(int i = 0; i < IOSIZE; i++){
    uint16_t  belt [64];
    int16_t* ibelt = (int16_t*) &belt;
    int ip = 0;
    int bp = 3;

    belt[0] = (io->inputs[i]      ) & 0xFF;
    belt[1] = (io->inputs[i] >>  8) & 0xFF;
    belt[2] = (io->inputs[i] >> 16) & 0xFF;
    belt[3] = (io->inputs[i] >> 24) & 0xFF;

    while(ip < p->length){
      uint16_t ins =  p->code[ip];
      uint16_t op  =  ins >> 6;
      uint16_t a   =  ins & 0x07;
      uint16_t b   = (ins >> 3) & 0x07;
      uint16_t imm =  ins & 0x3F;

      uint16_t uba =  belt[bp-a];
      uint16_t ubb =  belt[bp-b];
      int16_t  iba = ibelt[bp-a];
      int16_t  ibb = ibelt[bp-b];

      switch(op){
        case  0:  belt[bp+1] = uba + ubb; break;
        case  1:  belt[bp+1] = uba - ubb; break;
        case  2: ibelt[bp+1] = iba + ibb; break;
        case  3: ibelt[bp+1] = iba - ibb; break;
        case  4:  belt[bp+1] = uba + ubb + 1; break;
        case  5:  belt[bp+1] = uba - ubb + 1; break;
        case  6: ibelt[bp+1] = iba + ibb + 1; break;
        case  7: ibelt[bp+1] = iba - ibb + 1; break;
        case  8:  belt[bp+1] = uba & ubb; break;
        case  9:  belt[bp+1] = uba |   ubb; break;
        case 10:  belt[bp+1] = uba ^  ubb; break;
        case 11:  belt[bp+1] = uba >> ubb; break;
        case 12:  belt[bp+1] = uba << ubb; break;
        case 13:  belt[bp+1] = (uba >> ubb) | (uba << (16 - ubb)); break;
        case 14:  belt[bp+1] = (uba << ubb) | (uba >> (16 - ubb)); break;
        case 15:  belt[bp+1] = imm;                       break;
        case 16:  belt[bp+1] = uba != ubb; break;
        case 17:  belt[bp+1] = ubb & (uba -  ubb); break;
        case 18:  belt[bp+1] = uba > ubb; break;
        case 19:  belt[bp+1] = uba < ubb; break;
        case 20: ibelt[bp+1] = iba > ibb; break;
        case 21: ibelt[bp+1] = iba < ibb; break;
        case 22:  belt[bp+1] = uba * ubb; break;
        case 23:  belt[bp+1] = iba * ibb; break;
        case 24:  belt[bp+1] = (ubb != 0)? uba / ubb : 0; break;
        case 25: ibelt[bp+1] = (ibb != 0)? iba / ibb : 0; break;
        case 26:  belt[bp+1] = (ubb != 0)? uba % ubb : 0; break;
        case 27: ibelt[bp+1] = (ibb != 0)? iba % ibb : 0; break;
        case 28:  belt[bp+1] = uba & ~ubb; break;
        case 29:  ip += imm; break;
        case 30:  ip += (uba)? ibb : 0; break;

        case 32:  belt[bp+1] = ~a; break;
        case 33:  belt[bp+1] = a+1; break;
        case 34:  belt[bp+1] = a-1; break;
        case 35:  belt[bp+1] = (a < 0)? -a : a; break;
      }
      bp++;
      ip++;
    }

    if(bp >= 64) bp = 63;

    io->outputs[i] = 0;
    io->outputs[i] |= ((uint64_t)belt[bp-3]) << 24;
    io->outputs[i] |= ((uint64_t)belt[bp-2]) << 16;
    io->outputs[i] |= ((uint64_t)belt[bp-1]) <<  8;
    io->outputs[i] |= ((uint64_t)belt[bp  ]);

    io->outputs[i] &= outmask;
  }
}










void printAdvProgram(ADVANCEDPROGRAM* p){
  printf("PROGRAM:\n");
  for(int i = 0; i < p->length; i++){
    uint16_t ins =  p->code[i];
    uint16_t op  =  ins >> 6;
    uint16_t a   =  ins & 0x07;
    uint16_t b   = (ins >> 3) & 0x07;
    uint16_t imm =  ins & 0x3F;

    switch(op){
      case  0: printf("  uadd  b%i b%i\n", a, b); break;
      case  1: printf("  usub  b%i b%i\n", a, b); break;
      case  2: printf("  iadd  b%i b%i\n", a, b); break;
      case  3: printf("  isub  b%i b%i\n", a, b); break;
      case  4: printf("  uadc  b%i b%i\n", a, b); break;
      case  5: printf("  usbc  b%i b%i\n", a, b); break;
      case  6: printf("  iadc  b%i b%i\n", a, b); break;
      case  7: printf("  isbc  b%i b%i\n", a, b); break;
      case  8: printf("   and  b%i b%i\n", a, b); break;
      case  9: printf("    or  b%i b%i\n", a, b); break;
      case 10: printf("   xor  b%i b%i\n", a, b); break;
      case 11: printf("   shr  b%i b%i\n", a, b); break;
      case 12: printf("   shl  b%i b%i\n", a, b); break;
      case 13: printf("   rtr  b%i b%i\n", a, b); break;
      case 14: printf("   rtl  b%i b%i\n", a, b); break;
      case 15: printf("   cst  #%i    \n", imm ); break;
      case 16: printf("   neq  b%i b%i\n", a, b); break;
      case 17: printf("  minc  b%i b%i\n", a, b); break;
      case 18: printf("   ugt  b%i b%i\n", a, b); break;
      case 19: printf("   uls  b%i b%i\n", a, b); break;
      case 20: printf("   igt  b%i b%i\n", a, b); break;
      case 21: printf("   ils  b%i b%i\n", a, b); break;
      case 22: printf("  umul  b%i b%i\n", a, b); break;
      case 23: printf("  imul  b%i b%i\n", a, b); break;
      case 24: printf("  udiv  b%i b%i\n", a, b); break;
      case 25: printf("  idiv  b%i b%i\n", a, b); break;
      case 26: printf("  umod  b%i b%i\n", a, b); break;
      case 27: printf("  imod  b%i b%i\n", a, b); break;
      case 28: printf("  andn  b%i b%i\n", a, b); break;
      case 29: printf("     j  #%i    \n", imm ); break;
      case 30: printf("    br  b%i b%i\n", a, b); break;

      case 32: printf("   not  b%i    \n", a   ); break;
      case 33: printf("   inc  b%i    \n", a   ); break;
      case 34: printf("   dec  b%i    \n", a   ); break;
      case 35: printf("   abs  b%i    \n", a   ); break;
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










int cmpProgram(PROGRAM* p, IOSPACE* io, BITMODE b){
  IOSPACE x;
  for(int i = 0; i < IOSIZE; i++){
    x.inputs[i] = io->inputs[i];
  }
  runProgram(p, &x, b);

  uint64_t distance = 0;
  for(int i = 0; i < IOSIZE; i++){
    uint64_t bitdiff = x.outputs[i] ^ io->outputs[i];

    const uint64_t m1  = 0x5555555555555555;
    const uint64_t m2  = 0x3333333333333333;
    const uint64_t m4  = 0x0f0f0f0f0f0f0f0f;
    const uint64_t h01 = 0x0101010101010101;

    bitdiff -= (bitdiff >> 1) & m1;
    bitdiff = (bitdiff & m2) + ((bitdiff >> 2) & m2);
    bitdiff = (bitdiff + (bitdiff >> 4)) & m4;
    distance += (bitdiff * h01) >> 56;
  }

  return distance / IOSIZE;
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
    for(int i = 0; i < IOSIZE; i++){
      char pa[8], pb[8], pc[8], pd[8];
      char ra[8], rb[8], rc[8], rd[8];
      formatInt(ra, (io->outputs[i]      ) & 0xFF);
      formatInt(rb, (io->outputs[i] >>  8) & 0xFF);
      formatInt(rc, (io->outputs[i] >> 16) & 0xFF);
      formatInt(rd, (io->outputs[i] >> 24) & 0xFF);
      formatInt(pa, (io->inputs [i]      ) & 0xFF);
      formatInt(pb, (io->inputs [i] >>  8) & 0xFF);
      formatInt(pc, (io->inputs [i] >> 16) & 0xFF);
      formatInt(pd, (io->inputs [i] >> 24) & 0xFF);
      printf("|%s,%s,%s,%s>%s,%s,%s,%s|", pa, pb, pc, pd, ra, rb, rc, rd);
      if(i % 4 == 3) printf("\n");
    }
  }else{
    for(int i = 0; i < IOSIZE; i++){
      char pa[8], pb[8], pc[8], pd[8];
      char ra[8], rb[8], rc[8], rd[8];
      formatInt(ra, (io->outputs[i]      ) & 0xFFFF);
      formatInt(rb, (io->outputs[i] >> 16) & 0xFFFF);
      formatInt(rc, (io->outputs[i] >> 32) & 0xFFFF);
      formatInt(rd, (io->outputs[i] >> 48) & 0xFFFF);
      formatInt(pa, (io->inputs [i]      ) & 0xFFFF);
      formatInt(pb, (io->inputs [i] >> 16) & 0xFFFF);
      formatInt(pc, (io->inputs [i] >> 32) & 0xFFFF);
      formatInt(pd, (io->inputs [i] >> 48) & 0xFFFF);
      printf("|%s,%s,%s,%s>%s,%s,%s,%s|", pa, pb, pc, pd, ra, rb, rc, rd);
      if(i % 4 == 3) printf("\n");
    }
  }
}










void newProgram(PROGRAM* p, int minsz, int maxsz){
  for(int j = 0; j < 32; j++)
    p->code[j] = rnum();
  p->length = rnum() % maxsz;
  p->length = (p->length > minsz)? p->length : minsz;
}
