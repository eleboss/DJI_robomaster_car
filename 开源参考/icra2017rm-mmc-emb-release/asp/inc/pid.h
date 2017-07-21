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
 
#ifndef __PID_H__
#define __PID_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdint.h>
	
typedef struct
{
	float kp;
	float ki;
	float kd;
	float it;  // Integral threshold
	float Emax;
	float Pmax;
	float Imax;
	float Dmax;
	float Omax;
	
	float error[2];
	float Pout;
	float Iout;
	float Dout;
	float out;
}PID_t;

void PID_Config(PID_t* pid, float kp, float ki, float kd, float it, float Emax, float Pmax, float Imax, float Dmax, float Omax);
float PID_Calc(PID_t* pid, float ref, float fdb);
void PID_Reset(PID_t* pid);

#ifdef __cplusplus
}
#endif
	
#endif

