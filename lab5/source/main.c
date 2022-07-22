
#include  "../header/api.h"    		// private library - API layer

// GLOBAL VARIABLES
volatile unsigned int   state = 7;
enum SYSmode lpm_mode;
volatile unsigned int delay_int = 1;       // the default value for the delay
int steps;           // the default value for the delay
volatile float deg = 270;                      // the default value deg
volatile unsigned int current_step = 0;    // the value of the current step for restart
unsigned int step_cnt=0 ;           // the value of the current step for restart
volatile int motor_dir;                       // direction of the motor movement
volatile int motor_is_moving =0;              //
volatile char delay_str[10];                 // Receive the char to here for conversion
volatile char asci_char[10];

void main(void){
  // initial the system
    progConfig();                             // configurations and clearing the system
 // start in idle state on RESET 
  lpm_mode = mode0;
  while(1){
      joystick_2_motor(delay_int);
      deg = calc_degree();
      MOTOR_2_deg(deg);
  }

}

