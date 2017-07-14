#ifndef __CONTROL_H__
#define __CONTROL_H__

#define SWITCH GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)

typedef struct AUTOCONTROL{
	unsigned char Catch;
}AUTOCONTROL;

void SWITCH_Configuration(void);
void AutoControl_Init(void);
void RCControl_Init(void);

#endif
