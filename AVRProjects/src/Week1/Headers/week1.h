/*
 * week1.h
 *
 * Created: 02/02/2017 11:31:10
 *  Author: maxde
 */ 


#ifndef WEEK1_H_
#define WEEK1_H_

void wait(int ms);
void BlinkLedsSeperately();
void BlinkLed(int speed, int amount);
void ledbutton();
void LoopLight();
int States(int state);
void Pattern();
void ChangePortValue(int port, int bitchange);
void FullLoop();
void Testweek1();


#endif /* WEEK1_H_ */