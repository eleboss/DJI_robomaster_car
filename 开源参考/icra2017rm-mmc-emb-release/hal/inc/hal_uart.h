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

#ifndef __HAL_UART_H__
#define __HAL_UART_H__

/****************************************************/
/*          Hardware Abstract Layer - UART          */
/****************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

typedef struct
{
	uint32_t (*GetRxFifoSize)(void);
	uint32_t (*GetRxFifoUsed)(void);
	uint32_t (*GetRxFifoFree)(void);
	uint32_t (*GetTxFifoSize)(void);
	uint32_t (*GetTxFifoUsed)(void);
	uint32_t (*GetTxFifoFree)(void);
	int (*ReadByte)(void);
	int (*WriteByte)(uint8_t);
	int (*Read)(uint8_t*, uint32_t);
	int (*Write)(const uint8_t*, uint32_t);
	void (*PutCh)(uint8_t);
	uint8_t (*GetCh)(void);
	void (*Print)(const char* str);
}Hal_Uart_t;
	
#define HAL_UART_DEF(DEV) \
{ \
	.GetRxFifoSize = &DEV##_GetRxFifoSize, \
	.GetRxFifoUsed = &DEV##_GetRxFifoUsed, \
	.GetRxFifoFree = &DEV##_GetRxFifoFree, \
	.GetTxFifoSize = &DEV##_GetTxFifoSize, \
	.GetTxFifoUsed = &DEV##_GetTxFifoUsed, \
	.GetTxFifoFree = &DEV##_GetTxFifoFree, \
	.ReadByte      = &DEV##_ReadByte,      \
	.WriteByte     = &DEV##_WriteByte,     \
	.Read          = &DEV##_Read,          \
	.Write         = &DEV##_Write,         \
	.PutCh         = &DEV##_PutCh,         \
	.GetCh         = &DEV##_GetCh,         \
	.Print         = &DEV##_Print,         \
}

void Hal_Uart_Init(Hal_Uart_t* uart);

#ifdef __cplusplus
}
#endif

#endif


