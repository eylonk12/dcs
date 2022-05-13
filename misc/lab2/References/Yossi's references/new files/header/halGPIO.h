#ifndef _halGPIO_H_
#define _halGPIO_H_

#include  "../header/bsp.h"    		// private library - BSP layer
#include  "../header/app.h"    		// private library - APP layer


extern enum FSMstate state;   // global variable
extern enum SYSmode lpm_mode; // global variable

extern void sysConfig(void);
extern void print2LEDs(unsigned char);
extern void clrLEDs(void);
extern void toggleLEDs(char);
extern void setLEDs(char);
extern unsigned char readSWs(void);
extern void delay(unsigned int);
extern void print2LCD(const char * s, int location);
extern void enterLPM(unsigned char);
extern void incLEDs(char);
extern void enable_interrupts();
extern void disable_interrupts();
extern void stopWatch(void);
extern void reverse(char str[], int length);
extern char* itoa_self(int num, char* str);
extern void freqCounter(void);
extern void SignalReco (void);
extern __interrupt void PBs_handler(void);
extern __interrupt void Timer_A0(void);
extern __interrupt void Timer_A1(void);
extern __interrupt void ADC10_ISR(void);
#endif







