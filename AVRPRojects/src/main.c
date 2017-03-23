/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "main.h"
#include <avr/io.h>



int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();
	DDRC = 0xFF;
	PORTC = 0x00;
	
	
		//Testweek1();
		//Testweek2();
		//Testweek3();
		Testweek4();
		while(1){
			
		}
	

	/* Insert application code here, after the board has been initialized. */
}
