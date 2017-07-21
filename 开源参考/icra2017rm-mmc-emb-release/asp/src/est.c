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

#include "est.h"

void Est_Init(Est_t* est, Gdf_t* gdf, Ekf_t* ekf)
{
	est->gdf = gdf;
	est->ekf = ekf;
	Est_Reset(est);
}
void Est_Proc(Est_t* est, float v)
{
	if (est->error > 0) {
		Gdf_Proc(est->gdf, v);
		if (est->gdf->error < est->error) {
			est->error = est->gdf->error;
			Ekf_SetR(est->ekf, est->gdf->var);
			Ekf_SetE(est->ekf, est->gdf->avg);
			Ekf_SetD(est->ekf, est->gdf->avgd);
		}
		est->value = est->gdf->avg;
		est->delta = est->gdf->avgd;
	} else {
		Ekf_Proc(est->ekf, v);
		est->delta = est->ekf->e - est->value;
		est->value = est->ekf->e;
	}
}

void Est_Reset(Est_t* est)
{
	Gdf_Reset(est->gdf);
	Ekf_Reset(est->ekf);
	est->error = FLT_MAX;
	est->value = 0;
	est->delta = 0;
}

Est_t* Est_Create(uint32_t N, float Q)
{
	Est_t* est = (Est_t*)malloc(sizeof(Est_t));
	if (est == NULL) {
		return NULL;
	}
	est->gdf = Gdf_Create(N);
	if (est->gdf == NULL) {
		free(est);
		est = NULL;
		return NULL;
	}
	Gdf_Reset(est->gdf);
	est->ekf = Ekf_Create();
	if (est->ekf == NULL) {
		Gdf_Destroy(est->gdf);
		free(est);
		est = NULL;
		return NULL;
	}
	Ekf_Reset(est->ekf);
	Ekf_SetQ(est->ekf, Q);
	est->error = FLT_MAX;
	return est;
}

void Est_Destroy(Est_t* est)
{
	if (est != NULL) {
		Gdf_Destroy(est->gdf);
		Ekf_Destroy(est->ekf);
		free(est);
		est = NULL;
	}
}

