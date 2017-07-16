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
 
#include "sr04.h"

const SR04_t sr04[SR04_NUM] = SR04_GROUP;

static void SR04_IRQHandler(uint8_t num)
{
	uint8_t i = 0;
	uint32_t tmp = 1u << num;
	uint8_t trigger = 0;
	for (; i < SR04_NUM; i++) {
		if (num == GPIO_PIN_NUM(sr04[i].echoPin)) {
		  // Toggle trigger
			if (EXTI->RTSR & tmp) {
				EXTI->RTSR &= ~tmp;
				EXTI->FTSR |= tmp;
				trigger = 1;
			} else if (EXTI->FTSR & tmp) {
				EXTI->FTSR &= ~tmp;
				EXTI->RTSR |= tmp;
				trigger = 0;
			}
			SR04Callback(i, trigger);
			break; // Jump out
		}
	}
}

void SR04_Bind(const SR04_t* sr04)
{
	GPIO_Out(sr04->trigPin);
	EXTI_Bind(sr04->echoPin, 
	          SR04_NVIC_PRE_PRIORITY, 
	          SR04_NVIC_SUB_PRIORITY, 
	          EXTI_Trigger_Rising, 
	          SR04_IRQHandler
	          );
	
}

void SR04_Config(void)
{
	uint32_t i = 0;
	for (; i < SR04_NUM; i++) {
		SR04_Bind(&sr04[i]);
	}
}

