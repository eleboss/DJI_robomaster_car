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
 
#include "motor.h"

void CM_Cmd(CAN_TypeDef* CANx, int16_t c201, int16_t c202, int16_t c203, int16_t c204)
{
	CanTxMsg canTxMsg;
	canTxMsg.StdId = CM_CMD_CAN_MSG_ID;
	canTxMsg.IDE = CAN_Id_Standard;
	canTxMsg.RTR = CAN_RTR_Data;
	canTxMsg.DLC = 0x08;
	
	canTxMsg.Data[0] = (uint8_t)(c201 >> 8);
	canTxMsg.Data[1] = (uint8_t)c201;
	canTxMsg.Data[2] = (uint8_t)(c202 >> 8);
	canTxMsg.Data[3] = (uint8_t)c202;
	canTxMsg.Data[4] = (uint8_t)(c203 >> 8);
	canTxMsg.Data[5] = (uint8_t)c203;
	canTxMsg.Data[6] = (uint8_t)(c204 >> 8);
	canTxMsg.Data[7] = (uint8_t)c204;
	CAN_Transmit(CANx, &canTxMsg);
}

void GM_Cmd(CAN_TypeDef* CANx, int16_t c205, int16_t c206)
{
	CanTxMsg canTxMsg;
	canTxMsg.StdId = GM_CMD_CAN_MSG_ID;
	canTxMsg.IDE = CAN_Id_Standard;
	canTxMsg.RTR = CAN_RTR_Data;
	canTxMsg.DLC = 0x08;
	
	canTxMsg.Data[0] = (uint8_t)(c205 >> 8);
	canTxMsg.Data[1] = (uint8_t)c205;
	canTxMsg.Data[2] = (uint8_t)(c206 >> 8);
	canTxMsg.Data[3] = (uint8_t)c206;
	canTxMsg.Data[4] = (uint8_t)0x00;
	canTxMsg.Data[5] = (uint8_t)0x00;
	canTxMsg.Data[6] = (uint8_t)0x00;
	canTxMsg.Data[7] = (uint8_t)0x00;
	CAN_Transmit(CANx, &canTxMsg);
}
