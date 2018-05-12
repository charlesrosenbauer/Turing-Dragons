#include "stdlib.h"
//#include "SDL/SDL.h"
#include "stdio.h"
#include "turing.h"
#include "funcs.h"
#include "math.h"







const int TRIAL_CT = 1024;


int main(){
  seedrand(0x13F2E2C1279AE429);

  TAPE t;
  makeTape(&t, 2097152);
  MACHINE_3S m;

  float terms = 0;
  float termxs[TRIAL_CT];
  float termct= 0;

  float runs = 0;
  float runxs[TRIAL_CT];
  float runct= 0;

  int   loopct= 0;

  for(int i = 0; i < TRIAL_CT; i++){
    clearTape(&t);
    randomMachine_3S(&m, 255);
    m.index = 8388608 / 2;

    TERMCODE term = runMachine_3S(&m, &t, 50000000);

    if(term.termct == 0){
      loopct++;
      termxs[i] = 0;
      runxs [i] = 0;
      printf("%i : loop\n", i);
    }else if(term.termct > 0){
      terms += term.termct;
      termxs[i] = term.termct;
      termct++;
      runxs [i] = 0;
      printf("%i : Terminates after %i, min=%i, max=%i\n", i, (int)term.termct, (int)term.minIx, (int)term.maxIx);
    }else{
      runs -= term.termct;
      runxs [i] = -term.termct;
      runct++;
      termxs[i] = 0;
      printf("%i : Hits bounds after %i, min=%i, max=%i\n", i, (int)-term.termct, (int)term.minIx, (int)term.maxIx);
    }
  }


  //Compute avg and stddev for terms
  terms /= ((termct > 0)? termct : 1);
  float termdev = 0;
  float termmax = 0;
  for(int i = 0; i < TRIAL_CT; i++){
    termdev += sqrt((termxs[i] - terms) * (termxs[i] - terms));
    termmax = (termmax < termxs[i])? termxs[i] : termmax;
  }
  termdev /= ((termct > 1)? termct-1 : 1);

  runs /= ((runct > 0)? runct : 1);
  float rundev = 0;
  float runmax = 0;
  for(int i = 0; i < TRIAL_CT; i++){
    rundev += sqrt((runxs[i] - runs) * (runxs[i] - runs));
    runmax = (runmax < runxs[i])? runxs[i] : runmax;
  }
  rundev /= ((runct > 1)? runct-1 : 1);

  printf("Terminating   Turing Machines: %f total, %f max steps, %f avg steps, %f std dev steps\n", termct, termmax, terms, termdev);
  printf("Bound-hitting Turing Machines: %f total, %f max steps, %f avg steps, %f std dev steps\n",  runct,  runmax, runs,  rundev);
  printf("Non-terminating Turing Machines: %i total\n", loopct);
}
