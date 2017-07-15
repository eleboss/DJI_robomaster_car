#include "main.h"

int motor_circle = 0;

void BODAN_Configuration()
{
	GPIO_InitTypeDef          gpio;
	TIM_TimeBaseInitTypeDef   tim;
	TIM_OCInitTypeDef         oc;
	NVIC_InitTypeDef 					nvic;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//ENCODER TIM1 PA8&9
	gpio.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA,&gpio);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1); 
	
	tim.TIM_Prescaler = 0;
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Period = 0xffff; 
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM1,&tim);
	
	nvic.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn ;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI2, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
	//TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM1,32767);
	TIM_Cmd(TIM1, ENABLE);

	//PWM PC4
	gpio.GPIO_Pin = GPIO_Pin_4;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&gpio);
	GPIO_SetBits(GPIOC, GPIO_Pin_4);
	
	//IN1,IN2 TIM3 PA7&6
	gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP; 
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&gpio);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7, GPIO_AF_TIM3); 
	
	tim.TIM_Prescaler = 84;
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Period = 2000;   //2.0ms
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&tim);
	
	oc.TIM_OCMode = TIM_OCMode_PWM2;
	oc.TIM_Pulse=0;  
	oc.TIM_OutputState = TIM_OutputState_Enable;
	oc.TIM_OutputNState = TIM_OutputState_Disable;
	oc.TIM_OCPolarity = TIM_OCPolarity_Low;
	oc.TIM_OCNPolarity = TIM_OCPolarity_High;
	oc.TIM_OCIdleState = TIM_OCIdleState_Reset;
	oc.TIM_OCNIdleState = TIM_OCIdleState_Set;
	TIM_OC1Init(TIM3,&oc);
	TIM_OC2Init(TIM3,&oc);		
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);		
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_CtrlPWMOutputs(TIM3,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}

void TIM1_UP_TIM10_IRQHandler()
{
	if(!((TIM1->CR1 &(TIM_CR1_DIR)) == (TIM_CR1_DIR)))
		motor_circle++;
	else
		motor_circle--;
	delay_us(10);
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
}

//2400 per circle
int BodanMotorPos(void)
{
    return TIM1->CNT;
}

void BodanMotorSpeed(int PWM_Bodan)
{
	PWM_Bodan = LIMIT_MIN_MAX(PWM_Bodan, -1600, 1600);
	if(PWM_Bodan >= 0)
	{
			TIM3->CCR1 = 0;
			TIM3->CCR2 = PWM_Bodan;
	}
	if(PWM_Bodan < 0)
	{
			TIM3->CCR1 = -PWM_Bodan;
			TIM3->CCR2 = 0;
	}
}
