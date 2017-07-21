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
 
#include "can1.h"

void Can1_Config(void)
{
	GPIO_AF(CAN1_RX_PIN, CAN1);
	GPIO_AF(CAN1_TX_PIN, CAN1);

//	NVIC_Config(CAN1_RX_NVIC, CAN1_RX_NVIC_PRE_PRIORITY, CAN1_RX_NVIC_SUB_PRIORITY);
//	NVIC_Config(CAN1_TX_NVIC, CAN1_TX_NVIC_PRE_PRIORITY, CAN1_TX_NVIC_SUB_PRIORITY);

	//CAN BaudRate 45/(1+9+5)/3=1Mbps
	CAN_Config(CAN1, 3, 0, CAN_SJW_1tq, CAN_BS1_9tq, CAN_BS2_5tq);

	//CAN_Filter_Config(0x0000, 0x0000, 0x0000, 0x0000, 0, 0);

//	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
//	CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);
	
	//Can1_DisableIT();
}

void Can1_EnableIT(void)
{
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);
}

void Can1_DisableIT(void)
{
	CAN_ITConfig(CAN1, CAN_IT_FMP0, DISABLE);
	CAN_ITConfig(CAN1, CAN_IT_TME, DISABLE);
}

//void CAN1_RX_IRQ_HANDLER(void)
//{
//  if (CAN_GetITStatus(CAN1, CAN_IT_FMP0) != RESET)
//	{
//		CanRxMsg canRxMsg;
//		CAN_ClearITPendingBit(CAN1, CAN_IT_FF0);
//		CAN_ClearFlag(CAN1, CAN_FLAG_FF0);
//		CAN_Receive(CAN1, CAN_FIFO0, &canRxMsg);

//		Can1RxCallback(canRxMsg.StdId, canRxMsg.Data);
//  }
//}

//void CAN1_TX_IRQ_HANDLER(void)
//{
//  if (CAN_GetITStatus(CAN1, CAN_IT_TME) != RESET)
//	{
//		CAN_ClearITPendingBit(CAN1, CAN_IT_TME);
//  }
//}
