#include  <msp430xG46x.h> // IDE library 
#include <msp430.h>
//#include <stdio.h>

#include "../header/bsp.h"
#include "../header/hal.h"
#include "../header/api.h"

//  GLOBAL VARIABLES

volatile unsigned int State = 0;         // global variable

int song1_freq[55] = { 893, 669, 669, 669, 893, 795, 795, 893, 530, 530, 595, 595, 669, 893, 669, 669,
                        669, 893, 795, 795, 893, 530, 530, 595, 595, 669, 893, 669, 669, 669, 893, 669, 
                        669, 669, 669, 669, 669, 893, 669, 669, 669, 893, 669, 669, 669, 893, 795, 795,
                        893, 530, 530, 595, 595, 669, 0};

int song2_freq[48] = { 1002, 751, 595, 1002, 751, 595, 595, 669, 669, 669, 669, 595, 562, 562, 562, 500,
                        562, 595, 669, 595, 595, 595, 595, 751, 669, 595, 562, 562, 562, 500, 562, 562, 
                        595, 751, 595, 500, 500, 1002, 795, 669, 562, 595, 669, 751, 751, 751, 751, 0};

int song3_freq[41] = { 795, 669, 795, 795, 669, 795, 500, 530, 595, 669, 751, 893, 751, 595, 669, 669,
                        751, 795, 893, 1002, 795, 669, 795, 795, 669, 795, 500, 530, 595, 669, 751, 893,
                        751, 595, 669, 669, 751, 795, 893, 1002, 0};

int song1_dc[55] = { 446, 334, 334, 334, 446, 397, 397, 446, 265, 265, 297, 297, 334, 446, 334, 334,
                        334, 446, 397, 397, 446, 265, 265, 297, 297, 334, 446, 334, 334, 334, 446, 334, 
                        334, 334, 334, 334, 334, 446, 334, 334, 334, 446, 334, 334, 334, 446, 397, 397,
                        446, 265, 265, 297, 297, 334, 0};

int song2_dc[48] = { 501, 375, 297, 250, 375, 297, 297, 334, 334, 334, 334, 297, 281, 281, 281, 250,
                        281, 297, 334, 297, 297, 297, 297, 375, 334, 297, 281, 281, 281, 250, 281, 281, 
                        297, 375, 297, 250, 250, 250, 397, 334, 281, 297, 334, 375, 375, 375, 375, 0};

int song3_dc[41] = { 397, 334, 397, 397, 334, 397, 250, 265, 297, 334, 375, 446, 375, 297, 334, 334,
                        375, 397, 446, 501, 397, 334, 397, 397, 334, 397, 250, 265, 297, 334, 375, 446,
                        375, 297, 334, 334, 375, 397, 446, 501, 0};

int Recorder_song_freq[33] = {0};
int Recorder_song_dc[33] = {0};

/*------------------------------------------------------------*/ 
void main(void){
  
  InitGPIO();
  lcd_init();
  
  //Channel 0: freq
  DMAFreqSource = (int)song_choice_freq;                // Source block address
  DMAFreqDestination = (int)&TimerPWM_Freq;        // Destination block address: TBCCR0 (clock period of TimerB outmod)
  DMAFreqBlockSize = 0x020;                        // Block size 32 

  
  //Channel 1: DC
  DMADCsource = (int)song_choice_dc;                // Source block address
  DMADCdestination = (int)&TimerPWM_DC;        // Destination block address: TBCCR0 (clock period of TimerB outmod)
  DMADCblockSize = 0x020;                        // Block size 32 
  
  DMAtrigger = DMAFreqSelect1 + DMADCselect1;                     // TACCR2 trigger

  DMADCmode = DMADT_4 + DMASRCINCR_3 + DMASWDW + DMAEN;    // word-word, Block transfer, inc src, DMA enable
  DMAFreqMode = DMADT_4 + DMASRCINCR_3 + DMASWDW + DMAEN;    // word-word, Block transfer, inc src, DMA enable
  
  
  while(1){
	  
	switch (State) {

            case 0:
                    _BIS_SR(LPM0_bits + GIE);       // Enter LPM3 w/ interrupts			
                    break;
                    
            case 1:
                    tone_recorder();		    // start function for state 1
                    break;
					
            case 2:
                    audio_player();		   	 // start function for state 2
                    break;
                    
            default:
                    _BIS_SR(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts			
                    break;
                    
	}	
  }		
}		