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
 
#ifndef __CAN1_H__
#define __CAN1_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "stm32util.h"

#define CAN1_RX_PIN PD0
#define CAN1_TX_PIN PD1
#define CAN1_RX_IRQ_HANDLER IRQ_HANDLER(CAN1_RX0)
#define CAN1_RX_NVIC IRQ(CAN1_RX0)
#define CAN1_RX_NVIC_PRE_PRIORITY 1
#define CAN1_RX_NVIC_SUB_PRIORITY 1
#define CAN1_TX_IRQ_HANDLER IRQ_HANDLER(CAN1_TX)
#define CAN1_TX_NVIC IRQ(CAN1_TX)
#define CAN1_TX_NVIC_PRE_PRIORITY 1
#define CAN1_TX_NVIC_SUB_PRIORITY 1

#define CAN1_ENABLE_RX_IT() CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE)
#define CAN1_DISABLE_RX_IT() CAN_ITConfig(CAN1, CAN_IT_FMP0, DISABLE)
#define CAN1_ENABLE_TXE_IT() CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE)
#define CAN1_DISABLE_TXE_IT() CAN_ITConfig(CAN1, CAN_IT_TME, DISABLE)

void Can1_Config(void);
void Can1_EnableIT(void);
void Can1_DisableIT(void);

void Can1RxCallback(uint32_t id, uint8_t* data);

#ifdef __cplusplus
}
#endif

#endif
