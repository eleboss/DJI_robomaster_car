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

#ifndef __HCF_H__
#define __HCF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#include "hcp.h"

#define MOUSE_BTN_PRESS_CONFIRM_CNT 5
typedef struct
{
	uint8_t  b[MOUSE_BTN_CNT][3]; // 0: last raw state, 1: last filtered state, 2: this filtered state
	uint32_t fn[MOUSE_BTN_CNT]; // confirm counter
}Hcf_t; // Remote control protocol filtered frame structure

void Hcf_Init(Hcf_t* hcf);
void Hcf_Proc(Hcf_t* hcf, const Hcp_t* hcp);

#ifdef __cplusplus
}
#endif

#endif


