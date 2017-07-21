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
 
#include "upl.h"

/*****************************************/
/*         Up-Link Communication         */
/*****************************************/

static uint8_t buf[2][UPL_BUF_SIZE];
static FIFO_t fifo;

static MsgType_t msgType = MSG_TYPE_KYLIN;

static KylinMsg_t kylinMsg;
static Sr04sMsg_t sr04sMsg;
static ZGyroMsg_t zgyroMsg;
static PosCalibMsg_t posCalibMsg;
static VirtualRC_t virtualRC;

static void Upl_PushKylinMsg(void)
{
	kylinMsg.frame_id++;
	kylinMsg.cbus.fs = odo.fs;
	//Flag_Det(&kylinMsg.cbus.fs, MYLIN_MSG_FLAG_BIT_INI, Cal_IsDone());
	//Flag_Cpy(&kylinMsg.cbus.fs, WDG_ERR_ALL, 0x000fffff);
	kylinMsg.cbus.cv.x = odo.cv.x * KYLIN_MSG_VALUE_SCALE;
	kylinMsg.cbus.cv.y = odo.cv.y * KYLIN_MSG_VALUE_SCALE;
	kylinMsg.cbus.cv.z = odo.cv.z * KYLIN_MSG_VALUE_SCALE;
	kylinMsg.cbus.cp.x = odo.cp.x * KYLIN_MSG_VALUE_SCALE;
	kylinMsg.cbus.cp.y = odo.cp.y * KYLIN_MSG_VALUE_SCALE;
	kylinMsg.cbus.cp.z = odo.cp.z * KYLIN_MSG_VALUE_SCALE;
	kylinMsg.cbus.gv.e = odo.gv.e * KYLIN_MSG_VALUE_SCALE;
	kylinMsg.cbus.gp.e = odo.gp.e * KYLIN_MSG_VALUE_SCALE;
	kylinMsg.cbus.gv.c = odo.gv.c * KYLIN_MSG_VALUE_SCALE;
	kylinMsg.cbus.gp.c = odo.gp.c * KYLIN_MSG_VALUE_SCALE;
	Msg_Push(&fifo, buf[1], &msg_head_kylin, &kylinMsg);
}

static void Upl_PushSr04sMsg(void)
{
	sr04sMsg.frame_id++;
	sr04sMsg.fixed = srs[SR04_IDX_FIXED].mm_filtered;
	sr04sMsg.moble = srs[SR04_IDX_MOBLE].mm_filtered;
	sr04sMsg.left = srs[SR04_IDX_LEFT].mm_filtered;
	sr04sMsg.right = srs[SR04_IDX_RIGHT].mm_filtered;
	Msg_Push(&fifo, buf[1], &msg_head_sr04s, &sr04sMsg);
}

static void Upl_PushZGyroMsg(void)
{
	zgyroMsg.frame_id++;
	zgyroMsg.angle = zgyro.angle;
	zgyroMsg.rate = zgyro.rate;
	Msg_Push(&fifo, buf[1], &msg_head_zgyro, &zgyroMsg);
}

static void Upl_PushPosCalib(void)
{
	posCalibMsg.frame_id++;
	posCalibMsg.data.ch = map(CLAW_PWM_H, 1000, 2000, 0, PI) * POS_CALIB_VALUE_SCALE;
	posCalibMsg.data.cl = map(CLAW_PWM_L, 1000, 2000, 0, PI) * POS_CALIB_VALUE_SCALE;
	posCalibMsg.data.eh = cfg.pos.eh * POS_CALIB_VALUE_SCALE;
	posCalibMsg.data.el = cfg.pos.el * POS_CALIB_VALUE_SCALE;
	Msg_Push(&fifo, buf[1], &msg_head_pos_calib, &posCalibMsg);
}

static void Upl_PushVirtualRC(void)
{
	virtualRC.frame_id++;
	Rcp_Enc(&dbus.rcp, virtualRC.buf);
	Msg_Push(&fifo, buf[1], &msg_head_vrc, &virtualRC);
}

static void Upl_SendMsg(void)
{
	uint8_t data;
	while (!FIFO_IsEmpty(&fifo)) {
		FIFO_Pop(&fifo, &data, 1);
		IOS_COM_DEV.WriteByte(data);
	}
}

void Upl_Init(void)
{
	FIFO_Init(&fifo, buf[0], UPL_BUF_SIZE);
}

void Upl_Proc(void)
{
	switch (msgType) {
		case MSG_TYPE_KYLIN:
			if (IOS_COM_DEV.GetTxFifoFree() >= msg_head_kylin.attr.length + MSG_LEN_EXT) {
				Upl_PushKylinMsg();
				Upl_SendMsg();
				msgType = MSG_TYPE_SR04S;
			}
			break;
		case MSG_TYPE_SR04S:
			if (IOS_COM_DEV.GetTxFifoFree() >= msg_head_sr04s.attr.length + MSG_LEN_EXT) {
				Upl_PushSr04sMsg();
				Upl_SendMsg();
				msgType = MSG_TYPE_ZGYRO;
			}
			break;
		case MSG_TYPE_ZGYRO:
			if (IOS_COM_DEV.GetTxFifoFree() >= msg_head_zgyro.attr.length + MSG_LEN_EXT) {
				Upl_PushZGyroMsg();
				Upl_SendMsg();
				msgType = MSG_TYPE_POS_CALIB;
			}
			break;
		case MSG_TYPE_POS_CALIB:
			if (IOS_COM_DEV.GetTxFifoFree() >= msg_head_pos_calib.attr.length + MSG_LEN_EXT) {
				Upl_PushPosCalib();
				Upl_SendMsg();
				msgType = MSG_TYPE_VRC;
			}
			break;
		case MSG_TYPE_VRC:
			if (IOS_COM_DEV.GetTxFifoFree() >= msg_head_vrc.attr.length + MSG_LEN_EXT) {
				Upl_PushVirtualRC();
				Upl_SendMsg();
				msgType = MSG_TYPE_KYLIN;
			}
			break;
		default:
			msgType = MSG_TYPE_KYLIN;
		break;
	}
}


