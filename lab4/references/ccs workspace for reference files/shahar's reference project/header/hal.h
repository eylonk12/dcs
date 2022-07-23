// HAL - Hardware Abstraction Layer

#ifndef _hal_H_
#define _hal_H_

//================================================
//               Variables
//================================================
extern volatile unsigned int state;
extern volatile unsigned int x;
extern volatile char X[10];
extern volatile int Out_to_RGB; // state 1
//================================================
//                UART
//================================================
__interrupt void USCI0RX_ISR(void);
__interrupt void USCI0TX_ISR(void);
//================================================
//        SERVICE FUNCTIONS
//================================================
// State 1
extern void clear_RGB(void);
extern void blink_RGB(int delay);
extern void clear_RGB(void);

//------------------------------------------------
// State 5
extern void SC_from_POT(void);

extern void adc10_config();
extern void adc10_enable(short enable);
__interrupt void ADC10_ISR(void);
//------------------------------------------------
// State 6
extern void clearing(void);
//------------------------------------------------
// State 7
extern void enable_transmition(void);
//================================================
// CONFIG: LCD BASIC FUNCTIONS
//================================================
#ifdef CHECKBUSY
    #define LCD_WAIT lcd_check_busy()
#else
    #define LCD_WAIT DelayMs(5)
#endif

#define FOURBIT_MODE    0x0
#define EIGHTBIT_MODE   0x1
#define LCD_MODE        FOURBIT_MODE

#define OUTPUT_PIN      1
#define INPUT_PIN       0
#define OUTPUT_DATA     (LCD_MODE ? 0xFF : (0x0F << LCD_DATA_OFFSET))
#define INPUT_DATA      0x00

#define LCD_STROBE_READ(value)  LCD_EN(1), \
                asm(" nop"), asm(" nop"), \
                value=LCD_DATA_READ, \
                LCD_EN(0)


#define lcd_cursor(x)           lcd_cmd(((x)&0x7F)|0x80)
#define lcd_clear()             lcd_cmd(0x01)
#define lcd_putchar(x)          lcd_data(x)
#define lcd_goto(x)             lcd_cmd(0x80+(x))
#define lcd_cursor_right()      lcd_cmd(0x14)
#define lcd_cursor_left()       lcd_cmd(0x10)
#define lcd_display_shift()     lcd_cmd(0x1C)
#define lcd_home()              lcd_cmd(0x02)
#define cursor_off              lcd_cmd(0x0C)
#define cursor_on               lcd_cmd(0x0F)
#define lcd_function_set        lcd_cmd(0x3C) // 8bit,two lines,5x10 dots
#define lcd_new_line            lcd_cmd(0xC0)


extern void lcd_cmd(unsigned char);
extern void lcd_data(unsigned char c);
extern void lcd_puts(const char *s);
extern void move_cursor_left(int mat_amount);
extern void lcd_init();
extern void lcd_strobe();
extern void DelayMs(unsigned int);
extern void DelayUs(unsigned int);

////================================================
////  Delay [ms]
////================================================
// functions:
void delay_ms(int ms);

__interrupt void Timer_A(void);
//__interrupt void Timer_B (void);

#endif
