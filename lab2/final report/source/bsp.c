#include  "../header/bsp.h"    // private library - BSP layer
#include "msp430g2553.h"
//-----------------------------------------------------------------------------  
//           GPIO congiguration
//-----------------------------------------------------------------------------
void GPIOconfig(void){
 // volatile unsigned int i; // in case of while loop usage
  
  WDTCTL = WDTHOLD | WDTPW;		// Stop WDT
   
  // LCDs 4-bit Array Port configuration
  LCDsArrPortSel &= ~0xF0;            // GPIO capability
  LCDsArrPortDir |= 0xF0;             // P1.4 -P1.7 OUTPUT MODE FOR LCD
  //LCDsArrPort = 0x00;				  // clear all LCDs
  // P2.5-P2.7 CONTROL LCD OUTPUT CONFIG
  LCD_EN_SEL &= ~0xE0;   
  
  
  // PushButtons Setup
  PBsArrPortSel &= ~0x07;            //p1.2-p1.0 sel=0 I\O mode
  PBsArrPortDir &= ~0x07;            // /p1.2-p1.0 dir =0 input mode
  PBsArrIntEdgeSel |= 0x03;  	     // pull-up mode
  PBsArrIntEdgeSel &= ~0x04;         // pull-down mode
  PBsArrIntEn |= 0x07;                // interrupt enable
  PBsArrIntPend &= ~0x0F;            // clear pending interrupts 
  

  // port2 config
  GEN_SEL |=  0x10;    // p2.4 sel=1 I\O mode 
  GEN_DIR &= ~0x10;    // p2.4 dir =0 input mode
 // GEN_IE  |=  0x10;
 
  // pwm out port 2 config
  PWM_SEL  &= ~0x05;                   // p2.2 and p2.0 sel=0 I\O mode
  PWM_DIR  |=  0x04;                    //p2.2 dir =1 output mode
  PWM_DIR  &= ~0x01;                    //p2.0 dir =0 input mode
  PWM_INT_PEN &= ~0x01; 
  PWM_INT_EN |= 0x01;
  PWM_EDGE_SEL |= 0x01;
  
  _BIS_SR(GIE);                     // enable interrupts globally
}                             
//------------------------------------------------------------------------------------- 
//            Timers congiguration 
//-------------------------------------------------------------------------------------
void TIMERconfig(void){
  /*
	TA1CTL = TASSEL_2 + MC_2 + TACLR + TAIE +ID_3 ;  // SMCLK, UP mode, CLEAR CLK, INTERRUPT ENABLE
        TA1CCTL1 = CCIE;                                 // 
        TA1CCR1 = 0xffff;
        __bis_SR_register(LPM0_bits + GIE);
        __no_operation();
  */
} 


//------------------------------------------------------------------------------------- 
//            ADC congiguration 
//-------------------------------------------------------------------------------------
void ADCconfig(void){
	
	//write here ADC congiguration code
}              

   

