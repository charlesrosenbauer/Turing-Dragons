#include "draw.h"
#include "interpreter.h"










void getPos(uint16_t* x, uint16_t* y, PROGRAM* p){
  uint16_t a, b;
  /*
  for(int i = 0; i < p->length; i++){
    if(i%2){
      uint8_t m0 = 0x0F;
      uint8_t m1 = 0xF0;
      a ^= (uint16_t)(p->code[i] & m1) << (4 * (((i/2)+1)%3-1));
      a ^=  p->code[i] & m0;
    }else{
      uint8_t m0 = 0x0F;
      uint8_t m1 = 0xF0;
      b ^= (uint16_t)(p->code[i] & m1) << (4 * ((i/2)%3-1));
      b ^=  p->code[i] & m0;
    }
  }*/

  /*
  a = ((p->code[0] & 0x0F) <<  8) |  (p->code[1] & 0x0F);
  b = ((p->code[2] & 0x0F) <<  8) |  (p->code[3] & 0x0F);
  a |=((p->code[4] & 0x0F) << 12) | ((p->code[5] & 0x0F) << 4);
  b |=((p->code[6] & 0x0F) << 12) | ((p->code[7] & 0x0F) << 4);
  */

  for(int i = 0; i < p->length; i++){
    a |= 1 << (p->code[i] & 0x0F);
    b |= 1 << (p->code[i] >>   4);
  }
  *x = a;
  *y = b;
}










void rot(int n, int *x, int *y, int rx, int ry) {
  if(ry == 0){
    if(rx == 1){
      *x = n-1 - *x;
      *y = n-1 - *y;
    }
    int t = *x;
    *x = *y;
    *y = t;
  }
}










void hilbert(int n, int d, int *x, int *y) {
  int rx, ry, s, t=d;
  *x = *y = 0;
  for(int s=1; s < n; s *=2){
    rx = 1 & (t/2);
    ry = 1 & (t ^ rx);
    rot(s, x, y, rx, ry);
    *x += s * rx;
    *y += s * ry;
    t /= 4;
  }
}










void hilbert2D(int* x, int* y, int px, int py){
  //Assumes 512x512 pixels for now

  int32_t d = (px << 16) | py;
  hilbert(512, d, x, y);
}
