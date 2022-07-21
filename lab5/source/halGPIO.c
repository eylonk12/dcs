#include  "../header/halGPIO.h"     // private library - HAL layer
#include "../header/bsp.h"


// variables
volatile char POT_val[5];
unsigned int i,j;
int volatile MOTOR_DATA = 0x08 ;
unsigned int adc[2] = {0};	// This will hold the x,y axis values
int X_Axis = 0;
int Y_Axis = 0;
float        degree = 0;


//**************************************************************
//             System Configuration  
//**************************************************************
void sysConfig(void){ 
	GPIOconfig();
}

//---------------------------------------------------------------------
//            TIMER A config for counting 345 ms
//---------------------------------------------------------------------
void Enable_TimerA_345(void){
    TACTL = TAIE;    // SMCLK, up mode, divide SMCLK to become 2^17, TA interrupt enable
}

void Disable_TimerA_345(void){
    TACCTL0 &= ~CCIE;         // Disable interrupts from timer
    TACTL =  MC_0 + TACLR;    // Stop mode, clear timer
}


//**************************************************************
//            basic functions to states
//**************************************************************
void clear_all(void){
    CLR_RGB;
    CLR_MOTOR;
    CLR_LED;
}
void motor_cycle_cw(void){
    if (MOTOR_DATA == 0x01){
        MOTOR_DATA = 0x08;
    }else{
        MOTOR_DATA >>= 1;
    }
    MOTOR_OUT = MOTOR_DATA;
}
void motor_cycle_ccw(void){
    if (MOTOR_DATA == 0x08){
        MOTOR_DATA = 0x01;
    }else{
        MOTOR_DATA <<= 1;
    }
    MOTOR_OUT = MOTOR_DATA;
}

void read_from_juystick(void){
    ADC10CTL0 &= ~ENC;
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
    ADC10SA = (int)adc;			// Copies data in ADC10SA to unsigned int adc array
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start

    Y_Axis = adc[0];			            // adc array 0 copied to the variable y_Axis
    X_Axis = adc[1];						// adc array 1 copied to the variable x_Axis
    //__bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
}

void adc10_config(){
    ADC10CTL1 = INCH_3 + ADC10SSEL_0;             // Repeat single channel, A3, ADC10OSC
    ADC10CTL0 = ADC10SHT_0 + ADC10IE;             //ADC10 Interrupt Enalbe
}
void blink_RGB(int delay){
    for (int i =0; i<3; i++){
        if (RGB_DATA == 0x01){
            RGB_DATA = 0x80;
        }else if(RGB_DATA == 0x80){
            RGB_DATA = 0x40;
        }else
            RGB_DATA = 0x01;
        RGB_OUT = RGB_DATA;
        DelayMs(delay);
    }
}
void rotate_left(int delay){
    LED_OUT = 0xF0;
}
//**************************************************************
//            Interrupts Service Routine
//**************************************************************

//**************************************************************
//         ADC10 Interrupt Service Routine
//**************************************************************
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){
    __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}



//******************************************************************
// Delay usec functions
//******************************************************************
void DelayUs(unsigned int cnt){
  
	unsigned char i;
        for(i=cnt ; i>0 ; i--) asm(" nop"); // tha command asm(" nop") takes raphly 1usec
	
}
//******************************************************************
// Delay msec functions
//******************************************************************
void DelayMs(unsigned int cnt){
  
	unsigned char i;
        for(i=cnt ; i>0 ; i--) DelayUs(1000); // tha command asm(" nop") takes raphly 1usec
	
}

//**************************************************************
//            Enter from LPM0 mode and enable global interrupts
//**************************************************************
void enterLPM(unsigned char LPM_level){
	if (LPM_level == 0x00) 
	  _BIS_SR(LPM0_bits + GIE);     /* Enter Low Power Mode 0 */
        else if(LPM_level == 0x01) 
	  _BIS_SR(LPM1_bits + GIE);     /* Enter Low Power Mode 1 */
        else if(LPM_level == 0x02) 
	  _BIS_SR(LPM2_bits + GIE);     /* Enter Low Power Mode 2 */
	else if(LPM_level == 0x03) 
	  _BIS_SR(LPM3_bits + GIE);     /* Enter Low Power Mode 3 */
        else if(LPM_level == 0x04) 
	  _BIS_SR(LPM4_bits + GIE);     /* Enter Low Power Mode 4 */
}

//*********************************************************************
//            TIMERA Interrupt Service Rotine
//*********************************************************************
#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer_A1(void){
    switch (motor_dir){
        case 0:
            motor_cycle_ccw();
            break;
        case 1:
            motor_cycle_cw();
            break;
    }
    step_cnt ++;
    if(steps <= step_cnt){
        step_cnt = 0;
        motor_is_moving = 0;
        Disable_TimerA_345();   // Stop mode, clear timer
    }
}


        


