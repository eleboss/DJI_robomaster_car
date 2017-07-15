#include "main.h"
//TIM8-CH1/2, PC6/7, Ä¦²ÁÂÖ

void RubWheelPWMConfiguration(void)
{
		GPIO_InitTypeDef          gpio;
    TIM_TimeBaseInitTypeDef   tim;
    TIM_OCInitTypeDef         oc;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
		gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		gpio.GPIO_OType = GPIO_OType_PP; 
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOC,&gpio);

		GPIO_PinAFConfig(GPIOC,GPIO_PinSource6, GPIO_AF_TIM8);
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource7, GPIO_AF_TIM8);
		
		tim.TIM_Prescaler = 167;
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_Period = 20000;   
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM8,&tim);

		oc.TIM_OCMode = TIM_OCMode_PWM2;
    oc.TIM_OutputState = TIM_OutputState_Enable;
    oc.TIM_OutputNState = TIM_OutputState_Disable;
    oc.TIM_Pulse = 0;
    oc.TIM_OCPolarity = TIM_OCPolarity_Low;
    oc.TIM_OCNPolarity = TIM_OCPolarity_High;
    oc.TIM_OCIdleState = TIM_OCIdleState_Reset;
    oc.TIM_OCNIdleState = TIM_OCIdleState_Set;
		TIM_OC1Init(TIM8,&oc);
		TIM_OC2Init(TIM8,&oc);
		TIM_OC1PreloadConfig(TIM8,TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM8,TIM_OCPreload_Enable);
			
		TIM_ARRPreloadConfig(TIM8,ENABLE);
    TIM_CtrlPWMOutputs(TIM8,ENABLE);
    TIM_Cmd(TIM8,ENABLE);
}
