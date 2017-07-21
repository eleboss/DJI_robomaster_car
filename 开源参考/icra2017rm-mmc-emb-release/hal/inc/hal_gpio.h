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

#ifndef __HAL_GPIO_H__
#define __HAL_GPIO_H__

/****************************************************/
/*          Hardware Abstract Layer - GPIO          */
/****************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

typedef struct
{
	uint8_t (*ReadIn)(void);
}Hal_Gpio_ReadOnly_t;

typedef struct
{
	uint8_t (*ReadOut)(void);
	void (*Write)(uint8_t newState);
}Hal_Gpio_WriteOnly_t;

typedef struct
{
	uint8_t (*ReadIn)(void);
	uint8_t (*ReadOut)(void);
	void (*Write)(uint8_t newState);
}Hal_Gpio_t;
	
#define HAL_GPIO_DEF(DEV) \
{ \
	.ReadIn = &DEV##_ReadIn, \
	.ReadOut = &DEV##_ReadOut, \
	.Write = &DEV##_Write, \
}

void Hal_Gpio_ReadOnly_Init(Hal_Gpio_ReadOnly_t* gpio);
void Hal_Gpio_WriteOnly_Init(Hal_Gpio_WriteOnly_t* gpio);
void Hal_Gpio_Init(Hal_Gpio_t* gpio);

#ifdef __cplusplus
}
#endif

#endif


