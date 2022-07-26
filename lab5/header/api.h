#ifndef _api_H_
#define _api_H_

#include  "../header/halGPIO.h"     // private library - HAL layer
#define ERROR_RADIUS   50


//**************************************************************
//                 GLOBAL VARIABLES
//**************************************************************
enum SYSmode{mode0,mode1,mode2,mode3,mode4}; // global variable
extern char rec_mode;
extern volatile unsigned int state;
extern int ready;
extern int script;
extern int script_char_index;
extern volatile unsigned int current_step ;
extern volatile unsigned int delay_int ;
extern float deg ;
extern unsigned int step_cnt ;           // the value of the current step for restart
extern volatile int motor_dir;                       // direction of the motor movement
extern volatile int motor_is_moving;
extern int steps;
//**************************************************************
//        functions fors api
//**************************************************************
extern void progConfig(void);
extern void MOTOR_move(void);
extern void clear_all_leds(void);
extern void MOTOR_2_zero(int delay);
extern void sleep(void);
extern void joystick_2_motor(int delay);
extern float calc_degree(int mode);
extern void MOTOR_2_deg(float deg);
extern void set_delay(int new_delay);
extern void delayXms(long int);
extern void RGBBlink(int count);
extern void rlc_leds(int count);
extern void rrc_leds(int count);
extern void next_command (void);
extern void stepper_deg(void);
extern void send_degree(float deg);
extern void send_painter_mode_change();


#endif





