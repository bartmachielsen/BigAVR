/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ledmatrix.c
**
** Beschrijving:	Simple HT16K33 Ledmatix demo.
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ledmatrix.c
**					avr-gcc -g -mmcu=atmega128 -o ledmatrix.elf ledmatrix.o
**					avr-objcopy -O ihex ledmatrix.elf ledmatrix.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/


#include <avr/io.h>
#include <util/delay.h>
#include "Headers/week1.h"

/******************************************************************/
void twi_init(void)
/* 
short:			Init AVR TWI interface and set bitrate
inputs:			
outputs:	
notes:			TWI clock is set to 100 kHz
Version :    	DMK, Initial code
*******************************************************************/
{
	TWSR = 0;
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}

/******************************************************************/
void twi_start(void)
/* 
short:			Generate TWI start condition
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	TWCR = (0x80 | 0x20 | 0x04);
	while( 0x00 == (TWCR & 0x80) );
}

/******************************************************************/
void twi_stop(void)
/* 
short:			Generate TWI stop condition
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	TWCR = (0x80 | 0x10 | 0x04);
}

/******************************************************************/
void twi_tx(unsigned char data)
/* 
short:			transmit 8 bits data
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}

/******************************************************************/


void WriteRow(int row, int value){
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(row);	// Address
	twi_tx(value);	// data
	twi_stop();
}


/******************************************************************/
int InitDotmatrix( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Looping forever
Version :    	DMK, Initial code
*******************************************************************/
{
	
	twi_init();		// Init TWI interface

	// Init HT16K22. Page 32 datasheet
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit - because of TWI this is the adress of the display
	twi_tx(0x21);	// Internal osc on (page 10 HT16K33) - Normal operation mode
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit - because of TWI this is the adress of the display
	twi_tx(0xA0);	// HT16K33 pins all output
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit - because of TWI this is the adress of the display
	twi_tx(0xEF);	// Display Dimming 16/16 duty cycle - full brightness
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit - because of TWI this is the adress of the display
	twi_tx(0x81);	// Display ON - Blink ON
	twi_stop();

	return 1;
}
