/*
 * week3.c
 *
 * Created: 16-2-2017 10:44:37
 *  Author: bartm
 */ 
 #include "../Headers/week3.h"
 #include "../Headers/display.h"
 #include <util/delay.h>

 void Testweek3(){
	init_lcd();
	_delay_ms(10);
	lcd_writeLine1("hallo           ");
	lcd_writeLine2("bart            ");
 }