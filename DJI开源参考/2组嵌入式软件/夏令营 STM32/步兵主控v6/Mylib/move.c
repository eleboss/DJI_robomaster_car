#include "main.h"

extern RC_Ctl_t RC_Ctl; 

short offset_0(void)
{
  short offset;
	offset=(short)(RC_Ctl.rc.ch0-1024.0f)/660.0*MAXSPEED;
	if(abs(RC_Ctl.rc.ch0-1024)<10)
	{
		offset = 0;
	}
	return offset;
}
short offset_1(void)
{
  short offset;
	offset=(short)(RC_Ctl.rc.ch1-1024.0f)/660.0*MAXSPEED;
	if(abs(RC_Ctl.rc.ch1-1024)<10)
	{
		offset = 0;
	}
	return offset;
}
short offset_2(void)
{
  short offset;
	offset=(short)(RC_Ctl.rc.ch2-1024.0f)/660.0*MAXSPEED;
	if(abs(RC_Ctl.rc.ch2-1024)<10)
	{
		offset = 0;
	}
	return offset;
}
short offset_3(void)
{
  short offset;
	offset=(short)(RC_Ctl.rc.ch3-1024.0f)/660.0*MAXSPEED;
	if(abs(RC_Ctl.rc.ch3-1024)<10)
	{
		offset = 0;
	}
	return offset;
}

void MECANUM_MOVE(Speed *Sp,int x,int y,int w)
{
	Sp->LeftSpeed_1 = x+y-w;
	Sp->RightSpeed_1 = -x+y+w;
	Sp->LeftSpeed_2 = -x+y+-w;
	Sp->RightSpeed_2 = x+y+w;
}
