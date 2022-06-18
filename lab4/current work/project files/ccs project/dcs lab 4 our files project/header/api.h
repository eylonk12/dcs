#ifndef _api_H_
#define _api_H_

#include  "../header/halGPIO.h"     // private library - HAL layer


//**************************************************************
//                 GLOBAL VARIABLES
//**************************************************************
enum SYSmode{mode0,mode1,mode2,mode3,mode4}; // global variable
extern volatile unsigned int state;
extern volatile int top_to_bottom;                           // going to be the highest
extern volatile int bottom_to_top;                           // going to be 0
extern volatile char POT_val[5];
//**************************************************************
//        functions for api
//**************************************************************
extern void RGBBlink(int delay);                           // state 1
extern void Count_up(int delay);                           // state 2
extern void Count_down(int delay);                         // state 3
extern void Potentiometer(void);                           // state 5
extern void Restart_program(void);                         // state 6
extern void Transmit_menu(void);                           // state 7
extern void progConfig(void);
extern void sleep(void);


#endif





