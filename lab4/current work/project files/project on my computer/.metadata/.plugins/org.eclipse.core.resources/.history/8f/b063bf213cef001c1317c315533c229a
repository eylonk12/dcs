#include  "../header/bsp.h"    // private library - BSP layer
//#include "msp430fg4619.h"
//-----------------------------------------------------------------------------  
//           GPIO congiguration
//-----------------------------------------------------------------------------
void GPIOconfig(void){
 // volatile unsigned int i; // in case of while loop usage
  
  WDTCTL = WDTHOLD | WDTPW;		// Stop WDT
   
  if (CALBC1_1MHZ==0xFF)                  // If calibration constant erased
      {
        while(1);                               // do not load, trap CPU!!
      }
    DCOCTL = 0;                               // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
    DCOCTL = CALDCO_1MHZ;

  ///////////////////////     LCD CONFIGURATIONS         //////////////////////////////////
  // LCDs 4-bit Array Port configuration
  LCD_DATA_SEL &= ~0xF0;            // GPIO capability
  LCD_DATA_DIR |=  0xF0;            // P1.4 -P1.7 OUTPUT MODE FOR LCD
  // P2.5-P2.7 CONTROL LCD OUTPUT CONFIG
  LCD_EN_SEL  &= ~0xE0;              // p2.5-p2.7 sel =0 I\O mode
  LCD_DIR     |=  0xE0;              // p2.5-p2.7 dir =1 output mode
  LCD_ENABLES &= ~0xE0;              // p2.5-p2.7 clear bits
  ////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////     UART CONFIGURATIONS         //////////////////////////////////
  UART_SEL |= 0x06;
  UART_OUT &= ~(0x06);
  UCA0CTL1 |= UCSSEL_2;    // CLK = SMCLK
  // Setting the Baud rate to 9600 Baud.
  UCA0BR0 = 104;
  UCA0BR1 = 0x00;

  UCA0MCTL = UCBRS0;
  ////////////////////////////////////////////////////////////////////////////////////
    
  _BIS_SR(GIE);                     // enable interrupts globally


  ////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////     POT CONFIGURATIONS         //////////////////////////////////
  ADC10AE0 |=  0X08;               // P1.3 ADC option select
  POT_SEL  &= ~0x08;               // POT 1.3 as GPIO
  POT_DIR  |=  0X08;               // POT as output

  ///////////////////////     RGB CONFIGURATIONS         //////////////////////////////////
  RGB_SEL &= ~0x07;                // sel =0 => set as GPIO
  RGB_DIR |=  0x07;                // dir =1 => set as output
  CLR_RGB;                         //start fresh and clean the RGB


}                             

