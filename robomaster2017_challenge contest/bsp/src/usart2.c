#include "main.h"

/*-----USART2_TX-----PD4-----*/
/*-----USART2_RX-----PD6-----*/

float PID_RxPosition[3]={0};
float PID_RxYaw[3]={0};
float PID_RxSpeed[3]={0};
static uint8_t i=0,rebuf[12]={0};
extern char goup;

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

    usart2.USART_BaudRate = 9600 ;          // speed 10byte/ms
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
//		if (rebuf[0]==0x5A && rebuf[11]==0x8B)//帧头对数据有
//		{
//			//速度环 位置环 YAW
//			PID_RxSpeed[0]=(float)(rebuf[1]*0.01);
//			PID_RxSpeed[1]=(float)(rebuf[2]*0.01);
//			PID_RxSpeed[2]=(float)(rebuf[3]*0.01);
//			PID_RxPosition[0]=(float)(rebuf[4]*0.01);
//			PID_RxPosition[1]=(float)(rebuf[5]*0.01);
//			PID_RxPosition[2]=(float)(rebuf[6]*0.01);
//			PID_RxYaw[0]=(float)(rebuf[7]*0.01);
//			PID_RxYaw[1]=(float)(rebuf[8]*0.01);
//			PID_RxYaw[2]=(float)(rebuf[9]*0.01);
//			//紧急停车
//			if(rebuf[10]==0x01)
//			{
//				TIM6_Stop();
//				CAN1MotorSpeedSet(0, 0, 0,0);
//			
//			}
//			LED_RED_TOGGLE();
//		}
//		if (rebuf[0]!=0x5A)
//			i=0;
//		if(i==12)
//			i=0;
//	}
		if (rebuf[0]==0x5A && rebuf[2]==0x8B)//帧头对数据有
		{
			//速度环 位置环 YAW


			if(rebuf[1]==0x01)
			{
				yspeed=20;	
				xspeed=0;
				zspeed=0;
				PIDInit_Speed(&PID_Speed[0],1);
				PIDInit_Speed(&PID_Speed[1],1);
				PIDInit_Speed(&PID_Speed[2],1);
				PIDInit_Speed(&PID_Speed[3],1);
			}
			if(rebuf[1]==0x02)
			{
				yspeed=-20;
				xspeed=0;
				zspeed=0;
				PIDInit_Speed(&PID_Speed[0],1);
				PIDInit_Speed(&PID_Speed[1],1);
				PIDInit_Speed(&PID_Speed[2],1);
				PIDInit_Speed(&PID_Speed[3],1);
			
			}
			if(rebuf[1]==0x03)
			{
	//MECANUM_MOVE(&SpeedSet,-300,0,0);

//	CAN1MotorSpeedSet(SpeedSet.RightSpeed_1,SpeedSet.LeftSpeed_1, SpeedSet.LeftSpeed_2, SpeedSet.RightSpeed_2);
				//Delay_Ms(10);
				xspeed=-15;
				zspeed=0;
				yspeed=0;
				PIDInit_Speed(&PID_Speed[0],1);
				PIDInit_Speed(&PID_Speed[1],1);
				PIDInit_Speed(&PID_Speed[2],1);
				PIDInit_Speed(&PID_Speed[3],1);
			}
			if(rebuf[1]==0x04)
			{
		//			MECANUM_MOVE(&SpeedSet,300,0,0);

	//CAN1MotorSpeedSet(SpeedSet.RightSpeed_1,SpeedSet.LeftSpeed_1, SpeedSet.LeftSpeed_2, SpeedSet.RightSpeed_2);
			//	Delay_Ms(10);
				xspeed=15;
				yspeed=0;
				zspeed=0;
				PIDInit_Speed(&PID_Speed[0],1);
				PIDInit_Speed(&PID_Speed[1],1);
				PIDInit_Speed(&PID_Speed[2],1);
				PIDInit_Speed(&PID_Speed[3],1);
			
			}
			if(rebuf[1]==0x0c)
			{

				zspeed=15;
				yspeed=0;
				xspeed=0;
				PIDInit_Speed(&PID_Speed[0],0);
				PIDInit_Speed(&PID_Speed[1],0);
				PIDInit_Speed(&PID_Speed[2],0);
				PIDInit_Speed(&PID_Speed[3],0);
			}
			if(rebuf[1]==0x0d)
			{
				zspeed=-15;
				yspeed=0;
				xspeed=0;
				PIDInit_Speed(&PID_Speed[0],0);
				PIDInit_Speed(&PID_Speed[1],0);
				PIDInit_Speed(&PID_Speed[2],0);
				PIDInit_Speed(&PID_Speed[3],0);
			
			}
			if(rebuf[1]==0x0e)
			{

				goup=1;
				yspeed=60;
			}
			if(rebuf[1]==0x0b)
			{
				xspeed=0;
				yspeed=0;
				zspeed=0;
				PIDInit_Speed(&PID_Speed[0],1);
				PIDInit_Speed(&PID_Speed[1],1);
				PIDInit_Speed(&PID_Speed[2],1);
				PIDInit_Speed(&PID_Speed[3],1);
			}
			if(rebuf[1]==0x9)//WHEEL up
			{
				Wheel_Move(200,1,1000);
			}
			if(rebuf[1]==0x0a)//wheel down
			{
				Wheel_Move(200,0,1000);
			}
			if(rebuf[1]==0x05)//夹紧
			{
				Fetch_Move(200,0,3000);
			}
			if(rebuf[1]==0x06)//松开
			{
				Fetch_Move(200,1,3000);
			}
			if(rebuf[1]==0x07)//提升
			{
				Updown_Move(200,1,2000);
			}
			if(rebuf[1]==0x08)//下降
			{
				Updown_Move(200,0,2000);
			}
			LED_RED_TOGGLE();
		}
		if (rebuf[0]!=0x5A)
			i=0;
		if(i==3)
			i=0;
	}
}
