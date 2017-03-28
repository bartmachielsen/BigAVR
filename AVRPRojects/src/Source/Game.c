/*
 * Game.c
 *
 * Created: 23/03/2017 11:19:44
 *  Author: maxde
 */

 #include "Headers/Game.h"
 #include "Headers/Dotmatrix.h"
 #include <time.h>
 #include <stdlib.h>


 int matrix[8][8];
 Object objects[20];
 Object object;
 Object object2;

 void InitGame(){
   object.block[0][0] = 1;
   object.block[0][1] = 1;
   object.block[1][0] = 1;
   object.block[1][1] = 1;
   object.x = 3;
   object.y = -1;
   object.stuck = 0;
   object2.block[0][0] = 1;
   object2.block[0][1] = 1;
   object2.block[1][0] = 1;
   object2.block[1][1] = 1;
   object2.x = 3;
   object2.y = -1;
   object2.stuck = 0;
 }

 void RandomBlock(){
	  srand(time(NULL));   // should only be called once
	  int r = rand();
 }

 void Fillmatrix(int checker){
	for (int i = 0; i < 8; i++)
	{
    for (int i2 = 0; i2 < 8; i2++)
  	{
      matrix[i][i2] = checker;
  	}
	}
 }



 void SendtoMatrix(){
   for (int i = 0; i < 8; i++)
 	{
    int rowvalue = 0;
    for (int i2 = 0; i2 < 8; i2++)
   	{
      if(matrix[i][i2] > 0){
        int temp = 0;
         switch (i2) {
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
    WriteRow(i*2,rowvalue);
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
   if(object.stuck == 0){
     if(object.y+1 == 7) object.stuck = 1;
     else object.y += 1;
   } else {
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
