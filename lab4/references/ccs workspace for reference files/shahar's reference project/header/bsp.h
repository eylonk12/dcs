#ifndef _bsp_H_
#define _bsp_H_

extern void InitGPIO(void);


//UART-1.1-2, POT-1.3, PB0-1.4,RGB: B-1.5,G-1.6,R-1.7 - Port 1
//#define POT_PB0_RGBPortIN			P1IN
//#define POT_PB0_RGBPortOUT		   	P1OUT
//#define POT_PB0_RGBIntPending		P1IFG
//#define POT_PB0_RGBIntEnable		P1IE
//#define POT_PB0_RGBIntEdgeSel		P1IES
//#define POT_PB0_RGBPortSel   		P1SEL
//#define POT_PB0_RGBPortDir   		P1DIR

//Led Array - Port 2
//#define LEDsArrayPort           	P2OUT
//#define LEDsArrayPortSel           	P2SEL
//#define LEDsArrayPortDir        	P2DIR
//#define LEDs_CLR LEDsArrayPort = 0x00     //clear LEDs


#define RxBuffer UCA0RXBUF
#define TxBuffer UCA0TXBUF

//***********************************************
//            POT configuration
//***********************************************
#define  POTPortSel     P1SEL
#define  POTPortDir     P1DIR

//***********************************************
//            RGB configuration
//***********************************************
#define  RGBPortSel     P2SEL
#define  RGBPortDir     P2DIR
#define  RGBPortOUT     P2OUT

#define RGB_CLR RGBPortOUT &= ~(BIT0 + BIT1 + BIT2);  //clear RGB
//***********************************************
//            LCD data configuration
//***********************************************

#define LCD_DATA_WRITE       P1OUT
#define LCD_DATA_DIR         P1DIR
#define LCD_DATA_READ        P1IN

#define LCD_DATA_OFFSET 0x04 //data pin selection offset for 4 bit mode, variable range is 0-4, default 0 - Px.0-3, no offset

//***********************************************
//            LCD control configuration
//***********************************************

#define LCD_CTRL_OUT_PORT    P2OUT
#define LCD_CTRL_SEL_PORT    P2SEL
#define LCD_CTRL_DIR_PORT    P2DIR

#define LCD_EN(a)   (!a ? (LCD_CTRL_OUT_PORT&=~BIT5) : (LCD_CTRL_OUT_PORT|=BIT5))       // P2.5 is lcd enable pin
#define LCD_EN_DIR(a)   (!a ? (LCD_CTRL_DIR_PORT&=~BIT5) : (LCD_CTRL_DIR_PORT|=BIT5))   // P2.5 pin direction

#define LCD_RS(a)   (!a ? (LCD_CTRL_OUT_PORT&=~BIT6) : (LCD_CTRL_OUT_PORT|=BIT6))       // P2.6 is lcd RS pin
#define LCD_RS_DIR(a)   (!a ? (LCD_CTRL_DIR_PORT&=~BIT6) : (LCD_CTRL_DIR_PORT|=BIT6))   // P2.6 pin direction

#define LCD_RW(a)   (!a ? (LCD_CTRL_OUT_PORT&=~BIT7) : (LCD_CTRL_OUT_PORT|=BIT7))       // P2.7 is lcd RW pin
#define LCD_RW_DIR(a)   (!a ? (LCD_CTRL_DIR_PORT&=~BIT7) : (LCD_CTRL_DIR_PORT|=BIT7))   // P2.7 pin direction


////***********************************************
////     TimerA configuration (Trigger for DMA)
////***********************************************
//#define TimerCompare_Control    TACTL
//#define TimerCompare_mode       TACCTL0
//#define TimerCompare_compareVal TACCR0
//#define TimerCompare_Clock      TASSEL_2
//#define TimerCompare_Clear      TACLR
//#define TimerCompare_mode2      TACCTL2

#endif
