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
 
#include "snd.h"

static SndState_t state = SND_STATE_STOP;
static uint32_t index = 0;
static uint32_t lastSingTick = 0;

void Snd_Init(void)
{
	state = SND_STATE_STOP;
	index = 0;
}

void Snd_Proc(void)
{
	if (state == SND_STATE_PLAY) {
		if (Clk_GetMsTick() > lastSingTick) {
			Beep_SingStartupMusic(index++);
			if (index >= BEEP_START_UP_MUSIC_LEN) index = 0;
			lastSingTick = Clk_GetMsTick();
		}
	} else {
		Beep_Sing(Silent);
	}
}

void Snd_Play(void)
{
	state = SND_STATE_PLAY;
}

void Snd_Stop(void)
{
	state = SND_STATE_STOP;
}

