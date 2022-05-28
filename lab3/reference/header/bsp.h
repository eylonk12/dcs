// BSP - Board Support Package

#ifndef _bsp_H_
#define _bsp_H_

/*----------------------------------------------------------
  CONFIG: PUSH BUTTONS
------------------------------------------------------------*/
#define PBsArrayPort		 P1IN 
#define PBsArrayIntPending	 P1IFG 
#define PBsArrayIntEnable	 P1IE
#define PBsArrayIntEdgeSel	 P1IES
#define PBsArrayPortSel   	 P1SEL 
#define PBsArrayPortDir   	 P1DIR 

/*----------------------------------------------------------
  CONFIG: LCD DATA
------------------------------------------------------------*/
   
#define LCD_DATA_WRITE		 P1OUT
#define LCD_DATA_DIR		 P1DIR
#define LCD_DATA_READ		 P1IN

#define LCD_DATA_OFFSET 0x04 //data pin selection offset for 4 bit mode, variable range is 0-4, default 0 - Px.0-3, no offset


 /*----------------------------------------------------------
  CONFIG: LCD CONTROL
------------------------------------------------------------*/

#define LCD_CTRL_OUT_PORT	 P2OUT
#define LCD_CTRL_SEL_PORT	 P2SEL
#define LCD_CTRL_DIR_PORT	 P2DIR

#define LCD_EN(a)	(!a ? (LCD_CTRL_OUT_PORT&=~BIT5) : (LCD_CTRL_OUT_PORT|=BIT5))   // P2.5 is lcd enable pin
#define LCD_EN_DIR(a)	(!a ? (LCD_CTRL_DIR_PORT&=~BIT5) : (LCD_CTRL_DIR_PORT|=BIT5))   // P2.5 pin direction 
																  
#define LCD_RS(a)	(!a ? (LCD_CTRL_OUT_PORT&=~BIT6) : (LCD_CTRL_OUT_PORT|=BIT6))   // P2.6 is lcd RS pin
#define LCD_RS_DIR(a)	(!a ? (LCD_CTRL_DIR_PORT&=~BIT6) : (LCD_CTRL_DIR_PORT|=BIT6))   // P2.6 pin direction  
																  
#define LCD_RW(a)	(!a ? (LCD_CTRL_OUT_PORT&=~BIT7) : (LCD_CTRL_OUT_PORT|=BIT7))   // P2.7 is lcd RW pin
#define LCD_RW_DIR(a)	(!a ? (LCD_CTRL_DIR_PORT&=~BIT7) : (LCD_CTRL_DIR_PORT|=BIT7))   // P2.7 pin direction


/*----------------------------------------------------------
  CONFIG: BUZZER
------------------------------------------------------------*/    
#define BuzzerArrayPort	     P2OUT
#define BuzzerArrayPortSel   P2SEL 
#define BuzzerArrayPortDir   P2DIR

/*----------------------------------------------------------
  CONFIG: TIMER_B (PWM)
------------------------------------------------------------*/    
#define TimerPWM_Control  TBCTL 
#define TimerPWM_mode  	  TBCCTL1 
#define TimerPWM_Freq  	  TBCCR0 
#define TimerPWM_DC  	  TBCCR1 
#define TimerPWM_Clock 	  TBSSEL_2
#define TimerPWM_Clear 	  TBCLR

/*----------------------------------------------------------
  CONFIG: TIMER_A (DMA TRIGGER)
------------------------------------------------------------*/    
#define TimerCompare_Control  		TACTL 
#define TimerCompare_mode  	  	TACCTL0
#define TimerCompare_compareVal  	TACCR0
#define TimerCompare_Clock 	 	TASSEL_2
#define TimerCompare_Clear 	  	TACLR

/*----------------------------------------------------------
  CONFIG: DMA 
------------------------------------------------------------*/    

#define DMAtrigger		DMACTL0

#define DMAFreqSource  		DMA0SA 
#define DMAFreqDestination  	DMA0DA 
#define DMAFreqBlockSize	DMA0SZ
#define DMAFreqMode		DMA0CTL
#define DMAFreqSelect1		DMA0TSEL_1

#define DMADCsource  		DMA1SA 
#define DMADCdestination  	DMA1DA 
#define DMADCblockSize	        DMA1SZ
#define DMADCmode	        DMA1CTL
#define DMADCselect1		DMA1TSEL_1


/*----------------------------------------------------------
  CONFIG: KEYPAD   //CHECK
------------------------------------------------------------*/
#define KeypadArrayPortIn    P10IN 
#define KeypadArrayPortOut   P10OUT
#define KeypadArrayPortDir   P10DIR 

#define Keypad_IRQ_Port		 P2IN 
#define Keypad_IRQ_Pending	 P2IFG 
#define Keypad_IRQ_Enable	 P2IE
#define Keypad_IRQ_EdgeSel	 P2IES
#define Keypad_IRQ_Sel   	 P2SEL 
#define Keypad_IRQ_Dir   	 P2DIR 
      

/*----------------------------------------------------------
  INIT FUNCTION
------------------------------------------------------------*/  

extern void InitGPIO(void);


#endif