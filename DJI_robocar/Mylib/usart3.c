#include "main.h"

extern int CountForPC;
extern float YawOffset;

unsigned char RB[RBPackSize];
unsigned char TB[TBPackSize];
AUTOCONTROL AutoControl; 

void USART3_Configuration(void)
{
    USART_InitTypeDef usart3;
		GPIO_InitTypeDef  gpio;
    NVIC_InitTypeDef  nvic;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); 
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); 
	
		gpio.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
		gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOB,&gpio);

		usart3.USART_BaudRate = 115200;
		usart3.USART_WordLength = USART_WordLength_8b;
		usart3.USART_StopBits = USART_StopBits_1;
		usart3.USART_Parity = USART_Parity_No;
		usart3.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    usart3.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(USART3,&usart3);
		USART_Cmd(USART3,ENABLE);
		USART_DMACmd(USART3,USART_DMAReq_Rx|USART_DMAReq_Tx,ENABLE);
		
		nvic.NVIC_IRQChannel = DMA1_Stream1_IRQn;
		nvic.NVIC_IRQChannelPreemptionPriority = 3;
		nvic.NVIC_IRQChannelSubPriority = 2;
		nvic.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&nvic);
		
		nvic.NVIC_IRQChannel = DMA1_Stream3_IRQn;
		nvic.NVIC_IRQChannelPreemptionPriority = 3;
		nvic.NVIC_IRQChannelSubPriority = 2;
		nvic.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&nvic);
		
		//DMA
		{
			DMA_InitTypeDef 	dma;
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);
			//Tx
			dma.DMA_Channel= DMA_Channel_4;
			dma.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR); 
			dma.DMA_Memory0BaseAddr = (uint32_t)TB;
			dma.DMA_DIR = DMA_DIR_MemoryToPeripheral;  
			dma.DMA_BufferSize = TBPackSize; 
			dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
			dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
			dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
			dma.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
			dma.DMA_Mode = DMA_Mode_Circular;
			dma.DMA_Priority = DMA_Priority_VeryHigh;
			dma.DMA_FIFOMode = DMA_FIFOMode_Disable;
			dma.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
			dma.DMA_MemoryBurst = DMA_Mode_Normal;
			dma.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
//			DMA_Init(DMA1_Stream3,&dma);
//			DMA_Cmd(DMA1_Stream3,ENABLE);
			
			//Rx
			dma.DMA_Channel= DMA_Channel_4;
			dma.DMA_PeripheralBaseAddr = (uint32_t)&(USART3->DR);
			dma.DMA_Memory0BaseAddr = (uint32_t)RB;
			dma.DMA_DIR = DMA_DIR_PeripheralToMemory;
			dma.DMA_BufferSize = RBPackSize;
			dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
			dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
			dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
			dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
			dma.DMA_Mode = DMA_Mode_Circular;
			dma.DMA_Priority = DMA_Priority_Low;
			dma.DMA_FIFOMode = DMA_FIFOMode_Disable;
			dma.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
			dma.DMA_MemoryBurst = DMA_Mode_Normal;
			dma.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
			DMA_Init(DMA1_Stream1,&dma);
			DMA_Cmd(DMA1_Stream1,ENABLE);
			DMA_ITConfig(DMA1_Stream1,DMA_IT_TC,ENABLE);
	 }
}


void AutoControlInit(void)
{
	AutoControl.X_Auto = 1024;
	AutoControl.Y_Auto = 1024;
	AutoControl.Yaw_Reset = 0;
	AutoControl.Yaw_Auto = 1024;
	AutoControl.Grab_Auto = 0;
	AutoControl.Slide_Auto = 0;
	AutoControl.Finished = 0;
}


void DMA1_Stream1_IRQHandler(void)
{
	int PackPoint = 0;
	if(DMA_GetITStatus(DMA1_Stream1, DMA_IT_TCIF1))
	{
		DMA_ClearFlag(DMA1_Stream1, DMA_FLAG_TCIF1);
		DMA_ClearITPendingBit(DMA1_Stream1, DMA_IT_TCIF1);
		for(PackPoint = 0; PackPoint < RBPackSize; PackPoint++)
		{
			if((RB[PackPoint%RBPackSize] == '!')&&(RB[(PackPoint+RBPackSize-1)%RBPackSize] == '#'))
			{
				AutoControl.Y_Auto = LIMIT_MIN_MAX(RB[(PackPoint+1)%RBPackSize]<<8 | RB[(PackPoint+2)%RBPackSize], 364, 1684); 
				AutoControl.X_Auto = LIMIT_MIN_MAX(RB[(PackPoint+3)%RBPackSize]<<8 | RB[(PackPoint+4)%RBPackSize], 364, 1684);
				YawOffset = (double)RB[(PackPoint+5)%RBPackSize]*0.1 - 10;
				AutoControl.Grab_Auto = RB[(PackPoint+9)%RBPackSize];
				AutoControl.Yaw_Reset = RB[(PackPoint+12)%RBPackSize];
				AutoControl.Finished = RB[(PackPoint+14)%RBPackSize];
				CountForPC = 0;
				return;
			}
		}
	}		
}


void DMA1_Stream3_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_Stream3, DMA_IT_TCIF3))
	{
		DMA_ClearFlag(DMA1_Stream3, DMA_FLAG_TCIF3);
		DMA_ClearITPendingBit(DMA1_Stream3, DMA_IT_TCIF3);
	}
}
