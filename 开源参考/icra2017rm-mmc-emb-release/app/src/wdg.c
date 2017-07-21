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

#include "wdg.h"

/***********************************/
/*            Watch Dog            */
/***********************************/

static const uint32_t CNT[WDG_NUM] = WDG_OVERFLOW_CNT_DEFAULT;

static uint32_t cnt[WDG_NUM] = WDG_OVERFLOW_CNT_DEFAULT;

static uint32_t err = 0xFFFFFFFF;

void Wdg_Init(void)
{
	int i = 0;
	for(i = 0; i < WDG_NUM; i++)
	{
		cnt[i] = CNT[i];
	}
	err = 0xFFFFFFFF;
}

void Wdg_Proc(void)
{
	uint32_t i = 0;
	for(i = 0; i < WDG_NUM; i++)
	{
		if(cnt[i] < CNT[i])
		{
			err &= ~(uint32_t)(1u << i); //clear the error bit
			cnt[i]++;			        //add 1 each time
		}
		else
		{
			err |= (uint32_t)(1u << i); //set the error bit
		}
	}
}

void Wdg_Feed(uint8_t i)
{
	cnt[i] = 0;
}

void Wdg_Hang(uint8_t i)
{
	cnt[i] = CNT[i];
}

WdgErr_t Wdg_GetErr(void)
{
	return err;
}

WdgErr_t Wdg_HasErr(WdgErr_t mask)
{
	return err & mask;
}

WdgErr_t Wdg_HitErr(WdgErr_t mask)
{
	return (err & mask) == mask;
}

WdgErr_t Wdg_IsOkay(void)
{
	return !(Wdg_HitErr(WDG_ERR_SIGNAL) || Wdg_HasErr(WDG_ERR_MOTORS));
}

