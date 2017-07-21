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

#include "mpu6500_int.h"

static void MPU6500INTHandler(uint8_t num)
{
	//MPU6500INTCallback();
}

void MPU6500_INT_Config(void)
{
    EXTI_Bind(MPU6500_INT_PIN, MPU6500_NVIC_PRE_PRIORITY, MPU6500_NVIC_SUB_PRIORITY, EXTI_Trigger_Falling, MPU6500INTHandler);
}

