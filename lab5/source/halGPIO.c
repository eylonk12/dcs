#include  "../header/halGPIO.h"     // private library - HAL layer
#include "../header/bsp.h"
#include <string.h>


// variables
char tx_str_val[4];
unsigned int tx_str_idx = 0,j;
unsigned int OFFCount;
unsigned int dealy_cnt=0;
int volatile MOTOR_DATA = 0x08 ;
unsigned int adc[3] = {0};	// This will hold the x,y axis and PB values
int X_Axis = 0;
int Y_Axis = 0;
int PB_Axis = 0;
char rec_mode;
float degree = 0;
char tx_data = 'a';
char states_RX_buffer[60];

// Scirpts variables
extern Script_files script_files;
int s_size;
char s_size_str[3];
int s_idx;
char s_name[MAX_NAME_SIZE];
char s_content[SCRIPT_SIZE];


//**************************************************************
//             System Configuration  
//**************************************************************
void sysConfig(void){ 
	GPIOconfig();
}

//---------------------------------------------------------------------
//            TIMER A config for counting 345 ms
//---------------------------------------------------------------------
void delay10MS(void){
    OFFCount = 0;          // Rest Over flow counter
    dealy_cnt = 0;
    TACCTL0 |= CCIE;
    //TACTL |= TAIE;
    //TACCTL0 |= CCIE;
    //TACTL = TAIE;    // SMCLK, up mode, divide SMCLK to become 2^17, TA interrupt enable
    //TACCR0 = 1310-1;       // Start Timer, Compare value for Up Mode to get 10ms delay per loop
//Total count = TACCR0 + 1. Hence we need to subtract 1.
}


void Enable_TimerA_10ms(void){
    TACCTL0 |= CCIE;
    TACTL = TAIE;    // SMCLK, up mode, divide SMCLK to become 2^17, TA interrupt enable
}

