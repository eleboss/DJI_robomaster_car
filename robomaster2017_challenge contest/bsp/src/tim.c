#include "main.h"
uint32_t SystickCount0=0,SystickCount1=0;
void TIM6_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  tim;
    NVIC_InitTypeDef         nvic;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
    
    nvic.NVIC_IRQChannel = TIM6_DAC_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    tim.TIM_Prescaler = 90-1;        //84M internal clock
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    tim.TIM_Period = 1000;  //1ms,1000Hz
    TIM_TimeBaseInit(TIM6,&tim);
}
void TIM7_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  tim;
    NVIC_InitTypeDef         nvic;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
    
    nvic.NVIC_IRQChannel = TIM7_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    tim.TIM_Prescaler = 90-1;        //90M internal clock
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    tim.TIM_Period = 1000;  //1ms,1000Hz
    TIM_TimeBaseInit(TIM7,&tim);

}

void TIM6_Start(void)
{
    TIM_Cmd(TIM6, ENABLE);	 
    TIM_ITConfig(TIM6, TIM_IT_Update,ENABLE);
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);	
	
}
void TIM6_Stop(void)
{
    TIM_Cmd(TIM6, DISABLE);	 
    TIM_ITConfig(TIM6, TIM_IT_Update,DISABLE);
}

void TIM7_Start(void)
{
		TIM_Cmd(TIM7, ENABLE);	 
    TIM_ITConfig(TIM7, TIM_IT_Update,ENABLE);
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);	
}
void TIM6_DAC_IRQHandler(void)  
{
	
    if (TIM_GetITStatus(TIM6,TIM_IT_Update)!= RESET) 
	  {
			TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
      TIM_ClearFlag(TIM6, TIM_FLAG_Update);
			LED_GREEN_TOGGLE();
			Control_Task();         //底盘、云台控制任务

    }
}
void TIM7_IRQHandler(void)  
{
    if (TIM_GetITStatus(TIM7,TIM_IT_Update)!= RESET) 
	  {
			TIM_ClearITPendingBit(TIM7,TIM_IT_Update);
      TIM_ClearFlag(TIM7, TIM_FLAG_Update);
			SystickCount0++;
			if(SystickCount0==50000)
				SystickCount0=0;
			SystickCount1++;
			if(SystickCount1==50000)
				SystickCount1=0;
    }
}
