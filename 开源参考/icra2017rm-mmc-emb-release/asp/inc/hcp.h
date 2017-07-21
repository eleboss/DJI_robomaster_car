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

#ifndef __HCP_H__
#define __HCP_H__

#include <stdint.h>

#define HCP_FRAME_LEN 12

/* ----------------------- PC Mouse Value Definition------------------------------ */
#define MOUSE_SPEED_MAX		       ((int16_t)100    ) // Modified @ 32768
#define MOUSE_BTN_UP         	   ((uint8_t)0      )
#define MOUSE_BTN_DN             ((uint8_t)1      )
/* ----------------------- PC Key Value Definition-------------------------------- */
#define KEY_W         			     ((uint8_t)0x01<<0)
#define KEY_S         			 		 ((uint8_t)0x01<<1)
#define KEY_A         			     ((uint8_t)0x01<<2)
#define KEY_D         			     ((uint8_t)0x01<<3)
#define KEY_SHIFT     		       ((uint8_t)0x01<<4)
#define KEY_CTRL      		       ((uint8_t)0x01<<5)
#define KEY_Q         		       ((uint8_t)0x01<<6)
#define KEY_E         			     ((uint8_t)0x01<<7)

#define KEY_UP   0
#define KEY_DOWN 1

#define MOUSE_BTN_CNT   2
#define MOUSE_BTN_IDX_L 0
#define MOUSE_BTN_IDX_R 1

typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
	uint8_t b[MOUSE_BTN_CNT];
}Mouse_t; // Mouse control domain

typedef union
{
	uint16_t val;
	struct
	{
		uint8_t W : 1;
		uint8_t S : 1;
		uint8_t A : 1;
		uint8_t D : 1;
		uint8_t Shift : 1;
		uint8_t Ctrl : 1;
		uint8_t Q : 1;
		uint8_t E : 1;
	}press;
}Key_t; // Key control domain

typedef struct
{
	uint16_t val;
}Res_t; // Reserved control bits

typedef struct
{
	Mouse_t mouse;
	Key_t key;
	Res_t res;
}Hcp_t; // Host control protocol frame structure

void Hcp_Enc(const Hcp_t* hcp, uint8_t* buf);
void Hcp_Dec(Hcp_t* hcp, const uint8_t* buf);
void Hcp_Init(Hcp_t* hcp);

#endif

