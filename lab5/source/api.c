#include <msp430.h>                 //include  <msp430xG46x.h> IDE library

#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer
#include  "../header/bsp.h"         // private library - BSP layer
#include <stdio.h>
#include <math.h>
#include "stdint.h"

volatile int RGB_DATA = 0x01;    // initialize value for the RGB
float normal = 5.6861111;               // the normal for sizing the deg   2047 steps
volatile float normal_degree = (180/3.141592654); // the normal for the deg
int base_x = 477;
int base_y = 471;
double x,y =0;  

void progConfig(void){
    sysConfig();
}

void sleep(void){
    __bis_SR_register(CPUOFF + GIE);
}


//**************************************************************
//             MOTOR function
//**************************************************************
void MOTOR_move(void){
    current_step = 0;
    delay10MS();                     // SMCLK, up mode, divide SMCLK to become 2^17, TA interrupt enable
    while (state == 3){
        __bis_SR_register(CPUOFF + GIE);      // LPM0, ADC10_ISR will force exit
    }
    Disable_TimerA_345();
}
void MOTOR_2_zero(int delay){
    while (current_step != 0) {
        motor_cycle_cw();
        current_step--;
        if (current_step == 0)
            break;
    }
}
void MOTOR_2_deg(float deg){
    step_cnt = 0;
    int ccw_steps,cw_steps;
    if (deg*normal >= current_step){
        ccw_steps = deg*normal- current_step;
        cw_steps  = 2047 - deg*normal + current_step;
    }else{
        ccw_steps = 2047 -current_step + deg*normal;
        cw_steps  = current_step - deg*normal;
    }
    if (cw_steps < ccw_steps){
        motor_dir = 1;
        steps = cw_steps;
    }else{
        motor_dir = 0;
        steps = ccw_steps;
    }
    if (steps ==0)
        return;
    motor_is_moving =1;
    delay10MS();                     // SMCLK, up mode, divide SMCLK to become 2^17, TA interrupt enable
    while (motor_is_moving){
        __bis_SR_register(CPUOFF + GIE);      // LPM0, ADC10_ISR will force exit
    }
}

//**************************************************************
//             joystick function
//**************************************************************
void joystick_2_motor(int delay){
    read_from_juystick();
    read_from_juystick();
    read_from_juystick();
}

float calc_degree(int mode) {
    x = X_Axis - base_x;
    if (x == 0)
        if (mode == 0)
            return current_step / normal;
        else if (mode == 1)
            return 400;
    y = Y_Axis - base_y;
    if (pow(x, 2) + pow(y, 2) < pow(ERROR_RADIUS, 2))
        if (mode == 0)
            return current_step / normal;
        else if (mode == 1)
            return 400;
    float degree = atan2(y, x);
    degree = degree * normal_degree;
    if (degree < 0)
        degree = degree + 360;
    return degree;
}
// The delay is x*40usec
void delayXms(long int x){
    long long int i;
    for (i = 0; i < x; i++){
        delay10MS();
    }
}

void send_degree(float deg){
    int deg_int = (int)deg; 
    tx_str_val[0] = '0'; tx_str_val[1] = '0';  tx_str_val[2] = '0';  tx_str_val[3] = '0';
    int2str(tx_str_val,deg_int);
    tx_str_val[3] = '#';
    enable_transmition();
}

void send_painter_mode_change(){
    JOY_IE       |= 0x20;
    delayXms(10);
    JOY_IE       &= ~0x20;
}
//**************************************************************
//             script functions
//**************************************************************
void RGBBlink(int count, int delay){

    clear_all();
    int i;
    for (i =0; i<count; i++){
        blink_RGB(delay);
    }
    _BIS_SR(GIE);        // check with eylon if neccery
}
void rlc_leds(int count, int delay){

    clear_all();
    int i;
    for (i =0; i<count; i++){
        rotate_left(delay);
    }
    _BIS_SR(GIE);        // check with eylon if neccery
}
void set_delay(int new_delay){
    delay_int = new_delay;
}

