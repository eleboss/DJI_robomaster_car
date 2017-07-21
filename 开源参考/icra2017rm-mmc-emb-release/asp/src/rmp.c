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
 
#include "rmp.h"

void Rmp_Config(Rmp_t* rmp, uint32_t scale)
{
	rmp->scale = scale;
}

float Rmp_Calc(Rmp_t* rmp)
{
	if(rmp->count < rmp->scale)
	{
		rmp->count++;
		rmp->out = rmp->count / (float)rmp->scale;
	}
	return rmp->out;
}

void Rmp_Reset(Rmp_t* rmp)
{
	rmp->count = 0;
	rmp->out = 0;
}

uint8_t Rmp_IsOverflow(const Rmp_t* rmp)
{
	return rmp->count >= rmp->scale;
}