void Disable_TimerA_345(void){
    TACCTL0 &= ~CCIE;
    TACTL |= TACLR;
    //TACTL &= ~TAIE;
    //TACCR0 = 0; //Stop Timer
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

void DelayUs(unsigned int cnt){
  
	unsigned char i;
        for(i=cnt ; i>0 ; i--) asm(" nop"); // tha command asm(" nop") takes raphly 1usec
	
}
void DelayMs(unsigned int cnt){
  
	unsigned char i;
        for(i=cnt ; i>0 ; i--) DelayUs(1000); // tha command asm(" nop") takes raphly 1usec
	
}

void blink_RGB(int delay){
    int i;
    for (i =0; i<3; i++){
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

void enable_transmition(void){
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    IE2 |= UCA0TXIE;                          // Enable USCI_A0 TX interrupt
}

//**************************************************************
//            integer to string converter
//**************************************************************
void int2str(char str[4], int num){
    int strSize = 0;
    int tmp = num;//, len = 1;

    // Print out the numbers in reverse
    for(int j = 2; j >= 0; j--){
        str[j] = (num % 10) + '0';
        num /= 10;
    }
//    str[strSize] = '\0';
}

//**************************************************************
//            string to integer converter
//**************************************************************
int str2int(char str[3])
{
    int i,res = 0;
    for (i = 0; str[i] != '\n'; ++i) {
        if (str[i]> '9' || str[i]<'0')
            return -1;
        res = res * 10 + str[i] - '0';
    }
    return res;
}

//**************************************************************
//            Interrupts Service Routine
//**************************************************************
////**************************************************************
////        UART-  Transmitter Interrupt Service Routine
////**************************************************************
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
    if(state == 2){
        TxBuffer = tx_str_val[tx_str_idx];
        tx_str_idx++;
        if (TxBuffer == '$'){
          int error = 1;
        }
        if (tx_str_idx == sizeof tx_str_val){                         // TX over?
            tx_str_idx = 0;
            IE2 &= ~UCA0TXIE;                            // Disable USCI_A0 TX interrupt
            IE2 |= UCA0RXIE;                             // Enable USCI_A0 RX interrupt
            __bic_SR_register_on_exit(CPUOFF);
        }
    }
}
//**************************************************************
//        UART-  Receiver Interrupt Service Routine
//**************************************************************
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) {
    //char x = RxBuffer;
    states_RX_buffer[j] = UCA0RXBUF;
    j++;
    if (j>1 && states_RX_buffer[j-1] == '!') {
        strncpy(s_content, states_RX_buffer + 1, j-1);
        add_script(&script_files, s_name, s_size, s_idx, s_content);
        SEND_ACK;
        j = 0; 
    }
    else if (states_RX_buffer[j-1] == '\n')
    {
        switch (rec_mode) {
            case '#':
                state = states_RX_buffer[1]- 48;
                DISABLE_TX_INT;
                SEND_ACK;
                j = 0;
                break;
            case '$':
                strncpy(s_name, states_RX_buffer+1,j-1);
                SEND_ACK;
                j = 0;
                break;
            case '%':
                s_idx = states_RX_buffer[1] - 49;
                SEND_ACK;
                j = 0;
                break;
            case '@':
                strncpy(s_size_str, states_RX_buffer + 1, j - 1);
                s_size = str2int(s_size_str);
                SEND_ACK;
                j = 0;
                break;
        }

        //IE2 |= UCA0TXIE;
    }
    // Enable USCI_A0 TX interrupt
    //__bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)

    switch (states_RX_buffer[0]) {
        case '#': //state change
            rec_mode = '#';
            break;
        case '$'://get script name
            if (state == 4)
                rec_mode = '$';
            break;
        case '%'://get script idx
            if (state == 4)
                rec_mode = '%';
            break;
        case '@'://get script size
            if (state == 4)
                rec_mode = '@';
            break;
        case '!'://get script content
            if (state == 4)
                rec_mode = '!';
            break;
    }

    __bic_SR_register_on_exit(CPUOFF);
}
//**************************************************************
//         ADC10 Interrupt Service Routine
//**************************************************************
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){
      //PB_Axis = adc[2];						// adc array 2 copied to the variable JOY_PB
    __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

//*********************************************************************
//            Port1 Interrupt Service Rotine
//*********************************************************************
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void){
    DelayMs(1);
    JOY_INT_PEND &= ~0X20;
    tx_str_val[0] = '$'; tx_str_val[1] = '$';  tx_str_val[2] = '$';  tx_str_val[3] = '#';
    if(state==2){
        enable_transmition();
         return ;            // here we need to send click to the PC to change mode
    }
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
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(void){
    if (state == 3){
        if (dealy_cnt == delay_int){
            motor_cycle_cw();
            dealy_cnt =0;
            return;
        }else{
            dealy_cnt++;
            return;
        }
    }
    if(state == 2){
        Disable_TimerA_345();
    }
    if (dealy_cnt == delay_int){
        switch (motor_dir){
            case 0:
                motor_cycle_ccw();
                current_step = (current_step +1)%2047;
                step_cnt++;
                break;
            case 1:
                motor_cycle_cw();
                current_step = (current_step -1 + 2047)%2047;
                step_cnt++;
                break;
        }
        dealy_cnt = 0;
        // step_cnt ++;
        if(steps <= step_cnt){
            step_cnt = 0;
            steps = 0;
            motor_is_moving = 0;
            dealy_cnt =0;
            Disable_TimerA_345();   // Stop mode, clear timer
        }
    }else{
        dealy_cnt++;
    }
    __bic_SR_register_on_exit(LPM0_bits);         // Exit LPM0
}

//**************************************************************
//             script sturcture functions
//**************************************************************
void init_Scripts(Script_files *script_files) {
    // init for the files object
    int i;
    for (i = 0; i < NUM_SCRIPTS; i++) {
        script_files->sizes[i] = 0;
        script_files->p_scripts[i][0] = EOF;
    }
    script_files->num_of_scripts = 0;
}

void add_script(Script_files *script_files, char* name, int size, int idx, char content[SCRIPT_SIZE]) {
    // adding script to the files structure, inputs its name, size and index in the list, output its pointer
    strcpy(script_files->p_names[idx], name);
    if (script_files->sizes[idx] == 0)  // first time that this script index is added
        script_files->num_of_scripts += 1;
    script_files->sizes[idx] = size;
    strcpy(script_files->p_scripts[idx],content);
    script_files->p_scripts[idx][size] = EOF;
}

char* get_script(Script_files *script_files, int i, char* s_name_buffer, int* s_size) {
    // writes the name of the script (that is in index i ) and its size on the name buffer and size buffer
    // returnes the script's start pointer.
    strcpy(s_name_buffer, script_files->p_names[i]);
    *s_size = script_files->sizes[i];  // will be 0 if there is no script there
    return  script_files->p_scripts[i];
}

