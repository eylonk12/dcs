// HAL - Hardware Abstraction Layer

#ifndef _hal_H_
#define _hal_H_

/*----------------------------------------------------------
  GLOBAL VARIABLES
------------------------------------------------------------*/

extern volatile unsigned int State;
extern volatile int screen;			      // remember the screen that is shown in state 2
extern volatile unsigned int KB;                      // This will be the value of the Key Board
extern volatile int* song_choice_freq; 
extern volatile int* song_choice_dc; 
extern volatile int  song_length; 
extern volatile int playing345ms;
 
/*----------------------------------------------------------
  SERVICE FUNCTIONS
------------------------------------------------------------*/

extern void clear_recording(void);
extern void print_recording_screen(void);
extern void Disable_TimerA_345msec(void);
extern void  Enable_TimerA_345msec(void);
extern void  Disable_TimerB_out_PWM(void);
extern void Enable_TimerB_out_PWM(void);
extern void  set_DMA_TB_connection(void);
extern void  menu_choose_song(void);
extern void Disable_DMA(void);

/*----------------------------------------------------------
  INTERRUPT FUNCTIONS
------------------------------------------------------------*/

extern __interrupt void PORT1_ISR (void);       //Push Buttons
extern __interrupt void PORT2_ISR (void);       //KEYPAD
extern __interrupt void Timer_A(void);    

/*----------------------------------------------------------
  CONFIG: LCD BASIC FUNCTIONS
------------------------------------------------------------*/
#ifdef CHECKBUSY
	#define	LCD_WAIT lcd_check_busy()
#else
	#define LCD_WAIT DelayMs(5)
#endif

#define FOURBIT_MODE	0x0
#define EIGHTBIT_MODE	0x1
#define LCD_MODE        FOURBIT_MODE
   
#define OUTPUT_PIN      1	
#define INPUT_PIN       0	
#define OUTPUT_DATA     (LCD_MODE ? 0xFF : (0x0F << LCD_DATA_OFFSET))
#define INPUT_DATA      0x00	

#define LCD_STROBE_READ(value)	LCD_EN(1), \
				asm("nop"), asm("nop"), \
				value=LCD_DATA_READ, \
				LCD_EN(0) 
				

#define	lcd_cursor(x)		lcd_cmd(((x)&0x7F)|0x80)
#define lcd_clear()		lcd_cmd(0x01)
#define lcd_putchar(x)		lcd_data(x)
#define lcd_goto(x)		lcd_cmd(0x80+(x))
#define lcd_cursor_right()	lcd_cmd(0x14)
#define lcd_cursor_left()	lcd_cmd(0x10)
#define lcd_display_shift()	lcd_cmd(0x1C)
#define lcd_home()	        lcd_cmd(0x02)
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

/*----------------------------------------------------------
  CONSTANTS: KEPAD DEFINES   // CHECK IF NEEDED
------------------------------------------------------------*/
extern int Recorder_song_freq[33];
extern int song1_freq[55];
extern int song2_freq[48];
extern int song3_freq[41];
extern int song1_dc[55];
extern int song2_dc[48];
extern int song3_dc[41];
extern int Record_Periods[13];
extern int Recorder_song_dc[33];

extern char Const_LCD_label_1[15];
extern char Const_LCD_label_2[15];
extern char Const_LCD_label_3[16];

#endif