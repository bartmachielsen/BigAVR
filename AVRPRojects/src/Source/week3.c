/*
 * week3.c
 *
 * Created: 16-2-2017 10:44:37
 *  Author: bartm
 */ 
 #include "../Headers/week3.h"
 #include "../Headers/display.h"
 #include "../Headers/week1.h"
 #include <stdio.h>
 #include <util/delay.h>
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #define LED PD4
 #define SET_ONLY_BIT(var, pos) var = 1 << pos
 #define CLEAR_ALL(var) var = 0x00
 #define MAX_OVERFLOW 2
 #define REMAINDER_TIMER 31250

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

// 
//  int counter = 0;
//   ISR(INT0_vect){
// 		char text[20];
// 		sprintf(text, "%i           ", counter);
// 		lcd_setcursor(1);
// 		lcd_writeLine1(text);
// 
// 		
// 		counter++;
// 		PORTD = 0x000000000;
// }
//  void ShowPushCount(){
// 	 DDRD = 0xFF;
// 	 EICRA |= 0b00001010;
// 	 EIMSK |= 0b00000011;
// 	 sei();
//  }




  int overflow_count = 0;

  ISR ( TIMER1_OVF_vect )
  {
	  TCNT1 = REMAINDER_TIMER; // Reload timer with precalculated value
	  overflow_count += 1;
	  if(overflow_count >= MAX_OVERFLOW){
		  overflow_count = 0;
		  PORTC ^= (1 << 0) ; // Toggle the LED
	  }
  }

  void init_timer()
  {
	  DDRC |= (1 << 0);
	  
	  TIMSK |= (1 << TOIE1 ); // Enable overflow interrupt
	  sei () ; // Enable global interrupts
	  
	  TCNT1 = REMAINDER_TIMER; // Preload timer with precalculated value
	  
	  TCCR1B |= ((1 << CS10 ) | (1 << CS11 )) ; // Set up timer at Fcpu /64	//	CS11 --> CS12 bij 1024 preloader
  }


 void Testweek3(){
 	init_lcd();
 	_delay_ms(10);
 	lcd_writeLine1("hallo           ");
 	lcd_writeLine2("Diederich         ");

	//ShowPushCount();
	init_timer();


 	lcd_setcursor(16);
 	ShiftText();



	

}
