#include "main.h"
extern AUTOCONTROL AutoControl; 
extern int test1, test2;
extern int test3, test4;

/*----CAN1_TX-----PA12----*/
/*----CAN1_RX-----PA11----*/

void CAN1_Configuration(void)
{
	CAN_InitTypeDef        can;
	CAN_FilterInitTypeDef  can_filter;
	GPIO_InitTypeDef       gpio;
	NVIC_InitTypeDef       nvic;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);

	gpio.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &gpio);
	
	nvic.NVIC_IRQChannel = CAN1_RX0_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 0;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	can.CAN_TTCM = DISABLE;
	can.CAN_ABOM = DISABLE;
	can.CAN_AWUM = DISABLE;
	can.CAN_NART = DISABLE;
	can.CAN_RFLM = DISABLE;
	can.CAN_TXFP = ENABLE;
	can.CAN_Mode = CAN_Mode_Normal;
	can.CAN_SJW  = CAN_SJW_1tq;
	can.CAN_BS1 = CAN_BS1_9tq;
	can.CAN_BS2 = CAN_BS2_4tq;
	can.CAN_Prescaler = 3;   //CAN BaudRate 42/(1+9+4)/3=1Mbps
	CAN_Init(CAN1, &can);

	can_filter.CAN_FilterNumber=0;
	can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
	can_filter.CAN_FilterScale=CAN_FilterScale_32bit;
	can_filter.CAN_FilterIdHigh=0x0000;
	can_filter.CAN_FilterIdLow=0x0000;
	can_filter.CAN_FilterMaskIdHigh=0x0000;
	can_filter.CAN_FilterMaskIdLow=0x0000;
	can_filter.CAN_FilterFIFOAssignment=0;
	can_filter.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&can_filter);
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
}

void CAN1SendMessage(short speed1,short pos1,short pos2)
{
	CanTxMsg tx_message;
	
	tx_message.StdId = 0x05;
	tx_message.IDE = CAN_ID_STD;;
	tx_message.RTR = CAN_RTR_Data;
	tx_message.DLC = 8;
	
//	speed1 = LIMIT_MIN_MAX(speed1,800,2200);
//	pos1 = LIMIT_MIN_MAX(pos1,800,2200);
//	pos2 = LIMIT_MIN_MAX(pos2,800,2200);
	
	tx_message.Data[0] = (speed1>>8)&0xff;
	tx_message.Data[1] = speed1&0xff;
	tx_message.Data[2] = (pos1>>8)&0xff;
	tx_message.Data[3] = pos1&0xff;
	tx_message.Data[4] = (pos2>>8)&0xff;
	tx_message.Data[5] = pos2&0xff;
	
	CAN_Transmit(CAN1,&tx_message);
}

void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg rx_message;
	if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET) 
	{
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
		CAN_Receive(CAN1, CAN_FIFO0, &rx_message);
		CAN_FIFORelease(CAN1, CAN_FIFO0);
		if(rx_message.StdId == 0x06)
		{
			test1 = rx_message.Data[0];
			test2 = rx_message.Data[1];
			test4 = rx_message.Data[2];
			test3 = rx_message.Data[3];
		}
	}
}
