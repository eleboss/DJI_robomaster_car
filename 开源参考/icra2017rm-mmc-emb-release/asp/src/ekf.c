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

#include "ekf.h"

#define SQR(x) (x*x)

void Ekf_Init(Ekf_t* ekf, float q, float r)
{
	ekf->q = q;
	ekf->r = r;
	Ekf_Reset(ekf);
}

void Ekf_Reset(Ekf_t* ekf)
{
	ekf->e = 0;
	ekf->d = 0;
	ekf->k = 0;
	ekf->p = 0;
}

void Ekf_SetE(Ekf_t* ekf, float e)
{
	ekf->e = e;
}

void Ekf_SetD(Ekf_t* ekf, float d)
{
	ekf->d = d;
}

void Ekf_SetQ(Ekf_t* ekf, float q)
{
	ekf->q = q;
}

void Ekf_SetR(Ekf_t* ekf, float r)
{
	ekf->r = r;
}

float Ekf_Proc(Ekf_t* ekf, float x) {
	// update
	ekf->e += ekf->d;
	ekf->p += ekf->q;
	// fusion
	ekf->k = ekf->p / (ekf->p + ekf->r ); // kalman gain
	ekf->d = (x - ekf->e) * ekf->k; // delta mean
	ekf->e += ekf->d;                  // fused mean
	ekf->p -= SQR(ekf->p) * ekf->k; // fused variance
	return ekf->e;
}

Ekf_t* Ekf_Create(void)
{
	Ekf_t* ekf = (Ekf_t*)malloc(sizeof(Ekf_t));
	if (ekf == NULL) return NULL;
	Ekf_Reset(ekf);
	return ekf;
}

void Ekf_Destroy(Ekf_t* ekf)
{
	if (ekf != NULL) {
		free(ekf);
		ekf = NULL;
	}
}

