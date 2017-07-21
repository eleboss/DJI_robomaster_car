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
 
#include "main.h"

//uint32_t frame_cnt = 0;

int main()
{
	// Boot KOS
	KOS_Boot();
	
	// Play startup music
	Snd_Play();
	// Wait for startup music
	Delay_Ms(1000);
	// Stop startup music
	Snd_Stop();
	
	while(1)
	{
//		Srs_Proc();
//		Dnl_Proc();
//		if (Clk_GetUsTick() % 2000 == 0) {
//			Upl_Proc();
//		}
		CM_Cmd(CAN1,0,1000,0,1000);
		/*
		if (Clk_GetUsTick() % 5000 == 0) {
			uint8_t data = 0;
			uint8_t flag = MPU6500_SPI_Read_Reg(MPU6500_WHO_AM_I, &data);
			if (flag) {
				LED_GREEN_ON();
			} else {
				LED_GREEN_OFF();
			}
			printf("flag=%x, data=%x\n", flag, data);
			
		}
		*/
  }
}
