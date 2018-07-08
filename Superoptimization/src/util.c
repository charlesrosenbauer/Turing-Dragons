#include "util.h"










uint8_t rnum(){
  rseed = (rseed * 123571389)  + 1385179671;
  rseed ^= 1146146141641714;
  return (rseed / 256) % 256;
}










uint64_t rpar(){
  uint64_t x = 0;
  for(int i = 0; i < 8; i++){
    x |= rnum(); x <<= 8;
  }
  return x;
}
