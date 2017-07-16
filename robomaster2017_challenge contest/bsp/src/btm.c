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

#include "btm.h"

const Hal_Uart_t btm = HAL_UART_DEF(Btm);

static FIFO_t rx_fifo;
static FIFO_t tx_fifo;
static uint8_t rx_buf[BTM_RX_FIFO_SIZE];
static uint8_t tx_buf[BTM_TX_FIFO_SIZE];

void Btm_Config(void)
{
    USART_Bind(BTM_RX_PIN, BTM_TX_PIN,
    		 BTM_USART,
			   BTM_USART_BR,
			   BTM_USART_WL,
			   BTM_USART_PA,
			   BTM_USART_SB,
			   BTM_USART_FC
			   );

    USART_ITConfig(BTM_USART, USART_IT_RXNE, ENABLE);

    NVIC_Config(BTM_NVIC, BTM_NVIC_PRE_PRIORITY, BTM_NVIC_SUB_PRIORITY);

    FIFO_Init(&rx_fifo, rx_buf, BTM_RX_FIFO_SIZE);
    FIFO_Init(&tx_fifo, tx_buf, BTM_TX_FIFO_SIZE);

    USART_Cmd(BTM_USART, ENABLE);
}

uint32_t Btm_GetRxFifoSize(void)
{
	return FIFO_GetSize(&rx_fifo);
}

uint32_t Btm_GetRxFifoUsed(void)
{
	return FIFO_GetUsed(&rx_fifo);
}

uint32_t Btm_GetRxFifoFree(void)
{
	return FIFO_GetFree(&rx_fifo);
}

uint32_t Btm_GetTxFifoSize(void)
{
	return FIFO_GetSize(&tx_fifo);
}

uint32_t Btm_GetTxFifoUsed(void)
{
	return FIFO_GetUsed(&tx_fifo);
}

uint32_t Btm_GetTxFifoFree(void)
{
	return FIFO_GetFree(&tx_fifo);
}

int Btm_ReadByte(void)
{
	if (FIFO_IsEmpty(&rx_fifo)) {
		return -1;
	} else {
		uint8_t data = 0;
		BTM_DISABLE_IT_RXNE();
		FIFO_Pop(&rx_fifo, &data, 1);
		BTM_ENABLE_IT_RXNE();
		return data;
	}
}

int Btm_WriteByte(uint8_t b)
{
	if (FIFO_IsFull(&tx_fifo)) {
		return -1;
	} else {
		BTM_DISABLE_IT_TXE();
		FIFO_Push(&tx_fifo, &b, 1);
		BTM_ENABLE_IT_TXE();
		return b;
	}
}

int Btm_Read(uint8_t* buf, uint32_t len)
{
	uint32_t available = FIFO_GetUsed(&rx_fifo);
	if (!available) {
		return -1;
	} else {
		if (len > available) len = available;
		BTM_DISABLE_IT_RXNE();
		FIFO_Pop(&rx_fifo, buf, len);
		BTM_ENABLE_IT_RXNE();
		return len;
	}
}

int Btm_Write(const uint8_t* buf, uint32_t len)
{
	uint32_t available = FIFO_GetFree(&tx_fifo);
	if (!available) {
		return -1;
	} else {
		if (len > available) len = available;
		BTM_DISABLE_IT_TXE();
		FIFO_Push(&tx_fifo, buf, len);
		BTM_ENABLE_IT_TXE();
		return len;
	}
}

void Btm_PutCh(uint8_t c)
{
	while (FIFO_IsFull(&tx_fifo));
	BTM_DISABLE_IT_TXE();
	FIFO_Push(&tx_fifo, &c, 1);
	BTM_ENABLE_IT_TXE();
}

uint8_t Btm_GetCh(void)
{
	uint8_t c = 0;
	while (FIFO_IsEmpty(&rx_fifo));
	BTM_DISABLE_IT_RXNE();
	FIFO_Pop(&rx_fifo, &c, 1);
	BTM_ENABLE_IT_RXNE();
	return c;
}

void Btm_Print(const char* str)
{
	const uint32_t len = strlen(str);
	uint32_t i = 0;
	for (; i < len; i++) {
		Btm_PutCh(str[i]);
	}
}

void BTM_IRQ_HANDLER(void)
{
    if (USART_GetITStatus(BTM_USART, USART_IT_TXE) != RESET)
    {
			if (!FIFO_IsEmpty(&tx_fifo)) {
				uint8_t tx_data = 0;
				FIFO_Pop(&tx_fifo, &tx_data, 1);
				USART_SendData(BTM_USART, tx_data);
			} else {
				BTM_DISABLE_IT_TXE();
			}
    }
		else if (USART_GetITStatus(BTM_USART, USART_IT_RXNE) != RESET)
    {
        uint8_t rx_data = USART_ReceiveData(BTM_USART);
        if (FIFO_IsFull(&rx_fifo)) {
        	uint8_t tmp = 0;
        	FIFO_Pop(&rx_fifo, &tmp, 1);
        }
        FIFO_Push(&rx_fifo, &rx_data, 1);
        BtmRxCallback(rx_data);
    }
}


