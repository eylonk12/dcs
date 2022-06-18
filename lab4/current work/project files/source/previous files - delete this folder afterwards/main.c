
#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer


// GLOBAL VARIABLES
enum SYSmode lpm_mode;

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
          
              break;
          
          case state1:   
          
              break;
          
          case state2:
          
              break;
          
          case state3:
          
              break; 
        }
    }
}