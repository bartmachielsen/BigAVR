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
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
#define SET_BIT(var, pos) var |= 1 << pos
#define CLEAR_BIT(var, pos) var &= ~(1 << pos)
#define TOGGLE_BIT(var, pos) var ^= 1 << pos
#define SET_ONLY_BIT(var, pos) var = 1 << pos
#define CLEAR_ALL(var) var = 0

void wait(int ms)
{
	for (int i=0; i<ms; i++)
	{
		//max wait is 30ms with 8Mhz
		_delay_ms( 1 );
	}
}
//	OPGAVE B2
void BlinkLedsSeperately(){
	CLEAR_ALL(PORTD);
	SET_ONLY_BIT(PORTD,7);
	wait(500);
	SET_ONLY_BIT(PORTD,6);
	wait(500);
}

	{
		TOGGLE_BIT(PORTD, 7);
		wait(500);
	}
	{
		state += 1;
		if(state > maxstate){
			state = 0;
		}
	}
	{
		PORTD = array[i];
		PORTB = array2[i];
		PORTF = array3[i];
		wait(100);
	}