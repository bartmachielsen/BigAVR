/*
 * display.c
 *
 * Created: 16-2-2017 10:52:35
 *  Author: bartm
 */ 

 #include "../Headers/display.h"
 #include <avr/io.h>
 #include <util/delay.h>

 void init_lcd(void)
 {
	 lcd_command( 0x02 );
	 lcd_command( 0x28 );
	 lcd_command( 0x0C );
	 lcd_command( 0x06 );
	 lcd_command( 0x80 );
 }

 void lcd_setcursor(int position){
	 // reset/unshift cursor
	 lcd_command( 0x02 );
	 lcd_command( 0x0F );

	 // decide in which row the cursor
	if(position<32)
	if (position<16)
	{
		for (int i = 0; i < position; i++)
		{
			lcd_command( 0x14 );
			_delay_ms(1);
		}
	} else {
		lcd_command( 0xC0 );
		_delay_ms(1);
		for (int i = 0; i < position-16; i++)
		{
			lcd_command( 0x14 );
			_delay_ms(1);
		}
	}
 }

 void lcd_command ( unsigned char dat )
 {
	 //send first half
	 PORTC = dat & 0xF0;
	 PORTC = PORTC | 0x08;
	 _delay_ms(1); 
	 PORTC = 0x04;

	 //send second half
	 PORTC = (dat & 0x0F) << 4; 
	 PORTC = PORTC | 0x08;
	 _delay_ms(1);
	 PORTC = 0x00;
 }

 void lcd_writeChar( unsigned char dat )
 {
	 //send first half
	 PORTC = dat & 0xF0;
	 PORTC = PORTC | 0x0C;
	 _delay_ms(1);
	 PORTC = 0x04;

	 //send second half
	 PORTC = (dat & 0x0F) << 4;
	 PORTC = PORTC | 0x0C;
	 _delay_ms(1);
	 PORTC = 0x00;
 }

 void lcd_writeLine1 ( char text1[] )
 {
	//set cursor to 1st position
	 lcd_command(0x80);
	 for (int i=0; i<16; i++) {
		 lcd_writeChar( text1[i] );
	 }
 }

 void lcd_writeLine2 ( char text2[] )
 {
	 lcd_command(0xC0);
	 for (int i=0; i<16; i++) {
		 lcd_writeChar( text2[i] );
	 }
 }

  void lcd_shift(int direction){ 
	  _delay_ms(10);
	  if(direction == 0){
		lcd_command(0x1C);
	  }else if(direction == 1){
		lcd_command(0x18);
	  }
	  _delay_ms(10);
  }
