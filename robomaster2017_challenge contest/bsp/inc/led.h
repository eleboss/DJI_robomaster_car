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
	
#define LED_GREEN_PIN						GPIO_Pin_7
#define LED_RED_PIN							GPIO_Pin_14

#define LED_GREEN_GPIO					GPIOE
#define LED_RED_GPIO						GPIOF

#define LED_GREEN_OFF()  GPIO_SetBits(LED_GREEN_GPIO,LED_GREEN_PIN)
#define LED_GREEN_ON()   GPIO_ResetBits(LED_GREEN_GPIO,LED_GREEN_PIN)
#define LED_GREEN_TOGGLE()  LED_GREEN_GPIO->ODR ^= LED_GREEN_PIN

#define LED_RED_OFF()  GPIO_SetBits(LED_RED_GPIO,LED_RED_PIN)
#define LED_RED_ON()   GPIO_ResetBits(LED_RED_GPIO,LED_RED_PIN)
#define LED_RED_TOGGLE()  LED_RED_GPIO->ODR ^= LED_RED_PIN

void LED_Configuration(void);
#ifdef __cplusplus
}
#endif

#endif

