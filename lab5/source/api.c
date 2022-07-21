#include <msp430.h>                 //include  <msp430xG46x.h> IDE library

#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer
#include  "../header/bsp.h"         // private library - BSP layer
#include <stdio.h>
#include <math.h>
#include "stdint.h"

volatile int RGB_DATA = 0x01;    // initialize value for the RGB
float normal = (2047/360);               // the normal for sizing the deg
volatile float normal_degree = (180/3.121592654); // the normal for the deg
int base_x = 477;
int base_y = 471;
volatile double x,y =0;  

void progConfig(void){
    sysConfig();
}

void sleep(void){
    enterLPM(mode0);
}


//**************************************************************
//             MOTOR function
//**************************************************************
void MOTOR_move(int delay,int steps){
    for (int i = 0; i< steps; i++){
        motor_cycle_cw();
        current_step++;
        if (current_step == 2047)
            current_step = 0;
    }
}
void MOTOR_2_zero(int delay){
    while (current_step != 0) {
        motor_cycle_cw();
        current_step++;
        if (current_step == 2047)
            current_step = 0;
    }
}
void MOTOR_2_deg(float deg){
    steps = abs(((float)deg*normal));
    step_cnt = 0;
    if (steps ==0)
        return;
    if (deg <0)
        motor_dir =0;
    else
        motor_dir = 1;
    motor_is_moving =1;
    Enable_TimerA_345();   // SMCLK, up mode, divide SMCLK to become 2^17, TA interrupt enable
    while (motor_is_moving){
        __bis_SR_register(CPUOFF + GIE);      // LPM0, ADC10_ISR will force exit
    }
}
//for (int i=0 current_step != -steps) {
//motor_cycle_ccw(delay);
//current_step--;
//if (current_step == 2047)
//current_step = 0;}
//}else{
//while (current_step != steps) {
//motor_cycle_cw(delay);
//current_step++;
//if (current_step == 2047)
//current_step = 0;
//**************************************************************
//             joystick function
//**************************************************************
void joystick_2_motor(int delay){
        DelayMs(delay);
        read_from_juystick();
        read_from_juystick();
        read_from_juystick();
}

double calc_degree(void){
    x = X_Axis - base_x;
    y = Y_Axis - base_y;
    if (pow(x,2)+pow(y,2) <pow(ERROR_RADIUS,2))
        return current_step/normal;
    double degree = atan2(y,x);
    degree = degree*normal_degree;
    if (degree <0)
        degree = degree+360;
    return degree;


}
//**************************************************************
//             script functions
//**************************************************************
void RGBBlink(int count, int delay){

    clear_all();
    for (int i =0; i<count; i++){
        blink_RGB(delay);
    }
    _BIS_SR(GIE);        // check with eylon if neccery
}
void rlc_leds(int count, int delay){

    clear_all();
    for (int i =0; i<count; i++){
        rotate_left(delay);
    }
    _BIS_SR(GIE);        // check with eylon if neccery
}
void set_delay(int new_delay){
    delay_int = new_delay;
}