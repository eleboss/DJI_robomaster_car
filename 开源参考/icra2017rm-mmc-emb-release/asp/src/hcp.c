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

#include "hcp.h"

void Hcp_Enc(const Hcp_t* hcp, uint8_t* buf)
{
	buf[0] = hcp->mouse.x;
	buf[1] = hcp->mouse.x >> 8;
	buf[2] = hcp->mouse.y;
	buf[3] = hcp->mouse.y >> 8;
	buf[4] = hcp->mouse.z;
	buf[5] = hcp->mouse.z >> 8;
	buf[6] = hcp->mouse.b[MOUSE_BTN_IDX_L];
	buf[7] = hcp->mouse.b[MOUSE_BTN_IDX_R];
	buf[8] = hcp->key.val;
	buf[9] = hcp->key.val >> 8;
	buf[10] = hcp->res.val;
	buf[11] = hcp->res.val >> 8;
}

void Hcp_Dec(Hcp_t* hcp, const uint8_t* buf)
{
	hcp->mouse.x = buf[0] | (buf[1] << 8);   //!< Mouse X axis
	hcp->mouse.y = buf[2] | (buf[3] << 8);   //!< Mouse Y axis
	hcp->mouse.z = buf[4] | (buf[5] << 8);   //!< Mouse Z axis
	hcp->mouse.b[MOUSE_BTN_IDX_L] = buf[6];  //!< Mouse Left Is Press ?
	hcp->mouse.b[MOUSE_BTN_IDX_R] = buf[7];  //!< Mouse Right Is Press ?
	hcp->key.val = buf[8] | (buf[9] << 8);   //!< KeyBoard value
	hcp->res.val = buf[10] | (buf[11] << 8); //!< Reserve
}

void Hcp_Init(Hcp_t* hcp)
{

	uint8_t i = 0;
	for (; i < MOUSE_BTN_CNT; i++) {
		hcp->mouse.b[i] = MOUSE_BTN_UP;
	}
	hcp->mouse.x = 0;
	hcp->mouse.y = 0;
	hcp->mouse.z = 0;
	hcp->key.val = 0;
	hcp->res.val = 0;
}

