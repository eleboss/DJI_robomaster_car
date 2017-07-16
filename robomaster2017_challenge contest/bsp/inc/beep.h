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
  
#ifndef __BEEP_H__
#define __BEEP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_gpio.h"

typedef uint32_t GPIO;
	
#define BEEP_PIN GPIO_Pin_4
#define BEEP_TIM TIM3
#define BEEP_TIM_PS 89
#define BEEP_TIM_PD 1
#define BEEP_TIM_PW 0

#define BEEP_ARR BEEP_TIM->ARR
#define BEEP_CCR BEEP_TIM->CCR1

#define BEEP_CCR_H 599
#define BEEP_CCR_L 0
	
#define BEEP_ON() do { BEEP_CCR = BEEP_CCR_H; } while (0)
#define BEEP_OFF() do { BEEP_CCR = BEEP_CCR_L; } while (0)

typedef enum{

  Do1L = 0, ///*261.63Hz*/    3822us
  Re2L,     ///*293.66Hz*/    3405us
  Mi3L,     ///*329.63Hz*/    3034us
  Fa4L,     ///*349.23Hz*/    2863us
  So5L,     ///*392.00Hz*/    2551us
  La6L,     ///*440.00Hz*/    2272us
  Si7L,     ///*493.88Hz*/    2052us

  Do1M,     ///*523.25Hz*/    1911us
  Re2M,     ///*587.33Hz*/    1703us
  Mi3M,     ///*659.26Hz*/    1517us
  Fa4M,     ///*698.46Hz*/    1432us
  So5M,     ///*784.00Hz*/    1276us
  La6M,     ///*880.00Hz*/    1136us
  Si7M,     ///*987.77Hz*/    1012us

  Do1H,     ///*1046.50Hz*/   956us
  Re2H,     ///*1174.66Hz*/   851us
  Mi3H,     ///*1318.51Hz*/   758us
  Fa4H,     ///*1396.91Hz*/   716us
  So5H,     ///*1567.98Hz*/   638us
  La6H,     ///*1760.00Hz*/   568us
  Si7H,     ///*1975.53Hz*/   506us

  Silent,
}BeepTone_t;

//bass 1~7, mid 1~7, treble 1~7
#define BEEP_TONE_TABLE_LEN 21
#define BEEP_TONE_TABLE_DEF \
{ \
  3822,  3405, 3033, 2863, 2551, 2272, 2024, \
  1911,  1702, 1526, 1431, 1275, 1136, 1012, \
  955,   851,  758,  715,   637, 568,   506, \
}

#define BEEP_START_UP_MUSIC_LEN 14
#define BEEP_START_UP_MUSIC_DEF \
{ \
  So5L, So5L, So5L, So5L, La6L, La6L, La6L, La6L, Mi3M, Mi3M, Mi3M, Mi3M, Mi3M, Silent, \
}

#define PWM_BIND(A,B,C,D,TIM,PS,PD,PW) do { \
	uint8_t channel = 0; \
	if (IS_VALID_GPIO(A)) { \
		GPIO_Af(A, GPIO_AF_##TIM); \
		channel |= 0x01; \
	} \
	if (IS_VALID_GPIO(B)) { \
		GPIO_Af(B, GPIO_AF_##TIM); \
		channel |= 0x02; \
	} \
	if (IS_VALID_GPIO(C)) { \
		GPIO_Af(C, GPIO_AF_##TIM); \
		channel |= 0x04; \
	} \
	if (IS_VALID_GPIO(D)) { \
		GPIO_Af(D, GPIO_AF_##TIM); \
		channel |= 0x08; \
	} \
	TIM_Config(TIM, PS, TIM_CounterMode_Up, PD, TIM_CKD_DIV1, 0); \
	TIM_OC_Config(TIM, channel, TIM_OCMode_PWM2, PW); \
	TIM_ARRPreloadConfig(TIM, ENABLE); \
} while(0)



void BEEP_Configuration(void);

void Beep_Sing(BeepTone_t tone);
void Beep_SingStartupMusic(uint32_t index);

extern const uint16_t BEEP_TONE_TABLE[BEEP_TONE_TABLE_LEN];
extern const BeepTone_t BEEP_START_UP_MUSIC[BEEP_START_UP_MUSIC_LEN];


	#ifdef __cplusplus
}
#endif

#endif

