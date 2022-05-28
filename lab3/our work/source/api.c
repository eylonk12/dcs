#include  "../header/api.h"    		// private library - API layer

// Arrays for the frequency and dc delays of the recorded song.
int recorder_song_freq[33];
int recorder_song_dc[33];
// Frequencies of the 6th octave, relevant for the recorder. 
int octave_frequencies[13] = {1002, 946, 893, 842, 795, 751, 708, 669, 631, 595, 562, 530, 500};

// Global variables
int current_length =0;
volatile int display_screen = 0;
volatile unsigned int KP;  // Key Pad

//Functions
void tone_recoder(void){
  // Starting by clear the last recording and print on the screen the GUI.
  init_recorder();
  display_menu();
  current_length = 0;
  // main loop of the recording
  while((current_length < 32) && (state == state1)){
    enterLPM(lpm_mode);   /// Waiting for Key pad interrupt
    __no_operation();
    
    if((KP <= 12) && (state == state1)){ // if there is interupt from PB while recording
      recorder_song_freq[current_length] = octave_frequencies[KP];
      recorder_song_dc[current_length]   = octave_frequencies[KP]/2 ;
      Enable_TimerB_PWM();
      Enable_TimerA_345();
      current_length +=1;
      enterLPM(lpm_mode);    /// Waiting for Timer interrupt
    }else{
      break;
    }
  }
    // Entering the length of the recording
    output_string[15] = (char)(current_length%10) + '0';
    output_string[14] = (char)(current_length/10) + '0';
    lcd_clear(); //Display Clear.
    lcd_puts(output_string);  // Display output/
    
    // If the routine ended without a change of state, we go to state 0. 
    if(state == state1){
       state = state0;
    }
}

void audio_player(void){    
    choose_song_from_menu(); // UI for choosing song option. 
    dma_config();
    enterLPM(lpm_mode);
}


