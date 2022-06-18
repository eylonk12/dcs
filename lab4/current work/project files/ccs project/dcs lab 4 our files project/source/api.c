#include <msp430.h>                 //include  <msp430xG46x.h> IDE library

#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer
#include  "../header/bsp.h"         // private library - BSP layer

volatile int RGB_DATA = 0x01;    // initialize value for the RGB
volatile int sum_up_value = 0;               // the starting number for counting up
volatile int sum_down_value = 65535;         // the max value for counting down


void progConfig(void){
    sysConfig();
    lcd_init();
    lcd_clear();
    clear_rgb();
}

void sleep(void){
    enterLPM(mode0);
}


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
//             state 2 count up mode
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
        lcd_puts("going up:",sizeof("going up:"));
        lcd_puts(LCD_val_str,sizeof(LCD_val_str));    // print initial label 1 on LCD
        _BIS_SR(GIE);

    }
}

//**************************************************************
//             state 3 count down mode
//**************************************************************
void Count_down(int delay){

    unsigned int LCD_val_int;
    char LCD_val_str[20] ={'\0'};

    while(state == 3){
        DelayMs(delay);
        sum_down_value--;

        LCD_val_int = (unsigned int) sum_down_value;
        int2str(LCD_val_str, sum_down_value);
        lcd_home();
        lcd_puts("going down:",sizeof("going down:"));
        lcd_puts(LCD_val_str,sizeof(LCD_val_str));    // print initial label 1 on LCD
        _BIS_SR(GIE);

    }
}

//**************************************************************
//             state 5 potentiometer for output
//**************************************************************
void Potentiometer(void){
    adc10_config();                           // ADC wake up
    SRC_from_POT();                           // make the ADC as source
    int2str(POT_val,ADC10MEM);                    // taking the values of the ADC and convert to chars
    enable_transmition();                     // Transmit the chars
}

//**************************************************************
//             state 6 initialize and clear everything
//**************************************************************
void Restart_program(void){
    sum_up_value = 0;
    sum_down_value = 65535;

    clear_all();
    state = 8;
}


//**************************************************************
//             state 7 trasmit_menu
//**************************************************************
void Transmit_menu(void){                    // enable transmit , and then for state 7 print menu
    enable_transmition();
}



