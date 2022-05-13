#include  "../header/halGPIO.h"     // private library - HAL layer

//-------------------------------------------------------------------
//             Global Variables
//-------------------------------------------------------------------

//int flagStopWatch = 0;
  int time = 60;

//--------------------------------------------------------------------
//             System Configuration  
//--------------------------------------------------------------------
void sysConfig(void){ 
	GPIOconfig();
	TIMERconfig();
	ADCconfig();
}
//--------------------------------------------------------------------
// 				Print Byte to 8-bit LEDs array 
//--------------------------------------------------------------------
void print2LEDs(unsigned char ch){
	LEDsArrPort = ch;
}    
//--------------------------------------------------------------------
//				Clear 8-bit LEDs array 
//--------------------------------------------------------------------
void clrLEDs(void){
	LEDsArrPort = 0x000;
}  
//--------------------------------------------------------------------
//				Toggle 8-bit LEDs array 
//--------------------------------------------------------------------
void toggleLEDs(char ch){
	LEDsArrPort ^= ch;
}
//--------------------------------------------------------------------
//				Set 8-bit LEDs array 
//--------------------------------------------------------------------
void setLEDs(char ch){
	LEDsArrPort |= ch;
}
//--------------------------------------------------------------------
//				Read value of 4-bit SWs array 
//--------------------------------------------------------------------
unsigned char readSWs(void){
	unsigned char ch;
	
	ch = LCD_PB_Port;
	ch &= SWmask;     // mask the least 4-bit
	return ch;
}
//---------------------------------------------------------------------
//             Increment / decrement LEDs shown value 
//---------------------------------------------------------------------
void incLEDs(char val){
	LEDsArrPort += val;
}
//---------------------------------------------------------------------
//            Polling based Delay function
//---------------------------------------------------------------------
void delay(unsigned int t){  // t[msec]
	volatile unsigned int i;
	
	for(i=t; i>0; i--);
}

//---------------------------------------------------------------------
//            Int to String
//---------------------------------------------------------------------
  /* A utility function to reverse a string  */
char* reverse(char str[], int length)
{
    int i, temp;  
    for (i = 0; i<length/2; i++){
      temp = str[i];
      str[i] = str[length - i - 1];
      str[length - i - 1] = temp; 
    }
}
/////////////////////////////////////////////////////////////////////////////////////

// Implementation of itoa()
char* itoa_self(int num, char* str)
{
    int i = 0;
    int isNegative = 0;
    //char strout[40];
 
    /* Handle 0 explicitly, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0)
    {
        isNegative = 1;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % 10;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/10;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}
//////////////////////////////////////////////////////////////////////////////////

void stopWatch(void){
    char timestr[40];
    const char tamplate[] = "00:"; 
    time-=1;
    if (time<0){
       TA0CTL = MC_0;
       time = 60;
       lcd_cmd(0x01);
       return;
    }  
    itoa_self(time, timestr);
    lcd_cmd(0x01);
    lcd_puts(tamplate);
    lcd_puts(timestr);
    
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
//            Port2 Interrupt Service Rotine
//*********************************************************************
#pragma vector=PORT1_VECTOR
  __interrupt void PBs_handler(void){
   
	delay(debounceVal);
//---------------------------------------------------------------------
//            selector of transition between states
//---------------------------------------------------------------------
	switch(LCD_PB_IntPend){
		case PB0:
		 state = state1;
		 LCD_PB_IntPend &= ~PB0;
		 break;
		 
		case PB1:
		 state = state2;
		 LCD_PB_IntPend &= ~PB1;
		 break;
		 
		case PB2:
		 state = state3;
		 LCD_PB_IntPend &= ~PB2;
		 break;
                 
                 case PB3:
		 state = state4;
		 LCD_PB_IntPend &= ~PB3;
		 break;
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
 
// Timer A0 interrupt service routine

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A(void){
    switch(__even_in_range(TA0IV, 0x0A)){
        case TA0IV_NONE:
            break;                                               // Vector  0:  No interrupt
        case TA0IV_TACCR1:                                       // Vector  2:  TACCR1 CCIFG
            stopWatch();
            break;
        case TA0IV_TACCR2:                                       // Vector  4:  TACCR2 CCIFG
        /*    if(TA1CCTL2 & CCI)                                     // Capture Input Pin Status
            {
                // Rising Edge was captured
                if(!firstTime){
                    REdge1 = TA1CCR2;
                    firstTime++;
                } else{
                    REdge2 = TA1CCR2;
		    TA1CCTL2 &= ~CCIE;                                // enable interapt
		    firstTime = 0;
                    __bic_SR_register_on_exit(LPM0_bits + GIE);  // Exit LPM0 on return to main
                }
            }*/
            break;
        case TA0IV_6:
            break;                                               // Vector  6:  Reserved CCIFG
        case TA0IV_8:
            break;                                               // Vector  8:  Reserved CCIFG
        case TA0IV_TAIFG:
            //stopWatch();
            break;                                               // Vector 10:  TAIFG
        default:
            break;
    }
}






