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
 
#ifndef __SRS_H__
#define __SRS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>
	
#include "sr04.h"
#include "clk.h"
#include "maf.h"
#include "wdg.h"

#define SR04_TRIG_TUS 2000  // us
#define SR04_ECHO_RECIP 0.172f // 344/2/1e3 , mm
#define SR04_TRIG_PULSE_WIDTH 15 // > 10us
#define SR04_ECHO_PULSE_WIDTH_MAX 26162 // Range: 4500mm
#define SR04_WAIT_ECHO_TIMEOUT SR04_ECHO_PULSE_WIDTH_MAX

#define SR04_MAF_LEN 10

typedef enum
{
	SR04_STATE_IDLE = 0x00,
	SR04_STATE_TRIG = 0x01,
	SR04_STATE_WAIT = 0x02,
	SR04_STATE_ECHO = 0x03,
}SR04State_t;

typedef struct
{
	Maf_t maf;
	float buf[SR04_MAF_LEN];
	SR04State_t state;
	uint32_t frame_cnt;
	uint32_t startTrig;
	uint32_t endTrig;
	uint32_t startEcho;
	uint32_t endEcho;
	uint32_t echo;
	uint16_t mm;
	uint16_t mm_filtered;
}Srs_t;

void Srs_Init(void);
void Srs_Proc(void);

void Sr04_Proc(uint8_t i, uint8_t trigger);

extern Srs_t srs[SR04_NUM];

#ifdef __cplusplus
}
#endif

#endif
