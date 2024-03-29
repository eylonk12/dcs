
#include  "../header/api.h"    		// private library - API layer

// GLOBAL VARIABLES
volatile unsigned int   state = 7;
enum SYSmode lpm_mode;
volatile unsigned int delay_int = 500;       // the default value for the delay
volatile char delay_str[10];                 // Receive the char to here for conversion
volatile char asci_char[10];

void main(void){
  // initial the system
    progConfig();                             // configurations and clearing the system
 // start in idle state on RESET 
  lpm_mode = mode0;     
  
  while(1){
        switch(state){
          case 1:
              RGBBlink(delay_int);
              break;
          
          case 2:
              Count_up(delay_int);
              break;
          
          case 3:
              Count_down(delay_int);
              break;
          
          case 4:
              sleep();         //sleep and be ready for interrupt
              break;

          case 5:
              Potentiometer();
              break; 

          case 6:
              Restart_program();
              break;

          case 7:
              Transmit_menu();
              sleep();         //sleep and be ready for interrupt
              break;

          case 8:
              sleep();         //sleep and be ready for interrupt
              break;

          case 9:
              sleep();         //sleep and be ready for interrupt
              break;
          default:
              state = 8;
              break;
        }
    }
}
