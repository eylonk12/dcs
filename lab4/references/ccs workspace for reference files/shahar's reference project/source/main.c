//#include  <msp430xG46x.h> // IDE library

#include <msp430.h>

#include "../header/bsp.h"
#include "../header/hal.h"
#include "../header/api.h"

//  GLOBAL VARIABLES

volatile unsigned int state = 7;  // Display menu

volatile char X[10];
volatile unsigned int x = 500;

volatile int sum_up_value = 0;
volatile int sum_down_value = 65535;

void main(void){
	

    InitGPIO();
	lcd_init();
    while(1){
        // FSM:  
        switch(state){
            case 1:
                RGBBlink(x);
                break;
            case 2:
                UpCounter(x);
                break;
            case 3:
                DownCounter(x);
                break;
            case 4:
                __bis_SR_register(LPM0_bits+GIE);
                break;
            case 5:
                Potentiometer();
                break;
            case 6:
                clear_and_initialize();
                break;
			case 7:
				Transmit_menu();
				__bis_SR_register(LPM0_bits + GIE);   // Enter LPM0
                break;	
            case 8:
                __bis_SR_register(LPM0_bits + GIE);   // Enter LPM0
                break;
            default:
                state = 8;
                break;
        }
    }
}
