#include  "../header/halGPIO.h"     // private library - HAL layer
// Variables for state 1.
int enter_to_state_1;
unsigned int capture_1;
unsigned int capture_2;
unsigned int ifg_capture_1;
unsigned int ifg_capture_2;
unsigned int ifg_counter;
// Variables for state 2.
unsigned int seconds_counter;
unsigned int minutes_counter;
int enter_to_state_2;
int enter_to_state_4;
int state_2_interrupt_occured;
int state_2_interrupts_count = 0;
// Variables for state 4.
unsigned int second_counter;
unsigned int duty_cycle;

//--------------------------------------------------------------------
//             System Configuration  
//--------------------------------------------------------------------
void sysConfig(void){ 
	GPIOconfig();
	TIMERconfig();
	ADCconfig();
}


/* - - - - - - - LCD interface - - - - - - - - -
 *	This code will interface to a standard LCD controller
 *  It uses it in 4 or 8 bit mode.
 */

//******************************************************************
// send a command to the LCD
//******************************************************************
void lcd_cmd(unsigned char c){
  
	LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

	if (LCD_MODE == FOURBIT_MODE)
	{
		LCD_DATA_WRITE &= ~OUTPUT_DATA;// clear bits before new write
                LCD_DATA_WRITE |= ((c >> 4) & 0x0F) << LCD_DATA_OFFSET;
		lcd_strobe();
                LCD_DATA_WRITE &= ~OUTPUT_DATA;
    		LCD_DATA_WRITE |= (c & (0x0F)) << LCD_DATA_OFFSET;
		lcd_strobe();
	}
	else
	{
		LCD_DATA_WRITE = c;
		lcd_strobe();
	}
}
//******************************************************************
// send data to the LCD
//******************************************************************
void lcd_data(unsigned char c){
        
	LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

	LCD_DATA_WRITE &= ~OUTPUT_DATA;       
	LCD_RS(1);
	if (LCD_MODE == FOURBIT_MODE)
	{
    		LCD_DATA_WRITE &= ~OUTPUT_DATA;
                LCD_DATA_WRITE |= ((c >> 4) & 0x0F) << LCD_DATA_OFFSET;  
		lcd_strobe();		
                LCD_DATA_WRITE &= (0xF0 << LCD_DATA_OFFSET) | (0xF0 >> 8 - LCD_DATA_OFFSET);
                LCD_DATA_WRITE &= ~OUTPUT_DATA;
		LCD_DATA_WRITE |= (c & 0x0F) << LCD_DATA_OFFSET; 
		lcd_strobe();
	}
	else
	{
		LCD_DATA_WRITE = c;
		lcd_strobe();
	}
          
	LCD_RS(0);   
}

//******************************************************************
// initialize the LCD
//******************************************************************
void lcd_init(){
  
	char init_value;

	if (LCD_MODE == FOURBIT_MODE) init_value = 0x3 << LCD_DATA_OFFSET;
        else init_value = 0x3F;
	
	LCD_RS_DIR(OUTPUT_PIN);
	LCD_EN_DIR(OUTPUT_PIN);
	LCD_RW_DIR(OUTPUT_PIN);
        LCD_DATA_DIR |= OUTPUT_DATA;
        LCD_RS(0);
	LCD_EN(0);
	LCD_RW(0);
        
	DelayMs(15);
        LCD_DATA_WRITE &= ~OUTPUT_DATA;
	LCD_DATA_WRITE |= init_value;
	lcd_strobe();
	DelayMs(5);
        LCD_DATA_WRITE &= ~OUTPUT_DATA;
	LCD_DATA_WRITE |= init_value;
	lcd_strobe();
	DelayUs(200);
        LCD_DATA_WRITE &= ~OUTPUT_DATA;
	LCD_DATA_WRITE |= init_value;
	lcd_strobe();
	
	if (LCD_MODE == FOURBIT_MODE){
		LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h
                LCD_DATA_WRITE &= ~OUTPUT_DATA;
		LCD_DATA_WRITE |= 0x2 << LCD_DATA_OFFSET; // Set 4-bit mode
		lcd_strobe();
		lcd_cmd(0x28); // Function Set
	}
        else lcd_cmd(0x3C); // 8bit,two lines,5x10 dots 
	
	lcd_cmd(0xF); //Display On, Cursor On, Cursor Blink
	lcd_cmd(0x1); //Display Clear
	lcd_cmd(0x6); //Entry Mode
	lcd_cmd(0x80); //Initialize DDRAM address to zero
}
//******************************************************************
// Delay usec functions
//******************************************************************
void DelayUs(unsigned int cnt){
  
	unsigned char i;
        for(i=cnt ; i>0 ; i--) asm("nop"); // tha command asm("nop") takes raphly 1usec
	
}
//******************************************************************
// Delay msec functions
//******************************************************************
void DelayMs(unsigned int cnt){
  
	unsigned char i;
        for(i=cnt ; i>0 ; i--) DelayUs(1000); // tha command asm("nop") takes raphly 1usec
	
}
//******************************************************************
// lcd strobe functions
//******************************************************************
void lcd_strobe(){
  LCD_EN(1);
  asm("nop");
  asm("nop");
  LCD_EN(0);
}


