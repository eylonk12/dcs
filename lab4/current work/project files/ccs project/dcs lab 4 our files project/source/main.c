
#include  "../header/api.h"    		// private library - API layer

// GLOBAL VARIABLES
int  state;
enum SYSmode lpm_mode;

void main(void){
  // initial the system
    sysConfig();
    lcd_init();
    lcd_clear();
 // start in idle state on RESET 
  state = 0;  
  lpm_mode = mode0;     
  
  while(1){
        switch(state){
          case 0:
          
              break;
          
          case 1:   
          
              break;
          
          case 2:
          
              break;
          
          case 3:
          
              break; 
        }
    }
}
