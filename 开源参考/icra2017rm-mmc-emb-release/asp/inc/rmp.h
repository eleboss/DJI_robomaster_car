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
 
#ifndef __RMP_H__
#define __RMP_H__

#ifdef __cpluplus
extern "C" {
#endif

#include <stdint.h>

typedef struct
{
	uint32_t scale;
	uint32_t count;
	float out;
}Rmp_t;

void Rmp_Config(Rmp_t* rmp, uint32_t scale);
float Rmp_Calc(Rmp_t* rmp);
void Rmp_Reset(Rmp_t* rmp);
uint8_t Rmp_IsOverflow(const Rmp_t* rmp);

#define RMP(SCALE) { \
	.scale = SCALE, \
	.count = 0, \
	.out = 0, \
}
	
#ifdef __cpluplus
}
#endif

#endif

