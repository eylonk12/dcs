#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer

//******************************************************************
// write a string of chars to the LCD
//******************************************************************
void lcd_puts(const char * s, int size){
	for(int i=0;i<size;i++)
		lcd_data(*s++);
}

 
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
      TA0CTL    = TASSEL_2 + MC_2 + TACLR + TAIE  ;  // SMCLK (1M), UP mode, CLEAR CLK, INTERRUPT ENABLE, divides frequency by 8 (2**17)
      TA0CCTL0  = CCIE + CM_1;   // Compare mode, interrupt enable, interrupt on rising edge
      CCR0      = 0x0100; // counts until 0xFFFF (2**16)
      second_counter = 0;
      duty_cycle = 1;
      __bis_SR_register(LPM0_bits + GIE);
      __no_operation();
      
}

void clear_configurations(void){
      // Timer A1.
      //TA1CCTL2 &= ~CCIE;
      //TA1CTL   &= ~TAIE;
      //TA1CTL   &= ~MC_3;
      // Timer A0.
      //TA0CCTL0 &= ~CCIE;
      //TA0CTL   &= ~TAIE;
      //TA0CTL   &= ~MC_3;
}
