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
 
 #define BOTTOM -1
 #define CENTER 0
 #define TOP 1

 #define JOYSTICK_CENTER 150
 #define JOYSTICK_ALLO_DIFF 25
 #define HORIZONTAL 1
 #define VERTICAL 0


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

 int GetPosition(int way){
	int address = 0b011000000;
	if(way == HORIZONTAL){
		address = 0b011000001;
	}
	ADMUX = address;
	PORTB = address;
	ADCSRA = 0b11100110;
	wait(100);
	return GetDirection(ADCL+ADCH);
 }


 void TestJoyStick(){
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRB = 0xFF;
	init_lcd();
	wait(10);
	while(1){
		char text[20];
		sprintf(text, "number: %i   %i    ", GetPosition(HORIZONTAL), GetPosition(VERTICAL));
		lcd_writeLine1(text);
		wait(10);
	}
 }