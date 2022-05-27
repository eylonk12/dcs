#include  "../header/bsp.h"    // private library - BSP layer
#include "msp430fg4619.h"
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
  
  //port 10
  KEY_PAD_PORT_SEL &= ~0xff;            //p10.0-p10.7 sel=0 I\O mode
  KEY_PAD_PORT_DIR |=  0x0f;            // p10.0-p10.3 dir = 1 output mode
  KEY_PAD_PORT_DIR &= ~0xf0;            // p10.4-p10.7 dir = 0 input mode
    
  //port 2 config - keypad and buzzer 
  KEY_PAD_INT_SEL &= ~0x02;            //p2.1 sel=0 I\O mode
  KEY_PAD_INT_SEL |= ~0x04;            //p2.2 sel=1 sync timera0
  KEY_PAD_INT_DIR &= ~0x02;             //p2.1 dir=0 input mode
  KEY_PAD_INT_DIR |=  0x04;             //p2.2 dir=1 output mode
  KEY_PAD_INT_IE  |= 0x02 ;            // interrupt enable for p2.1
  KEY_PAD_INT_PEN &= ~0x02 ;           // clear pending interupts
  KEY_PAD_INT_EDGE_SEL  |= 0x02;       // pull-up mode
    

  
  _BIS_SR(GIE);                     // enable interrupts globally
}                             
//------------------------------------------------------------------------------------- 
//            Timers congiguration 
//-------------------------------------------------------------------------------------
void TIMERconfig(void){
  	TA0CTL    =  TASSEL_2 + MC_2 + TACLR /*+ TAIE */   ;  // SMCLK, UP mode, CLEAR CLK, INTERRUPT ENABLE, counts until 0xFFFF
        TA0CCTL0  = /*CCIE +*/ CM_1;   // Compare mode, interrupt enable, interrupt on rising edge
        TA0CCR0   = 0x03EA; // 1046.5hz
        TA0CCTL1  = OUTMOD_7;
        TA0CCR1   = 0x01F5; // counts until half of ccr0        
} 


//------------------------------------------------------------------------------------- 
//            ADC congiguration 
//-------------------------------------------------------------------------------------
void ADCconfig(void){
	TA0CTL =  TASSEL_2 + MC_2 + TACLR + TAIE + ID_3  ;  // SMCLK, UP mode, CLEAR CLK, INTERRUPT ENABLE, counts until 0xFFFF
        TA0CCTL0  = CCIE + CM_1;   // Compare mode, interrupt enable, interrupt on rising edge
        TA0CCR0      = 0xFFFF; // counts until 0xFFFF (2**16)
	
}              

/*
void timer_state_1_config(void){
      TA1CTL    = TASSEL_2 + MC_2 + TACLR + TAIE + ID_3  ;  // SMCLK, UP mode, CLEAR CLK, INTERRUPT ENABLE, counts until 0xFFFF
      TA1CCTL2  = CCIE + CAP + CM_1 + SCS;   // Capture mode, interrupt enable, interrupt on rising edge
      lcd_clear();
      capture_1       = 0;
      capture_2       = 0;
      ifg_capture_1   = 0;
      ifg_capture_2   = 0;
      ifg_counter     = 0;
      __bis_SR_register(LPM0_bits + GIE);
      __no_operation(); 
      
}

void timer_state_2_config(void){
      TA0CTL    = TASSEL_2 + MC_2 + TACLR + TAIE + ID_3  ;  // SMCLK (1M), UP mode, CLEAR CLK, INTERRUPT ENABLE, divides frequency by 8 (2**17)
      TA0CCTL0  = CCIE + CM_1;   // Compare mode, interrupt enable, interrupt on rising edge
      CCR0      = 0xFFFF; // counts until 0xFFFF (2**16)
      minutes_counter = 1;
      seconds_counter = 60;
      __bis_SR_register(LPM0_bits + GIE);
      __no_operation();
}

void timer_state_4_config(void){
      TA0CCTL0 = CCIE;                             // CCR0 interrupt enabled
      TA0CCR0 = 0x100;
      TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode    
      second_counter = 0;
      duty_cycle = 1;
      __bis_SR_register(LPM0_bits + GIE);
      __no_operation();
}
*/
