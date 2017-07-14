#include "main.h"

extern AUTOCONTROL AutoControl;

unsigned char RB[RBPackSize];
unsigned char TB[TBPackSize];

void USART1_Configuration(void)
{
	USART_InitTypeDef usart;
	GPIO_InitTypeDef  gpio;
	NVIC_InitTypeDef  nvic;
	DMA_InitTypeDef   dma;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	gpio.GPIO_Pin = GPIO_Pin_10;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio);

	gpio.GPIO_Pin = GPIO_Pin_9;  
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&gpio);

	usart.USART_BaudRate = 115200;
	usart.USART_WordLength = USART_WordLength_8b;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_Parity = USART_Parity_No ;
	usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   
	USART_Init(USART1,&usart);
	USART_Cmd(USART1,ENABLE);
	USART_DMACmd(USART1,USART_DMAReq_Tx|USART_DMAReq_Rx,ENABLE);
	
	nvic.NVIC_IRQChannel = DMA1_Channel5_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	//TX
//	dma.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);
//	dma.DMA_MemoryBaseAddr = (uint32_t)TB;
//	dma.DMA_DIR = DMA_DIR_PeripheralDST;
//	dma.DMA_BufferSize = TBPackSize;
//	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//	dma.DMA_Mode = DMA_Mode_Circular;
//	dma.DMA_Priority = DMA_Priority_VeryHigh;
//	dma.DMA_M2M = DMA_M2M_Disable;
//	DMA_Init(DMA1_Channel4,&dma);
//	DMA_Cmd(DMA1_Channel4,ENABLE);
	
	//RX
	dma.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);
	dma.DMA_MemoryBaseAddr = (uint32_t)RB;
	dma.DMA_DIR = DMA_DIR_PeripheralSRC;
	dma.DMA_BufferSize = RBPackSize;
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dma.DMA_Mode = DMA_Mode_Circular;
	dma.DMA_Priority = DMA_Priority_Low;
	dma.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel5,&dma);
	DMA_Cmd(DMA1_Channel5,ENABLE);
	DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
}

void DMA1_Channel5_IRQHandler()
{
	int PackPoint = 0;
	if(DMA_GetITStatus(DMA1_IT_TC5))
	{
		DMA_ClearFlag(DMA1_FLAG_TC5);
		DMA_ClearITPendingBit(DMA1_IT_GL5);
		for(PackPoint = 0; PackPoint < RBPackSize; PackPoint++)
		{
			if((RB[PackPoint%RBPackSize] == '!')&&(RB[(PackPoint+RBPackSize-1)%RBPackSize] == '#'))
			{
				AutoControl.Catch = RB[(PackPoint+1)%RBPackSize];
				return;
			}
		}
	}
}

//				AutoControl.Y_Auto = LIMIT_MIN_MAX(RB[(PackPoint+1)%RBPackSize]<<8 | RB[(PackPoint+2)%RBPackSize], 364, 1684); 
//				AutoControl.X_Auto = LIMIT_MIN_MAX(RB[(PackPoint+3)%RBPackSize]<<8 | RB[(PackPoint+4)%RBPackSize], 364, 1684);
//				AutoControl.Yaw_Reset = RB[(PackPoint+5)%RBPackSize];
//				CountForPC = 0;
