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
 
#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#include "can1.h"
#include "can2.h"
#include "beep.h"
#include "led.h"
#include "motor.h"
#include "delay.h"
#include "control.h"
#include "tim.h"
#include "usart2.h"
#include "usart3.h"


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define abs(x) ((x)>0? (x):(-(x)))
#define LIMIT_MIN_MAX(x,min,max)	(((x)<=(min))?(min):(((x)>=(max))?(max):(x)))

extern HG900MotorRecvmsg HG900MotorData[4];
extern float CarDirectionAngel;
extern PID PID_Speed[4];
extern PID PID_Position;
extern PID PID_YawControl;
extern ENCODER ENCODER_CAN[4];
extern Speed SpeedSet;
extern float SpeedSend[4];
extern double AverageDistance;

typedef struct{
	struct
	{
		unsigned short ch0;
		unsigned short ch1;
		unsigned short ch2;
		unsigned short ch3;
		unsigned char s1;
		unsigned char s2;
	}rc;
	struct
	{
		short x;
		short y;
		short z;
		unsigned char press_l;
		unsigned char press_r;
	}mouse;
	struct
	{
		unsigned short w;
		unsigned short a;
		unsigned short s;
		unsigned short d;
		unsigned short ctrl;
		unsigned short shift;
	}key;
}RC_Ctl_t;

#endif 

