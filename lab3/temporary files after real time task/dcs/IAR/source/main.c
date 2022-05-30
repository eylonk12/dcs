
#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer


// GLOBAL VARIABLES
enum FSMstate state;
enum SYSmode lpm_mode;

char str[157] = "Google Colaboratory is a free Jupyter notebook environment that runs on Google’s cloud servers, letting the user leverage backend hardware like GPUs and TPUs";

void main(void){
  // initial the system
    sysConfig();
    lcd_init();
    lcd_clear();
 // start in idle state on RESET 
  state = state0;  
  lpm_mode = mode0;     
  
  while(1){
        switch(state){
          case state0:
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
        // Mirror string using the DMA. 
          case state3:
             _BIC_SR(GIE);
             mirror_string(str);
             state = state0;
             _BIS_SR(GIE);
            break; 
        }
    }
}