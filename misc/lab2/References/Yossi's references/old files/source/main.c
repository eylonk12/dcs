#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer
//#include  "../header/LCD.h"


enum FSMstate state;
enum SYSmode lpm_mode;

void main(void){
  state = state0;  // start in idle state on RESET
  lpm_mode = mode0;     // start in idle state on RESET
  sysConfig();
  
  while(1){
	switch(state){
	  case state0:
                enterLPM(lpm_mode); // TODO: check if delete?
		break;
		 
	  case state1:

		break;
		 
	  case state2:
                //Write2LCD("hannia gay");
                startStopWatch();
                //state = state0;
		break;
                
	  case state3:
	  
               break;
               
          case state4:
             
               break;
	}
  }
}
  
  
  
  
  
  