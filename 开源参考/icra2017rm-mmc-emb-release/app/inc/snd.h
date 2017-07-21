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

#ifndef __SND_H__
#define __SND_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "bsp.h"
#include "clk.h"

#define SND_PLAY_TMS 100

typedef enum
{
	SND_STATE_STOP = 0x00,
	SND_STATE_PLAY = 0x01,
}SndState_t;

void Snd_Init(void);
void Snd_Proc(void);

void Snd_Play(void);
void Snd_Stop(void);

#ifdef __cplusplus
}
#endif

#endif


