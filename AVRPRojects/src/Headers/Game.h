/*
 * IncFile1.h
 *
 * Created: 23/03/2017 11:19:52
 *  Author: maxde
 */


#ifndef INCFILE1_H_
#define INCFILE1_H_

typedef struct {
  int block[2][2];
  int x, y;
  int stuck;
} Object;

void Fillmatrix(int checker);
void SendtoMatrix(void);
void InitGame(void);
void Showscore(void);
void Worldtick(void);
int collision(Object);



#endif /* INCFILE1_H_ */
