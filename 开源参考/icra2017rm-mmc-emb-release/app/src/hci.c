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
 
#include "hci.h"

/********************************************/
/*          Host Control Interface          */
/********************************************/

#define MAF_NUM 4

static Hcf_t hcf;
static Maf_t maf[MAF_NUM];
static float buf[MAF_NUM][HCI_KEY_CTL_MAF_LEN];

static void GetPeriphsStateRef(const Hcp_t* hcp)
{
}

static void GetChassisStateRef(const Hcp_t* hcp)
{
	float sx = hcp->key.press.Shift ? cfg.vel.x : cfg.vel.x / 2.f;
	float sy = hcp->key.press.Shift ? cfg.vel.y : cfg.vel.y / 2.f;
	float sz = hcp->key.press.Shift ? cfg.vel.z : cfg.vel.z / 2.f;
	float vx = hcp->key.press.A ? -sx : hcp->key.press.D ? sx : 0;
	float vy = hcp->key.press.S ? -sy : hcp->key.press.W ? sy : 0;
	float mx = constrain(hcp->mouse.x, -MOUSE_SPEED_MAX, MOUSE_SPEED_MAX);
	float vz = map(mx, -MOUSE_SPEED_MAX, MOUSE_SPEED_MAX, -sz, sz);
	cmd.cv.x = Maf_Proc(&maf[0], vx);
	cmd.cv.y = Maf_Proc(&maf[1], vy);
	cmd.cv.z = Maf_Proc(&maf[2], vz);
}

static void GetGrabberStateRef(const Hcp_t* hcp)
{
	float se = hcp->key.press.Shift ? cfg.vel.e : cfg.vel.e / 2.f;
	float ve = hcp->key.press.Q ? -se : hcp->key.press.E ? se : 0; // m/s
	cmd.gv.e = Maf_Proc(&maf[3], ve);
	cmd.gp.e += cmd.gv.e * SYS_CTL_TSC; // Integral velocity to get position, unit: m
	LIMIT(cmd.gp.e, cfg.pos.el, cfg.pos.eh); // Constrain elevator position
	cmd.gv.c = Hci_MouseBtn(MOUSE_BTN_IDX_L) == MOUSE_BTN_DN ? cfg.vel.c : Hci_MouseBtn(MOUSE_BTN_IDX_R) == MOUSE_BTN_DN ? -cfg.vel.c : 0; // rad/s
	cmd.gp.c += cmd.gv.c * SYS_CTL_TSC; // Integral velocity to get position, unit: rad
	LIMIT(cmd.gp.c, cfg.pos.cl, cfg.pos.ch); // Constrain grabber position
}

void Hci_PreProc(const Hcp_t* hcp)
{
	Hcf_Proc(&hcf, hcp);
}

uint8_t Hci_MouseBtn(uint8_t i)
{
	return hcf.b[i][2];
}

void Hci_Init(void)
{
	uint32_t i = 0;
	for (; i < MAF_NUM; i++) {
		Maf_Init(&maf[i], buf[i], HCI_KEY_CTL_MAF_LEN);
	}
	Hcf_Init(&hcf);
}

void Hci_Proc(const Hcp_t* hcp)
{
	Hci_PreProc(hcp);
	
	GetPeriphsStateRef(hcp);
	GetChassisStateRef(hcp);
	GetGrabberStateRef(hcp);
}


