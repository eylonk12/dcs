#include  <msp430xG46x.h> // IDE library
#include <msp430.h>

#include <stdio.h>

#include "../header/hal.h"
#include "../header/bsp.h"


/* - - - - - - - LCD interface - - - - - - - - -
*	This code will interface to a standard LCD controller
*  It uses it in 4 or 8 bit mode.
*/

//******************************************************************
//        send a command to the LCD
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
//        send data to the LCD
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
//        write a string of chars to the LCD
//******************************************************************
void lcd_puts(const char *s){
  
  while(*s)
    lcd_data(*s++);
}
//******************************************************************
//         initialize the LCD
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
//         Delay usec functions
//******************************************************************
void DelayUs(unsigned int cnt){
  
  unsigned char i;
  for(i=cnt ; i>0 ; i--) asm("nop"); // tha command asm("nop") takes raphly 1usec
  
}
//******************************************************************
//         Delay msec functions
//******************************************************************
void DelayMs(unsigned int cnt){
  
  unsigned char i;
  for(i=cnt ; i>0 ; i--) DelayUs(1000); // tha command asm("nop") takes raphly 1usec
  
}
//******************************************************************
//         lcd strobe functions
//******************************************************************
void lcd_strobe(){
  
  LCD_EN(1);
  asm("nop");
  asm("nop");
  LCD_EN(0);
  
} 
//******************************************************************
//          TIMERA: TIMER FUNCTIONS
//******************************************************************
void Disable_TimerA_345msec(void){
  TimerCompare_mode &= ~ CCIE;                                // CCR2 of Timer A interrupt disabled
  TimerCompare_Control = MC_0 + TimerCompare_Clear;           // Stop mode - Timer is halted
}
//------------------------------------------------------------------
void Enable_TimerA_345msec(void){
  //TimerCompare_mode |= CCIE;                                   // CCR2 of Timer A interrupt enabled
  TimerCompare_Control = TimerCompare_Clock + MC_1 + ID_3 + TAIE;    // SMCLK, up mode, divide SMCLK to become 2^17
}

//******************************************************************
//           TIMERB: TIMER FUNCTIONS
//******************************************************************
void Disable_TimerB_out_PWM(void){

  TimerPWM_Freq = 0;
  TimerPWM_DC = 0;
  TimerPWM_Control &= ~(TimerPWM_Clock + MC_1);    // Stop Timer
 // TimerPWM_mode &= ~OUTMOD_7;
}
//------------------------------------------------------------------
void Enable_TimerB_out_PWM(void){
	
  TimerPWM_Freq = Record_Periods[KB];
  TimerPWM_DC = TimerPWM_Freq / 2;
  TimerPWM_mode = OUTMOD_7;                    // Reset/set
  TimerPWM_Control = TimerPWM_Clock + MC_1;    // SMCLK, up mode 
}

//******************************************************************
//         DMA FUNCTIONS
//******************************************************************

void set_DMA_TB_connection(void){
  
  //Channel 0: Frequency
  DMAFreqSource = (int)song_choice_freq;                   // Source block address
  DMAFreqDestination = (int)&TimerPWM_Freq;                // Destination block address: TBCCR0 (clock period of TimerB outmod)
  DMAFreqBlockSize = 0x020;                                // Block size 32 

  
  //Channel 1: DC
  DMADCsource = (int)song_choice_dc;                       // Source block address
  DMADCdestination = (int)&TimerPWM_DC;                    // Destination block address: TBCCR0 (clock period of TimerB outmod)
  DMADCblockSize = song_length;                            // Block size 32 
  
  DMAtrigger = DMAFreqSelect1 + DMADCselect1;              // TACCR2 trigger

  DMADCmode = DMADT_4 + DMASRCINCR_3 + DMASWDW + DMAEN;    // word-word, Block transfer, inc src, DMA enable
  DMAFreqMode = DMADT_4 + DMASRCINCR_3 + DMASWDW + DMAEN;  // word-word, Block transfer, inc src, DMA enable
  
  TimerPWM_mode = OUTMOD_7;                    // Reset/set
  TimerPWM_Control = TimerPWM_Clock + MC_1;    // SMCLK, up mode 
  
  TimerCompare_Control = TimerCompare_Clock + MC_1 + ID_3 + CCIE;	//Enable timer A for DMA trigger
  TACCTL2 &= ~CCIE;
}

void Disable_DMA(void){
  
    DMADCmode &= ~DMAEN;                         // DMA disable
    DMAFreqMode &= ~DMAEN;                         // DMA disable
}
//******************************************************************
//       Choose Song
//******************************************************************
void menu_choose_song(void){
	
	char line1[12] = {'C','h','o','o','s','e',' ','s','o','n','g',':'};
	char line2[13] = {'P','B','2',' ','t','o',' ','s','c','r','o','l','l'};	
	char line3[13] = {'1',' ','H','a','d','o','d',' ','M','o','s','h','e'};
	char line4[15] = {'2',' ','H','a','o','t','o',' ','S','h','e','l','a','n','o'};
	char line5[15] = {'3',' ','Y','a','d','a','i','m',' ','L','e','m','a','l','a'};
	char line6[15] = {'4',' ','R','e','c','o','r','d','e','r',' ','s','o','n','g'};
	
	while (screen < 4)	{
		switch(screen) {
		case 0:
		  lcd_clear();                                 // Clear lcd
		  lcd_puts(line1);	                       // print label on LCD
		  lcd_new_line;   
		  lcd_puts(line2);	                       // print label on LCD
		  __bis_SR_register(LPM0_bits + GIE);          // Wait for user to choose 	
		  break;		
		case 1:
		  lcd_clear();                                 // Clear lcd
		  lcd_puts(line3);	                       // print label on LCD
		  lcd_new_line;   
		  lcd_puts(line4);	                       // print label on LCD
		  __bis_SR_register(LPM0_bits + GIE);          // Wait for user to choose 	
		  break;
		case 2:
		  lcd_clear();                                 // Clear lcd
		  lcd_puts(line5);	                       // print label on LCD
		  lcd_new_line;   
		  lcd_puts(line6);	                       // print label on LCD
		  __bis_SR_register(LPM0_bits + GIE);          // Wait for user to choose 	
		  break;				
		} 
	}
	
	switch (KB) {					       // save chosen song's address in global variable
		case 1: 
                  song_choice_freq = song1_freq;
                  song_choice_dc = song1_dc;
                  song_length = 55;
                  break;
		case 2: 
                  song_choice_freq = song2_freq;
                  song_choice_dc = song2_dc;
                  song_length = 48;
                  break;
		case 3: 
                  song_choice_freq = song3_freq;
                  song_choice_dc = song3_dc;
                  song_length = 41;
                  break;
		case 4: 
                  song_choice_freq = Recorder_song_freq;
                  song_choice_dc = Recorder_song_dc;
                  song_length = 32;
                  break;
		}
	screen = 0; // unnecessary. 
}		 

