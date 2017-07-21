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
 
#include "pid.h"

void PID_Config(PID_t* pid, float kp, float ki, float kd, float it, float Emax, float Pmax, float Imax, float Dmax, float Omax)
{
	pid->kp = kp;
	pid->ki = ki;
	pid->kd = kd;
	pid->it = it;
	pid->Emax = Emax;
	pid->Pmax = Pmax;
	pid->Imax = Imax;
	pid->Dmax = Dmax;
	pid->Omax = Omax;
}

void PID_Reset(PID_t *pid)
{
	pid->error[0] = 0;
	pid->error[1] = 0;
	pid->Pout = 0;
	pid->Iout = 0;
	pid->Dout = 0;
	pid->out = 0;
}

#define LIMIT(val,min,max) do { val = val > max ? max : val < min ? min : val; } while (0)
float PID_Calc(PID_t* pid, float ref, float fdb)
{
	pid->error[0] = pid->error[1];
	pid->error[1] = ref - fdb; // calculate error
	LIMIT(pid->error[1], -pid->Emax, pid->Emax);
	pid->Pout = pid->kp * pid->error[1]; // P
	LIMIT(pid->Pout, -pid->Pmax, pid->Pmax); // limit P
	if (pid->error[1] < pid->it) {
		pid->Iout += pid->ki * pid->error[1]; // I
		LIMIT(pid->Iout, -pid->Imax, pid->Imax); // limit I
	} else {
		pid->Iout = 0;
	}
	pid->Dout = pid->kd * (pid->error[1] - pid->error[0]); // D
	LIMIT(pid->Dout, -pid->Dmax, pid->Dmax); // limit D
	pid->out = pid->Pout + pid->Iout + pid->Dout; // output
	LIMIT(pid->out, -pid->Omax, pid->Omax); // limit output
	return pid->out;
}

