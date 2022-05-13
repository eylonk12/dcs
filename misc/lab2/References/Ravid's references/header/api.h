#ifndef _api_H_
#define _api_H_

#include  "../header/halGPIO.h"     // private library - HAL layer


void lcd_puts(const char *);
void lcd_disp_min();
void freq_counter_init(int );
void ADC_Init();
void disable_all_states();
#endif







