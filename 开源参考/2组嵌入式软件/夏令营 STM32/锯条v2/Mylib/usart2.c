#include "main.h"

extern int CountForZigBee;

unsigned char RZigBee[RZigBeePackSize];
unsigned char TZigBee[TZigBeePackSize];

void USART2_Configuration(void)
{
	USART_InitTypeDef usart;
	GPIO_InitTypeDef  gpio;
	NVIC_InitTypeDef  nvic;
	DMA_InitTypeDef   dma;


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	gpio.GPIO_Pin = GPIO_Pin_3;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio);

	gpio.GPIO_Pin = GPIO_Pin_2;  
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&gpio);

	usart.USART_BaudRate = 9600;
	usart.USART_WordLength = USART_WordLength_8b;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_Parity = USART_Parity_No ;
	usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   
	USART_Init(USART2,&usart);
	USART_Cmd(USART2,ENABLE);
	USART_DMACmd(USART2,USART_DMAReq_Tx|USART_DMAReq_Rx,ENABLE);
	
	nvic.NVIC_IRQChannel = DMA1_Channel6_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	//TX
	dma.DMA_PeripheralBaseAddr = (uint32_t)&(USART2->DR);
	dma.DMA_MemoryBaseAddr = (uint32_t)TZigBee;
	dma.DMA_DIR = DMA_DIR_PeripheralDST;
	dma.DMA_BufferSize = TZigBeePackSize;
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dma.DMA_Mode = DMA_Mode_Circular;
	dma.DMA_Priority = DMA_Priority_VeryHigh;
	dma.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel7,&dma);
	DMA_Cmd(DMA1_Channel7,ENABLE);
	
	//RX
	dma.DMA_PeripheralBaseAddr = (uint32_t)&(USART2->DR);
	dma.DMA_MemoryBaseAddr = (uint32_t)RZigBee;
	dma.DMA_DIR = DMA_DIR_PeripheralSRC;
	dma.DMA_BufferSize = RZigBeePackSize;
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dma.DMA_Mode = DMA_Mode_Circular;
	dma.DMA_Priority = DMA_Priority_Low;
	dma.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel6,&dma);
	DMA_Cmd(DMA1_Channel6,ENABLE);
	DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);
}


void DMA1_Channel6_IRQHandler()
{
	int PackPoint = 0;
	if(DMA_GetITStatus(DMA1_IT_TC6))
	{
		DMA_ClearFlag(DMA1_FLAG_TC6);
		DMA_ClearITPendingBit(DMA1_IT_GL6);
		for(PackPoint = 0; PackPoint < RBPackSize; PackPoint++)
		{
			if((RZigBee[PackPoint%RZigBeePackSize] == 't')&&(RZigBee[(PackPoint+RZigBeePackSize-1)%RZigBeePackSize] == 'e'))
			{
				CountForZigBee = 0;
				return;
			}
		}
	}
}
