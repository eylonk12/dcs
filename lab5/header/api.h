#ifndef _api_H_
#define _api_H_

#include  "../header/halGPIO.h"     // private library - HAL layer
#define ERROR_RADIUS   50

//**************************************************************
//                 GLOBAL VARIABLES
//**************************************************************
enum SYSmode{mode0,mode1,mode2,mode3,mode4}; // global variable
extern volatile unsigned int state;
extern volatile int top_to_bottom;                           // going to be the highest
extern volatile int bottom_to_top;                           // going to be 0
extern volatile char POT_val[5];
extern volatile unsigned int current_step ;
extern volatile unsigned int delay_int ;
extern unsigned int step_cnt ;           // the value of the current step for restart
extern volatile int motor_dir;                       // direction of the motor movement
extern volatile int motor_is_moving;
extern int steps;
//**************************************************************
//        functions fors api
//**************************************************************
extern void progConfig(void);
extern void MOTOR_move(int delay,int steps);
extern void MOTOR_2_zero(int delay);
extern void sleep(void);
extern void joystick_2_motor(int delay);
extern double calc_degree(void);
extern void MOTOR_2_deg(float deg);
extern void set_delay(int new_delay);
extern void RGBBlink(int count, int delay);
extern void rlc_leds(int count, int delay);


#endif





