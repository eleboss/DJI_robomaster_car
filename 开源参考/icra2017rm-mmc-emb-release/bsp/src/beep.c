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
  
#include "beep.h"

const uint16_t BEEP_TONE_TABLE[BEEP_TONE_TABLE_LEN] = BEEP_TONE_TABLE_DEF;
const BeepTone_t BEEP_START_UP_MUSIC[BEEP_START_UP_MUSIC_LEN] = BEEP_START_UP_MUSIC_DEF;

void Beep_Sing(BeepTone_t tone)
{
  if(Silent == tone) {
    BEEP_CCR = 0;
	} else {
    BEEP_ARR = BEEP_TONE_TABLE[tone];
    BEEP_CCR = BEEP_TONE_TABLE[tone] / 2;
  }
}

//play the start up music
void Beep_SingStartupMusic(uint32_t index)
{
  if(index < BEEP_START_UP_MUSIC_LEN)
    Beep_Sing(BEEP_START_UP_MUSIC[index]);
}

void Beep_Config(void)
{
	PWM_Bind(BEEP_PIN, 0, 0, 0,
    	 BEEP_TIM,
			 BEEP_TIM_PS,
			 BEEP_TIM_PD,
			 BEEP_TIM_PW);
  TIM_Cmd(BEEP_TIM, ENABLE);
}

