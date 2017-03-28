/*
 * Game.c
 *
 * Created: 23/03/2017 11:19:44
 *  Author: maxde
 */

 #include "Headers/week1.h"
 #include "Headers/Game.h"
 #include "Headers/Dotmatrix.h"
 #include "Headers/Joystick.h"
 #define HORIZONTAL_MATRIX_ROWS 8
 #define VERTICAL_MATRIX_ROWS 8
 
 int matrix[HORIZONTAL_MATRIX_ROWS][VERTICAL_MATRIX_ROWS];
 Object moving_object;

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
 void MoveObject(Object object){
	wait(50);
	int vertical_position = GetPosition(VERTICAL);
	wait(200);
	int horizontal_position = GetPosition(HORIZONTAL);
	object.x += horizontal_position;
	object.y += vertical_position;
	if(object.x > HORIZONTAL_MATRIX_ROWS-1){
		object.x = HORIZONTAL_MATRIX_ROWS-1;
	}
	if(object.x < 0){
		object.x = 0;
	}
	if(object.y > VERTICAL_MATRIX_ROWS-1){
		object.y = VERTICAL_MATRIX_ROWS-1;
	}
	if(object.y < 0){
		object.y = 0;
	}
 }

 void Fillmatrix(int checker){
	for (int x = 0; x < HORIZONTAL_MATRIX_ROWS; x++)
	{
		for (int y = 0; y < VERTICAL_MATRIX_ROWS; y++)
		{
			matrix[x][y] = checker;
		}
	}
 }



 void SendtoMatrix(){

	int tempmatrix[HORIZONTAL_MATRIX_ROWS][VERTICAL_MATRIX_ROWS];
	for (int x = 0; x < HORIZONTAL_MATRIX_ROWS; x++)
	{
		for (int y = 0; y < VERTICAL_MATRIX_ROWS; y++)
		{
			tempmatrix[x][y] = matrix[x][y];
		}
	}
	tempmatrix[moving_object.x][moving_object.y] = moving_object.block[0][0];
	tempmatrix[moving_object.x+1][moving_object.y] = moving_object.block[1][0];
	tempmatrix[moving_object.x][moving_object.y+1] = moving_object.block[0][1];
	tempmatrix[moving_object.x+1][moving_object.y+1] = moving_object.block[1][1];

   for (int x = 0; x < HORIZONTAL_MATRIX_ROWS; x++)
 	{
    int rowvalue = 0;
    for (int y = 0; y < VERTICAL_MATRIX_ROWS; y++)
   	{
      if(tempmatrix[x][y] > 0){
        int temp = 0;

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
        rowvalue = rowvalue + temp;
       }
   	}
    WriteRow(x*2,rowvalue);
 	}
 }

int collision(Object o1){
  if(matrix[o1.x][o1.y] || matrix[o1.x+1][o1.y] || matrix[o1.x][o1.y+2] || matrix[o1.x+1][o1.y+2] || o1.y+2 == VERTICAL_MATRIX_ROWS){
	return 1;
  }
  return 0;
}

 void Worldtick(){
	MoveObject(moving_object);
	// checking if object is stuck
	if(collision(moving_object)==0){
		moving_object.y += 1;
	}
	else {
		moving_object.stuck = 1;
		matrix[moving_object.x][moving_object.y] = moving_object.block[0][0];
		matrix[moving_object.x+1][moving_object.y] = moving_object.block[1][0];
		matrix[moving_object.x][moving_object.y+1] = moving_object.block[0][1];
		matrix[moving_object.x+1][moving_object.y+1] = moving_object.block[1][1];

		InitGame();
		
		if (collision(moving_object)==1)
		{
			Fillmatrix(0);
		}
	}

 }
