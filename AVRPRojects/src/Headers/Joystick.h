/*
 * Joystick.h
 *
 * Created: 23-3-2017 11:17:48
 *  Author: bartm
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_
 #define BOTTOM -1
 #define CENTER 0
 #define TOP 1

 #define JOYSTICK_CENTER 150
 #define JOYSTICK_ALLO_DIFF 25
 #define HORIZONTAL 1
 #define VERTICAL 0

 int GetDirection(int);
 int GetPosition(int);
 void ShowOnDisplay(int positionx, int positiony);
 void TestJoyStick(void);




#endif /* JOYSTICK_H_ */