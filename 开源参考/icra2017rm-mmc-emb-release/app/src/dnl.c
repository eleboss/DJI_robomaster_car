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
 
#include "dnl.h"
#include "upl.h"
#include "cmd.h"
#include "dci.h"
#include "fun.h"

/*****************************************/
/*        Down-Link Communication        */
/*****************************************/

static KylinMsg_t kylinMsg;

static VirtualRC_t vrc;
static VirtualHC_t vhc;
static VirtualDBUS_t vdbus;

static CBUS_t cbus;

/*
SubscMsg_t subscMsg;
CalibMsg_t calibMsg;

PIDCalib_t pidCalib;
IMUCalib_t imuCalib;
MagCalib_t magCalib;
VelCalib_t velCalib;
MecCalib_t mecCalib;
PosCalib_t posCalib;
*/

static uint8_t buf[2][DNL_BUF_SIZE];
static FIFO_t fifo;

static void Dnl_ProcVRC(const VirtualRC_t* vrc)
{
	Wdg_Feed(WDG_IDX_VRC);
	if (Rci_Sw(SW_IDX_R) == SW_DN) {
		Rcp_Dec(&dbus.rcp, vrc->buf);
		Rci_Proc(&dbus.rcp);
	}
}

static void Dnl_ProcVHC(const VirtualHC_t* vhc)
{
	Wdg_Feed(WDG_IDX_VHC);
	if (Rci_Sw(SW_IDX_R) == SW_DN) {
		Hcp_Dec(&dbus.hcp, vhc->buf);
		Hci_Proc(&dbus.hcp);
	}
}

static void Dnl_ProcVDBUS(const VirtualDBUS_t* vdbus)
{
	Wdg_Feed(WDG_IDX_VDBUS);
	// To use this mode, the remote controller must be turned of.
	if (Wdg_HasErr(WDG_ERR_RCV)) {
		DBUS_Dec(&dbus, vdbus->buf);
		Dci_Proc(&dbus);
	}
}

static void Dnl_ProcCBUS(const CBUS_t* vcbus)
{
	Wdg_Feed(WDG_IDX_CBUS);
	if (Rci_Sw(SW_IDX_R) == SW_DN) {
		Cci_Proc(vcbus);
	}
}

/*
static void Dnl_ProcSubscMsg(const SubscMsg_t* subscMsg)
{
	if (subscMsg->msg_type & MSG_TYPE_CALIB) {
	}
}

static void Dnl_ProcCalibMsg(const CalibMsg_t* calibMsg)
{
	Wdg_Feed(WDG_IDX_CALIB);
	if (calibMsg->auto_cali_flag & CALIB_FLAG_BIT_POS) {
		Cal_Init();
	}
}
*/

static void Dnl_ProcKylinMsg(const KylinMsg_t* kylinMsg)
{
	Wdg_Feed(WDG_IDX_KYLIN);
	if (Rci_Sw(1) == SW_DN && Wsm_GetWs() == WORKING_STATE_NORMAL) {
		Cci_Proc(&kylinMsg->cbus);
	}
}


