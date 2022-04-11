#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer

enum FSMstate state;
enum SYSmode lpm_mode;
char state_2_last_value;
char state_4_last_colour;

void main(void){
  char id[] = {0x02,0x00,0x05,0x06,0x07,0x01,0x08,0x05,0x02};
  state_2_last_value  = 0x01;
  state_4_last_colour = 0x00; 
  state = state0;  // start in idle state on RESET
  lpm_mode = mode0;     // start in idle state on RESET
  sysConfig();
  PWMPin |= 0x02;
  
  while(1){
	switch(state){
	  case state0:
            clrLEDs();
            enterLPM(lpm_mode);
		break;
		 
	  case state1:
		disable_interrupts();
		printArr2SWs(id, 9, LEDs_SHOW_RATE);
                state = state0;
		enable_interrupts();
		break;
		 
	  case state2:
		disable_interrupts();
        for (int i=0; i<14; i++){
            printArr2SWs(&state_2_last_value, 1, LEDs_SHOW_RATE);
            state_2_last_value = state_2_last_value << 1;
            if (state_2_last_value == 0x00) {
                state_2_last_value = 0x01;
            }
        } 
                state = state0;
                enable_interrupts();
		break;
        
        case state3: // PWM.
          PWMPin &= 0x7F; // Assigning 0.
          delay(4); // 25% of the period.
          PWMPin |= 0x80; // Assigning 1.
          delay(15); // 75% of the period.    
		break;
                
         case state4: // PWM.
            disable_interrupts();
            for (int i=0; i<10; i++){
              printArr2RGBLEDS(&state_4_last_colour, 1, LEDs_SHOW_RATE);
              state_4_last_colour += 0x20;
            } 
            state = state0;
	    enable_interrupts();   
	  break;
	}
  }
}
  
  
  
  
  
  