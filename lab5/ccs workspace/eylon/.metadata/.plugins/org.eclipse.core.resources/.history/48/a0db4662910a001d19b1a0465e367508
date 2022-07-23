#ifndef _bsp_H_
#define _bsp_H_

#include  <msp430g2553.h>          // MSP430x2xx
// #include  <msp430xG46x.h>  // MSP430x4xx
//#include  <msp430xG46x.h> // IDE library
#include <msp430.h>

extern void GPIOconfig(void);
#define   debounceVal      1000

////////////////// UART DEFINES //////////////////

#define UART_SEL           P1SEL
#define UART_OUT           P1OUT
#define RxBuffer UCA0RXBUF
#define TxBuffer UCA0TXBUF

////////////////// RGB DEFINES //////////////////
#define RGB_SEL            P1SEL
#define RGB_DIR            P1DIR
#define RGB_OUT            P1OUT

////////////////// TIMER DEFINES //////////////////
#define RGB_SEL            P1SEL
#define RGB_DIR            P1DIR
#define RGB_OUT            P1OUT

////////////////// JOYTSTICK DEFINES //////////////////
#define JOY_IN             P1IN
#define JOY_INT_PEND       P1IFG
#define JOY_IE             P1IE
#define JOY_IES            P1IES
#define JOY_SEL            P1SEL
#define JOY_DIR            P1DIR
#define JOY_PB             0x20  // P1.5 is PushButton from joystick

////////////////// MOTOR STEPPER DEFINES //////////////////
#define MOTOR_SEL            P2SEL
#define MOTOR_DIR            P2DIR
#define MOTOR_OUT            P2OUT

////////////////// LCD DEFINES //////////////////
#define LED_SEL            P2SEL
#define LED_DIR            P2DIR
#define LED_OUT            P2OUT


#define CLR_RGB RGB_OUT &= ~0xc1;    //turn off the RGB
#define CLR_MOTOR MOTOR_OUT &= ~0x0F;    //set motor value as 0
#define CLR_LED LED_OUT &= ~0xF0;    //turn off the leds



#endif




