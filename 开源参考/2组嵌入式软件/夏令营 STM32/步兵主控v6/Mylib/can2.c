#include "main.h"

/*----CAN2_TX-----PB13----*/
/*----CAN2_RX-----PB12----*/
HG900MotorRecvmsg HG900MotorData[4];

void CAN2_Configuration(void)
{
	CAN_InitTypeDef        can;
	CAN_FilterInitTypeDef  can_filter;
	GPIO_InitTypeDef       gpio;
	NVIC_InitTypeDef       nvic;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2); 

	gpio.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_12 ;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &gpio);

	nvic.NVIC_IRQChannel = CAN2_RX0_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	can.CAN_TTCM = DISABLE;
	can.CAN_ABOM = DISABLE;    
	can.CAN_AWUM = DISABLE;    
	can.CAN_NART = DISABLE;    
	can.CAN_RFLM = DISABLE;    
	can.CAN_TXFP = ENABLE;     
	can.CAN_Mode = CAN_Mode_Normal;
	//can.CAN_Mode = CAN_Mode_LoopBack;
	can.CAN_SJW  = CAN_SJW_1tq;
	can.CAN_BS1 = CAN_BS1_9tq;
	can.CAN_BS2 = CAN_BS2_4tq;
	can.CAN_Prescaler = 3;   //CAN BaudRate 42/(1+9+4)/3=1Mbps
	CAN_Init(CAN2, &can);
	
	can_filter.CAN_FilterNumber=14; 
	can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
	can_filter.CAN_FilterScale=CAN_FilterScale_32bit;
	can_filter.CAN_FilterIdHigh=0x0000;
	can_filter.CAN_FilterIdLow=0x0000;
	can_filter.CAN_FilterMaskIdHigh=0x0000;
	can_filter.CAN_FilterMaskIdLow=0x0000;
	can_filter.CAN_FilterFIFOAssignment=0;//the message which pass the filter save in fifo0
	can_filter.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&can_filter);
	
	CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);
}

void CAN2MotorSpeedSet(int speed1,int speed2,int speed3,int speed4)
{
	CanTxMsg tx_message;
	
	tx_message.StdId = 0x200;
	tx_message.IDE = CAN_ID_STD;;
	tx_message.RTR = CAN_RTR_Data;
	tx_message.DLC = 8;
	
	if(speed1>LimitedSpeed)	speed1 = LimitedSpeed;
	if(speed2>LimitedSpeed) speed2 = LimitedSpeed;
	if(speed3>LimitedSpeed)	speed3 = LimitedSpeed;
	if(speed4>LimitedSpeed) speed4 = LimitedSpeed;
	if(speed1<-LimitedSpeed)	speed1 = -LimitedSpeed;
	if(speed2<-LimitedSpeed)	speed2 = -LimitedSpeed;
	if(speed3<-LimitedSpeed)	speed3 = -LimitedSpeed;
	if(speed4<-LimitedSpeed)	speed4 = -LimitedSpeed;
	
	tx_message.Data[0] = (speed1>>8)&0xff;
	tx_message.Data[1] = speed1&0xff;
	tx_message.Data[2] = (speed2>>8)&0xff;
	tx_message.Data[3] = speed2&0xff;
	tx_message.Data[4] = (speed3>>8)&0xff;
	tx_message.Data[5] = speed3&0xff;
	tx_message.Data[6] = (speed4>>8)&0xff;
	tx_message.Data[7] = speed4&0xff;
	
	CAN_Transmit(CAN2,&tx_message);
}

void CAN2_RX0_IRQHandler(void)
{
	CanRxMsg rx_message;
	if (CAN_GetITStatus(CAN2,CAN_IT_FMP0)!= RESET) 
	{
		CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
		CAN_Receive(CAN2, CAN_FIFO0, &rx_message);
		switch(rx_message.StdId)
		{
			case 0x201:
				HG900MotorData[0].Angle = rx_message.Data[0]<<8 | rx_message.Data[1];
				HG900MotorData[0].RealCurrent = rx_message.Data[2]<<8 | rx_message.Data[3];
				HG900MotorData[0].Current = rx_message.Data[4]<<8 | rx_message.Data[5];
				HG900MotorData[0].Hall = rx_message.Data[6];

				break;
			case 0x202:
				HG900MotorData[1].Angle = rx_message.Data[0]<<8 | rx_message.Data[1];
				HG900MotorData[1].RealCurrent = rx_message.Data[2]<<8 | rx_message.Data[3];
				HG900MotorData[1].Current = rx_message.Data[4]<<8 | rx_message.Data[5];
				HG900MotorData[1].Hall = rx_message.Data[6];
				break;
			case 0x203:
				HG900MotorData[2].Angle = rx_message.Data[0]<<8 | rx_message.Data[1];
				HG900MotorData[2].RealCurrent = rx_message.Data[2]<<8 | rx_message.Data[3];
				HG900MotorData[2].Current = rx_message.Data[4]<<8 | rx_message.Data[5];
				HG900MotorData[2].Hall = rx_message.Data[6];
				break;
			case 0x204:
				HG900MotorData[3].Angle = rx_message.Data[0]<<8 | rx_message.Data[1];
				HG900MotorData[3].RealCurrent = rx_message.Data[2]<<8 | rx_message.Data[3];
				HG900MotorData[3].Current = rx_message.Data[4]<<8 | rx_message.Data[5];
				HG900MotorData[3].Hall = rx_message.Data[6];
				break;
			default:
				break;
		}
		CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
	}
}
