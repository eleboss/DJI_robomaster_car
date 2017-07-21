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
 
#include "msg.h"

const MsgHead_t msg_head_vrc = MSG_HEAD_VRC;
const MsgHead_t msg_head_vhc = MSG_HEAD_VHC;
const MsgHead_t msg_head_vdbus = MSG_HEAD_VDBUS;
const MsgHead_t msg_head_vcbus = MSG_HEAD_CBUS;
const MsgHead_t msg_head_zgyro = MSG_HEAD_ZGYRO;
const MsgHead_t msg_head_imu9x = MSG_HEAD_IMU9X;
const MsgHead_t msg_head_motor = MSG_HEAD_MOTOR;
const MsgHead_t msg_head_odome = MSG_HEAD_ODOME;
const MsgHead_t msg_head_grasp = MSG_HEAD_GRASP;
const MsgHead_t msg_head_statu = MSG_HEAD_STATU;
const MsgHead_t msg_head_subsc = MSG_HEAD_SUBSC;
const MsgHead_t msg_head_calib = MSG_HEAD_CALIB;
const MsgHead_t msg_head_kylin = MSG_HEAD_KYLIN;
const MsgHead_t msg_head_pid_calib = MSG_HEAD_PID_CALIB;
const MsgHead_t msg_head_imu_calib = MSG_HEAD_IMU_CALIB;
const MsgHead_t msg_head_mag_calib = MSG_HEAD_MAG_CALIB;
const MsgHead_t msg_head_vel_calib = MSG_HEAD_VEL_CALIB;
const MsgHead_t msg_head_mec_calib = MSG_HEAD_MEC_CALIB;
const MsgHead_t msg_head_pos_calib = MSG_HEAD_POS_CALIB;
const MsgHead_t msg_head_sr04s = MSG_HEAD_SR04S;

/**
 * @brief Push a single message to message buffer. 
 * @param fifo Message fifo
 * @param buf Message buffer
 * @param head Message head
 * @param body Message body
 * @return Message length (num of bytes)
 */
uint32_t Msg_Push(FIFO_t* fifo, void* buf, const void* head, const void* body)
{
	const MsgHead_t* phead = (MsgHead_t*)head;
	uint32_t len = phead->attr.length + MSG_LEN_EXT;
	if (FIFO_GetFree(fifo) < len) {
		return 0;
	} else {
		len = 0;
		memcpy(buf, head, sizeof(MsgHead_t));
		len += sizeof(MsgHead_t);
		memcpy((uint8_t*)buf + len, body, phead->attr.length);
		len += phead->attr.length;
		CRC16Append(buf, len + 2, phead->attr.token);
		len += 2;
		FIFO_Push(fifo, buf, len);
		return len;
	}
}

/**
 * @brief: Pop a single message from message buffer. 
 * @param fifo Message fifo
 * @param buf Message buffer
 * @param head Message head
 * @param body Message body
 * @param Message length (num of bytes)
 */
uint32_t Msg_Pop(FIFO_t* fifo, void* buf, const void* head, void* body)
{
	const MsgHead_t* phead = (MsgHead_t*)head;
	uint32_t len = phead->attr.length + MSG_LEN_EXT;
	if (FIFO_GetUsed(fifo) < len) {
		return 0;
	} else {
		MsgHead_t mhead;
		FIFO_Peek(fifo, (uint8_t*)&mhead, sizeof(MsgHead_t));
		if (mhead.attr.id != phead->attr.id) {
			return 0;
		} else if (mhead.attr.length != phead->attr.length) {
			return 0;
		} else if (mhead.attr.token != phead->attr.token) {
			return 0;
		} else {
			FIFO_Peek(fifo, buf, len);
			if (CRC16Check(buf, len, phead->attr.token)) {
				memcpy(body, (uint8_t*)buf + sizeof(MsgHead_t), phead->attr.length);
				FIFO_Pop(fifo, buf, len);
				return len;
			} else {
				return 0;
			}
		}
	}
}

