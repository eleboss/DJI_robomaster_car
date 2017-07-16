/**
 * Copyright (c) 2011-2016, Jack Mo (mobangjack@foxmail.com).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "rcv.h"

static uint8_t buf[2][RCV_DMA_BUF_SIZE];

void Rcv_Config(void)
{
	USART_Bind(RCV_SIG_PIN, 0,
			   RCV_USART,
			   RCV_USART_BR,
			   RCV_USART_WL,
			   RCV_USART_PA,
			   RCV_USART_SB,
			   RCV_USART_FC);

	USART_DMACmd(RCV_USART, USART_DMAReq_Rx, ENABLE);
		
	DMA_Config(RCV_DMA_STREAM,
			   RCV_DMA_CHANNEL,
			   (u32)&RCV_USART->DR,
			   (u32)buf[0], 0,
			   RCV_DMA_BUF_SIZE);

	DMA_DoubleBufferModeConfig(RCV_DMA_STREAM, (u32)buf[1], DMA_Memory_0);
	DMA_DoubleBufferModeCmd(RCV_DMA_STREAM, ENABLE);
	
	DMA_Cmd(RCV_DMA_STREAM, ENABLE);
	
	NVIC_Config(RCV_NVIC, RCV_NVIC_PRE_PRIORITY, RCV_NVIC_SUB_PRIORITY);
    
	USART_ITConfig(RCV_USART, USART_IT_IDLE, ENABLE); // 14mspf
  USART_Cmd(RCV_USART, ENABLE);

}

void Rcv_EnableIT(void)
{
	USART_Cmd(RCV_USART, ENABLE);
}

void Rcv_DisableIT(void)
{
	USART_Cmd(RCV_USART, DISABLE);
}

void RCV_IRQ_HANDLER(void)
{
	if(USART_GetITStatus(RCV_USART, USART_IT_IDLE) != RESET)
	{
		uint8_t* dbuf = buf[0];

		uint16_t rx_len = 0;

		//clear the idle pending flag
		//USART_ClearITPendingBit(RCV_USART, USART_IT_IDLE);
		//USART_ClearFlag(RCV_USART, USART_FLAG_IDLE);
		
		(void)RCV_USART->SR;
		(void)RCV_USART->DR;
		
		DMA_Cmd(RCV_DMA_STREAM, DISABLE);
		rx_len = RCV_DMA_BUF_SIZE - DMA_GetCurrDataCounter(RCV_DMA_STREAM);
		RCV_DMA_STREAM->NDTR = (uint16_t)RCV_DMA_BUF_SIZE;     //relocate the DMA memory pointer to the beginning position
		//Target is Memory0
		if(DMA_GetCurrentMemoryTarget(RCV_DMA_STREAM) == 0)
		{
			dbuf = buf[0];
			RCV_DMA_STREAM->CR |= (uint32_t)(DMA_SxCR_CT);        //enable the current selected memory is Memory 1
		}
		else
		{
			dbuf = buf[1];
			RCV_DMA_STREAM->CR &= ~(uint32_t)(DMA_SxCR_CT);       //enable the current selected memory is Memory 0
		}
		DMA_Cmd(RCV_DMA_STREAM, ENABLE);
		if(rx_len == RCV_FRAME_LEN)
		{
			RcvCallback(dbuf);
		}
	}       
}