/*
#define DPCT_MAX 3.0f
#define DPCR_MAX 3.0f
#define DPGE_MAX 3.0f
#define DPGC_MAX 3.0f
#define DPCT_KP 10.0f
#define DPCR_KP 10.0f
#define DPGE_KP 10.0f 
#define DPGC_KP 10.0f
static void Dnl_ProcKylinMsg(const KylinMsg_t* kylinMsg)
{
	Wdg_Feed(WDG_IDX_KYLIN);
	if (Rci_Sw(1) == SW_DN && Wsm_GetWs() == WORKING_STATE_NORMAL) {
		float pxr = kylinMsg->cp.x / KYLIN_MSG_VALUE_SCALE;
		float pyr = kylinMsg->cp.y / KYLIN_MSG_VALUE_SCALE;
		float pzr = kylinMsg->cp.z / KYLIN_MSG_VALUE_SCALE;
		float per = kylinMsg->gp.e / KYLIN_MSG_VALUE_SCALE;
		float pcr = kylinMsg->gp.c / KYLIN_MSG_VALUE_SCALE;
		float vxr = kylinMsg->cv.x / KYLIN_MSG_VALUE_SCALE;
		float vyr = kylinMsg->cv.y / KYLIN_MSG_VALUE_SCALE;
		float vzr = kylinMsg->cv.z / KYLIN_MSG_VALUE_SCALE;
		float ver = kylinMsg->gv.e / KYLIN_MSG_VALUE_SCALE;
		float vcr = kylinMsg->gv.c / KYLIN_MSG_VALUE_SCALE;
		
		LIMIT_ABS(vxr, cfg.vel.x);
		LIMIT_ABS(vyr, cfg.vel.y);
		LIMIT_ABS(vzr, cfg.vel.z);
		LIMIT_ABS(ver, cfg.vel.e);
		LIMIT_ABS(vcr, cfg.vel.c);
		
		float dpx = (pxr - odo.cp.x) * DPCT_KP;
		float dpy = (pyr - odo.cp.y) * DPCT_KP;
		float dpz = (pzr - odo.cp.z) * DPCR_KP;
		float dpe = (per - odo.gp.e) * DPGE_KP;
		float dpc = (pcr - odo.gp.c) * DPGC_KP;
		
		LIMIT_ABS(dpx, DPCT_MAX);
		LIMIT_ABS(dpy, DPCT_MAX);
		LIMIT_ABS(dpz, DPCR_MAX);
		LIMIT_ABS(dpe, DPGE_MAX);
		LIMIT_ABS(dpc, DPGC_MAX);
		
		float vxc = map(dpx, -DPCT_MAX, DPCT_MAX, -1, 1);
		float vyc = map(dpy, -DPCT_MAX, DPCT_MAX, -1, 1);
		float vzc = map(dpz, -DPCR_MAX, DPCR_MAX, -1, 1);
		float vec = map(dpe, -DPGE_MAX, DPGE_MAX, -1, 1);
		float vcc = map(dpc, -DPGC_MAX, DPGC_MAX, -1, 1);
		
		cmd.cv.x = vxc * vxr;
		cmd.cv.y = vyc * vyr;
		cmd.cv.z = vzc * vzr;
		cmd.gv.e = vec * ver;
		cmd.gv.c = vcc * vcr;
		
		//cmd.cv.x = kylinMsg->cv.x / KYLIN_MSG_VALUE_SCALE;
		LIMIT(cmd.cv.x, -cfg.vel.x, cfg.vel.x);
		cmd.cp.x += cmd.cv.x * SYS_CTL_TSC;
		
		//cmd.cv.y = kylinMsg->cv.y / KYLIN_MSG_VALUE_SCALE;
		LIMIT(cmd.cv.y, -cfg.vel.y, cfg.vel.y);
		cmd.cp.y += cmd.cv.y * SYS_CTL_TSC;
		
		//cmd.cv.z = kylinMsg->cv.z / KYLIN_MSG_VALUE_SCALE;
		LIMIT(cmd.cv.z, -cfg.vel.z, cfg.vel.z);
		cmd.cp.z += cmd.cv.z * SYS_CTL_TSC;
		
		//cmd.gv.e = kylinMsg->gv.e / KYLIN_MSG_VALUE_SCALE;
		LIMIT(cmd.gv.e, -cfg.vel.e, cfg.vel.e);
		cmd.gp.e += cmd.gv.e * SYS_CTL_TSC;
		LIMIT(cmd.gp.e, cfg.pos.el, cfg.pos.eh);
		
		//cmd.gv.c = kylinMsg->gv.c / KYLIN_MSG_VALUE_SCALE;
		LIMIT(cmd.gv.c, -cfg.vel.c, cfg.vel.c);
		cmd.gp.c += cmd.gv.c * SYS_CTL_TSC;
		LIMIT(cmd.gp.c, cfg.pos.cl, cfg.pos.ch);
	}
}
*/

