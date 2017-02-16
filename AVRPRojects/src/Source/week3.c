/*
 * week3.c
 *
 * Created: 16-2-2017 10:44:37
 *  Author: bartm
 */ 
 #include "../Headers/week3.h"
 #include "../Headers/display.h"
 #include "../Headers/week1.h"
 #include <util/delay.h>

 void ShiftText(){
	 while(1){
		 for(int i = 0; i < 18; i++){
			 wait(300);
			 lcd_shift(0);
		 }
		 for(int i = 0; i < 18; i++){
			 wait(300);
			 lcd_shift(1);
		 }
	 }
 }



 void Testweek3(){
	init_lcd();
	_delay_ms(10);
	lcd_writeLine1("hallo           ");
	lcd_writeLine2("bart            ");
	lcd_setcursor(16);
	//dont know if this works bart, was a merge conflict so yeah.. ShiftText();
}
