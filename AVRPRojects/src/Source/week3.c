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
 #define ON_TIME 15
 #define OFF_TIME 25


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



   int state = 0;
   int ms = 0;
  ISR( TIMER2_COMP_vect )
  {
  
	  ms += 1; // Increment ms counter
	  if((state == 0 && ms >= OFF_TIME) || (state == 1 && ms >= ON_TIME)){
		  PORTC ^= 1<<1; // Toggle bit 0 van PORTC
		  state +=1;
		  if(state > 1){
			state = 0;
		  }
		  ms = 0; // Reset ms_count value
	  } 
   }

 void init_counter(){
	 DDRD = 0b000000000;
	 DDRA = 0xFF;
	 TCNT2 = 0x00;
	 DDRB = 0xFF;
	 OCR2 = 1;
	 TIMSK |= 0b0000001;
	 TCCR2 = 0x07; 
	 while(1){
		 PORTA = TCNT2; // debugging
		 char text[20];
		 sprintf(text, "number: %i       ", TCNT2);
		 lcd_writeLine1(text);
		 wait(10);
	 }

 }

  void init_timer()
  {
	  DDRC = 0xFF;
	  OCR2 = 125; // Preload timer with precalculated value
	  TIMSK |= 1 << 7; // Enable overflow interrupt
	  TCCR2 = 0b00001011;
	  sei(); 
	 }


 void Testweek3(){
 	init_lcd();
 	_delay_ms(10);
 	lcd_writeLine1("hallo           ");
 	lcd_writeLine2("Diederich         ");

	//ShowPushCount();
	//init_timer();
	//init_counter();

 	//lcd_setcursor(16);
 	//ShiftText();



	

}
