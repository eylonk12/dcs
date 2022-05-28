#ifndef _bsp_H_
#define _bsp_H_

// #include  <msp430g2553.h>          // MSP430x2xx
// #include  <msp430xG46x.h>  // MSP430x4xx
#include  <msp430xG46x.h> // IDE library
#include <msp430.h>

extern void GPIOconfig(void);
extern void TIMERconfig(void);

#define   debounceVal      250

// LCD modes
#define LCD_DATA_WRITE     P1OUT
#define LCD_DATA_READ      P1IN
#define LCD_DATA_DIR       P1DIR
#define LCD_DATA_SEL       P1SEL
//LCD CONTROL
#define LCD_EN_SEL         P2SEL
#define LCD_DIR            P2DIR
#define LCD_ENABLES        P2OUT

// PushButtons abstraction
#define PBsArrPort	   P1IN 
#define PBsArrIntPend	   P1IFG 
#define PBsArrIntEn	   P1IE
#define PBsArrIntEdgeSel   P1IES
#define PBsArrPortSel      P1SEL 
#define PBsArrPortDir      P1DIR 
#define PB0                0x01
#define PB1                0x02
#define PB2                0x04
#define PB3                0x01

//Keypad rows and coloumns configurations
#define KEY_PAD_PORT_SEL   P10SEL
#define KEY_PAD_PORT_DIR   P10DIR
#define KEY_PAD_PORT_IN	   P10IN 
#define KEY_PAD_PORT_OUT   P10OUT 

//Keypad interrupt signal configurations
#define KEY_PAD_INT_IN        P2IN
#define KEY_PAD_INT_PEN	      P2IFG 
#define KEY_PAD_INT_IE        P2IE
#define KEY_PAD_INT_EDGE_SEL  P2IES
#define KEY_PAD_INT_SEL       P2SEL
#define KEY_PAD_INT_DIR       P2DIR

//Buzzer interrupt signal configurations
#define BUZZER_OUT            P2OUT
#define BUZZER_SEL            P2SEL
#define BUZZER_DIR            P2DIR






#endif




