#include "main.h"

void BSP_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);     
	PWM_Configuration();//发射机构用PWM控制
	Led_Configuration();            
	Laser_Configuration();
	TIM2_Configuration();//LED闪烁	
	MPU6050_Initialize();    
	TIM6_Configuration();//定时控制底盘、云台		
	Quad_Encoder_Configuration();		
	CAN1_Configuration();           
	CAN2_Configuration();            
	USART1_Configuration(100000);        
	USART3_Configuration();         
	TIM6_Start();   	
	MPU6050_IntConfiguration();     
	MPU6050_EnableInt();    	
	Encoder_Start();
}

