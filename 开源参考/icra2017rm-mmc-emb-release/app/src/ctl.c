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
 
#include "ctl.h"

/**********************************************/
/*              Logic Controller              */
/**********************************************/

Ctl_t ctl;
Pid_t pid;
Rmp_t rmp;

static void RmpGeneraterCtl(void)
{
	Rmp_Calc(&rmp);
}

static void PeriphsStateCtl(void)
{
	FS_Cpy(&ctl.fs, cmd.fs, FS_ALL);
}

static void ChassisStateCtl(void)
{
	ctl.cv.x = PID_Calc(&pid.cp.x, cmd.cp.x, odo.cp.x);
	ctl.cv.y = PID_Calc(&pid.cp.y, cmd.cp.y, odo.cp.y);
	ctl.cv.z = PID_Calc(&pid.cp.z, cmd.cp.z, odo.cp.z);
	ctl.cc.x = PID_Calc(&pid.cv.x, ctl.cv.x, odo.cv.x) * rmp.out;
	ctl.cc.y = PID_Calc(&pid.cv.y, ctl.cv.y, odo.cv.y) * rmp.out;;
	ctl.cc.z = PID_Calc(&pid.cv.z, ctl.cv.z, odo.cv.z) * rmp.out;;
	
	Mec_Decomp((float*)&ctl.cv, (float*)&ctl.mv);
	Mec_Decomp((float*)&ctl.cc, (float*)&ctl.mc);
}

static void GrabberStateCtl(void)
{
	ctl.gv.e = PID_Calc(&pid.gp.e, cmd.gp.e, odo.gp.e);
	ctl.gc.e = PID_Calc(&pid.gv.e, ctl.gv.e, odo.gv.e) * rmp.out;;
	ctl.gc.c = map(cmd.gp.c, cfg.pos.cl, cfg.pos.ch, CLAW_PWM_L, CLAW_PWM_H); // Direct PWM control (1000~2000)/2500, map rad to pwm duty cycle
}

static void Rmp_Init(Rmp_t* rmp)
{
	Rmp_Config(rmp, cfg.rmp.cnt);
	Rmp_Reset(rmp);
}

static void Cpl_Init(PID_t* pid)
{
	PID_Config(pid, 
		 cfg.cpl.kp, 
		 cfg.cpl.ki, 
		 cfg.cpl.kd, 
		 cfg.cpl.it,
		 cfg.cpl.Emax,
		 cfg.cpl.Pmax, 
		 cfg.cpl.Imax, 
		 cfg.cpl.Dmax, 
		 cfg.cpl.Omax);
	PID_Reset(pid);
}

static void Cvl_Init(PID_t* pid)
{
	PID_Config(pid, 
		 cfg.cvl.kp, 
		 cfg.cvl.ki, 
		 cfg.cvl.kd, 
		 cfg.cvl.it,
		 cfg.cvl.Emax,
		 cfg.cvl.Pmax, 
		 cfg.cvl.Imax, 
		 cfg.cvl.Dmax, 
		 cfg.cvl.Omax);
	PID_Reset(pid);
}

static void Gvl_Init(PID_t* pid)
{
	PID_Config(pid, 
		 cfg.gvl.kp, 
		 cfg.gvl.ki, 
		 cfg.gvl.kd, 
		 cfg.gvl.it,
		 cfg.gvl.Emax,
		 cfg.gvl.Pmax, 
		 cfg.gvl.Imax, 
		 cfg.gvl.Dmax, 
		 cfg.gvl.Omax);
	PID_Reset(pid);
}

static void Gpl_Init(PID_t* pid)
{
	PID_Config(pid, 
		 cfg.gpl.kp, 
		 cfg.gpl.ki, 
		 cfg.gpl.kd, 
		 cfg.gpl.it,
		 cfg.gpl.Emax,
		 cfg.gpl.Pmax, 
		 cfg.gpl.Imax, 
		 cfg.gpl.Dmax, 
		 cfg.gpl.Omax);
	PID_Reset(pid);
}

/**********************************************/
/*       Logic Controller Initialization      */
/**********************************************/
void Ctl_Init(void)
{
	Rmp_Init(&rmp);
	
	Cvl_Init(&pid.cv.x);
	Cvl_Init(&pid.cv.y);
	Cvl_Init(&pid.cv.z);
	
	Cpl_Init(&pid.cp.x);
	Cpl_Init(&pid.cp.y);
	Cpl_Init(&pid.cp.z);
	
	Gvl_Init(&pid.gv.e);
	Gpl_Init(&pid.gp.e);
	
	memset(&ctl, 0, sizeof(Ctl_t));
}

/**********************************************/
/*          Logic Controller Process          */
/**********************************************/
void Ctl_Proc(void)
{
	RmpGeneraterCtl();
	PeriphsStateCtl();
	ChassisStateCtl();
	GrabberStateCtl();
}

void Ctl_Zero(void)
{
	Cvl_Init(&pid.cv.x);
	Cvl_Init(&pid.cv.y);
	Cvl_Init(&pid.cv.z);
	
	Cpl_Init(&pid.cp.x);
	Cpl_Init(&pid.cp.y);
	Cpl_Init(&pid.cp.z);
	
	memset(&ctl.cv, 0, sizeof(ChassisState_t));
	memset(&ctl.cc, 0, sizeof(ChassisState_t));
	memset(&ctl.mv, 0, sizeof(MecanumState_t));
	memset(&ctl.mc, 0, sizeof(MecanumState_t));
}

