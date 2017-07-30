#include "main.h"

/*-----USART2_TX-----PD4-----*/
/*-----USART2_RX-----PD6-----*/

float PID_RxPosition[3]={0};
float PID_RxYaw[3]={0};
float PID_RxSpeed[3]={0};
static uint8_t i=0,rebuf[12]={0};


void USART2_Configuration(void)
{
    USART_InitTypeDef usart2;
    GPIO_InitTypeDef  gpio;
    NVIC_InitTypeDef  nvic;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

    GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2); 

    gpio.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD,&gpio);

    usart2.USART_BaudRate = 115200;          // speed 10byte/ms
    usart2.USART_WordLength = USART_WordLength_8b;
    usart2.USART_StopBits = USART_StopBits_1;
    usart2.USART_Parity = USART_Parity_No;
    usart2.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
    usart2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART2,&usart2);

    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART2,ENABLE);

    nvic.NVIC_IRQChannel = USART2_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&nvic);
}


void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)    //接收中断
	{
		rebuf[i++]=USART_ReceiveData(USART2);//读取串口数据，同时清接收标志
		if (rebuf[0]==0x5A && rebuf[11]==0x8B)//帧头对数据有
		{
			//速度环 位置环 YAW
			PID_RxSpeed[0]=(float)(rebuf[1]*0.01);
			PID_RxSpeed[1]=(float)(rebuf[2]*0.01);
			PID_RxSpeed[2]=(float)(rebuf[3]*0.01);
			PID_RxPosition[0]=(float)(rebuf[4]*0.01);
			PID_RxPosition[1]=(float)(rebuf[5]*0.01);
			PID_RxPosition[2]=(float)(rebuf[6]*0.01);
			PID_RxYaw[0]=(float)(rebuf[7]*0.01);
			PID_RxYaw[1]=(float)(rebuf[8]*0.01);
			PID_RxYaw[2]=(float)(rebuf[9]*0.01);
			//紧急停车
			if(rebuf[10]==0x01)
			{
				TIM6_Stop();
				CAN1MotorSpeedSet(0, 0, 0,0);
			}
			LED_RED_TOGGLE();
		}
		if (rebuf[0]!=0x5A)
			i=0;
		if(i==12)
			i=0;
	}
}
