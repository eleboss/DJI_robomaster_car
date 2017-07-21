#include "main.h"
CanRxMsg rx_message;

void CAN_Configuration(void)
{
		CAN_InitTypeDef        can;
		CAN_FilterInitTypeDef  can_filter;
		GPIO_InitTypeDef 	   	gpio;
		NVIC_InitTypeDef   	   nvic;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,  ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO , ENABLE);
    
		gpio.GPIO_Pin = GPIO_Pin_11;
		gpio.GPIO_Mode = GPIO_Mode_IPU;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &gpio);	
	
		gpio.GPIO_Pin = GPIO_Pin_12;	   
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &gpio);    
    
    nvic.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;  
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
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
		can.CAN_SJW = CAN_SJW_1tq;
		can.CAN_BS1 = CAN_BS1_5tq;
		can.CAN_BS2 = CAN_BS2_3tq;
		can.CAN_Prescaler = 4;     //CAN BaudRate 36/(1+5+3)/4=1Mbps
		CAN_Init(CAN1, &can);
	
		can_filter.CAN_FilterNumber = 0; 
		can_filter.CAN_FilterMode = CAN_FilterMode_IdMask;
		can_filter.CAN_FilterScale = CAN_FilterScale_32bit;
		can_filter.CAN_FilterIdHigh = 0;
		can_filter.CAN_FilterIdLow = 0;
		can_filter.CAN_FilterMaskIdHigh = 0;
		can_filter.CAN_FilterMaskIdLow = 0;
		can_filter.CAN_FilterFIFOAssignment = 0;
		can_filter.CAN_FilterActivation = ENABLE;
		CAN_FilterInit(&can_filter);
    
    CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
}

void CANOnLineClaim(unsigned char switch1, unsigned char switch2, unsigned char switch3, unsigned char switch4)
{
		CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD; 
    tx_message.RTR = CAN_RTR_DATA;
    tx_message.DLC = 0x08;          
    tx_message.StdId = 0x06;      
		
    tx_message.Data[0] = switch1;
    tx_message.Data[1] = switch2;
    tx_message.Data[2] = switch3;
    tx_message.Data[3] = switch4;
    tx_message.Data[4] = 0x55;
    tx_message.Data[5] = 0x55;
    tx_message.Data[6] = 0x55;
    tx_message.Data[7] = 0x55;

    CAN_Transmit(CAN1,&tx_message);
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{
	if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET) 
	{
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
		CAN_Receive(CAN1, CAN_FIFO0, &rx_message);
		CAN_FIFORelease(CAN1, CAN_FIFO0);
		if(rx_message.StdId == 0x05)
		{
			TIM_SetCompare1(TIM4, (short)((rx_message.Data[0]<<8) | rx_message.Data[1]));
			TIM_SetCompare2(TIM4, (short)((rx_message.Data[2]<<8) | rx_message.Data[3]));
			TIM_SetCompare3(TIM4, (short)((rx_message.Data[4]<<8) | rx_message.Data[5]));
		}
	}
}
