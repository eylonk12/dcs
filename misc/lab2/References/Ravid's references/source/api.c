#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer

//******************************************************************
// write a string of chars to the LCD
//******************************************************************
void lcd_puts(const char * s){
  
	while(*s)
		lcd_data(*s++);
}
//******************************************************************
// LCD Min - state 2
//******************************************************************
void lcd_disp_min(){
        lcd_clear();
        lcd_home();
        timer_a0_en_rst();
        cursor_off;
        lcd_puts("01:00");
}
//******************************************************************
//    freq_counter_init - state 1
//******************************************************************
void freq_counter_init(int cou){
  lcd_clear();
  lcd_home();
  cursor_off;
  lcd_puts("fin = ");
  TA1_Init_inter();
}
//******************************************************************
//    ADC_Init
//******************************************************************
void ADC_Init(){
     lcd_clear();
     ADC_en();
     ADC10CTL1 = INCH_3 + CONSEQ_2;               // A3, single channel 
      ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE + MSC; //
      ADC10AE0 |= 0x08;                         // P1.3 ADC10 option select
      ADC10CTL0 |= ADC10SC + ENC;
}
//******************************************************************
//    disable_all_states - Timer + DAC
//******************************************************************
void disable_all_states(){
    ADC10CTL0 &= ~(ENC+ADC10IE+ADC10SC);
    CCTL0 = ~CCIE;
    TA1CCTL2 &= ~CCIE;
    TA1CTL &= ~TAIE;
}