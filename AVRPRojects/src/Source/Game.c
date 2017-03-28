/*
 * Game.c
 *
 * Created: 23/03/2017 11:19:44
 *  Author: maxde
 */

 #include "Headers/Game.h"
 #include "Headers/Dotmatrix.h"
 #include "Headers/Joystick.h"
 #define HORIZONTAL_MATRIX_ROWS 8
 #define VERTICAL_MATRIX_ROWS 8
 
 int matrix[HORIZONTAL_MATRIX_ROWS,VERTICAL_MATRIX_ROWS];
 Object moving_object;

 void InitGame(){
   moving_object.block[0][0] = 1;
   moving_object.block[0][1] = 1;
   moving_object.block[1][0] = 1;
   moving_object.block[1][1] = 1;
   moving_object.x = 3;
   moving_object.y = -1;
   moving_object.stuck = 0;

 }

 void MoveObject(Object object){
	GetPosition(VERTICAL);
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
   for (int x = 0; x < HORIZONTAL_MATRIX_ROWS; x++)
 	{
    int rowvalue = 0;
    for (int y = 0; y < VERTICAL_MATRIX_ROWS; y++)
   	{
      if(matrix[x][y] > 0){
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

int collision(Object o1, Object o2){
  if(o1.x == o2.x || o1.x+1 == o2.x || o1.x == o2.x+1){
    if(o2.y+2 == o1.y){
      return 1;
    }
  }
  return 0;
}

 void Worldtick(){
    int i;
	Object object;
	for(i = 0; i < added_objects; i++){
		object = objects[i];
		// checking if object is stuck on bottom
		if(object.stuck == 0){
			if(object.y+1 == VERTICAL_MATRIX_ROWS-1) object.stuck = 1;
			else object.y += 1;
		}
		//	check collision
	}


   
     if(collision(object,object2) || object2.y+1 == 7) object2.stuck = 1;
     else object2.y += 1;

        matrix[object2.x][object2.y] = object2.block[0][0];
        matrix[object2.x+1][object2.y] = object2.block[1][0];
        matrix[object2.x][object2.y+1] = object2.block[0][1];
        matrix[object2.x+1][object2.y+1] = object2.block[1][1];
   }



   matrix[object.x][object.y] = object.block[0][0];
   matrix[object.x+1][object.y] = object.block[1][0];
   matrix[object.x][object.y+1] = object.block[0][1];
   matrix[object.x+1][object.y+1] = object.block[1][1];
 }
