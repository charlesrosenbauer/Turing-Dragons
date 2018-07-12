#include "util.h"










uint8_t rnum(){
  rstate = (rstate * 56137596173) + 135917635781;
  return (rstate >> 8) & 0xFF;
}










uint64_t rnum8(){
  uint64_t ret = 0;

  rstate = (rstate * 3178956978153) + 65718936781;
  ret = (rstate >> 8) & 0xFFFF;

  rstate = (rstate * 1537697165781) + 70873891123;
  ret <<= 16;
  ret |= (rstate >> 8) & 0xFFFF;

  rstate = (rstate * 7895103781351) + 51347674897;
  ret <<= 16;
  ret |= (rstate >> 8) & 0xFFFF;

  rstate = (rstate * 8071853978411) + 48169789611;
  ret <<= 16;
  ret |= (rstate >> 8) & 0xFFFF;

  return ret;
}
