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
#define F_CPU 8000000
#include <asf.h>
#include "main.h"
#include <avr/io.h>



int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();
	
	DDRD = 0b11111111;
	DDRC = 0b00000000;
	
	while (1)
	{
		BlinkLedsSeperately(500);
	}

	/* Insert application code here, after the board has been initialized. */
}
