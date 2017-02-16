/*
 * display.h
 *
 * Created: 16-2-2017 10:52:46
 *  Author: bartm
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

void init_lcd(void);
void lcd_setcursor(int position);
void lcd_command ( unsigned char dat );
void lcd_writeChar( unsigned char dat );
void lcd_writeLine1 ( char text1[] );
void lcd_writeLine2 ( char text2[] );
void lcd_shift( int direction);


#endif /* DISPLAY_H_ */