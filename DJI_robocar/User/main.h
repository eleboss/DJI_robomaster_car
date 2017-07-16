#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#include "can.h"
#include "delay.h"
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "usart4.h"
#include "led.h"
#include "move.h"
#include "control.h"

#include "bodanmotor.h"
#include "rubwheel.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define abs(x) ((x)>0? (x):(-(x)))
#define LIMIT_MIN_MAX(x,min,max)	(((x)<=(min))?(min):(((x)>=(max))?(max):(x)))

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

void SystemConfiguration(void);

#endif 
