
#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer


// GLOBAL VARIABLES
enum FSMstate state;
enum SYSmode lpm_mode;



void main(void){
  // initial the system
    sysConfig();
    lcd_init();
 // start in idle state on RESET 
  state = state0;  
  lpm_mode = mode0;     
  
  while(1){
        switch(state){
          case state0:
            lcd_clear();
            enterLPM(lpm_mode);
          break;
        // Tone recorder state = state1.
          case state1:   
              tone_recoder();
           break;
        // Audio player for a specific song or a recorded one. 
          case state2:
              audio_player(); 
            break;
        }
    }
}