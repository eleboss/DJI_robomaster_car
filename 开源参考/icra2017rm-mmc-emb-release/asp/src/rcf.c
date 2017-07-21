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

#include "rcf.h"

void Rcf_Init(Rcf_t* rcf)
{
	uint32_t i = 0, j = 0;
	for (; i < SW_CNT; i++) {
		for (; j < 3; j++) {
			rcf->sw[i][j] = SW_MD;
		}
	}
	memset(rcf->fn, 0, sizeof(rcf->fn));
}

void Rcf_Proc(Rcf_t* rcf, const Rcp_t* rcp)
{
	uint32_t i = 0;
	for (; i < SW_CNT; i++) {
		if (rcf->sw[i][0] == rcp->sw[i]) {
			if (rcf->fn[i] < SWITCH_CONFIRM_CNT) {
				rcf->fn[i]++;
			} else {
				rcf->sw[i][1] = rcf->sw[i][2];
				rcf->sw[i][2] = rcp->sw[i];
			}
		} else {
			rcf->fn[i] = 0;
		}
		rcf->sw[i][0] = rcp->sw[i];
	}
}

