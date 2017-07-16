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
 
#ifndef __MOTOR_H__
#define __MOTOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "platform.h"

#define MOTOR_CAN CAN1
#define CM_CMD(c201,c202,c203,c204) CM_Cmd(MOTOR_CAN,c201,c202,c203,c204)
#define GM_CMD(c205,c206) GM_Cmd(MOTOR_CAN,c205,c206)

#define CM_CMD_CAN_MSG_ID 0x200
#define GM_CMD_CAN_MSG_ID 0x1ff

void CM_Cmd(CAN_TypeDef *CANx, int16_t c201, int16_t c202, int16_t c203, int16_t c204);
void GM_Cmd(CAN_TypeDef *CANx, int16_t c205, int16_t c206);

#ifdef __cplusplus
}
#endif
	
#endif
