#ifndef _bsp_H_
#define _bsp_H_

#include  <msp430g2553.h>          // MSP430x2xx
 
// #include  <msp430xG46x.h>  // MSP430x4xx


#define   debounceVal      250
#define   LEDs_SHOW_RATE   0xFFFF  // 62_5ms
#define   LEDs_SHOW_RATE_ex1   0x7fff8  // 0.5s
#define   LEDs_SHOW_RATE_off   0x0003  // 4khertz
#define   LEDs_SHOW_RATE_on   0x000F  // 4khertz

// LEDs abstraction
#define LEDsArrPort        P3OUT


// Switches abstraction
//#define SWsArrPort         P2IN

//#define SWsArrPortDir      P2DIR
//#define SWsArrPortSel      P2SEL
#define SWmask             0x70

// PushButtons abstraction
#define LCD_PB_Port	   P1IN 
#define LCD_PB_IntPend	   P1IFG 
#define LCD_PB_IntEn	   P1IE
#define LCD_PB_IntEdgeSel  P1IES
#define LCD_PB_Sel         P1SEL 
#define LCD_PB_Dir         P1DIR 
#define LCD_CONTROL_SEL    P2SEL
#define PB0                0xF1
#define PB1                0xF2
#define PB2                0xF4
#define PB3                0xF8




//change
#define Pwm_out1            P1OUT



extern void GPIOconfig(void);
extern void TIMERconfig(void);
extern void ADCconfig(void);

#endif



