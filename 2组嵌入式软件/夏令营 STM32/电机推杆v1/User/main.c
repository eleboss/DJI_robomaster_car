#include "main.h"
int ms10,ms50;					//10ms中断计数器 

unsigned char test1 = 0, test2 = 0;
unsigned char test3 = 0, test4 = 0;

int main(void)
{
	delay_ms(3000);
	SystemConfiguration();
	
	while(1)
	{
		test1 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9);
		test2 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10);
		test3 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15);
		test4 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);
	}
}

void SystemConfiguration(void)
{
	RCC_Configuration();	
	LED_Configuration();					//状态指示灯初始化
	USART3_Configuration();				//串口初始化
	CAN_Configuration();					//CAN1通信
	PWM_Configuration();					//各种PWM
	SWITCH_Configuration();
		
	SysTick_Config(72000);				//1ms定时中断
}

//1ms中断
void SysTick_Handler(void)
{
	CANOnLineClaim(test1, test2, test3, test4);
	if(ms10<20)	ms10++;
	else
	{
		ms10 = 0;
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
