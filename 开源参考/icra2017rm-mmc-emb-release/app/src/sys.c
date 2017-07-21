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

#include "sys.h"

PeriphsState_t FS_Get(const PeriphsState_t* fs, PeriphsState_t mask)
{
	return Flag_Get(fs, mask);
}

void FS_Set(PeriphsState_t* fs, PeriphsState_t mask)
{
	Flag_Set(fs, mask);
}

void FS_Clr(PeriphsState_t* fs, PeriphsState_t mask)
{
	Flag_Clr(fs, mask);
}

void FS_Tog(PeriphsState_t* fs, PeriphsState_t mask)
{
	Flag_Tog(fs, mask);
}

void FS_Cpy(PeriphsState_t* fs, PeriphsState_t src, PeriphsState_t mask)
{
	Flag_Cpy(fs, src, mask);
}

void FS_Det(PeriphsState_t* fs, Flag_t mask, uint32_t condition)
{
	Flag_Det(fs, mask, condition);
}

void CS_Set(ChassisState_t* cs, float x, float y, float z)
{
	cs->x = x;
	cs->y = y;
	cs->z = z;
}

void MS_Set(MecanumState_t* ms, float w1, float w2, float w3, float w4)
{
	ms->w1 = w1;
	ms->w2 = w2;
	ms->w3 = w3;
	ms->w4 = w4;
}

void GS_Set(GrabberState_t* gs, float e, float c)
{
	gs->e = e;
	gs->c = c;
}


