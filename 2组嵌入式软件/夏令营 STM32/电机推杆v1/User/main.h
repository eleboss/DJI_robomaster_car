#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f10x.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "led.h"
#include "can.h"
#include "pwm.h"
#include "delay.h"
#include "usart1.h"
#include "strikeswitch.h"
#include "control.h"

#define abs(x) ((x)>0? (x):(-(x)))
#define LIMIT_MIN_MAX(x,min,max)	(((x)<=(min))?(min):(((x)>=(max))?(max):(x)))
#define CAN_ID_SPEED_MODE	CAN_ID_SPEED_MODE_NUM01

void SystemConfiguration(void);
void RCC_Configuration(void);

#endif
