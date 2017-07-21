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
 
#ifndef __CAL_H__
#define __CAL_H__

/*****************************************/
/*              Calibration              */
/*****************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "bsp.h"
#include "drv.h"
#include "odo.h"
#include "maf.h"
#include "cfg.h"

#define CAL_GM_UP_DIR 1
#define CAL_GM_DRV_CURRENT 5000
#define CAL_GM_START_UP_DELAY 200
#define CAL_GM_BANG_VEL_TH 5e-2f
#define CAL_GM_MAF_BUF_LEN 3

typedef uint32_t CalFlag_t;

#define CAL_FLAG_GPEH       ((CalFlag_t)(1u << 0))
#define CAL_FLAG_GPEL       ((CalFlag_t)(1u << 1))
#define CAL_FLAG_GPCH       ((CalFlag_t)(1u << 2))
#define CAL_FLAG_GPCL       ((CalFlag_t)(1u << 3))

#define CAL_FLAG_GPE (CAL_FLAG_GPEH | CAL_FLAG_GPEL)
#define CAL_FLAG_GPC (CAL_FLAG_GPCH | CAL_FLAG_GPCL)
#define CAL_FLAG_GIM (CAL_FLAG_GPE | CAL_FLAG_GPC)
#define CAL_FLAG_ALL (CAL_FLAG_GIM)

void Cal_Init(void);
void Cal_Proc(void);

CalFlag_t Cal_GetFlag(void);
void Cal_SetFlag(CalFlag_t flag);
void Cal_ClrFlag(CalFlag_t flag);
CalFlag_t Cal_HasFlag(CalFlag_t mask);
CalFlag_t Cal_HitFlag(CalFlag_t mask);
CalFlag_t Cal_IsDone(void);
	
#ifdef __cplusplus
}
#endif

#endif




