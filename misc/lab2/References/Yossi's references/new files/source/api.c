#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer

//-------------------------------------------------------------
//            Print SWs value onto LEDs
//-------------------------------------------------------------
void printSWs2LEDs(void){
	unsigned char ch;
	
	ch = readSWs();
	print2LEDs(ch);
}
//--------------------------------------------------------------------
//            Print array to LEDs array with rate of LEDs_SHOW_RATE
//--------------------------------------------------------------------            
void printArr2SWs( char Arr[], int size, unsigned int rate){
	unsigned int i;
	
	for(i=0; i<size; i++){
		print2LEDs(Arr[i]);
		delay(rate);
	}
}

int printMulBy2( int val, unsigned int rate){
	unsigned int i;
	int size = 14;
        
	for(i=0; i<size; i++){
               print2LEDs((char)val);
               val = val * 2;
               if (val > 256){
                    val = 1;}
		
		delay(rate);
	}
        return val;
}
 
 void PWM_sig ( unsigned int val){
  
  Pwm_out1 = val? 0x80 :0x00 ;               //p2.7=1


} 

void PWM_SW (void)
{
  unsigned char ch;
  ch = readSWs();
  
  switch (ch){
  
    case (0x10):
           Pwm_out1 = 0x00;
           break;
      
    case (0x20):
          Pwm_out1 = 0x80;
          delay(13);
         Pwm_out1 = 0x00;  
          delay(39);
          break;
      
    case (0x30):
        Pwm_out1 = 0x80;
        delay(26);
       Pwm_out1 = 0x00;  
        delay(26);
        break;
       
    case (0x40):
        Pwm_out1 = 0x80;
        break;
      }
     
}
         

