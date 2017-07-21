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

#ifndef __RCF_H__
#define __RCF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#include "rcp.h"

#define SWITCH_CONFIRM_CNT 5
typedef struct
{
	uint8_t  sw[SW_CNT][3]; // 0: last raw state, 1: last filtered state, 2: this filtered state
	uint32_t fn[SW_CNT]; // confirm counter
}Rcf_t; // Remote control protocol filtered frame structure

void Rcf_Init(Rcf_t* rcf);
void Rcf_Proc(Rcf_t* rcf, const Rcp_t* rcp);

#ifdef __cplusplus
}
#endif

#endif

