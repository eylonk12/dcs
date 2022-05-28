#include  <msp430xG46x.h> // IDE library
#include <msp430.h>
#include "../header/bsp.h"

void InitGPIO(void){
  
  WDTCTL = WDTHOLD | WDTPW;				// Stop WDT

/*----------------------------------------------------------
  CONFIG: PUSH BUTTONS
------------------------------------------------------------*/   									
  PBsArrayPortSel    &= ~(BIT0 + BIT1 + BIT2);          // P1.0 - P1.2 as GPIO (PB)
  PBsArrayPortDir    &= ~(BIT0 + BIT1 + BIT2);          // P1.0 - P1.2 as GPIO-input
  PBsArrayIntPending  = 0x00;                           // clear all interrupts pending
  PBsArrayIntEnable  |= (BIT0 + BIT1 + BIT2);           // enable P1.0 - P1.2 interrupts 
  PBsArrayIntEdgeSel |= (BIT0 + BIT1 + BIT2);           // P1.0 - P1.2 as falling-down edge select
  
/*----------------------------------------------------------
  CONFIG: BUZZER
------------------------------------------------------------*/    
  BuzzerArrayPortSel   |= BIT2;                        // P2.2 for TA1.1 output
  BuzzerArrayPortDir   |= BIT2;                        // P2.2 output
  BuzzerArrayPort      &= ~BIT2;	         
  
  /*----------------------------------------------------------
  CONFIG: TIMER A2 (TRIGGER FOR DMA)
------------------------------------------------------------*/ 
  TimerCompare_compareVal = 0xB0A3;                                      // With SMCLK and Timer A0 on UpMode we get 345 ms
  TimerCompare_Control = TimerCompare_Clock + TACLR + ID_3;             // SMCLK, divide SMCLK to become 2^17

/*----------------------------------------------------------
  CONFIG: TIMER B1 (PWM >> Buzzer)
------------------------------------------------------------*/
  // Configure TB to PWM mode              	            // The values of CCR0 and CCR1 will be set when this timer is used
  TimerPWM_mode = OUTMOD_7;                                 // CCR1 reset/set                                    
  TimerPWM_Control = TimerPWM_Clock  + TimerPWM_Clear;      // SMCLK;  

  
  /*----------------------------------------------------------
  CONFIG: LCD CONTROL
------------------------------------------------------------*/
  LCD_CTRL_OUT_PORT  &= ~BIT5; 							  // P2.5 is lcd enable pin
  LCD_CTRL_SEL_PORT  &= ~BIT5;  					          // P2.5 pin sel 
  LCD_CTRL_DIR_PORT  |= BIT5;  							  // P2.5 pin direction 

														  									
  LCD_CTRL_OUT_PORT  &= ~BIT6; 							  // P2.6 is lcd RS pin
  LCD_CTRL_SEL_PORT  &= ~BIT6;  					          // P2.6 pin sel 
  LCD_CTRL_DIR_PORT  |= BIT6;  							  // P2.6 pin direction  
														  									
  LCD_CTRL_OUT_PORT  &= ~BIT7; 							  // P2.7 is lcd RW pin
  LCD_CTRL_SEL_PORT  &= ~BIT7;  					          // P2.7 pin sel 
  LCD_CTRL_DIR_PORT  |= BIT7;  							  // P2.7 pin direction

  /*----------------------------------------------------------
  CONFIG: KEYPAD   //CHECK
------------------------------------------------------------*/    
  KeypadArrayPortDir |= (BIT0 + BIT1 + BIT2 + BIT3);     // Key Board ports, P10.0-P10.3 = Output, P10.4-P10.7 = Input
  KeypadArrayPortOut  = 0x00;
           
  Keypad_IRQ_Sel     &= ~(BIT1);          // P2.1 as GPIO (KeyPad)
  Keypad_IRQ_Dir     &= ~(BIT1);          // P2.1 as GPIO-input
  Keypad_IRQ_Pending  = 0x00;             // clear all interrupts pending
  Keypad_IRQ_Enable  |= (BIT1);           // enable P2.1 interrupts 
  Keypad_IRQ_EdgeSel |= (BIT1);           // P2.1 as falling-down edge select
	
}