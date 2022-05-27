#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer

//******************************************************************
// write a string of chars to the LCD
//******************************************************************
void lcd_puts(const char * s, int size){
	for(int i=0;i<size;i++)
		lcd_data(*s++);
}
