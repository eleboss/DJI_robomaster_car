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
 
#include "rci.h"

/**********************************************/
/*          Remote Control Interface          */
/**********************************************/

static Rcf_t rcf;

static void GetPeriphsStateRef(const Rcp_t* rcp)
{
	
}

static void GetChassisStateRef(const Rcp_t* rcp)
{
	cmd.cv.x = map(rcp->ch[0], CH_MIN, CH_MAX, -cfg.vel.x, cfg.vel.x); // m/s
	cmd.cp.x += cmd.cv.x * SYS_CTL_TSC;
	cmd.cv.y = map(rcp->ch[1], CH_MIN, CH_MAX, -cfg.vel.y, cfg.vel.y); // m/s
	cmd.cp.y += cmd.cv.y * SYS_CTL_TSC;
	cmd.cv.z = map(rcp->ch[2], CH_MIN, CH_MAX, -cfg.vel.z, cfg.vel.z); // rad/s
	cmd.cp.z += cmd.cv.z * SYS_CTL_TSC;
}

static void GetGrabberStateRef(const Rcp_t* rcp)
{
	cmd.gv.e = map(rcp->ch[3], CH_MIN, CH_MAX, -cfg.vel.e, cfg.vel.e); // m/s
	cmd.gp.e -= cmd.gv.e * SYS_CTL_TSC; // Integral velocity to get position, unit: m
	LIMIT(cmd.gp.e, cfg.pos.el, cfg.pos.eh); // Constrain elevator position
	cmd.gv.c = Rci_Sw(SW_IDX_L) == SW_UP ? cfg.vel.c : Rci_Sw(SW_IDX_L) == SW_DN ? -cfg.vel.c : 0; // rad/s
	cmd.gp.c += cmd.gv.c * SYS_CTL_TSC; // Integral velocity to get position, unit: rad
	LIMIT(cmd.gp.c, cfg.pos.cl, cfg.pos.ch); // Constrain grabber position
}

void Rci_Init(void)
{
	Rcf_Init(&rcf);
}

void Rci_PreProc(const Rcp_t* rcp)
{
	Rcf_Proc(&rcf, rcp);
}

uint8_t Rci_Sw(uint8_t i)
{
	return rcf.sw[i][2];
}

uint8_t Rci_LastSw(uint8_t i)
{
	return rcf.sw[i][1];
}

void Rci_Proc(const Rcp_t* rcp)
{
	GetPeriphsStateRef(rcp);
	GetChassisStateRef(rcp);
	GetGrabberStateRef(rcp);
}

