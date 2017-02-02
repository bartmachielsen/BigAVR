/*
 * week1c.c
 *
 * Created: 02/02/2017 11:30:59
 *  Author: maxde
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "Week1/Headers/week1.h"

void BlinkLedsSeperately(int delay){
	PORTD = 0b00000010;
	wait(delay);
	PORTD = 0b00000100;
	wait(delay);
}

void wait(int ms)
{
	for (int i=0; i<ms; i++)
	{
		//max wait is 30ms with 8Mhz
		_delay_ms( 1 ); 
	}
}void Testweek1(){	DDRD = 0b11111111;
	DDRC = 0b10000000;	DDRA = 0b11111111;	DDRB = 0b11111111;	DDRF = 0b11111111;	DDRF = 0b11111111;			int array[] = {0b00000001,0b00000011,0b00000111,0b00001111,0b00011111,0b00111111,0b01111111,0b11111111,0b01111111,0b00111111,0b00011111,0b00001111,0b00000111,0b00000011,0b00000001,0b00000000};	int array2[] = {0b00000001,0b00000011,0b00000111,0b00001111,0b00011111,0b00111111,0b01111111,0b11111111,0b11111110,0b11111100,0b11111000,0b11110000,0b11100000,0b11000000,0b10000000,0b00000000};	int array3[] = {0b00011000,0b00111100,0b01111110,0b11111111,0b11100111,0b11000011,0b10000001,0b00000000,0b10000001,0b11000011,0b11100111,0b11111111,0b01111110,0b00111100,0b00011000,0b00000000};		int state = 1;	while(1){		if (PINC & 0b00000001)
		{
			BlinkLedsSeperately(500);
		}
		else{
			PORTD = 0;
		}				//state		if (PINC & 0b00000010)
		{
			state += 1;
			if(state == 4){
				state = 1;
			}
		}				switch (state)
		{
			case 1:
			for(int i = 0; i < 3; i++){
				PORTC = 0b10000000;
				wait(1000);
				PORTC = 0b00000000;
				wait(1000);
			}
			break;
			case 2:
			for(int i = 0; i < 3; i++){
				PORTC = 0b10000000;
				wait(500);
				PORTC = 0;
				wait(500);				
			}
			break;
			case 3:
			for(int i = 0; i < 3; i++){
				PORTC = 0b10000000;
				wait(250);
				PORTC = 0;
				wait(250);	
			}
			break;
		}				//patroon		for (int i = 0; i < sizeof(array)/sizeof(array[0]);i++)
		{
			PORTD = array[i];
			PORTB = array2[i];
			PORTF = array3[i];
			wait(50);
		}				//looplicht		for (int i = 0; i <8; i++)
		{
			PORTA = 0b00000001 << i;
			wait(50);
		}		for (int i = 1; i <7; i++)
		{
			PORTA = 0b10000000 >> i;
			wait(50);
		}			}	}
