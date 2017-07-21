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
 
#include "led.h"

const Hal_Gpio_t ledR = HAL_GPIO_DEF(LedRed);
const Hal_Gpio_t ledG = HAL_GPIO_DEF(LedGreen);

void Led_Config(void)
{
    GPIO_Out(LED_GREEN_PIN);
    GPIO_Out(LED_RED_PIN);

    LED_GREEN_OFF();
    LED_RED_OFF();
}

uint8_t LedRed_ReadIn(void)
{
	return GPIO_READ_IN(LED_RED_PIN);
}

uint8_t LedRed_ReadOut(void)
{
	return GPIO_READ_OUT(LED_RED_PIN);
}

void LedRed_Write(uint8_t newState)
{
	GPIO_WRITE(LED_RED_PIN, newState);
}

uint8_t LedGreen_ReadIn(void)
{
	return GPIO_READ_IN(LED_GREEN_PIN);
}

uint8_t LedGreen_ReadOut(void)
{
	return GPIO_READ_OUT(LED_GREEN_PIN);
}

void LedGreen_Write(uint8_t newState)
{
	GPIO_WRITE(LED_GREEN_PIN, newState);
}

