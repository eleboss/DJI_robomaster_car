/**
 * Copyright (c) 2016, Jack Mo (mobangjack@foxmail.com).
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

#ifndef __PWR_H__
#define __PWR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "can.h"
#include "maf.h"

#define PWR_SAMPLE_TMS 500

#define PWR_MOTOR_MAF_LEN 10
#define PWR_MOTOR_DEAD_LOCK_SPEED_TH 2
#define PWR_MOTOR_CURRENT_OVERLOAD_TH 41000

#define PWR_MOTOR_MAF_GRP_N 2
#define PWR_MOTOR_MAF_IDX_V 0
#define PWR_MOTOR_MAF_IDX_C 1
	
typedef uint32_t PwrOLFlag_t;

#define PWR_OL_FLAG_MOTOR1 (1u << 0)
#define PWR_OL_FLAG_MOTOR2 (1u << 1)
#define PWR_OL_FLAG_MOTOR3 (1u << 2)
#define PWR_OL_FLAG_MOTOR4 (1u << 3)
#define PWR_OL_FLAG_MOTOR5 (1u << 4)
#define PWR_OL_FLAG_MOTOR6 (1u << 5)

#define PWR_OL_FLAG_MOTORS (PWR_OL_FLAG_MOTOR1 | PWR_OL_FLAG_MOTOR2 | PWR_OL_FLAG_MOTOR3 | PWR_OL_FLAG_MOTOR4 | PWR_OL_FLAG_MOTOR5 | PWR_OL_FLAG_MOTOR6)
#define PWR_OL_FLAG_ALL (PWR_OL_FLAG_MOTORS)

void Pwr_Init(void);
void Pwr_Proc(void);

PwrOLFlag_t Pwr_GetOLFlag(void);
void Pwr_SetOLFlag(PwrOLFlag_t flag);
PwrOLFlag_t Pwr_HasOLFlag(PwrOLFlag_t flag);
PwrOLFlag_t Pwr_HitOLFlag(PwrOLFlag_t flag);
void Pwr_ClrOLFlag(PwrOLFlag_t flag);
PwrOLFlag_t Pwr_IsOkay(void);

#ifdef __cplusplus
}
#endif

#endif
	

