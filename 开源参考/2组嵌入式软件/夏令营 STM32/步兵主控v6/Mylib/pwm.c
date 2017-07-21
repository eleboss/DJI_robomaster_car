#include "main.h"

void PWM_Configuration()
{
		GPIO_InitTypeDef          gpio;
    TIM_TimeBaseInitTypeDef   tim;
    TIM_OCInitTypeDef         oc;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
		gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		gpio.GPIO_Mode = GPIO_Mode_OUT;
		gpio.GPIO_OType = GPIO_OType_PP; 
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB,&gpio);
	
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource6, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource7, GPIO_AF_TIM4);
	
		tim.TIM_Prescaler = 83;
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_Period = 2999;   
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM4,&tim);
		
		oc.TIM_OCMode = TIM_OCMode_PWM2;
    oc.TIM_OutputState = TIM_OutputState_Enable;
    oc.TIM_OutputNState = TIM_OutputState_Disable;
    oc.TIM_Pulse = 0;
    oc.TIM_OCPolarity = TIM_OCPolarity_Low;
    oc.TIM_OCNPolarity = TIM_OCPolarity_High;
    oc.TIM_OCIdleState = TIM_OCIdleState_Reset;
    oc.TIM_OCNIdleState = TIM_OCIdleState_Set;
    TIM_OC1Init(TIM4,&oc);
		TIM_OC2Init(TIM4,&oc);
		TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
		TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);		
		
		TIM_ARRPreloadConfig(TIM4,ENABLE);
    TIM_CtrlPWMOutputs(TIM4,ENABLE);
    TIM_Cmd(TIM4,ENABLE);
}
