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
 
#include "pwr.h"

static PwrOLFlag_t pwrOLFlag;

static Maf_t maf[PWR_MOTOR_MAF_GRP_N][MOTOR_NUM];
static float buf[PWR_MOTOR_MAF_GRP_N][MOTOR_NUM][PWR_MOTOR_MAF_LEN];

void Pwr_Init(void)
{
	uint32_t i = 0;
	uint32_t j = 0;
	for ( i = 0; i < PWR_MOTOR_MAF_GRP_N; i++) {
		for ( j = 0; j < MOTOR_NUM; j++) {
			Maf_Init(&maf[i][j], buf[i][j], PWR_MOTOR_MAF_LEN);
		}
	}
	pwrOLFlag = 0;
}

void Pwr_Proc(void)
{
	uint32_t i = 0;
	for ( i = 0; i < PWR_MOTOR_MAF_GRP_N; i++) {
		Maf_Proc(&maf[PWR_MOTOR_MAF_IDX_V][i], ABSVAL(motor[i].rate_filtered));
		Maf_Proc(&maf[PWR_MOTOR_MAF_IDX_C][i], ABSVAL(motor[i].current_ref));
		if (maf[PWR_MOTOR_MAF_IDX_V][i].avg < PWR_MOTOR_DEAD_LOCK_SPEED_TH && maf[PWR_MOTOR_MAF_IDX_C][i].avg > PWR_MOTOR_CURRENT_OVERLOAD_TH) {
			Pwr_SetOLFlag(i);
		}
	}
}

PwrOLFlag_t Pwr_GetOLFlag(void)
{
	return pwrOLFlag;
}

void Pwr_SetOLFlag(PwrOLFlag_t flag)
{
	pwrOLFlag |= flag;
}

PwrOLFlag_t Pwr_HasOLFlag(PwrOLFlag_t flag)
{
	return pwrOLFlag & flag;
}

PwrOLFlag_t Pwr_HitOLFlag(PwrOLFlag_t flag)
{
	return (pwrOLFlag & flag) == flag;
}

void Pwr_ClrOLFlag(PwrOLFlag_t flag)
{
	pwrOLFlag &= ~flag;
}

PwrOLFlag_t Pwr_IsOkay(void)
{
	return (!Pwr_HasOLFlag(PWR_OL_FLAG_ALL));
}
