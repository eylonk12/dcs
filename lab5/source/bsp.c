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
  ///////////////////////     RGB CONFIGURATIONS         //////////////////////////////////
    RGB_SEL &= ~0xc1;                // sel =0 => set as GPIO
    RGB_DIR |=  0xc1;                // dir =1 => set as output
    CLR_RGB;                         //start fresh and clean the RGB
  ///////////////////////     UART CONFIGURATIONS         //////////////////////////////////
  UART_SEL |= 0x06;
  P1SEL2   |= 0x06;
  UART_OUT &= ~(0x06);
  UCA0CTL1 |= UCSSEL_2;    // CLK = SMCLK
  // Setting the Baud rate to 9600 Baud.
  UCA0BR0 = 104;
  UCA0BR1 = 0x00;

  UCA0MCTL = UCBRS0;   // start bit 1
  ////////////////////////////////////////////////////////////////////////////////////
    
  _BIS_SR(GIE);                     // enable interrupts globally

  ////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////     JOYSTICK CONFIGURATIONS         //////////////////////////////////
  JOY_SEL      &= ~0x38;               // P1.3 - P1.5 as GPIO
  JOY_DIR      &= ~0X38;               // P1.3 - P1.5 as input
  JOY_IES      &= ~0x20;               // choose P1.5 as pull-down mode
//  JOY_IE       |= 0x20;                // interrupt enable for joystick pushbutton
  JOY_INT_PEND &= ~0X20;               // clear pending interrupts from joystick




  ///////////////////////     TIMER CONFIGURATIONS         //////////////////////////////////
  TACCR0 = 500-1;                         // Initially, stop the Timer. 1310-1 is the right one
  TACCTL0 &= ~CCIE;
  TACCTL0 |= CCIE;                      // Enable interrupt for CCR0.
  TACTL  = TASSEL_2 + TACLR + ID_3 + MC_1 ;     // SMCLK, clear counter , divide smclk by 3 to get 2^17 freq, UP MODE.


    ///////////////////////     ADC CONFIGURATIONS         //////////////////////////////////
  ADC10AE0 |=  0X18;               // P1.3, P1.4 ADC option select x and y
  ADC10CTL1 = INCH_4 + CONSEQ_3+ ADC10SSEL_0;            // A1/A0, repeated sequence
  ADC10CTL0 = ADC10SHT_0 + MSC + ADC10ON + ADC10IE;     // SHT for sample and hold, MSC- multiple sample and conversion,interrupt enable
  ADC10DTC1 = 0x02;                         // 2 conversions
  ADC10AE0 |= 0x18;                         // Disable digital I/O on P1.3 to P1.4

  ///////////////////////     MOTOR CONFIGURATIONS         //////////////////////////////////
  MOTOR_SEL &= ~0x0F;                 // P2.0 - P2.3 set as GPIO
  MOTOR_DIR |=  0x0F;                 // P2.0 - P2.3 set as output
  CLR_MOTOR;                        // set output of the motor as 0

  ///////////////////////     LEDS CONFIGURATIONS         //////////////////////////////////
  LED_SEL &= 0xF0;                 // P2.4 - P2.7 set as GPIO
  LED_DIR |= 0xF0;                 // P2.4 - P2.7 set as output
  CLR_LED;
}                             

