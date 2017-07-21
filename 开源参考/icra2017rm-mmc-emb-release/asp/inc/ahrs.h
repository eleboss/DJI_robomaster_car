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

#ifndef __AHRS_H__
#define __AHRS_H__

/*******************************************/
/*    Attitude Heading Reference System    */
/*******************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>

typedef struct
{
	float q[4];
	float kp;
	float ki;
	float exInt;
	float eyInt;
	float ezInt;
}AHRS_t;

typedef struct
{
	float yaw;
	float pitch;
	float roll;
}Euler_t;

void AHRS_Config(AHRS_t* ahrs, float kp, float ki);
void AHRS_Update(AHRS_t* ahrs, float* buf, float halfT);
void AHRS_Q2Euler(float* q, Euler_t* euler);

#ifdef __cplusplus
}
#endif

#endif

