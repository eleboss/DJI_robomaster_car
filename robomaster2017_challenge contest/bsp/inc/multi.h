#ifndef __MULTI_H__
#define __MULTI_H__

#include "stdio.h"
#include "stm32f4xx_tim.h"


typedef struct TIM_CAPTURE{
			TIM_TypeDef *timX;
			unsigned short int TIM_IT_CCX;
			unsigned  char CAPTURE_STA;
			unsigned  int CAPTURE_VAL;
			
}TIM_CAPTURE;

void TIM5_Cap_Init(u32 arr,u16 psc);

#endif
