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

#ifndef __GDF_H__
#define __GDF_H__

/*******************************************/
/*       Gauss Distribution Function       */
/*******************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
	
typedef struct
{
	float* buf;   // data buffer
	uint32_t len; // buffer length
	uint32_t i;   // ring buffer index

	float avg;  // average
	float avgd; // average difference
	float var;  // variance
	float vard; // variance difference
	float error; // gauss error
}Gdf_t;

void Gdf_Init(Gdf_t* gdf, float* buf, uint32_t len);
void Gdf_Reset(Gdf_t* gdf);
void Gdf_Proc(Gdf_t* gdf, float v);

Gdf_t* Gdf_Create(uint32_t len);
void Gdf_Destroy(Gdf_t* gdf);

#ifdef __cplusplus
}
#endif

#endif