//---------------------------------------------------------------------
//            timer a0 reset and enable for state 1
//---------------------------------------------------------------------
void timer_a0_rst_ena(){
  CCTL0 = CCIE;
  CCR0 = 65535;
}
//---------------------------------------------------------------------
//            timer a1 reset and enable for state 2
//---------------------------------------------------------------------
void timer_a1_rst_ena(){ 
      TACCTL1 = CCIE + CAP;                  //  interrupt enabled
      TACTL =  TACLR;                  //  reset of the counteø
}
//---------------------------------------------------------------------
//            Polling based Delay function
//---------------------------------------------------------------------
void delay(unsigned int t){  // t[msec]
	volatile unsigned int i;
	
	for(i=t; i>0; i--);
}
//---------------------------------------------------------------------
//            Enter from LPM0 mode
//---------------------------------------------------------------------
void enterLPM(unsigned char LPM_level){
	if (LPM_level == 0x00) 
	  _BIS_SR(LPM0_bits);     /* Enter Low Power Mode 0 */
        else if(LPM_level == 0x01) 
	  _BIS_SR(LPM1_bits);     /* Enter Low Power Mode 1 */
        else if(LPM_level == 0x02) 
	  _BIS_SR(LPM2_bits);     /* Enter Low Power Mode 2 */
	else if(LPM_level == 0x03) 
	  _BIS_SR(LPM3_bits);     /* Enter Low Power Mode 3 */
        else if(LPM_level == 0x04) 
	  _BIS_SR(LPM4_bits);     /* Enter Low Power Mode 4 */
}
//---------------------------------------------------------------------
//            Enable interrupts
//---------------------------------------------------------------------
void enable_interrupts(){
  _BIS_SR(GIE);
}
//---------------------------------------------------------------------
//            Disable interrupts
//---------------------------------------------------------------------
void disable_interrupts(){
  _BIC_SR(GIE);
}
//*********************************************************************
//            TIMERA1 Interrupt Service Rotine
//*********************************************************************

#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer_A1(void){
    switch(__even_in_range(TA1IV, 0x0A)){
        case TA1IV_NONE:
            break;                 // Vector  0:  No interrupt
        case TA1IV_TACCR1:         // Vector  2:  TACCR1 CCIFG
            
            break;
        case TA1IV_TACCR2:         // Vector  4:  TACCR2 CCIFG
           if(TA1CCTL2 & CCI)      // Capture Input Pin Status
            {
              // Rising Edge was captured
              capture_1 = capture_2;    
              capture_2 = TA1CCR2;
              ifg_capture_1 = ifg_capture_2;    
              ifg_capture_2 = ifg_counter;
              //__bic_SR_register_on_exit(LPM0_bits + GIE);  // Exit LPM0 on return to main
            }
            break;
        case TA1IV_TAIFG:
            ifg_counter++;
            break;                                               // Vector 10:  TAIFG
        default:
            break;
    }
}


