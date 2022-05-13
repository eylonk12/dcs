#include  "../header/halGPIO.h"     // private library - HAL layer

//--------------------------------------------------------------------
//             System Configuration  
//--------------------------------------------------------------------
void sysConfig(void){ 
	GPIOconfig();
	TIMERconfig();
	ADCconfig();
}
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
//            Polling based Delay function
//---------------------------------------------------------------------
void delay(unsigned int t){  // t[msec]
	volatile unsigned int i;
        volatile unsigned int j;
        j=1;
        //j++;
        //__NOP();
	for(i=t; i>0; i--);
}
///
//---------------------------------------------------------------------
//          global variables
//---------------------------------------------------------------------
// State 1 :
volatile unsigned int Period;
volatile unsigned int number;
char per_0;
char per_1;
char per_2;
char per_3;
char per_4;
volatile unsigned int overflow_TA1_count;
volatile unsigned char Count,disp_Count;
volatile unsigned int REdge1, REdge2;
// State 2 :
int sec = 59;
char sec_0;
char sec_1;
// State 3 :
volatile float freq;
volatile unsigned int num_of_delay;
volatile int ADC_ON;
volatile int buzzer_out=0;
//---------------------------------------------------------------------
//           ADC enable
//---------------------------------------------------------------------
void ADC_en(){
  ADC_ON = 1;
  TA1CTL = TASSEL_2 + MC_1;
  TA1CCTL1 |= OUTMOD_3;
  
 // TA0CTL &= ~MC_3;
 // TA0CTL |= MC_1;
 //CCTL0 = CCIE;   
/////  CCR0 = 65535;
}
//---------------------------------------------------------------------
//           PWM_Buzzer
//---------------------------------------------------------------------
void PWM_Buzzer(unsigned int amplitude){
  // freq = amplitude*a + b   -- a = 1.955 , b=1000 (1k) 
  // N = (f/freq)*0.5
  freq = 1.955*amplitude+1000;
  num_of_delay = (1048576*(1/freq));
  TA1CCR0 = num_of_delay;
  TA1CCR1 = 0.5*num_of_delay;
}
//---------------------------------------------------------------------
//            state 1
//---------------------------------------------------------------------
void TA1_Init_inter(){
  TA1CTL = TASSEL_2 + MC_2 + TACLR;
  TA1CCTL2 = CAP + CM_1 + SCS + CCIS_0;
  ADC_ON = 0;
  overflow_TA1_count = 0;
  //TA1_count = 0;
    // Variable Initialization
  Count = 0x0;
  disp_Count = 0x0;
  TA1CTL |= TAIE;
  TA1CCTL2 |= CCIE;        
}
void freq_conter(){
   // Rising Edge was captured    
  if (!Count)
  {
    REdge1 = TA1CCR2;     // TA1CCR2(to)
    Count++;         
  }     
  else
  {          
    REdge2 = TA1CCR2;     // TA1CCR2(t1)   
    Count = 0x0;
    number = 0xffff*(overflow_TA1_count-1) + REdge2 + (0xffff-REdge1);             // Calculate Period

    Period = (1048576)/ number; // 2^20 =1048576 
    //lcd_puts('0'+Period);
    overflow_TA1_count = 0;
    per_0 = '0' + Period % 10 ;
    per_1 = '0' + (Period / 10)%10;
    per_2 = '0' + (Period / 100)%10;
    per_3 = '0' + (Period / 1000)%10;
    per_4 = '0' + (Period / 10000)%10;
    if (disp_Count==3){
      lcd_data(per_4);
      lcd_data(per_3);
      lcd_data(per_2);
      lcd_data(per_1);
      lcd_data(per_0);
      lcd_puts("Hz");
      lcd_cursor_left();
      lcd_cursor_left();
      lcd_cursor_left();
      lcd_cursor_left();
      lcd_cursor_left();
      lcd_cursor_left();
      lcd_cursor_left();
      disp_Count=0;
    }
    else{
      disp_Count++;
    }
  }      
}
//---------------------------------------------------------------------
//            Timer_A0 - interrupt enabled & reset of the counter
//---------------------------------------------------------------------
void timer_a0_en_rst(){ 
            TA0CTL |= MC_3 + ID_3;
            CCTL0 = CCIE;   
            CCR0 = 65535;
            ADC_ON = 0;
}
//---------------------------------------------------------------------
//            Timer_A1 - interrupt enabled & reset of the counter
//---------------------------------------------------------------------
void timer_a1_en_rst(){ 
      TA0CCTL0 = CCIE;                  // CCR0 interrupt enabled
      TA0CTL =  TACLR;                  //  reset of the counter
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
//           TimerA0 Interrupt Service Rotine
//*********************************************************************
// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{
 // if (ADC_ON==0){
    if(sec>=0){
      lcd_home();
      lcd_puts("00:");
      sec_0 = '0' +sec % 10 ;
      sec_1 = '0' + sec / 10 ;
      lcd_data(sec_1);
      lcd_data(sec_0);
      sec = sec-1;
    }
     else {
       CCTL0 = ~CCIE;
       lcd_clear();
       sec=59;
      }
 // }
 // else{
  //  if (buzzer_out){
  ///      PWM_OUT &= ~0x04;
  //      buzzer_out=0;
 //   }
  //  else{
   //     PWM_OUT |= 0x04;
   //     buzzer_out++;
  //  }
 // }    
}
//*********************************************************************
//*********************************************************************
//*********************************************************************
//           TA1_A1 Interrupt vector
//*********************************************************************
#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer_A1 (void)
{
 switch(__even_in_range(TA1IV,0x0A))
  {  
    case  TA1IV_NONE:
      break;              // Vector  0:  No interrupt 
    case  TA1IV_TACCR1:                   
      break;              // Vector  2:  TACCR1 CCIFG 
    case  TA1IV_TACCR2:                   // Vector  4:  TACCR2 CCIFG 
      if (TA1CCTL2 & CCI)                 // Capture Input Pin Status 
      {    
       // TA1_count++;
        freq_conter();
      }    
      break;    
    case TA0IV_6: break;                  // Vector  6:  Reserved CCIFG
    case TA0IV_8: break;                  // Vector  8:  Reserved CCIFG
    case TA1IV_TAIFG:    {                 // Vector 10:  TAIFG
      overflow_TA1_count++;
      break;          
      }    
      default: 	break;
  }
}
//*********************************************************************
//           ADC10 interrupt service routine
//*********************************************************************
volatile int MEM_read=0;
volatile int MEM_4[4];
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  if(MEM_read==4){
    PWM_Buzzer(((MEM_4[0]+MEM_4[1]+MEM_4[2]+MEM_4[3])/4)); //
    MEM_4[0]= MEM_4[2];
    MEM_4[1]= MEM_4[3];
    MEM_4[2]= ADC10MEM;
    MEM_read=3;
  }
  else{
    MEM_4[MEM_read]=ADC10MEM;
    MEM_read++;
  }
  if(PBsArrIntPend & PB0){
    ADC10CTL0 &= ~(ENC+ADC10IE+ADC10SC);
    TA1CCTL1 = OUTMOD_5;
 //  state = state1;
  // PBsArrIntPend &= ~PB0;
 //  LPM0_EXIT;
  }
  else if(PBsArrIntPend & PB1){
    ADC10CTL0 &= ~(ENC+ADC10IE+ADC10SC);
    TA1CCTL1 = OUTMOD_5;
   // state = state2;
   // sec=59;
   // PBsArrIntPend &= ~PB1; 
  //  LPM0_EXIT;
  }
// if (ADC10MEM < 0x3f0)                     // ADC10MEM = A1 > 0.5V? ---0x155
  //  P2OUT &= ~0x04;                         // Clear P1.0 LED off
//  else
 // P2OUT |= 0x04;                          // Set P1.0 LED on
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
	  state = state1;
	  PBsArrIntPend &= ~PB0;
        }
        else if(PBsArrIntPend & PB1){
	  state = state2;
          sec=59;
	  PBsArrIntPend &= ~PB1; 
        }
	else if(PBsArrIntPend & PB2){ 
	  state = state3;
	  PBsArrIntPend &= ~PB2;
        }
        else if(PBsArrIntPend & PB3){ 
	  state = state0;
	  PBsArrIntPend &= ~PB3;
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
 