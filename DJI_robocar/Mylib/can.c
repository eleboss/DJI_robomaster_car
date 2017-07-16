#include "main.h"

/*----CAN1_TX-----PD1----*/
/*----CAN1_RX-----PD0----*/
HG900MotorRecvmsg HG900MotorData[4];

void CAN1_Configuration(void)
{
	CAN_InitTypeDef        can;
	CAN_FilterInitTypeDef  can_filter;
	GPIO_InitTypeDef       gpio;
	NVIC_InitTypeDef       nvic;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);


	gpio.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0 ;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &gpio);
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1); 

//	nvic.NVIC_IRQChannel = CAN1_RX0_IRQn;
//	nvic.NVIC_IRQChannelPreemptionPriority = 1;
//	nvic.NVIC_IRQChannelSubPriority = 1;
//	nvic.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&nvic);



		
	can.CAN_TTCM = DISABLE;
	can.CAN_ABOM = DISABLE;    
	can.CAN_AWUM = DISABLE;       
	can.CAN_RFLM = DISABLE;    
	can.CAN_TXFP = ENABLE;     
	can.CAN_Mode = CAN_Mode_Normal;
	//can.CAN_Mode = CAN_Mode_LoopBack;
	can.CAN_SJW  = CAN_SJW_1tq;
	can.CAN_BS1 = CAN_BS1_9tq;
	can.CAN_BS2 = CAN_BS2_5tq;
	can.CAN_Prescaler = 3;   //CAN BaudRate 45/(1+9+5)/3=1Mbps
	CAN_Init(CAN1, &can);
	
//	can_filter.CAN_FilterNumber=0; 
//	can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
//	can_filter.CAN_FilterScale=CAN_FilterScale_32bit;
//	can_filter.CAN_FilterIdHigh=0x0000;
//	can_filter.CAN_FilterIdLow=0x0000;
//	can_filter.CAN_FilterMaskIdHigh=0x0000;
//	can_filter.CAN_FilterMaskIdLow=0x0000;
//	can_filter.CAN_FilterFIFOAssignment=0;//the message which pass the filter save in fifo0
//	can_filter.CAN_FilterActivation=ENABLE;
//	CAN_FilterInit(&can_filter);
//	
//	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
//	CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);
}

void CAN1MotorSpeedSet(int speed1,int speed2,int speed3,int speed4)
{
	CanTxMsg tx_message;
	
	tx_message.StdId = 0x200;
	tx_message.IDE = CAN_ID_STD;;
	tx_message.RTR = CAN_RTR_Data;
	tx_message.DLC = 0x08;
	
//	if(speed1>LimitedSpeed)	speed1 = LimitedSpeed;
//	if(speed2>LimitedSpeed) speed2 = LimitedSpeed;
//	if(speed3>LimitedSpeed)	speed3 = LimitedSpeed;
//	if(speed4>LimitedSpeed) speed4 = LimitedSpeed;
//	if(speed1<-LimitedSpeed)	speed1 = -LimitedSpeed;
//	if(speed2<-LimitedSpeed)	speed2 = -LimitedSpeed;
//	if(speed3<-LimitedSpeed)	speed3 = -LimitedSpeed;
//	if(speed4<-LimitedSpeed)	speed4 = -LimitedSpeed;
	
//	tx_message.Data[0] = (speed1>>8)&0xff;
//	tx_message.Data[1] = speed1&0xff;
//	tx_message.Data[2] = (speed2>>8)&0xff;
//	tx_message.Data[3] = speed2&0xff;
//	tx_message.Data[4] = (speed3>>8)&0xff;
//	tx_message.Data[5] = speed3&0xff;
//	tx_message.Data[6] = (speed4>>8)&0xff;
//	tx_message.Data[7] = speed4&0xff;
	
	tx_message.Data[0] = (uint8_t)(speed1>>8);
	tx_message.Data[1] = (uint8_t)speed1;
	tx_message.Data[2] = (uint8_t)(speed2>>8);
	tx_message.Data[3] = (uint8_t)speed2;
	tx_message.Data[4] = (uint8_t)(speed3>>8);
	tx_message.Data[5] = (uint8_t)speed3;
	tx_message.Data[6] = (uint8_t)(speed4>>8);
	tx_message.Data[7] = (uint8_t)speed4;
	
	CAN_Transmit(CAN1,&tx_message);
}

void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg rx_message;
	if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET) 
	{
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
		CAN_Receive(CAN1, CAN_FIFO0, &rx_message);
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
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
	}
}
void CAN1_TX_IRQ_HANDLER(void)
{
  if (CAN_GetITStatus(CAN1, CAN_IT_TME) != RESET)
	{
		CAN_ClearITPendingBit(CAN1, CAN_IT_TME);
  }
}
