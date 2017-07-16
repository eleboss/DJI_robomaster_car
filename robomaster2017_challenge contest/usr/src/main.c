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

Speed SpeedSet;
float SpeedSend[4];



int main()
{
	CAN1_Configuration();
	LED_Configuration();
  LED_GREEN_ON();
	LED_RED_ON();

	
	//Delay_Ms(1000);
	while(1)
	{
		MECANUM_MOVE(&SpeedSet,0,0,-1000);
		SpeedSend[0] = SpeedSet.RightSpeed_1;
		SpeedSend[1] = SpeedSet.LeftSpeed_1;
		SpeedSend[2] = SpeedSet.LeftSpeed_2;
		SpeedSend[3] = SpeedSet.RightSpeed_2;
		CAN1MotorSpeedSet(-SpeedSend[0], SpeedSend[1], SpeedSend[2], -SpeedSend[3]);
  	//CAN1MotorSpeedSet(-1000,0,1400,0);
	}
}
