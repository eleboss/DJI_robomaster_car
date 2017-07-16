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
 
#ifndef __RCV_H__
#define __RCV_H__


#ifdef __cplusplus
extern "C" {
#endif
	
#include "stm32util.h"

#define RCV_SIG_PIN PB7
#define RCV_USART USART1
#define RCV_USART_BR 100000
#define RCV_USART_WL 8
#define RCV_USART_PA 'E'
#define RCV_USART_SB 1
#define RCV_USART_FC 'N'

#define RCV_IRQ_HANDLER IRQ_HANDLER(USART1)
#define RCV_NVIC IRQ(USART1)
#define RCV_NVIC_PRE_PRIORITY 0
#define RCV_NVIC_SUB_PRIORITY 1
#define RCV_DMA_STREAM DMA2_Stream2
#define RCV_DMA_CHANNEL DMA_Channel_4

#define RCV_FRAME_LEN 18u
#define RCV_DMA_BUF_SIZE 36u

#define RCV_ENABLE_IDLE_IT(RCV_USART, USART_IT_IDLE, ENABLE)
#define RCV_DISABLE_IDLE_IT(RCV_USART, USART_IT_IDLE, DISABLE)

void Rcv_Config(void);
void Rcv_EnableIT(void);
void Rcv_DisableIT(void);

void RcvCallback(const uint8_t* dbuf);

#ifdef __cplusplus
}
#endif

#endif
