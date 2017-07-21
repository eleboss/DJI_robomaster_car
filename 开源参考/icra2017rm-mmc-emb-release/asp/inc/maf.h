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

#ifndef __MAF_H__
#define __MAF_H__

/*******************************************/
/*          Moving Average Filter          */
/*******************************************/

#ifdef __cpluplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	float* buf;    // buffer
	uint32_t len;  // length
	uint32_t i;    // index
	float avg;     // average
}Maf_t;

void Maf_Init(Maf_t* maf, float* buf, uint32_t len);
void Maf_Reset(Maf_t* maf);
float Maf_Proc(Maf_t* maf, float v);
void Maf_Preload(Maf_t* maf, float v);

Maf_t* Maf_Create(uint32_t len);
void Maf_Destroy(Maf_t* maf);

#ifdef __cpluplus
}
#endif

#endif