//******************************************************************
//           RECORD FUNCTIONS
//****************************************************************** 
void clear_recording(void){
  volatile unsigned int i;
  for(i = 0 ; i < 32 ; i++){
    Recorder_song_freq[i] = 0;    // Delete previous recordings
    Recorder_song_dc[i] = 0;
  }
  }
//------------------------------------------------------------------
void print_recording_screen(void){
  
  lcd_clear();                           // clear lcd
  lcd_puts(Const_LCD_label_1);	 // print initial label 1 on LCD
  lcd_new_line;   
  lcd_puts(Const_LCD_label_2);	 // print initial label 2 on LCD
  
}
  
//******************************************************************
//    Port1: P1.0-P1.2 Interrupt Service Routine (Push Buttons)
//******************************************************************
#pragma vector=PORT1_VECTOR
  __interrupt void PORT1_ISR (void){
    
    volatile unsigned int i;
    if (PBsArrayIntPending & 0x01){                       // case of PB P1.0             
          State = 1;					  // move to state 1
          Disable_TimerB_out_PWM();
		  screen = 4;
          _BIC_SR_IRQ(LPM0_bits);                         // exit LPM3 bits from 0(SR) (exit sleep mode)
      
     }else if (PBsArrayIntPending & 0x02){                // case of PB P1.1
        State = 2;					  // move to state 2
        screen = 0;
	_BIC_SR_IRQ(LPM0_bits);       	                  // exit LPM3 bits from 0(SR) (exit sleep mode)
        
    }else if (PBsArrayIntPending & 0x04){                  // case of PB P1.2
		if (screen == 2){ 
			screen = 0;	
		} else {
			screen ++; 
		}
	_BIC_SR_IRQ(LPM0_bits);       	                   // exit LPM3 bits from 0(SR) (exit sleep mode)
    }
    DelayUs(1000);                                         // delay, button debounce    
    PBsArrayIntPending &= ~0x0F;                           // manual clear of P1.0 - P1.3 interrupt flags 
  }
 
//******************************************************************
//       Port2: P2.0 Interrupt Service Routine (KEYPAD)
//******************************************************************
#pragma vector=PORT2_VECTOR
  __interrupt void PORT2_ISR (void){
    
    Keypad_IRQ_Pending &= ~BIT1;                         // manual clear of P2.1 interrupt flags 

    if (State != 0) {                                    // If the KeyPad was pressed by accident (Not for States 1 and 2)

      KeypadArrayPortOut = 0x0E;
      if      ((KeypadArrayPortIn & 0x10) == 0)   KB = 13;
      else if ((KeypadArrayPortIn & 0x20) == 0)   KB = 14;
      else if ((KeypadArrayPortIn & 0x40) == 0)   KB = 0;
      else if ((KeypadArrayPortIn & 0x80) == 0)   KB = 15;
        
      KeypadArrayPortOut = 0x0D;
      if      ((KeypadArrayPortIn & 0x10) == 0)   KB = 12;
      else if ((KeypadArrayPortIn & 0x20) == 0)   KB = 9;
      else if ((KeypadArrayPortIn & 0x40) == 0)   KB = 8;
      else if ((KeypadArrayPortIn & 0x80) == 0)   KB = 7;
        
      KeypadArrayPortOut = 0x0B;
      if      ((KeypadArrayPortIn & 0x10) == 0)   KB = 11;
      else if ((KeypadArrayPortIn & 0x20) == 0)   KB = 6;
      else if ((KeypadArrayPortIn & 0x40) == 0)   KB = 5;
      else if ((KeypadArrayPortIn & 0x80) == 0)   KB = 4;

      KeypadArrayPortOut = 0x07;
      
      if      ((KeypadArrayPortIn & 0x10) == 0)   KB = 10;
      else if ((KeypadArrayPortIn & 0x20) == 0)   KB = 3;
      else if ((KeypadArrayPortIn & 0x40) == 0)   KB = 2;
      else if ((KeypadArrayPortIn & 0x80) == 0)   KB = 1;
 

      screen = 4;	
							  // Exit scrren show to save chosen song
      __bic_SR_register_on_exit(LPM0_bits + GIE);         // Exit LPM0
    }
     DelayMs(250);
    KeypadArrayPortOut  = 0x00;                           // manual clear of Key Board Rows
    
  }
 
//******************************************************************
//       Timer A Interrupt Routine
//******************************************************************

#pragma vector = TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
  Disable_TimerB_out_PWM();
  Disable_TimerA_345msec();

}

