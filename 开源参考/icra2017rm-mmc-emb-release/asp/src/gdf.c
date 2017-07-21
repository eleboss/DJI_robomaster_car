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

#include "gdf.h"

void Gdf_Init(Gdf_t* gdf, float* buf, uint32_t len)
{
	gdf->buf = buf;
	gdf->len = len;
	Gdf_Reset(gdf);
}

void Gdf_Reset(Gdf_t* gdf)
{
	memset(gdf->buf, 0, gdf->len * sizeof(float));
	gdf->i = 0;
	gdf->avg = 0;
	gdf->var = 0;
	gdf->avgd = 0;
	gdf->vard = 0;
	gdf->error = FLT_MAX;
}

#define SQR(x) (x*x)
void Gdf_Proc(Gdf_t* gdf, float v)
{
	float avg = gdf->avg;
	float del = v - gdf->buf[gdf->i];
	gdf->avgd = del / gdf->len;
	gdf->avg += gdf->avgd;
	gdf->vard = del * (gdf->buf[gdf->i] - avg + v - gdf->avg) / gdf->len;
	gdf->var += gdf->vard;
	gdf->error = SQR(gdf->avgd) + SQR(gdf->vard);
	gdf->buf[gdf->i++] = v;
	if (gdf->i == gdf->len) gdf->i = 0;
}

Gdf_t* Gdf_Create(uint32_t len)
{
	Gdf_t* gdf = (Gdf_t*)malloc(sizeof(Gdf_t));
	if (gdf == NULL) {
		return NULL;
	}
	memset(gdf, 0, sizeof(Gdf_t));
	gdf->len = len;
	gdf->buf = (float*)malloc(len * sizeof(float));
	if (gdf->buf == NULL) {
		free(gdf);
		gdf = NULL;
		return NULL;
	}
	Gdf_Reset(gdf);
	return gdf;
}

void Gdf_Destroy(Gdf_t* gdf)
{
	if (gdf != NULL) {
		if (gdf->buf != NULL) {
			free(gdf->buf);
			gdf->buf = NULL;
		}
		free(gdf);
		gdf = NULL;
	}
}
