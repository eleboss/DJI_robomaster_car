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

#ifndef __EFK_H__
#define __EFK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
  /* Critical Section */
  float q;    // process noise
  float r;    // measurement noise
  /* Critical Section */
  
  float e;    // estimation
  float d;    // difference
  float k;    // kalman gain
  float p;    // fused variance
}Ekf_t;

void Ekf_Init(Ekf_t* ekf, float q, float r);
void Ekf_Reset(Ekf_t* ekf);
void Ekf_SetE(Ekf_t* ekf, float e);
void Ekf_SetD(Ekf_t* ekf, float d);
void Ekf_SetQ(Ekf_t* ekf, float q);
void Ekf_SetR(Ekf_t* ekf, float r);
float Ekf_Proc(Ekf_t* ekf, float x);

Ekf_t* Ekf_Create(void);
void Ekf_Destroy(Ekf_t* ekf);

#ifdef __cplusplus
}
#endif

#endif

