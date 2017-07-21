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
 
#ifndef __PWM_H__
#define __PWM_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "stm32util.h"

#define CLAW_PWM_PIN_1 PD12
#define CLAW_PWM_PIN_2 PD13
#define CLAW_PWM_PIN_3 PD14
#define CLAW_PWM_PIN_4 PD15

#define CLAW_PWM_TIM TIM4
#define CLAW_PWM_TIM_PS 89
#define CLAW_PWM_TIM_PD 2500
#define CLAW_PWM_TIM_PW 1000

#define CLAW_PWM_1 CLAW_PWM_TIM->CCR1
#define CLAW_PWM_2 CLAW_PWM_TIM->CCR2
#define CLAW_PWM_3 CLAW_PWM_TIM->CCR3
#define CLAW_PWM_4 CLAW_PWM_TIM->CCR4

#define CLAW_PWM CLAW_PWM_1
	
#define CLAW_PWM_H 1700
#define CLAW_PWM_L 1000

#define CLAW_GET_PWM() CLAW_PWM
#define CLAW_SET_PWM(PWM) do { CLAW_PWM_1 = CLAW_PWM_2 = CLAW_PWM_3 = CLAW_PWM_4 = PWM; } while(0)
#define CLAW_OPEN()     CLAW_SET_PWM(CLAW_PWM_H)
#define CLAW_CLOSE()    CLAW_SET_PWM(CLAW_PWM_L)
#define CLAW_IS_OPEN()  (CLAW_PWM_1==CLAW_PWM_H)
#define CLAW_IS_CLOSE() (CLAW_PWM_1==CLAW_PWM_L)
#define CLAW_TOG()      do { if(CLAW_IS_OPEN()) CLAW_CLOSE(); else CLAW_OPEN(); } while(0)

#define GP_CMD(PWM) CLAW_SET_PWM(PWM)

void Pwm_Config(void);

#ifdef __cplusplus
}
#endif

#endif

