#include "main.h"

void MOTOR_Configuration(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	gpio.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_12;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE,&gpio);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
}
//轮子上升下降  STEP:PC4,PC5  DIR:PC1,PC0
void Wheel_Move(u32 wheel,u32 dir,u32 delay)
{
	u32 i=0;
	if(dir==1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_0);
		GPIO_SetBits(GPIOC,GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	}
	for(i=0;i<=wheel;i++)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_5);
		GPIO_SetBits(GPIOC,GPIO_Pin_4);
		Delay_Us(delay);
		GPIO_ResetBits(GPIOC,GPIO_Pin_5);
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		Delay_Us(delay);
	}
}
//退箱子  STEP:PA5 DIR:PA4
void Push_Move(u32 wheel,u32 dir,u32 delay)
{
	u32 i=0;
	if(dir==1)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	}
	for(i=0;i<=wheel;i++)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		Delay_Us(delay);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		Delay_Us(delay);
	}
}
//箱子夹子  STEP:PC3,PC2  DIR:PB1,PB0
void Fetch_Move(u32 wheel,u32 dir,u32 delay)
{
	u32 i=0;
	if(dir==1)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
		GPIO_SetBits(GPIOB,GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	}
	for(i=0;i<=wheel;i++)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_3);
		GPIO_SetBits(GPIOC,GPIO_Pin_2);
		Delay_Us(delay);
		GPIO_ResetBits(GPIOC,GPIO_Pin_3);
		GPIO_ResetBits(GPIOC,GPIO_Pin_2);
		Delay_Us(delay);
	}
}
//夹子提升降落  STEP:PE6,PE5 DIR:PE12,PE4
void Updown_Move(u32 wheel,u32 dir,u32 delay)
{
	u32 i=0;
	if(dir==1)
	{
		GPIO_SetBits(GPIOE,GPIO_Pin_12);
		GPIO_SetBits(GPIOE,GPIO_Pin_4);
	}
	else
	{
		GPIO_ResetBits(GPIOE,GPIO_Pin_12);
		GPIO_ResetBits(GPIOE,GPIO_Pin_4);
	}
	for(i=0;i<=wheel;i++)
	{
		GPIO_SetBits(GPIOE,GPIO_Pin_6);
		GPIO_SetBits(GPIOE,GPIO_Pin_5);
		Delay_Us(delay);
		GPIO_ResetBits(GPIOE,GPIO_Pin_6);
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);
		Delay_Us(delay);
	}
}
