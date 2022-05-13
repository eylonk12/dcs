#ifndef _api_H_
#define _api_H_

#include  "../header/halGPIO.h"     // private library - HAL layer
//#include  "../header/LCD.h"


extern void printArr2SWs(char Arr[], int size, unsigned int rate);
extern int printMulBy2(int val, unsigned int rate);
extern void startStopWatch();
extern void startFreqCounter();
extern void startSignalReco();
#endif







