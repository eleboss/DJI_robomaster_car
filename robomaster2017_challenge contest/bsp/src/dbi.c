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
 
#include "dbi.h"

const Hal_Uart_t dbi = HAL_UART_DEF(Dbi);

static FIFO_t rx_fifo;
static FIFO_t tx_fifo;
static uint8_t rx_buf[DBI_RX_FIFO_SIZE];
static uint8_t tx_buf[DBI_TX_FIFO_SIZE];

void Dbi_Config(void)
{
    USART_Bind(DBI_RX_PIN, DBI_TX_PIN,
			   DBI_USART,
			   DBI_USART_BR,
			   DBI_USART_WL,
			   DBI_USART_PA,
			   DBI_USART_SB,
			   DBI_USART_FC
			   );

    USART_ITConfig(DBI_USART, USART_IT_RXNE, ENABLE);

    NVIC_Config(DBI_NVIC, DBI_NVIC_PRE_PRIORITY, DBI_NVIC_SUB_PRIORITY);

    FIFO_Init(&rx_fifo, rx_buf, DBI_RX_FIFO_SIZE);
    FIFO_Init(&tx_fifo, tx_buf, DBI_TX_FIFO_SIZE);

    USART_Cmd(DBI_USART, ENABLE);
}

uint32_t Dbi_GetRxFifoSize(void)
{
	return FIFO_GetSize(&rx_fifo);
}

uint32_t Dbi_GetRxFifoUsed(void)
{
	return FIFO_GetUsed(&rx_fifo);
}

uint32_t Dbi_GetRxFifoFree(void)
{
	return FIFO_GetFree(&rx_fifo);
}

uint32_t Dbi_GetTxFifoSize(void)
{
	return FIFO_GetSize(&tx_fifo);
}

uint32_t Dbi_GetTxFifoUsed(void)
{
	return FIFO_GetUsed(&tx_fifo);
}

uint32_t Dbi_GetTxFifoFree(void)
{
	return FIFO_GetFree(&tx_fifo);
}

int Dbi_ReadByte(void)
{
	if (FIFO_IsEmpty(&rx_fifo)) {
		return -1;
	} else {
		uint8_t data = 0;
		DBI_DISABLE_IT_RXNE();
		FIFO_Pop(&rx_fifo, &data, 1);
		DBI_ENABLE_IT_RXNE();
		return data;
	}
}

int Dbi_WriteByte(uint8_t b)
{
	if (FIFO_IsFull(&tx_fifo)) {
		return -1;
	} else {
		DBI_DISABLE_IT_TXE();
		FIFO_Push(&tx_fifo, &b, 1);
		DBI_ENABLE_IT_TXE();
		return b;
	}
}

int Dbi_Read(uint8_t* buf, uint32_t len)
{
	uint32_t available = FIFO_GetUsed(&rx_fifo);
	if (!available) {
		return -1;
	} else {
		if (len > available) len = available;
		DBI_DISABLE_IT_RXNE();
		FIFO_Pop(&rx_fifo, buf, len);
		DBI_ENABLE_IT_RXNE();
		return len;
	}
}

int Dbi_Write(const uint8_t* buf, uint32_t len)
{
	uint32_t available = FIFO_GetFree(&tx_fifo);
	if (!available) {
		return -1;
	} else {
		if (len > available) len = available;
		DBI_DISABLE_IT_TXE();
		FIFO_Push(&tx_fifo, buf, len);
		DBI_ENABLE_IT_TXE();
		return len;
	}
}

void Dbi_PutCh(uint8_t c)
{
	while (FIFO_IsFull(&tx_fifo));
	DBI_DISABLE_IT_TXE();
	FIFO_Push(&tx_fifo, &c, 1);
	DBI_ENABLE_IT_TXE();
}

uint8_t Dbi_GetCh(void)
{
	uint8_t c = 0;
	while (FIFO_IsEmpty(&rx_fifo));
	DBI_DISABLE_IT_RXNE();
	FIFO_Pop(&rx_fifo, &c, 1);
	DBI_ENABLE_IT_RXNE();
	return c;
}

void Dbi_Print(const char* str)
{
	const uint32_t len = strlen(str);
	uint32_t i = 0;
	for (; i < len; i++) {
		Dbi_PutCh(str[i]);
	}
}

void DBI_IRQ_HANDLER(void)
{  
	if (USART_GetITStatus(DBI_USART, USART_IT_TXE) != RESET)
	{   
		if (!FIFO_IsEmpty(&tx_fifo)) {
			uint8_t tx_data = 0;
			FIFO_Pop(&tx_fifo, &tx_data, 1);
			USART_SendData(DBI_USART, tx_data);
		} else {
			DBI_DISABLE_IT_TXE();
		}
	}
	else if (USART_GetITStatus(DBI_USART, USART_IT_RXNE) != RESET)
	{
		uint8_t rx_data = USART_ReceiveData(DBI_USART);
		if (FIFO_IsFull(&rx_fifo)) {
			uint8_t tmp = 0;
			FIFO_Pop(&rx_fifo, &tmp, 1);
		}
		FIFO_Push(&rx_fifo, &rx_data, 1);
		DbiRxCallback(rx_data);
	}       
}

