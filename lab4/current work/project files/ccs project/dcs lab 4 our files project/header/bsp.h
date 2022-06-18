#ifndef _bsp_H_
#define _bsp_H_

// #include  <msp430g2553.h>          // MSP430x2xx
// #include  <msp430xG46x.h>  // MSP430x4xx
#include  <msp430xG46x.h> // IDE library
#include <msp430.h>

extern void GPIOconfig(void);
#define   debounceVal      1000

////////////////// LCD DEFINES //////////////////
// LCD modes
#define LCD_DATA_WRITE     P1OUT
#define LCD_DATA_READ      P1IN
#define LCD_DATA_DIR       P1DIR
#define LCD_DATA_SEL       P1SEL
//LCD CONTROL
#define LCD_EN_SEL         P2SEL
#define LCD_DIR            P2DIR
#define LCD_ENABLES        P2OUT

////////////////// UART DEFINES //////////////////

#define UART_SEL           P1SEL
#define UART_OUT           P1OUT

////////////////// POT DEFINES //////////////////
#define POT_SEL            P1SEL
#define POT_DIR            P1DIR

////////////////// RGB DEFINES //////////////////
#define RGB_SEL            P2SEL
#define RGB_DIR            P2DIR
#define RGB_OUT            P2OUT

#define CLR_RGB RGB_OUT &= ~0x07;    //turn of the RGB



#endif




