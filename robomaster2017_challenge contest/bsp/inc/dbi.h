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
 
#ifndef __DBI_H__
#define __DBI_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "stm32util.h"
#include "fifo.h"
#include "hal_uart.h"
	
#define DBI_TX_PIN PD8
#define DBI_RX_PIN PD9
#define DBI_USART USART3
#define DBI_USART_BR 115200
#define DBI_USART_WL 8
#define DBI_USART_PA 'N'
#define DBI_USART_SB 1
#define DBI_USART_FC 'N'

#define DBI_ENABLE_IT_TXE() USART_ITConfig(DBI_USART, USART_IT_TXE, ENABLE)
#define DBI_DISABLE_IT_TXE() USART_ITConfig(DBI_USART, USART_IT_TXE, DISABLE)
#define DBI_ENABLE_IT_RXNE() USART_ITConfig(DBI_USART, USART_IT_RXNE, ENABLE)
#define DBI_DISABLE_IT_RXNE() USART_ITConfig(DBI_USART, USART_IT_RXNE, DISABLE)

#define DBI_IRQ_HANDLER IRQ_HANDLER(USART3)
#define DBI_NVIC IRQ(USART3)
#define DBI_NVIC_PRE_PRIORITY 1
#define DBI_NVIC_SUB_PRIORITY 1

#define DBI_RX_FIFO_SIZE 256u
#define DBI_TX_FIFO_SIZE 256u

void Dbi_Config(void);

uint32_t Dbi_GetRxFifoSize(void);
uint32_t Dbi_GetRxFifoUsed(void);
uint32_t Dbi_GetRxFifoFree(void);
uint32_t Dbi_GetTxFifoSize(void);
uint32_t Dbi_GetTxFifoUsed(void);
uint32_t Dbi_GetTxFifoFree(void);
int Dbi_ReadByte(void);
int Dbi_WriteByte(uint8_t b);
int Dbi_Read(uint8_t* buf, uint32_t len);
int Dbi_Write(const uint8_t* buf, uint32_t len);

void Dbi_PutCh(uint8_t c);
uint8_t Dbi_GetCh(void);
void Dbi_Print(const char* str);

void DbiRxCallback(uint8_t data);

extern const Hal_Uart_t dbi;

#ifdef __cplusplus
}
#endif

#endif

