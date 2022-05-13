
#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer

char char_arr[10];

enum FSMstate state;
enum SYSmode lpm_mode;
unsigned int Nsmclk, freq, num_of_digits;
const int max_digits_for_frequency   = 5;
  
void main(void){
  // Constant string variables for state 1.
  char fin_string[] ="fin=00000Hz" ;
  int fin_string_size=11;
  // Constant string variables for state 2.  
  int  countdown_string_size= 5;
  // Variables for state1;
  
  state = state0;  // start in idle state on RESET
  lpm_mode = mode0;     // start in idle state on RESET
  sysConfig();
  lcd_init();
  while(1){
	switch(state){
	  case state0:
            lcd_clear();
            clear_configurations();
            enterLPM(lpm_mode);
	  break;
		 
	  case state1:
            if (enter_to_state_1 == 1) {
              timer_state_1_config();
              lcd_puts(fin_string, fin_string_size);
              lcd_cursor_left();
              lcd_cursor_left();
              enter_to_state_1 = 0;
            }

            // Nsmclk = {TBRmax*(Nifg-1)+TBRt1}+(TBRmax-TBRt2)}
            Nsmclk = (65535*(ifg_capture_2-ifg_capture_1-1)+capture_2)+(65535-capture_1);
            freq = (65535*2)/Nsmclk;
            num_of_digits = count_digits(freq);
            int_to_char_arr(freq);

            for (int i=0; i<(max_digits_for_frequency); i++){
              lcd_cursor_left();
            }
            for (int i=0; i<(max_digits_for_frequency - num_of_digits ); i++){
              lcd_puts("0", 1);
            }
            DelayMs(1000);
            cursor_off;
            lcd_puts(char_arr, num_of_digits);;
            break;
		 
	  case state2:
            if (enter_to_state_2 == 1) {
              lcd_clear();
              timer_state_2_config();
              lcd_puts("0", 1);
              enter_to_state_2 = 0;
            }
            if ((seconds_counter == 0)&&(minutes_counter == 0)){
               state = state0;
            }  
            if (state_2_interrupt_occured == 0){
              break;
            }
            state_2_interrupt_occured = 0;
            int_to_char_arr(minutes_counter);

            lcd_puts(char_arr, 1);
            lcd_puts(":", 1);
            if (minutes_counter == 1){
              lcd_puts("00", 2);
            } else{
              if (count_digits(seconds_counter) == 1 ){
                lcd_puts("0", 1);
              }
              int_to_char_arr(seconds_counter);

              lcd_puts(char_arr, count_digits(seconds_counter));
            }
            
            for (int i=0; i<countdown_string_size-1; i++){
              lcd_cursor_left();
            }          
            
            
            
                    
            break;
		
	}
    
    
  }
}
  
 
// Counts the number of digits in n.
int count_digits(unsigned int n){
    int count = 0;
    do {
    n /= 10;
    ++count;
  } while (n != 0);
  return count;
} 

void int_to_char_arr(unsigned int a){
    int int_arr[10];
    int size = count_digits(a);
    for (int i=0; i<size; i++){
        int_arr[i] = a%10;
        a = a/10;
    }
    for (int i=0; i<size; i++){
        char_arr[i] = int_arr[size-i-1] + 48;
    }
}
  
  