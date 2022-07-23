//#include  <msp430xG46x.h> // IDE library
#include <msp430.h>

#include  "../header/api.h"             // private library - API layer
#include  "../header/hal.h"             // private library - HAL layer
#include  "../header/bsp.h"             // private library - BSP layer

volatile int Out_to_RGB = 0x01;
//==========================================================
//                     STATE 1
//==========================================================
void RGBBlink(int delay){

    clear_RGB();
    while(state == 1){

        blink_RGB(delay);
        _BIS_SR(GIE);
//        RGBPortOUT += 0x20;
//        delay_ms(delay);
    }
}
//==========================================================
//                     STATE 2
//==========================================================
void UpCounter(int delay){

    unsigned int SumValTmp;
    char SumValTXT[20] ={'\0'};
    lcd_clear();
    //LEDsArrayPort = 0x01;
    while(state == 2){
        delay_ms(delay);
        sum_up_value++;

        SumValTmp = (unsigned int) sum_up_value;
        int2str(SumValTXT, SumValTmp);
        lcd_home();
//        lcd_clear();                           // clear lcd
        lcd_puts("c_up: ");
        lcd_puts(SumValTXT);    // print initial label 1 on LCD
        _BIS_SR(GIE);

    }
}
//==========================================================
//                     STATE 3
//==========================================================
void DownCounter(int delay){

    unsigned int SumValTmp;
    char SumValTXT[20] ={'\0'};

    //LEDsArrayPort = 0x01;
    while(state == 3){
        delay_ms(delay);
        sum_down_value--;

        SumValTmp = (unsigned int) sum_down_value;
        int2str(SumValTXT, sum_down_value);
        lcd_home();
//        lcd_clear();                           // clear lcd
        lcd_puts("c_down: ");
        lcd_puts(SumValTXT);    // print initial label 1 on LCD
        _BIS_SR(GIE);

    }
    }


//==========================================================
//                     STATE 5
//==========================================================
void Potentiometer(void){
    adc10_config();
    SC_from_POT();
//    ADC10CTL0 |= ADC10ON;                   // ADC10 ON
//    ADC10CTL0 &= ~ENC;                      // ~Enable conversion
//    while(ADC10CTL1 & ADC10BUSY);           // Wait if ADC10 core is active
//    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
//    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
//    __no_operation();                       // For debugger
//    ADC10CTL0 &= ~ADC10ON;                  // ADC10 OFF
    int2str(POT,ADC10MEM);
    enable_transmition();
}
//==========================================================
//                     STATE 6
//==========================================================
void clear_and_initialize(void){
    sum_up_value = 0;
    sum_down_value = 65535;

    clearing();
    state = 8;
}

//==========================================================
//                     STATE 7
//==========================================================
void Transmit_menu(void){
    enable_transmition();
}



