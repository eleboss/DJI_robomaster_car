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
 
#include "srs.h"

static uint32_t sri = 0;

Srs_t srs[SR04_NUM];

void Srs_Init(void)
{
	for (sri = 0; sri < SR04_NUM; sri++) {
		memset(&srs[sri], 0, sizeof(Srs_t));
		Maf_Init(&srs[sri].maf, srs[sri].buf, SR04_MAF_LEN);
	}
	sri = 0;
}

void Srs_Proc(void)
{
	uint8_t i = 0;
	for (; i < SR04_NUM; i++) {
		// Idle
		if (srs[sri].state == SR04_STATE_IDLE) {
			uint32_t interval = Clk_GetUsTick() - srs[sri].endEcho;
			if (interval > SR04_TRIG_TUS) {
				GPIO_RST(sr04[i].trigPin);
				GPIO_SET(sr04[i].trigPin);
				srs[sri].startTrig = Clk_GetUsTick();
				srs[sri].state = SR04_STATE_TRIG;
			}
		}
		else if (srs[sri].state == SR04_STATE_TRIG) {
			uint32_t interval = Clk_GetUsTick() - srs[sri].startTrig;
			if (interval > SR04_TRIG_PULSE_WIDTH) {
				GPIO_RST(sr04[i].trigPin);
				srs[sri].endTrig = Clk_GetUsTick();
				srs[sri].state = SR04_STATE_WAIT;
			}
		}
		else if (srs[sri].state == SR04_STATE_WAIT) {
			uint32_t interval = Clk_GetUsTick() - srs[sri].endTrig;
			if (interval > SR04_WAIT_ECHO_TIMEOUT) {
				GPIO_RST(sr04[i].trigPin);
				GPIO_SET(sr04[i].trigPin);
				srs[sri].startTrig = Clk_GetUsTick();
			}
		}
	}
}

void Sr04_Proc(uint8_t i, uint8_t trigger)
{
	if (i == SR04_IDX_FIXED) {
		Wdg_Feed(WDG_IDX_SR04F);
	} else if (i == SR04_IDX_MOBLE) {
		Wdg_Feed(WDG_IDX_SR04M);
	} else if (i == SR04_IDX_LEFT) {
		Wdg_Feed(WDG_IDX_SR04L);
	} else if (i == SR04_IDX_RIGHT) {
		Wdg_Feed(WDG_IDX_SR04R);
	}
	if (i < SR04_NUM) {
		// Rising edge trigger -> start echo
		if (trigger == 1) {
			srs[i].startEcho = Clk_GetUsTick();
			srs[i].state = SR04_STATE_ECHO;
		}
		// Falling edge trigger -> end echo
		else if (trigger == 0) {
			srs[i].frame_cnt++;
			srs[i].endEcho = Clk_GetUsTick();
			srs[i].echo = srs[i].endEcho - srs[i].startEcho;
			srs[i].mm = (uint16_t)(srs[i].echo * SR04_ECHO_RECIP);
		  srs[i].mm_filtered = Maf_Proc(&srs[i].maf, srs[i].mm);
			srs[i].state = SR04_STATE_IDLE;
		}
	}
}

