#include  <msp430xG46x.h> // IDE library
#include <msp430.h>

#include  "../header/api.h"    		// private library - API layer
#include  "../header/hal.h"             // private library - HAL layer
#include  "../header/bsp.h"             // private library - BSP layer


/*----------------------------------------------------------
                  GLOBAL VARIABLES
------------------------------------------------------------*/ 
char Const_LCD_label_1[15] = {'S','t','a','r','t',' ','R','e','c','o','r','d','i','n','g'};
char Const_LCD_label_2[15] = {'T','o',' ','S','t','o','p',' ','P','r','e','s','s',':','*'};
char Const_LCD_label_3[16] = {'R','e','c','o','r','d',' ','L','e','n','g','t','h',':','0','0'};
int Record_Periods[13] = {1002, 946, 893, 842, 795, 751, 708, 669, 631, 595, 562, 530, 500};
int j = 0;
volatile int screen = 0;
volatile int* song_choice_freq; 
volatile int* song_choice_dc; 
volatile unsigned int KB = 0;  
volatile int playing345ms = 1;
volatile int song_length = 32;

 /*----------------------------------------------------------
                STATE 1 FUNCTION
------------------------------------------------------------*/ 

void tone_recorder(void){                                 // Function for State 1
 
// Variable Initialization

      // Print the 'Start Recording' screen for the User
      clear_recording();			         // delete previous recording and set array to 0
      print_recording_screen(); 	                 // print request from user // CHECK!!!
      playing345ms = 1;
      j = 0;
      // Save the Recording
      while((j < 32) && (playing345ms == 1) && (State == 1)){
        __bis_SR_register(LPM0_bits + GIE);              // Enter LPM0
        __no_operation();
        
        if((KB <= 12) && (State != 1 /*added condition for state*/)){ 
          Recorder_song_freq[j] = Record_Periods[KB];
          Recorder_song_dc[j] = Record_Periods[KB] / 2;
          Enable_TimerB_out_PWM();	                // Start Timer B
          Enable_TimerA_345msec();
          __no_operation();
          
          j = j + 1;
          __bis_SR_register(LPM0_bits + GIE);              // Enter LPM0
        }else{
          playing345ms = j;
          j = 32;
          break;
        }
      }
      
      // Print the Recording Length for the User
      Const_LCD_label_3[15] = (char)(playing345ms%10)  + '0';            //print recordng length (i) by digit
      Const_LCD_label_3[14] = (char)((playing345ms/10)%10)  + '0';
      lcd_clear();                                                       //clear lcd
      lcd_puts(Const_LCD_label_3);	                                 //print initial label 3 on LCD
      
      if (state == 1){
	      State = 0;
	  }		  
  }

/*----------------------------------------------------------
              STATE 2 FUNCTION
------------------------------------------------------------*/ 
void audio_player(void){					// Function for State 2
  menu_choose_song();						// print screen and wait for user to choose song
  set_DMA_TB_connection();
  __bis_SR_register(LPM0_bits + GIE);                           // Enter LPM0
}


