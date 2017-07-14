#include "main.h"

AUTOCONTROL AutoControl;
extern RC_Ctl_t RC_Ctl; 

void SWITCH_Configuration(void)
{
	GPIO_InitTypeDef gpio;   

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	
	gpio.GPIO_Pin = GPIO_Pin_1;	
	gpio.GPIO_Mode = GPIO_Mode_IPU;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);
}


void AutoControl_Init(void)
{
	AutoControl.Catch = 0;
}


void RCControl_Init(void)
{
	RC_Ctl.rc.ch0 = 1024;
	RC_Ctl.rc.ch1 = 1024;
	RC_Ctl.rc.ch2 = 1024;
	RC_Ctl.rc.ch3 = 1024;
	RC_Ctl.rc.s1 = 1;
	RC_Ctl.rc.s2 = 1;
}
