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

/*******************************************/
/*          Moving Average Filter          */
/*******************************************/

#include "maf.h"

void Maf_Init(Maf_t* maf, float* buf, uint32_t len)
{
	maf->buf = buf;
	maf->len = len;
	Maf_Reset(maf);
}

void Maf_Reset(Maf_t* maf)
{
	for (maf->i = 0; maf->i < maf->len; maf->i++) {
		maf->buf[maf->i] = 0;
	}
	maf->i = 0;
	maf->avg = 0;
}

float Maf_Proc(Maf_t* maf, float v)
{
	maf->avg += (v - maf->buf[maf->i]) / maf->len;
	maf->buf[maf->i++] = v;
	if (maf->i >= maf->len) maf->i = 0;
	return maf->avg;
}

void Maf_Preload(Maf_t* maf, float v)
{
	maf->avg = v;
	for (maf->i = 0; maf->i < maf->len; maf->i++) {
		maf->buf[maf->i] = v / maf->len;
	}
	maf->i = 0;
}

Maf_t* Maf_Create(uint32_t len)
{
	Maf_t* maf = (Maf_t*)malloc(sizeof(Maf_t));
	if(maf == NULL) return NULL;
	memset(maf, 0, sizeof(Maf_t));
	maf->buf = (float*)malloc(len * sizeof(float));
	if(maf->buf == NULL) {
		free(maf);
		maf = NULL;
		return NULL;
	}
	maf->len = len;
	Maf_Reset(maf);
	return maf;
}

void Maf_Destroy(Maf_t* maf)
{
	if (maf != NULL) {
		if (maf->buf != NULL) {
			free(maf->buf);
			maf->buf = NULL;
		}
		free(maf);
		maf = NULL;
	}
}


