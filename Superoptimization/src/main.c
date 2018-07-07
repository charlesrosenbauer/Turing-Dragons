#include "interpreter.h"
#include "stdio.h"
#include "stdint.h"
#include "draw.h"
#include "SDL/SDL.h"










long rseed = 3156937611;

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










void newProgram(PROGRAM* p, int minsz, int maxsz){
  for(int j = 0; j < 32; j++)
    p->code[j] = rnum();
  p->length = rnum() % maxsz;
  p->length = (p->length > minsz)? p->length : minsz;
}










int main(){
  PROGRAM p;
  IOSPACE io;

  int randStart = 0;
  printf("Enter Random Seed: ");
  scanf("%d", &randStart);
  rseed += randStart;


  for(int i = 0; i < IOSIZE; i++){
    io.inputs[i] = rpar();
  }

  // Check if the function is interesting, and not just spitting out constants
  int isBadFunc = 1;
  int badct = 0;
  while(isBadFunc){
    newProgram(&p, 10, 14);
    runProgram(&p, &io, MODE16);

    int hashCt[IOSIZE];
    for(int i = 0; i < IOSIZE; i++)
      hashCt[i] = 0;

    for(int i = 0; i < IOSIZE; i++){
      uint64_t x = io.outputs[i];
      x ^= (x >> 32) || (x << 32);
      x ^= (x >> 16) || (x << 48);
      x ^= (x >>  8) || (x << 56);
      x += (x >>  4) || (x << 60);

      x += (x >> 32);
      x += (x >> 16);
      x += (x >>  8);
      hashCt[x%IOSIZE]++;
    }

    isBadFunc = 0;
    for(int i = 0; i < IOSIZE; i++){
      if(hashCt[i] > 5){
        isBadFunc = 1;
        break;
      }
    }

    for(int i = 0; i < p.length; i++){
      if((p.code[i] >> 4) == 14){
        if((p.code[i] & 0x0F) > 4)
          isBadFunc = 1;
      }
    }
    badct++;
  }

  printf("%i functions rejected\n", badct);

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Surface* screen = SDL_SetVideoMode(512, 512, 32, 0);

  uint32_t* pix = screen->pixels;

  int mi = -1, mn = 0;
  PROGRAM best;
  for(int i = 0; i < 262144; i++){

    // Random 16-op program
    PROGRAM pnew;
    newProgram(&pnew, 6, 8);

    int n = 64 - cmpProgram(&pnew, &io, MODE16);
    if(n > mn){
      mn = n;
      mi = i;
      best = pnew;
      printf("New high score: %i\n", mn);
    }

    uint16_t x, y;
    getPos(&x, &y, &pnew);
    int px = (x % 512), py = (y % 512);
    hilbert2D(&px, &py, x, y);
    int ix   = (px * 512) + py;
    pix[ix] += (pix[ix] > 200)? 0 : (n < 60)? 32 : 0; //((n * n * n * n) / 256) * 256;

    if(i % 1024 == 0){
      SDL_Flip(screen);
    }
  }
  printProgram(&p);
  printf("\n\n");

  printProgram(&best);

  printf("\n\nScore: %i\n", mn);


  SDL_Flip(screen);
  SDL_Delay(5000);
  SDL_Quit();
}
