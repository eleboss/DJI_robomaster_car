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

#include "rcp.h"

void Rcp_Enc(const Rcp_t* rcp, uint8_t* buf)
{
	buf[0] = rcp->ch[0] & 0xff;
	buf[1] = (rcp->ch[1] << 3) | (rcp->ch[0] >> 8);
	buf[2] = (rcp->ch[2] << 6) | (rcp->ch[1] >> 5);
	buf[3] = rcp->ch[2];
	buf[4] = (rcp->ch[3] << 1) | (rcp->ch[2] >> 10);
	buf[5] = (rcp->sw[SW_IDX_R] << 6) |
			 (rcp->sw[SW_IDX_L] << 4) |
			 (rcp->ch[3] >> 7);
}

void Rcp_Dec(Rcp_t* rcp, const uint8_t* buf)
{
	rcp->ch[0] = (buf[0] | (buf[1] << 8)) & 0x07ff;         //!< Channel 0
	rcp->ch[1] = ((buf[1] >> 3) | (buf[2] << 5)) & 0x07ff;  //!< Channel 1
	rcp->ch[2] = ((buf[2] >> 6) | (buf[3] << 2) |           //!< Channel 2
		(buf[4] << 10)) & 0x07ff;
	rcp->ch[3] = ((buf[4] >> 1) | (buf[5] << 7)) & 0x07ff;  //!< Channel 3
	rcp->sw[SW_IDX_L] = ((buf[5] >> 4) & 0x000c) >> 2;    //!< Switch left
	rcp->sw[SW_IDX_R] = ((buf[5] >> 4) & 0x0003);         //!< Switch right
}

void Rcp_Init(Rcp_t* rcp)
{
	uint8_t i = 0;
	for (; i < CH_CNT; i++) {
		rcp->ch[i] = CH_MID;
	}
	for (i = 0; i < SW_CNT; i++) {
		rcp->sw[i] = SW_MD;
	}
}

