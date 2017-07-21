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
 
#include "odo.h"

/**********************************************/
/*                  Odometer                  */
/**********************************************/

Odo_t odo;

static void GetFunctionalStateFdb(void)
{
	FS_Det(&odo.fs, FS_KEY_H, KEY_H_IS_PRESSED());
	FS_Det(&odo.fs, FS_KEY_L, KEY_L_IS_PRESSED());
	FS_Det(&odo.fs, FS_KEY_M, KEY_M_IS_PRESSED());
	FS_Det(&odo.fs, FS_KEY_N, KEY_N_IS_PRESSED());
	FS_Det(&odo.fs, FS_LED_RED, LED_RED_IS_ON());
	FS_Det(&odo.fs, FS_LED_GREEN, LED_GREEN_IS_ON());
}

static void GetMecanumPositionFdb(void)
{
	odo.mp.w1 = motor[0].angle_rad;
	odo.mp.w2 = motor[1].angle_rad;
	odo.mp.w3 = motor[2].angle_rad;
	odo.mp.w4 = motor[3].angle_rad;
}

static void GetMecanumVelocityFdb(void)
{
	odo.mv.w1 = motor[0].rate_rad;
	odo.mv.w2 = motor[1].rate_rad;
	odo.mv.w3 = motor[2].rate_rad;
	odo.mv.w4 = motor[3].rate_rad;
}

static void GetMecanumCurrentsFdb(void)
{
	odo.mc.w1 = motor[0].current_ref;
	odo.mc.w2 = motor[1].current_ref;
	odo.mc.w3 = motor[2].current_ref;
	odo.mc.w4 = motor[3].current_ref;
}

static void GetChassisPositionFdb(void)
{
	Mec_Synthe((float*)&odo.mp, (float*)&odo.cp);
	//odo.cp.z = zgyro.angle_rad;
}

static void GetChassisVelocityFdb(void)
{
	Mec_Synthe((float*)&odo.mv, (float*)&odo.cv);
	//odo.cv.z = zgyro.rate_rad;
}

static float odo_gp_c = 0;
static void GetGrabberPositionFdb(void)
{
	odo.gp.e = motor[5].angle_rad * SCREW_PITCH_RECIP;
	odo_gp_c = odo.gp.c; // 
	odo.gp.c = map(CLAW_GET_PWM(), 1000, 2000, 0, PI);
}

static void GetGrabberVelocityFdb(void)
{
	odo.gv.e = motor[5].rate_rad * SCREW_PITCH_RECIP;
	odo.gv.c = (odo.gp.c - odo_gp_c) / SYS_CTL_TSC; // 
}

static void GetGrabberCurrentsFdb(void)
{
	odo.gc.e = motor[5].current_ref;
	odo.gc.c = odo.gv.c * odo.gv.c; // 
}

void Odo_Init(void)
{
	odo_gp_c = 0;
	memset((void*)&odo, 0, sizeof(Odo_t));
}

void Odo_Proc(void)
{
	GetFunctionalStateFdb();
	GetMecanumPositionFdb();
	GetMecanumVelocityFdb();
	GetMecanumCurrentsFdb();
	GetChassisPositionFdb();
	GetChassisVelocityFdb();
	GetGrabberPositionFdb();
	GetGrabberVelocityFdb();
	GetGrabberCurrentsFdb();
}

void Odo_Zero(void)
{
	Can_Zero();
	
	memset(&odo.cp, 0, sizeof(ChassisState_t));
	memset(&odo.cv, 0, sizeof(ChassisState_t));
	memset(&odo.mp, 0, sizeof(MecanumState_t));
	memset(&odo.mv, 0, sizeof(MecanumState_t));
	memset(&odo.mc, 0, sizeof(MecanumState_t));
}

