/*
 * week1c.c
 *
 * Created: 02/02/2017 11:30:59
 *  Author: maxde
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "Headers/week1.h"
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
void BlinkLed(int speed, int amount){	CLEAR_ALL(PORTD);	for(int i = 0; i < amount; i++){		TOGGLE_BIT(PORTD, 7);		wait(speed);	}}// OPGAVE B3void LedButton(){				CLEAR_ALL(PORTD);	while (CHECK_BIT(PINC,0))
	{
		TOGGLE_BIT(PORTD, 7);
		wait(500);
	}}// OPGAVE B4void LoopLight(){	for(int i = 0; i < 8; i ++){		SET_ONLY_BIT(PORTD, i);		wait(100);	}	for(int i = 7; i > 0; i--){		SET_ONLY_BIT(PORTD, i);		wait(100);	}}// OPGAVE B6int States(int state){	int speeds[] = {1000,500,250};	int maxstate = 3;	if (CHECK_BIT(PINC,0))
	{
		state += 1;
		if(state > maxstate){
			state = 0;
		}
	}	BlinkLed(speeds[state],3);	return state;}// OPGAVE B5void Pattern(){	int array[] = {0b00000001,0b00000011,0b00000111,0b00001111,0b00011111,0b00111111,0b01111111,0b11111111,0b01111111,0b00111111,0b00011111,0b00001111,0b00000111,0b00000011,0b00000001,0b00000000};	int array2[] = {0b00000001,0b00000011,0b00000111,0b00001111,0b00011111,0b00111111,0b01111111,0b11111111,0b11111110,0b11111100,0b11111000,0b11110000,0b11100000,0b11000000,0b10000000,0b00000000};	int array3[] = {0b00011000,0b00111100,0b01111110,0b11111111,0b11100111,0b11000011,0b10000001,0b00000000,0b10000001,0b11000011,0b11100111,0b11111111,0b01111110,0b00111100,0b00011000,0b00000000};	for (int i = 0; i < sizeof(array)/sizeof(array[0]);i++)
	{
		PORTD = array[i];
		PORTB = array2[i];
		PORTF = array3[i];
		wait(100);
	}}void ChangePortValue(int port, int bitchange){	switch(port){		case 0:	PORTA = bitchange;		break;		case 1:	PORTB = bitchange;		break;		case 2:	PORTD = bitchange;		break;		case 3:	PORTE = bitchange;		break;		case 4:	PORTF = bitchange;		break;	}}void FullLoop(){	int amountofstrips = 5;	int amountofleds = 8;	for(int i = 0; i < amountofstrips*amountofleds; i++ ){		int bitchange = 1 << (i%8);		int strip = i/amountofleds;		if(i%amountofleds == 0){			ChangePortValue(strip-1,0);		}				ChangePortValue(strip, bitchange);		wait(100);		ChangePortValue(strip,0);	}	for(int i = amountofstrips*amountofleds; i > 1; i--){		int bitchange = 1 << (i%8);		int strip = i/amountofleds;		if(i%amountofleds == 0){			ChangePortValue(strip-1,0);		}				ChangePortValue(strip, bitchange);		wait(100);		ChangePortValue(strip,0);	}}void SetLedCharlieplexing(int ledid)
{
	PORTD &= 0xF8;
	DDRD  |= 0x07;

	switch ( ledid )
	{
		case 0:
				DDRD  &= 0xFB;
				PORTD |= 0x01;
				break;
		
		case 1:
				DDRD  &= 0xFB;
				PORTD |= 0x02;
				break;
		
		case 2:
				DDRD  &= 0xFE;
				PORTD |= 0x02;
				break;

		case 3:
				DDRD  &= 0xFE;
				PORTD |= 0x04;
				break;
		
		case 4:
				DDRD  &= 0xFD;
				PORTD |= 0x01;
		
		case 5:
				DDRD  &= 0xFD;
				PORTD |= 0x04;
				break;
	}}void CharliePlexing(){	for(int i = 0; i < 6; i ++){		SetLedCharlieplexing(i);		wait(500);	}}void Testweek1(){	//	D,A,B,E,F AS OUTPUT		//  C AS INPUT	DDRA = 0b11111111; 	DDRB = 0b11111111; 	DDRC = 0b10000000;	DDRD = 0b11111111; 	DDRE = 0b11111111; 	DDRF = 0b11111111;		CharliePlexing();		int state = 0;	while(1){		BlinkLedsSeperately();		LedButton();		LoopLight();		state = States(state);		Pattern();		//FullLoop();	}	}