/*
static void Dnl_ProcIMUCalib(const IMUCalib_t* IMUCalib)
{
	Calib_SetIMU(&cfg.imu, IMUCalib);
	Cfg_SetFlag(CFG_FLAG_IMU);
	cfg_sync_flag = 1;
}

static void Dnl_ProcMagCalib(const MagCalib_t* MagCalib)
{
	Calib_SetMag(&cfg.mag, MagCalib);
	Cfg_SetFlag(CFG_FLAG_MAG);
	cfg_sync_flag = 1;
}

static void Dnl_ProcVelCalib(const VelCalib_t* VelCalib)
{
	Calib_SetVel(&cfg.vel, VelCalib);
	Cfg_SetFlag(CFG_FLAG_VEL);
	cfg_sync_flag = 1;
}

static void Dnl_ProcMecCalib(const MecCalib_t* MecCalib)
{
	Calib_SetMec(&cfg.mec, MecCalib);
	Cfg_SetFlag(CFG_FLAG_MEC);
	cfg_sync_flag = 1;
}

static void Dnl_ProcPosCalib(const PosCalib_t* PosCalib)
{
	Calib_SetPos(&cfg.pos, PosCalib);
	Cfg_SetFlag(CFG_FLAG_POS);
	cfg_sync_flag = 1;
}

static void Dnl_ProcPIDCalib(const PIDCalib_t* PIDCalib)
{
	if (PIDCalib->type == PID_CALIB_TYPE_CHASSIS_VELOCITY) {
		Calib_SetPID(&cfg.cvl, PIDCalib);
		Cfg_SetFlag(CFG_FLAG_CVL);
		cfg_sync_flag = 1;
	}
	else if (PIDCalib->type == PID_CALIB_TYPE_GRABBER_VELOCITY) {
		Calib_SetPID(&cfg.gvl, PIDCalib);
		Cfg_SetFlag(CFG_FLAG_GVL);
		cfg_sync_flag = 1;
	}
	else if (PIDCalib->type == PID_CALIB_TYPE_GRABBER_POSITION) {
		Calib_SetPID(&cfg.gpl, PIDCalib);
		Cfg_SetFlag(CFG_FLAG_GPL);
		cfg_sync_flag = 1;
	}
}
*/

void Dnl_Init(void)
{
	FIFO_Init(&fifo, buf[0], DNL_BUF_SIZE);
	//DBUS_Init(&dbus);
	CBUS_Init(&cbus);
}

void Dnl_Proc(void)
{
	// Get fifo free space
	int len = FIFO_GetFree(&fifo);
	// If fifo free space insufficient, pop one element out
	if (len < 1) {
		uint8_t b;
		len = FIFO_Pop(&fifo, &b, 1);
	}
	// Read input stream according to the fifo free space left
	len = IOS_COM_DEV.Read(buf[1], len);
	// If input stream not available, abort
	if (len > 0) {
		// Push stream into fifo
		FIFO_Push(&fifo, buf[1], len);
	}
	// Check if any message received
	if (Msg_Pop(&fifo, buf[1], &msg_head_kylin, &kylinMsg)) {
		Dnl_ProcKylinMsg(&kylinMsg);
	}
	if (Msg_Pop(&fifo, buf[1], &msg_head_vrc, &vrc)) {
		Dnl_ProcVRC(&vrc);
	}
	if (Msg_Pop(&fifo, buf[1], &msg_head_vhc, &vhc)) {
		Dnl_ProcVHC(&vhc);
	}
	if (Msg_Pop(&fifo, buf[1], &msg_head_vdbus, &vdbus)) {
		Dnl_ProcVDBUS(&vdbus);
	}
	if (Msg_Pop(&fifo, buf[1], &msg_head_vcbus, &cbus)) {
		Dnl_ProcCBUS(&cbus);
	}
	/*
	else if (Msg_Pop(&fifo, buf[1], &msg_head_subsc, &subscMsg)) {
		Dnl_ProcSubscMsg(&subscMsg);
	} else if (Msg_Pop(&fifo, buf[1], &msg_head_calib, &calibMsg)) {
		Dnl_ProcCalibMsg(&calibMsg);
	} else if (Msg_Pop(&fifo, buf[1], &msg_head_kylin, &kylinMsg)) {
		Dnl_ProcKylinMsg(&kylinMsg);
		//LED_GREEN_TOG();
	} else if (Msg_Pop(&fifo, buf[1], &msg_head_pid_calib, &pidCalib)) {
		Dnl_ProcPIDCalib(&pidCalib);
	} else if (Msg_Pop(&fifo, buf[1], &msg_head_imu_calib, &imuCalib)) {
		Dnl_ProcIMUCalib(&imuCalib);
	} else if (Msg_Pop(&fifo, buf[1], &msg_head_mag_calib, &magCalib)) {
		Dnl_ProcMagCalib(&magCalib);
	} else if (Msg_Pop(&fifo, buf[1], &msg_head_vel_calib, &velCalib)) {
		Dnl_ProcVelCalib(&velCalib);
	} else if (Msg_Pop(&fifo, buf[1], &msg_head_mec_calib, &mecCalib)) {
		Dnl_ProcMecCalib(&mecCalib);
	} else if (Msg_Pop(&fifo, buf[1], &msg_head_pos_calib, &posCalib)) {
		Dnl_ProcPosCalib(&posCalib);
	} else {
	}
	*/
}




