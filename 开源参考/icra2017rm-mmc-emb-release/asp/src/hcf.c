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

#include "hcf.h"

void Hcf_Init(Hcf_t* hcf)
{
	uint32_t i = 0, j = 0;
	for (; i < MOUSE_BTN_CNT; i++) {
		for (; j < 3; j++) {
			hcf->b[i][j] = MOUSE_BTN_UP;
		}
	}
	memset(hcf->fn, 0, sizeof(hcf->fn));
}

void Hcf_Proc(Hcf_t* hcf, const Hcp_t* hcp)
{
	uint32_t i = 0;
	for (; i < MOUSE_BTN_CNT; i++) {
		if (hcf->b[i][0] == hcp->mouse.b[i]) {
			if (hcf->fn[i] < MOUSE_BTN_PRESS_CONFIRM_CNT) {
				hcf->fn[i]++;
			} else {
				hcf->b[i][1] = hcf->b[i][2];
				hcf->b[i][2] = hcp->mouse.b[i];
			}
		} else {
			hcf->fn[i] = 0;
		}
		hcf->b[i][0] = hcp->mouse.b[i];
	}
}

