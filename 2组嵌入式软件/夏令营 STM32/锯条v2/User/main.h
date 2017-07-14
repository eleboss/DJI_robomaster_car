#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f10x.h"
#include <stdio.h>
#include <stdlib.h>

#include "led.h"
#include "pwm.h"
#include "delay.h"
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "control.h"

#define abs(x) ((x)>0? (x):(-(x)))
#define LIMIT_MIN_MAX(x,min,max)	(((x)<=(min))?(min):(((x)>=(max))?(max):(x)))

void SystemConfiguration(void);
void RCC_Configuration(void);

#endif
