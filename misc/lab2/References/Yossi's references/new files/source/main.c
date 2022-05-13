#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer
//#include  "../header/LCD.h"


enum FSMstate state;
enum SYSmode lpm_mode;

void main(void){
  int size = 9;
  long time = 524000;  //8*FFFF
  //int time2 = 16;
  //int val = 1;
  char id[9] = {3,1,3,3,0,7,7,5,3};
  state = state0;  // start in idle state on RESET
  lpm_mode = mode0;     // start in idle state on RESET
  sysConfig();
  
  while(1){
	switch(state){
	  case state0:
                clrLEDs();
                enterLPM(lpm_mode); // TODO: check if delete?
		break;
		 
	  case state1:
		disable_interrupts();
                printArr2SWs(id, size, time);
		//delay(LEDs_SHOW_RATE);	// delay of 62.5 [ms]
		state = state0;
                LCD_PB_IntPend &= ~0x80;
                enable_interrupts();

		break;
		 
	  case state2:
		//val = printMulBy2(val, time);
                //lcd_cmd(0x01); //Display Clear
              //  lcd_data(0);
                state = state0;
                LCD_PB_IntPend &= ~0x80;
		break;
                
	  case state3:
	      PWM_sig(1);
              delay(16);		// delay of 62.5 [micros]              
              PWM_sig(0);
              delay(1);		// delay of 62.5 [micros]
              LCD_PB_IntPend &= ~0x80;
               break;
               
          case state4:
               PWM_SW();
               LCD_PB_IntPend &= ~0x80;
               break;
	}
  }
}
  
  
  
  
  
  