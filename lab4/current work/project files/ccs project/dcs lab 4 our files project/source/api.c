#include <msp430.h>                 //include  <msp430xG46x.h> IDE library

#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer
#include  "../header/bsp.h"         // private library - BSP layer

volatile int RGB_DATA = 0x01;    // initialize value for the RGB
volatile int sum_up_value = 0;
volatile int sum_down_value = 65535;

//**************************************************************
//             state 1 RGB blinks
//**************************************************************
void RGBBlink(int delay){

    clear_rgb();
    while(state == 1){

        blink_RGB(delay);
        _BIS_SR(GIE);        // check with eylon if neccery
    }
}

//**************************************************************
//             System Configuration
//**************************************************************
void Count_up(int delay){

    unsigned int LCD_val_int;
    char LCD_val_str[20] ={'\0'};
    lcd_clear();
    while(state == 2){
        DelayMs(delay);
        sum_up_value++;

        LCD_val_int = (unsigned int) sum_up_value;
        int2str(LCD_val_str, LCD_val_int);
        lcd_home();
        lcd_puts("going up: ");
        lcd_puts(LCD_val_str);    // print initial label 1 on LCD
        _BIS_SR(GIE);

    }
}

//**************************************************************
//             System Configuration
//**************************************************************


//**************************************************************
//             System Configuration
//**************************************************************


//**************************************************************
//             System Configuration
//**************************************************************


//**************************************************************
//             System Configuration
//**************************************************************




