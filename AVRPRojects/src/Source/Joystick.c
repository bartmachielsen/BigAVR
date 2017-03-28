/*
 * Joystick.c
 *
 * Created: 23-3-2017 11:17:33
 *  Author: bartm
 */ 
 #include "../Headers/Joystick.h"
 #include "../Headers/display.h"
 #include "../Headers/week1.h"
 #include <stdio.h>
 #include <avr/io.h>


 int GetDirection(int value){
	int center_difference = JOYSTICK_CENTER-value;
	if((center_difference <= JOYSTICK_ALLO_DIFF && center_difference > 0) ||
			(center_difference <= 0 && -center_difference <= JOYSTICK_ALLO_DIFF)){
		return CENTER;
	}
	if(center_difference <= 0){
		return BOTTOM;
	}
	return TOP;
 }
 /*!
 *	Function for getting direction of joystick connected to portF
 *	Get position of given axis
 *	1 for horizontal (or use defined HORIZONTAL)
 *  0 for vertical (or use defined VERTICAL
 *	WARNING! FUNCTION NEEDS TO WAIT BETWEEN TWO READINGS!
 * @return a direction (BOTTOM,CENTER,TOP) as integer (-1,0,1)
 */
 int GetPosition(int way){
	int address = 0b011000000;
	if(way == HORIZONTAL){
		address = 0b011000001;
	}
	ADMUX = address;
	PORTB = address;
	ADCSRA = 0b11100110;
	return GetDirection(ADCL+ADCH);
 }

 void ShowOnDisplay(int positionx, int positiony){
	 char text[20];
	 sprintf(text, "number: %i   %i    ", positionx,positiony);
	 lcd_writeLine1(text);
 }


 void TestJoyStick(){
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRB = 0xFF;
	init_lcd();
	wait(10);
	while(1){
		char text[20];
		wait(50);
		int position1 = GetPosition(VERTICAL);
		wait(200);
		int position2 = GetPosition(HORIZONTAL);
		sprintf(text, "number: %i   %i    ", position1,position2);
		
		lcd_writeLine1(text);
		wait(10);
	}
 }