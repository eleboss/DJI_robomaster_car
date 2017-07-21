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

#ifndef __SCH_H__
#define __SCH_H__

/********************************************************/
/*                    Task Scheduler                    */
/********************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//#include "clk.h"
	
typedef void (*SchRun_t)(void);

typedef struct SchTask_t
{
	SchRun_t run;
	uint32_t interval;
	uint32_t lastrun;
	struct SchTask_t* prev;
	struct SchTask_t* next;
}SchTask_t;

void Sch_Init(void);
void Sch_Proc(void);

uint8_t Sch_Arrange(SchRun_t run, uint32_t interval);
uint8_t Sch_Dismiss(SchRun_t run);

#ifdef __cplusplus
}
#endif

#endif
