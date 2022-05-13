#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer

enum FSMstate state;
enum SYSmode lpm_mode;



void main(void){
  
  state = state0;  // start in idle state on RESET
  lpm_mode = mode0;     // start in idle state on RESET
  sysConfig();
  lcd_init();
  
  while(1){
	switch(state){
	  case state0:
                enterLPM(lpm_mode);
		break;
		 
	  case state1:
                disable_all_states();
                freq_counter_init(1);
                state = state0;
		break;
		 
	  case state2:
                disable_all_states();
                lcd_disp_min();
                state = state0;
		break;
		
          case state3:
                disable_all_states();
                ADC_Init();
                state = state0;
                break;
	}
  }
}
  
  
  
  
  
  