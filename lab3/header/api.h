#ifndef _api_H_
#define _api_H_

#include  "../header/halGPIO.h"     // private library - HAL layer


void lcd_puts(const char *, int);
int count_digits(unsigned int);
void int_to_char_arr(unsigned int);
#endif





