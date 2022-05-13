#include  "../header/bsp.h"    // private library - BSP layer


//-----------------------------------------------------------------------------  
//           GPIO congiguration
//-----------------------------------------------------------------------------
void GPIOconfig(void){
 // volatile unsigned int i; // in case of while loop usage
  
  WDTCTL = WDTHOLD | WDTPW;		// Stop WDT
   

    
      // LEDs 8-bit Array Port configuration
  //LEDsArrPortSel &= ~0xFF;            // GPIO capability
  //LEDsArrPortDir |= 0xFF;             // output dir
  //LEDsArrPort = 0x00;				  // clear all LEDs
  
  // Switches Setup
  //SWsArrPortSel &= ~0x7F;    // 0x0F
  //SWsArrPortDir &= ~0x7F;   // 0x0F
  
  // PushButtons Setup
  LCD_PB_Sel &= 0x00;
  LCD_PB_Dir &= 0xF0;
  LCD_PB_Dir |= 0xF0;
  LCD_PB_IntEdgeSel |= 0x03;  	     // pull-up mode   origin: IntEdgeSel |= 0x30
  LCD_PB_IntEdgeSel &= ~0x0C;        // pull-down mode  oriigin: PBsArrIntEdgeSel &= 0xC0   ~0x04;
  LCD_PB_IntEn &= ~0xFF;
  LCD_PB_IntEn |= 0x0F;                //   PBsArrIntEn |= 0x0F;   0x07;
  LCD_PB_IntPend &= ~0xFF;            // clear pending interrupts origin:   PBsArrIntPend &= ~0xF0;
  
  _BIS_SR(GIE);                     // enable interrupts globally
   //Pwm_out1 &= 0x00;
  

    
    
}                             
//------------------------------------------------------------------------------------- 
//            Timers congiguration 
//-------------------------------------------------------------------------------------
void TIMERconfig(void){
	
	//write here timers congiguration code
} 
//------------------------------------------------------------------------------------- 
//            ADC congiguration 
//-------------------------------------------------------------------------------------
void ADCconfig(void){
	
	//write here ADC congiguration code
}              

           
             

 
             
             
            
  

