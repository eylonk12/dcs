#ifndef _bsp_H_
#define _bsp_H_

#include  <msp430g2553.h>          // MSP430x2xx
// #include  <msp430xG46x.h>  // MSP430x4xx


#define   debounceVal      250

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
#define PB3                0x08


// LCD - configurations
/*----------------------------------------------------------
  CONFIG: change values according to your port pin selection
------------------------------------------------------------*/
//#define LCD_DATA_SEL    P1SEL
//#define LCD_DATA_DIR    P1DIR

#define LCDsArrPortSel    P1SEL
#define LCDsArrPortDir    P1DIR
#define LCDsArrPort       P1OUT

#define LCD_DATA_WRITE	  P1OUT
#define LCD_DATA_DIR	  P1DIR
#define LCD_DATA_READ	  P1IN

#define LCD_EN_SEL        P2SEL
#define LCD_DIR 	  P2DIR
#define LCD_ENABLES       P2OUT

#define GEN_SEL            P2SEL
#define GEN_DIR            P2DIR
#define GEN_IN             P2IN

#define PWM_SEL            P2SEL
#define PWM_DIR            P2DIR
#define PWM_OUT            P2OUT

/*---------------------------------------------------------
  END CONFIG
-----------------------------------------------------------*/


// CLK abstraction


extern void GPIOconfig(void);
extern void TIMERconfig(void);
extern void ADCconfig(void);

#endif


