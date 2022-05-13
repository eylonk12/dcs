#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer

//-------------------------------------------------------------
//            Print SWs value onto LEDs
//-------------------------------------------------------------
void Write2LCD(const char * s){

	lcd_puts(s);
}
//--------------------------------------------------------------------
//            Print array to LEDs array with rate of LEDs_SHOW_RATE
//--------------------------------------------------------------------            
void printArr2SWs( char Arr[], int size, unsigned int rate){
	unsigned int i;
	
	for(i=0; i<size; i++){
		print2LEDs(Arr[i]);
		delay(rate);
	}
}

int printMulBy2( int val, unsigned int rate){
	unsigned int i;
	int size = 14;
        
	for(i=0; i<size; i++){
               print2LEDs((char)val);
               val = val * 2;
               if (val > 256){
                    val = 1;}
		
		delay(rate);
	}
        return val;
}
 
//--------------------------------------------------------------------
//            Print array to LEDs array with rate of LEDs_SHOW_RATE
//--------------------------------------------------------------------            
void startStopWatch(void){
  TA0CTL = TASSEL_2 + MC_2 + TACLR+TAIE + ID_3;  // SMCLK, UP MODE, CLEAR CLK, INTERRUPT ENABLE
  TA0CCTL1 = CCIE;
  TA0CCR1 = 0xffff;
  //TA0CCR1 = 20000;
  __bis_SR_register(LPM0_bits + GIE);
  __no_operation();
  //StopWatch();
}