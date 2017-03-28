/*
 * Game.c
 *
 * Created: 23/03/2017 11:19:44
 *  Author: maxde
 */

 #include "Headers/week1.h"
 #include "Headers/Game.h"
 #include "Headers/Dotmatrix.h"
 #include "Headers/display.h"
 #include "Headers/Joystick.h"
  #include <stdio.h>
  #include <avr/io.h>
 #define HORIZONTAL_MATRIX_ROWS 8
 #define VERTICAL_MATRIX_ROWS 8
 #define ROW_SCORE 1


 int matrix[HORIZONTAL_MATRIX_ROWS][VERTICAL_MATRIX_ROWS];
 Object moving_object;
 int score = 0;
 int highscore = 0;

 void InitGame(){
   moving_object.block[0][0] = 1;
   moving_object.block[0][1] = 1;
   moving_object.block[1][0] = 1;
   moving_object.block[1][1] = 1;
   moving_object.x = 3;
   moving_object.y = 0;
   moving_object.stuck = 0;
 }
 /*!
 * Function for moving objects in matrix (changing position variables)
 * WARNING! FUNCTION WAITS FOR 250 MS TO MAKE SURE THAT THE READINGS ARE NOT TO FAST
 */
 void MoveObject(Object* object){
	wait(50);
	int vertical_position = -GetPosition(VERTICAL);
	wait(200);
	int horizontal_position = GetPosition(HORIZONTAL);

	
	object->x += horizontal_position;
	if(vertical_position != 1){
		object->y += vertical_position;
	}
	if(collision(*object) || object->x < 0 || object->x >= HORIZONTAL_MATRIX_ROWS-1 || object->y < 0 || object->y >= VERTICAL_MATRIX_ROWS){
		object->x -= horizontal_position;

		
	}

 }

 void MoveAll(int start){
	for(int row = start-1; row >= 0; row--){
		for(int x = 0; x < HORIZONTAL_MATRIX_ROWS; x++){
			matrix[x][row+1] = matrix[x][row];
		}
	}
 }

 void Showscore(){
	char text[16];
	char text2[16];
	sprintf(text, "HIGHSCORE: %i      ", highscore);
	sprintf(text2, "SCORE: %i         ", score);
	lcd_writeLine1(text);
	lcd_writeLine2(text2);
 }

 void CheckRowsFinished(){
	for(int row = VERTICAL_MATRIX_ROWS-1; row >= 0; row--){
		int complete = 1;
		for(int x = 0; x < HORIZONTAL_MATRIX_ROWS; x++){
			if(matrix[x][row] == 0){
				complete = -1;
			}
		}
		
		if(complete == 1){
			MoveAll(row);
			score += ROW_SCORE;
			CheckRowsFinished();
			break;
		}
	}
	
 }
 /*
	DESCRIPTION: this function fills the matrix with the value given, this is used for resetting the matrix by calling
	this function with paramater 0
	INPUT: int value which the matrix need to be filled with
 */
 void Fillmatrix(int checker){
	for (int x = 0; x < HORIZONTAL_MATRIX_ROWS; x++)
	{
		for (int y = 0; y < VERTICAL_MATRIX_ROWS; y++)
		{
			matrix[x][y] = checker;
		}
	}
 }

 /*
	DESCRIPTION: this function makes an temporary 2d array and fills it with the matrix and the moving_object
	then the 2d array is calculated per column and send to the Dotmatrix
 */
 void SendtoMatrix(){
	// the temporary 2d array
	int tempmatrix[HORIZONTAL_MATRIX_ROWS][VERTICAL_MATRIX_ROWS];
	// copies the matrix in the temporary 2d array
	for (int x = 0; x < HORIZONTAL_MATRIX_ROWS; x++)
	{
		for (int y = 0; y < VERTICAL_MATRIX_ROWS; y++)
		{
			tempmatrix[x][y] = matrix[x][y];
		}
	}
	// copies the moving_object in the temporary 2d array
	tempmatrix[moving_object.x][moving_object.y] = moving_object.block[0][0];
	tempmatrix[moving_object.x+1][moving_object.y] = moving_object.block[1][0];
	tempmatrix[moving_object.x][moving_object.y+1] = moving_object.block[0][1];
	tempmatrix[moving_object.x+1][moving_object.y+1] = moving_object.block[1][1];

	// calculates the value needed to send to the dotmatrix per column 
   for (int x = 0; x < HORIZONTAL_MATRIX_ROWS; x++)
 	{
	// temp value of the row
    int rowvalue = 0;
    for (int y = 0; y < VERTICAL_MATRIX_ROWS; y++)
   	{
		// if the value in the matrix is 0 it does need to add a value to the rowvalue
        if(tempmatrix[x][y] > 0){
			 int temp = 0;
			 //the value of each led which needs to be added for that led to turn on
			 switch (y) {
			   case 0:
			   temp = 128;
			   break;
			   case 1:
			   temp = 1;
			   break;
			   case 2:
			   temp = 2;
			   break;
			   case 3:
			   temp = 4;
			   break;
			   case 4:
			   temp = 8;
			   break;
			   case 5:
			   temp =16;
			   break;
			   case 6:
			   temp = 32;
			   break;
			   case 7:
			   temp = 64;
			   break;
         }
		// Add the value of that led to the rowvalue
        rowvalue = rowvalue + temp;
       }
   	}
	// Writes one row per time with that rows rowvalue
    WriteRow(x*2,rowvalue);
 	}
 }

 /*
	DESCRIPTION: this function checks if the object will overlap the matrix in the next step
	INPUT: Object o1 the object that is falling
	OUTPUT: returns 1 if the it will overlap. returns 0 if it wont overlap
 */
int collision(Object o1){
  if(matrix[o1.x][o1.y] || matrix[o1.x+1][o1.y] || matrix[o1.x][o1.y+2] || matrix[o1.x+1][o1.y+2] || o1.y+2 == VERTICAL_MATRIX_ROWS){
	return 1;
  }
  return 0;
}


/*
	DESCRIPTION: this is the function which handles the whole game logic
*/
 void Worldtick(){
	// handles joystick input
	MoveObject(&moving_object);
	// checking if object is stuck
	if(collision(moving_object)==0){
		// if not stuck move the object down
		moving_object.y += 1;
	}
	else {
		//if the object is stuck, make it stuck and place its position in the matrix
		moving_object.stuck = 1;
		matrix[moving_object.x][moving_object.y] = moving_object.block[0][0];
		matrix[moving_object.x+1][moving_object.y] = moving_object.block[1][0];
		matrix[moving_object.x][moving_object.y+1] = moving_object.block[0][1];
		matrix[moving_object.x+1][moving_object.y+1] = moving_object.block[1][1];

		//because it is stuck we need to check if this made an complete row
		CheckRowsFinished();
		//compare score with highscore
		if(score > highscore){
			highscore = score;
		}
		//reset the object
		InitGame();
		
		//check if the new object is already stuck
		if (collision(moving_object)==1)
		{
			//if so the game is over
			//clear the matrix and reset score
			Fillmatrix(0);
			score = 0;
		}
		//update score on LCD
		Showscore();
	}
	

 }
