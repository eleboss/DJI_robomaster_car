#ifndef __USART3_H__
#define __USART3_H__

#define RBPackSize 16
#define TBPackSize 7

typedef struct AUTOCONTROL{
	short  Yaw_Reset;
	short  Slide_Auto;
	short  Turn_Auto;
	short		Grab_Auto;
	short  Land_Auto;
	short  Grab_Fin;
	short Finished;
	short Y_Auto;
	short X_Auto;
	short Yaw_Auto;
	short Y_Pos;
	short	X_Pos;
}AUTOCONTROL;

void USART3_Configuration(void);
void AutoControlInit(void);

#endif
