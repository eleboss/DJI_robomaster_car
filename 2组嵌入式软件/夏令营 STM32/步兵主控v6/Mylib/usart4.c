#include "main.h"

unsigned char GYRO_buffer[11];
GYRO gyro;

void UART4_Configuration(void)
{
    USART_InitTypeDef usart;
		GPIO_InitTypeDef  gpio;
    NVIC_InitTypeDef  nvic;
		DMA_InitTypeDef 	dma;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

		GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4);
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); 
	
		gpio.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10;
		gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOC,&gpio);

		usart.USART_BaudRate = 115200;
		usart.USART_WordLength = USART_WordLength_8b;
		usart.USART_StopBits = USART_StopBits_1;
		usart.USART_Parity = USART_Parity_No;
		usart.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
    usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(UART4,&usart);

		USART_Cmd(UART4,ENABLE);
		USART_DMACmd(UART4,USART_DMAReq_Rx,ENABLE);
		
		nvic.NVIC_IRQChannel = DMA1_Stream2_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 3;
    nvic.NVIC_IRQChannelSubPriority = 3;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
		
		DMA_Cmd(DMA1_Stream2,ENABLE);
		{
			DMA_DeInit(DMA1_Stream2);
			dma.DMA_Channel= DMA_Channel_4;
			dma.DMA_PeripheralBaseAddr = (uint32_t)&(UART4->DR);
			dma.DMA_Memory0BaseAddr = (uint32_t)GYRO_buffer;
			dma.DMA_DIR = DMA_DIR_PeripheralToMemory;
			dma.DMA_BufferSize = 11;
			dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
			dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
			dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
			dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
			dma.DMA_Mode = DMA_Mode_Circular;
			dma.DMA_Priority = DMA_Priority_VeryHigh;
			dma.DMA_FIFOMode = DMA_FIFOMode_Disable;
			dma.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
			dma.DMA_MemoryBurst = DMA_Mode_Normal;
			dma.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
			DMA_Init(DMA1_Stream2,&dma);
			DMA_ITConfig(DMA1_Stream2,DMA_IT_TC,ENABLE);
			DMA_Cmd(DMA1_Stream2,ENABLE);
	 }
}

void DMA1_Stream2_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_Stream2, DMA_IT_TCIF2))
    {
        DMA_ClearFlag(DMA1_Stream2, DMA_FLAG_TCIF2);
        DMA_ClearITPendingBit(DMA1_Stream2, DMA_IT_TCIF2);
				if(GYRO_buffer[0] == 0x55)
				{
						switch(GYRO_buffer[1])
						{
							/*
							case 0x51:
								gyro.AX = ((short)(GYRO_buffer[3]<<8 | GYRO_buffer[2]))/32768.0*16;//g
								gyro.AY = ((short)(GYRO_buffer[5]<<8 | GYRO_buffer[4]))/32768.0*16;
								gyro.AZ = ((short)(GYRO_buffer[7]<<8 | GYRO_buffer[6]))/32768.0*16;
								gyro.Temperature = ((short)(GYRO_buffer[9]<<8 | GYRO_buffer[8])) /340.0f+36.53f;
							break;
							case 0x52:
								gyro.GX = ((short)(GYRO_buffer[3]<<8 | GYRO_buffer[2]))/32768.0*2000;//°/s
								gyro.GY = ((short)(GYRO_buffer[5]<<8 | GYRO_buffer[4]))/32768.0*2000;
								gyro.GZ = ((short)(GYRO_buffer[7]<<8 | GYRO_buffer[6]))/32768.0*2000;
								gyro.Temperature = ((short)(GYRO_buffer[9]<<8 | GYRO_buffer[8])) /340.0f+36.53f;
							break;
							*/
							case 0x53:
								gyro.PITCH = ((short)(GYRO_buffer[3]<<8 | GYRO_buffer[2]))/32768.0*180;//度
								gyro.ROLL = ((short)(GYRO_buffer[5]<<8 | GYRO_buffer[4]))/32768.0*180;
								gyro.YAW = ((short)(GYRO_buffer[7]<<8 | GYRO_buffer[6]))/32768.0*180;
								gyro.Temperature = ((short)(GYRO_buffer[9]<<8 | GYRO_buffer[8])) /340.0f+36.53f;
							break;
						}
				}
			}
}
