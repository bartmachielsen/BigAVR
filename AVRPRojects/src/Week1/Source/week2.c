/*
 * week2.c
 *
 * Created: 09/02/2017 10:38:42
 *  Author: maxde
 */ 
 
 #define F_CPU 8000000
 #include "Week1/Headers/week2.h"
 #include "Week1/Headers/week1.h"
 #include <avr/io.h>
 #include <util/delay.h>

 patroon table[] = {
	 {0b00111111,500}, //0
	 {0b00010010,500}, //1
	 {0b01001111,500}, //2
	 {0b01011011,500}, //3
	 {0b01110010,500}, //4
	 {0b11111001,500}, //5
	 {0b11111101,500}, //6
	 {0b00010011,500}, //7
	 {0b01111111,500}, //8
	 {0b01111011,500}, //9

	 {0b01110111,500}, //a
	 {0b01111100,500}, //b
	 {0b00101101,500}, //c
	 {0b01011110,500}, //d
	 {0b01101111,500}, //e
	 {0b01100101,500}, //f
	 {0b01101101,500}  //E
 };

 patroon FUN[] = {
	 {0b00111111,100},
	 {0b00000000,100},
	 {0b00111111,100},
	 {0b00000000,100},
	 {0b00111111,100},
	 {0b00000000,100},
	 {0b00000001,100},
	 {0b00000011,100},
	 {0b00010011,100},
	 {0b00011011,100},
	 {0b00011111,100},
	 {0b00111111,100},
	 {0b01111111,100},
	 {0b01111110,100},
	 {0b01111100,100},
	 {0b01101100,100},
	 {0b01100100,100},
	 {0b01100000,100},
	 {0b01000000,100},
	 {0b00000000,100},
 };
  
 void SevenSegment(int Display){
	if (Display>16)
	{
		PORTD = table[16].Byte;
	} else{
		PORTD = table[Display].Byte;
	}
 }

 void HexidecimaleCijfers(){
	 // Opgave 3
	 for(int i = 0; i <17; i++){
		 SevenSegment(i);
		 wait(table[i].delay);
	 }
 }

 void FunDisplay(){
 	 // Opgave 4
	 for(int i = 0; i <20; i++){
		 PORTD = FUN[i].Byte;
		 wait(FUN[i].delay);
	 }
 }

 void Testweek2(){ 	DDRD = 0b11111111;

	while(1){
		HexidecimaleCijfers();
		FunDisplay();
	}
 }