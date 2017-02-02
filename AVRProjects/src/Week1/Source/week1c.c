/*
 * week1c.c
 *
 * Created: 02/02/2017 11:30:59
 *  Author: maxde
 */ 

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
}
