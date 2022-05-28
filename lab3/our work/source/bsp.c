#include  "../header/bsp.h"    // private library - BSP layer
//#include "msp430fg4619.h"
//-----------------------------------------------------------------------------  
//           GPIO congiguration
//-----------------------------------------------------------------------------
void GPIOconfig(void){
 // volatile unsigned int i; // in case of while loop usage
  
  WDTCTL = WDTHOLD | WDTPW;		// Stop WDT
   
  // LCDs 4-bit Array Port configuration
  LCD_DATA_SEL &= ~0xF0;            // GPIO capability
  LCD_DATA_DIR |= 0xF0;             // P1.4 -P1.7 OUTPUT MODE FOR LCD
  // P2.5-P2.7 CONTROL LCD OUTPUT CONFIG
  LCD_EN_SEL  &= ~0xE0;              // p2.5-p2.7 sel =0 I\O mode
  LCD_DIR     |= 0xE0;               // p2.5-p2.7 dir =1 output mode
  LCD_ENABLES &= ~0xE0;              // p2.5-p2.7 clear bits
  
  
  
  
  // PushButtons Setup
  PBsArrPortSel &= ~0x07;            //p1.2-p1.0 sel=0 I\O mode
  PBsArrPortDir &= ~0x07;            // /p1.2-p1.0 dir =0 input mode
  PBsArrIntEdgeSel |= 0x03;  	     // pull-up mode
  PBsArrIntEdgeSel &= ~0x04;         // pull-down mode
  PBsArrIntEn |= 0x07;                // interrupt enable
  PBsArrIntPend &= ~0xff;            // clear pending interrupts 
  
  //Keypad rows and coloumns
  KEY_PAD_PORT_SEL &= ~0xff;            //p10.0-p10.7 sel=0 I\O mode
  KEY_PAD_PORT_DIR |=  0x0f;            // p10.0-p10.3 dir = 1 output mode
  KEY_PAD_PORT_DIR &= ~0xf0;            // p10.4-p10.7 dir = 0 input mode
  KEY_PAD_PORT_OUT  =  0x00;
    
  //Keypad interrupt
  KEY_PAD_INT_SEL &= ~0x02;            //p2.1 sel=0 I\O mode
  KEY_PAD_INT_DIR &= ~0x02;             //p2.1 dir=0 input mode
  KEY_PAD_INT_IE  |=  0x02;            // interrupt enable for p2.1
  KEY_PAD_INT_PEN &= ~0xff;           // clear pending interupts
  KEY_PAD_INT_EDGE_SEL  |= 0x02;       // pull-up mode
    
  // Buzzer
   BUZZER_OUT &= ~0x04;           
   BUZZER_SEL |=  0x04; // *NOT* I/O mode, PWM of TA1.1 output.       
   BUZZER_DIR |=  0x04;           
  
  
  
  _BIS_SR(GIE);                     // enable interrupts globally
}                             
//------------------------------------------------------------------------------------- 
//            Timers congiguration 
//-------------------------------------------------------------------------------------
// Configurating TIMER_A and TIMER_B to trigger the DMA and create PWM for the buzzer 
void TIMERconfig(void){
        // TIMER_A2 config for DMA.
        TACCR0 = 0xB0A4;                      // When using smclk counting until 0xB0A4 for 345 ms.
        TACTL  = TASSEL_2 + TACLR + ID_3;     // SMCLK, clear counter , divide smclk by 3 to get 2^17 freq.
        // TIMER_B config for PWM.
        TBCTL     = TBSSEL_2 + TBCLR;  // SMCLK, CLEAR CLK.
        TBCCTL1   = OUTMOD_7;          // Set\reset mode of output unit, out is from p2.2.
}