//*********************************************************************
//            TIMERA0 Interrupt Service Rotine
//*********************************************************************

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
     if (state == state4) {
        if (second_counter == 4096){
          // Counted a second.
          duty_cycle = duty_cycle%3 + 1;
          second_counter=0;
        }
//        if (second_counter < ((4096*duty_cycle)/4)){
        if (second_counter%4 < duty_cycle){
            // Current value is under duty cycle -> output=1.
            PWM_OUT |= 0x04;
        } else {
            PWM_OUT &= ~0x04;                    
        }
        second_counter ++;
     }
    switch(__even_in_range(TA0IV, 0x0A)){
      /*  case TA0IV_NONE:
            break;                 // Vector  0:  No interrupt
        case TA0IV_TACCR1:         // Vector  2:  TACCR1 CCIFG
            break;
        case TA0IV_TACCR2:         // Vector  4:  TACCR2 CCIFG
           if(TA0CCTL2 & CCI)      // Capture Input Pin Status
            break;]*/
        case TA0IV_TAIFG:
             {
               if (state == state2){ 
                 if (state_2_interrupts_count == 0){  
                      state_2_interrupt_occured = 1;
                    if (minutes_counter == 0){
                      seconds_counter--;
                        }
                    if (minutes_counter == 1){
                      minutes_counter = 0;
                    } 
                    state_2_interrupts_count = 1;
                 } else {
                    state_2_interrupts_count = 0;
                 } 
               }
            }
            break;                                               // Vector 10:  TAIFG
        default:
            break;
    }
}

//*********************************************************************
//            Port1 Interrupt Service Rotine
//*********************************************************************
#pragma vector=PORT1_VECTOR
  __interrupt void PBs_handler(void){
   
	delay(debounceVal);
//---------------------------------------------------------------------
//            selector of transition between states
//---------------------------------------------------------------------
	if(PBsArrIntPend & PB0){
          clear_configurations();
	  state = state1;
          enter_to_state_1 = 1;
	  PBsArrIntPend &= ~PB0;
        }
        else if(PBsArrIntPend & PB1){
          clear_configurations();
          enter_to_state_2 = 1;
          state_2_interrupt_occured = 1;
	  state = state2;
	  PBsArrIntPend &= ~PB1; 
        }
	else if(PBsArrIntPend & PB2){ 
          clear_configurations();
	  // state = state0;
	  PBsArrIntPend &= ~PB2;
        }





//---------------------------------------------------------------------
//            Exit from a given LPM 
//---------------------------------------------------------------------	
        switch(lpm_mode){
		case mode0:
		 LPM0_EXIT; // must be called from ISR only
		 break;
		 
		case mode1:
		 LPM1_EXIT; // must be called from ISR only
		 break;
		 
		case mode2:
		 LPM2_EXIT; // must be called from ISR only
		 break;
                 
                case mode3:
		 LPM3_EXIT; // must be called from ISR only
		 break;
                 
                case mode4:
		 LPM4_EXIT; // must be called from ISR only
		 break;
	}
  }

//*********************************************************************
//            Port2 Interrupt Service Rotine
//*********************************************************************
#pragma vector=PORT2_VECTOR
  __interrupt void PB3_handler(void){
   
	delay(debounceVal);
//---------------------------------------------------------------------
//            selector of transition between states
//---------------------------------------------------------------------
	 if(PWM_INT_PEN & PB3){ 
          clear_configurations();
          enter_to_state_4 = 1;
	  state = state4;
	  PWM_INT_PEN &= ~PB3;
        }
  
        
//---------------------------------------------------------------------
//            Exit from a given LPM 
//---------------------------------------------------------------------	
        switch(lpm_mode){
		case mode0:
		 LPM0_EXIT; // must be called from ISR only
		 break;
		 
		case mode1:
		 LPM1_EXIT; // must be called from ISR only
		 break;
		 
		case mode2:
		 LPM2_EXIT; // must be called from ISR only
		 break;
                 
                case mode3:
		 LPM3_EXIT; // must be called from ISR only
		 break;
                 
                case mode4:
		 LPM4_EXIT; // must be called from ISR only
		 break;
	}
        
}
 




