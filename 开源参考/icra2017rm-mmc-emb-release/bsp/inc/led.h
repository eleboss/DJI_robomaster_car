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
 
#ifndef __LED_H__
#define __LED_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "stm32util.h"
#include "hal_gpio.h"
	
#define LED_GREEN_PIN PF14
#define LED_RED_PIN   PE7

#define LED_GREEN_STATE()   GPIO_READ_OUT(LED_GREEN_PIN)
#define LED_GREEN_IS_ON()   (LED_GREEN_STATE() == 0)
#define LED_GREEN_IS_OFF()  (LED_GREEN_STATE() != 0)
#define LED_GREEN_ON()      GPIO_RST(LED_GREEN_PIN)
#define LED_GREEN_OFF()     GPIO_SET(LED_GREEN_PIN)
#define LED_GREEN_TOG()     GPIO_TOG(LED_GREEN_PIN)

#define LED_RED_STATE()     GPIO_READ_OUT(LED_RED_PIN)
#define LED_RED_IS_ON()     (LED_RED_STATE() == 0)
#define LED_RED_IS_OFF()    (LED_RED_STATE() != 0)
#define LED_RED_ON()        GPIO_RST(LED_RED_PIN)
#define LED_RED_OFF()       GPIO_SET(LED_RED_PIN)
#define LED_RED_TOG()       GPIO_TOG(LED_RED_PIN)

void Led_Config(void);

uint8_t LedRed_ReadIn(void);
uint8_t LedRed_ReadOut(void);
void LedRed_Write(uint8_t newState);

uint8_t LedGreen_ReadIn(void);
uint8_t LedGreen_ReadOut(void);
void LedGreen_Write(uint8_t newState);

extern const Hal_Gpio_t ledR;
extern const Hal_Gpio_t ledG;

#ifdef __cplusplus
}
#endif

#endif

