#ifndef __MOVE_H__
#define __MOVE_H__

#define MAXSPEED 200

typedef struct Speed
{
	int LeftSpeed_1;
	int RightSpeed_1;
	int LeftSpeed_2;
	int RightSpeed_2;
}Speed;

short offset_0(void);
short offset_1(void);
short offset_2(void);
short offset_3(void);

void MECANUM_MOVE(Speed *Sp,int x,int y,int w);


#endif 

