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

#include "tim.h"

void TickTim_Config(void)
{
	TIM_Config(TICK_TIM, TICK_TIM_PS, TIM_CounterMode_Up, TICK_TIM_PD, TIM_CKD_DIV1, 0);
	TIM_ARRPreloadConfig(TICK_TIM, ENABLE);
	NVIC_Config(TICK_TIM_NVIC, TICK_TIM_NVIC_PRE_PRIORITY, TICK_TIM_NVIC_SUB_PRIORITY);
}

void TickTim_Start(void)
{
	TIM_ClearFlag(TICK_TIM, TIM_FLAG_Update);
	TIM_ITConfig(TICK_TIM, TIM_IT_Update, ENABLE);
	TIM_Cmd(TICK_TIM, ENABLE);
}

void TickTim_Stop(void)
{
	TIM_Cmd(TICK_TIM, DISABLE);
	TIM_ITConfig(TICK_TIM, TIM_IT_Update, DISABLE);
	TIM_ClearFlag(TICK_TIM, TIM_FLAG_Update);
}

void TICK_TIM_IRQ_HANDLER(void)
{
	if (TIM_GetITStatus(TICK_TIM, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TICK_TIM, TIM_IT_Update);
		TIM_ClearFlag(TICK_TIM, TIM_FLAG_Update);

		TickTimCallback();
	}
}

void SyncTim_Config()
{
	TIM_Config(SYNC_TIM, SYNC_TIM_PS, TIM_CounterMode_Up, SYNC_TIM_PD, TIM_CKD_DIV1, 0);
	NVIC_Config(SYNC_TIM_NVIC, SYNC_TIM_NVIC_PRE_PRIORITY, SYNC_TIM_NVIC_SUB_PRIORITY);
}

void SyncTim_Start()
{
	TIM_ClearFlag(SYNC_TIM, TIM_FLAG_Update);
	TIM_ITConfig(SYNC_TIM, TIM_IT_Update, ENABLE);
	TIM_Cmd(SYNC_TIM, ENABLE);
}

void SyncTim_Stop()
{
	TIM_Cmd(SYNC_TIM, DISABLE);
	TIM_ITConfig(SYNC_TIM, TIM_IT_Update, DISABLE);
	TIM_ClearFlag(SYNC_TIM, TIM_FLAG_Update);
}

void SYNC_TIM_IRQ_HANDLER()
{
	if (TIM_GetITStatus(SYNC_TIM, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(SYNC_TIM, TIM_IT_Update);
		TIM_ClearFlag(SYNC_TIM, TIM_FLAG_Update);

		SyncTimCallback();
	}
}

void Tim_Config()
{
	TickTim_Config();
	SyncTim_Config();
}

void Tim_Start()
{
	TickTim_Start();
	SyncTim_Start();
}

void Tim_Stop()
{
	TickTim_Stop();
	SyncTim_Stop();
}



