#ifndef _halGPIO_H_
#define _halGPIO_H_

#include  "../header/bsp.h"    		// private library - BSP layer

// LCD header file's content.

// #define CHECKBUSY	1  // using this define, only if we want to read from LCD

#ifdef CHECKBUSY
	#define	LCD_WAIT lcd_check_busy()
#else
	#define LCD_WAIT DelayMs(5)
#endif
//**************************************************************
// variables
//**************************************************************
extern volatile unsigned int  state;            // Current state global variable
extern enum SYSmode lpm_mode; // global variable
extern volatile char delay_str[10];   // data for buffer
extern volatile unsigned int delay_int;   // data for buffer
extern volatile int RGB_DATA ; // the data to RGB output


extern void sysConfig(void);
extern void enterLPM(unsigned char);
//**************************************************************
// UART,TIMER and ADC interrupt vectors
//**************************************************************
__interrupt void USCI0RX_ISR(void);
__interrupt void USCI0TX_ISR(void);
__interrupt void ADC10_ISR(void);
__interrupt void Timer_A(void);
//**************************************************************
// functions for states
//**************************************************************
extern void clear_rgb(void);
extern void blink_RGB(int delay);
extern void SRC_from_POT(void);
extern void adc10_config();
extern void adc10_enable(short enable);
extern void clear_all(void);
extern void enable_transmition(void);

//**************************************************************
// LCD functions
//**************************************************************
extern void lcd_cmd(unsigned char);
extern void lcd_data(unsigned char);
extern void lcd_puts(const char *s, int size);
extern void lcd_disp_min();
extern void lcd_init();
extern void lcd_strobe();
extern void DelayMs(unsigned int);
extern void DelayUs(unsigned int);

#define exit_lpm __bic_SR_register_on_exit(LPM0_bits + GIE);
#define LCD_STROBE_READ(value)  LCD_EN(1), \
                asm(" nop"), asm(" nop"), \
                value=LCD_DATA_READ, \
                LCD_EN(0)

#define lcd_cursor(x)       lcd_cmd(((x)&0x7F)|0x80)
#define lcd_clear()     lcd_cmd(0x01)
#define lcd_putchar(x)      lcd_data(x)
#define lcd_goto(x)     lcd_cmd(0x80+(x))
#define lcd_cursor_right()  lcd_cmd(0x14)
#define lcd_cursor_left()   lcd_cmd(0x10)
#define lcd_display_shift() lcd_cmd(0x1C)
#define lcd_home()      lcd_cmd(0x02)
#define cursor_off              lcd_cmd(0x0C)
#define cursor_on               lcd_cmd(0x0F)
#define lcd_function_set        lcd_cmd(0x3C) // 8bit,two lines,5x10 dots
#define lcd_new_line            lcd_cmd(0xC0)

/*----------------------------------------------------------
  CONFIG: change values according to your port pin selection
------------------------------------------------------------*/
#define LCD_EN(a)	(!a ? (LCD_ENABLES&=~0X20) : (LCD_ENABLES|=0X20)) // P2.5 is lcd enable pin
#define LCD_EN_DIR(a)	(!a ? (LCD_DIR&=~0X20) : (LCD_DIR|=0X20)) // P2.5 pin direction 

#define LCD_RS(a)	(!a ? (LCD_ENABLES&=~0X40) : (LCD_ENABLES|=0X40)) // P2.6 is lcd RS pin
#define LCD_RS_DIR(a)	(!a ? (LCD_DIR&=~0X40) : (LCD_DIR|=0X40)) // P2.6 pin direction  
  
#define LCD_RW(a)	(!a ? (LCD_ENABLES&=~0X80) : (LCD_ENABLES|=0X80)) // P2.7 is lcd RW pin
#define LCD_RW_DIR(a)	(!a ? (LCD_DIR&=~0X80) : (LCD_DIR|=0X80)) // P2.7 pin direction

#define LCD_DATA_OFFSET 0x04 //data pin selection offset for 4 bit mode, variable range is 0-4, default 0 - Px.0-3, no offset
   
#define LCD_DATA_WRITE	P1OUT
#define LCD_DATA_DIR	P1DIR
#define LCD_DATA_READ	P1IN
/*---------------------------------------------------------
  END CONFIG
-----------------------------------------------------------*/
#define FOURBIT_MODE	0x0
#define EIGHTBIT_MODE	0x1
#define LCD_MODE        FOURBIT_MODE
   
#define OUTPUT_PIN      1	
#define INPUT_PIN       0	
#define OUTPUT_DATA     (LCD_MODE ? 0xFF : (0x0F << LCD_DATA_OFFSET))
#define INPUT_DATA      0x00	





#endif







