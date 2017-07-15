#include "main.h"
#define Pos1ChangeMax 1
#define Pos2ChangeMax 1

#define Pos1OriDistance 1520
#define Pos2OriDistance 1520

#define Pos1MaxDistance 2100
#define Pos2MaxDistance 2100
#define Pos1MinDistance 900
#define Pos2MinDistance 900 

extern RC_Ctl_t RC_Ctl;
extern AUTOCONTROL AutoControl;
extern unsigned char TZigBee[TZigBeePackSize];

int ms10, ms50;					
float Pos1 = Pos1OriDistance, Pos2 = Pos2OriDistance;
float PosLast1 = Pos1OriDistance, PosLast2 = Pos2OriDistance;

int CountForZigBee = 0;

int main(void)
{
	RCControl_Init();
	AutoControl_Init();
	SystemConfiguration();
	TZigBee[0] = 'l';
	TZigBee[1] = 'o';
	TZigBee[2] = 's';
	TZigBee[3] = 'f';
	TZigBee[4] = 'o';
	TZigBee[5] = 'l';
	TZigBee[6] = 'd';
	
	while(1)
	{	
		delay_ms(100);
	}
}

void SystemConfiguration(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	RCC_Configuration();	
	PWM_Configuration();
	LED_Configuration();			
	USART1_Configuration();	
	USART2_Configuration();
	USART3_Configuration();
	//SWITCH_Configuration();
	SysTick_Config(72000);
}

//1ms÷–∂œ
void SysTick_Handler(void)
{
	if(ms10 <= 10)	ms10 ++;
	else 			
	{
		ms10 = 0;
	}
	
	if(ms50 <= 50)	ms50 ++;
	{
		ms50 = 0;	
		LEDToggle();
		if(RC_Ctl.rc.s2 == 2)
		{
			Pos1 += (abs(RC_Ctl.rc.ch1-1024)<15 ? 0 : (RC_Ctl.rc.ch1-1024)*0.01);
			Pos2 += (abs(RC_Ctl.rc.ch3-1024)<15 ? 0 : (RC_Ctl.rc.ch3-1024)*0.01);
			AutoControl_Init();
		}
		else
		{
			if(AutoControl.Catch == 1)
			{
				Pos1 = 1650;
				Pos2 = 1650;
			}
			else if(AutoControl.Catch == 2)
			{
				Pos1 = 2100;
				Pos2 = 2100;
			}
			else if(AutoControl.Catch == 0)
			{
				Pos1 = 962;
				Pos2 = 962;
			}
			else
			{
				Pos1 = 1520;
				Pos2 = 1520;
			}//2100
		}
			
		Pos1 = LIMIT_MIN_MAX(Pos1, PosLast1-Pos1ChangeMax, PosLast1+Pos1ChangeMax);
		Pos2 = LIMIT_MIN_MAX(Pos2, PosLast2-Pos2ChangeMax, PosLast2+Pos2ChangeMax);
		
		Pos1 = LIMIT_MIN_MAX(Pos1, Pos1MinDistance, Pos1MaxDistance);
		Pos2 = LIMIT_MIN_MAX(Pos2, Pos2MinDistance, Pos2MaxDistance);
		
		PosLast1 = Pos1;
		PosLast2 = Pos2;
		
		TIM_SetCompare4(TIM3, (int)Pos1);
		TIM_SetCompare3(TIM3, (int)Pos1+130);
		//TIM_SetCompare3(TIM3, (int)Pos2);
	}
}


void RCC_Configuration(void)
{
		ErrorStatus HSEStartUpStatus;
		RCC_DeInit();
		RCC_HSEConfig(RCC_HSE_ON);  
		HSEStartUpStatus = RCC_WaitForHSEStartUp();
		if(HSEStartUpStatus == SUCCESS)        
		{
				RCC_HCLKConfig(RCC_SYSCLK_Div1);     
				RCC_PCLK1Config(RCC_HCLK_Div2);   
				FLASH_SetLatency(FLASH_Latency_2);     
				FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);    
				RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);     
				RCC_PLLCmd(ENABLE); 
 
				while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)      
				{
				}
				RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 
	
				while(RCC_GetSYSCLKSource() != 0x08)     
				{ 
				}
		}	
}
