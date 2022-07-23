#ifndef _api_H_
#define _api_H_


//==========================================================
//                 GLOBAL VARIABLES
//==========================================================
extern volatile unsigned int state;
extern volatile int sum_up_value;                           // state 2
extern volatile int sum_down_value;                         // state 3
extern volatile char POT[5];
//================================================
//        SERVICE FUNCTIONS
//================================================
extern void RGBBlink(int delay);                           // state 1
//------------------------------------------------
extern void UpCounter(int delay);                          // state 2
//------------------------------------------------
extern void DownCounter(int delay);                        // state 3
//------------------------------------------------
extern void Potentiometer(void);                           // state 5
//------------------------------------------------
extern void clear_and_initialize(void);                    // state 6
//------------------------------------------------
extern void Transmit_menu(void);                           // state 7

#endif

