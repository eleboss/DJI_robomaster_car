#include "main.h"

void LED_Configuration(void)
{
    GPIO_InitTypeDef gpio;   

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
		
		gpio.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;	
		gpio.GPIO_Mode = GPIO_Mode_Out_PP;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &gpio);
    
    LED_GREEN_ON();
    LED_BLUE_OFF();
}
