#include  "../header/bsp.h"    // private library - BSP layer

//-----------------------------------------------------------------------------  
//           GPIO configuration
//-----------------------------------------------------------------------------
void GPIOconfig(void){
 // volatile unsigned int i; // in case of while loop usage
  
  WDTCTL = WDTHOLD | WDTPW;		// Stop WDT
   
  // P1- LCD 4-bit Array Port configuration
  LCDsArrPortSel &= ~0xF0;            // p1.7-p1.4 SEL=0 => I/O mode
  LCDsArrPortDir |= 0xF0;             // p1.7-p1.4 DIR=1 => Output mode
  //LCDsArrPort &= 0x0F;		      // clear all 4 bits of the LCD

  // P2 - PushButtons Setup & Output
  PBsArrPortSel &= ~0x07;          // p1.2-p1.0 SEL=0 => I/O mode
  PBsArrPortDir &= ~0x07;          // p1.2-p1.0 DIR=0 => Input mode
  PBsArrIntEdgeSel |= 0x03;  	   // pull-up mode
  PBsArrIntEdgeSel &= ~0x04;       // pull-down mode
  PBsArrIntEn |= 0x07;             // Enable interrupts 
  PBsArrIntPend &= ~0x07;          // clear pending interrupts 
  
  // P2.5-2.7 - Output   
  LCD_EN_SEL &= ~0xE0;            // p2.5-p2.7 SEL=0 => I/O mode
    
  // P2.4 - Output   
  GEN_SEL |= 0x10;               // p2.4 SEL=1 => I/O mode
  GEN_DIR &= ~0x10;               // p2.4 DIR=0 => Input mode
  
  // P2.2 - PWM Output
  PWM_SEL |= 0x04;               // p2.2 SEL=1 => I/O mode
  PWM_DIR |= 0x04;               // p2.2 DIR=1 => Output mode

  _BIS_SR(GIE);                   // enable interrupts globally
}                             
//------------------------------------------------------------------------------------- 
//            Timers configuration 
//-------------------------------------------------------------------------------------
void TIMERconfig(void){
  // State 1
  TA1CTL |= TASSEL_2 + MC_2 + TACLR;
  TA1CCTL2 = CAP + CM_1 + SCS + CCIS_0;
  // State 2
  TA0CTL = TASSEL_2; // state 2 - 1 s. -- TA0CTL = TASSEL_2 + MC_3 + ID_3; 
} 
//------------------------------------------------------------------------------------- 
//            ADC configuration 
//-------------------------------------------------------------------------------------
void ADCconfig(void){
	
}              

           
             

 
             
             
            
  

