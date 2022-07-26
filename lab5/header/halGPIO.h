#ifndef _halGPIO_H_
#define _halGPIO_H_

#include  "../header/bsp.h"    		// private library - BSP layer
#include <stdio.h>

// LCD header file's content.

// #define CHECKBUSY	1  // using this define, only if we want to read from LCD

#ifdef CHECKBUSY
	#define	LCD_WAIT lcd_check_busy()
#else
	#define LCD_WAIT DelayMs(5)
#endif

#define exit_lpm __bic_SR_register_on_exit(LPM0_bits + GIE);
#define FOURBIT_MODE	0x0
#define EIGHTBIT_MODE	0x1

#define OUTPUT_PIN      1
#define INPUT_PIN       0
#define ACK             6
#define STOP_SCRIPT     18
#define START_SCRIPT    19
#define SEND_ACK        TxBuffer = ACK
#define DISABLE_TX_INT  IE2 &= ~UCA0TXIE;

#define NUM_SCRIPTS 3
#define SCRIPT_SIZE 50
#define MAX_NAME_SIZE 20

//**************************************************************
// variables
//**************************************************************
extern volatile unsigned int state;            // Current state global variable
extern enum SYSmode lpm_mode; // global variable
extern char tx_str_val[4];   // data for buffer
extern volatile unsigned int delay_int;   // data for buffer
extern float deg;   // data for buffer
extern volatile unsigned int current_step ;   // current step
extern volatile int RGB_DATA ; // the data to RGB output
extern volatile int MOTOR_DATA ; // the data to MOTOR output
extern volatile int LED_DATA ; // the data to LED output
extern int X_Axis ; // the x value
extern int Y_Axis ; // the y value
extern volatile char asci_char[10];

extern void sysConfig(void);
extern void enterLPM(unsigned char);
//**************************************************************
// UART,TIMER and ADC interrupt vectors
//**************************************************************
__interrupt void USCI0RX_ISR(void);
__interrupt void USCI0TX_ISR(void);
__interrupt void ADC10_ISR(void);
//**************************************************************
// functions for states
//**************************************************************
extern void clear_rgb(void);
extern void int2str(char str[4], int num);
int str2int(char str[3]);
extern void blink_RGB(int delay);
extern void rotate_left(int delay);
extern void SRC_from_MOTOR(void);
extern void adc10_config();
extern void adc10_enable(short enable);
extern void clear_all(void);
extern void DelayMs(unsigned int);
extern void DelayUs(unsigned int);
extern void motor_cycle_cw(void);
extern void motor_cycle_ccw(void);
extern void read_from_juystick(void);
extern void Enable_TimerA_10ms(void);
extern void Disable_TimerA_345(void);
extern void enable_transmition(void);
extern void blink_RGB(int delay);
extern unsigned int step_cnt ;           // the value of the current step for restart
extern volatile int motor_dir;                       // direction of the motor movement
extern volatile int motor_is_moving;
extern int steps;
extern void delay10MS(void);

typedef struct {
    char p_scripts[NUM_SCRIPTS][SCRIPT_SIZE];
    char p_names[NUM_SCRIPTS][MAX_NAME_SIZE];
    int sizes[NUM_SCRIPTS];
    int num_of_scripts;
} Script_files;


void init_Scripts(Script_files *script_files);

void add_script(Script_files *script_files, char* name, int size, int idx, char* content);

char* get_script(Script_files *script_files, int i, char* s_name_buffer, int* s_size);

#endif







