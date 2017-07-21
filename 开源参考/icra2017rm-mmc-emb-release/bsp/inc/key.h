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
 
#ifndef __KEY_H__
#define __KEY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32util.h"

#define KEY_H_PIN PB0
#define KEY_L_PIN PC2
#define KEY_M_PIN PB1
#define KEY_N_PIN PC3
	
#define KEY_H_IS_PRESSED() (GPIO_READ_IN(KEY_H_PIN) == 0)
#define KEY_L_IS_PRESSED() (GPIO_READ_IN(KEY_L_PIN) == 0)
#define KEY_M_IS_PRESSED() (GPIO_READ_IN(KEY_M_PIN) == 0)
#define KEY_N_IS_PRESSED() (GPIO_READ_IN(KEY_N_PIN) == 0)
	
void Key_Config(void);

#ifdef __cplusplus
}
#endif

#endif


