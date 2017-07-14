#include "main.h"

void LED_Configuration(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	gpio.GPIO_Pin = LED_GREEN_PIN;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(LED_GREEN_GPIO,&gpio);

	gpio.GPIO_Pin = LED_RED_PIN;
	GPIO_Init(LED_RED_GPIO,&gpio);
	
	LED_GREEN_OFF();
	LED_RED_OFF();
}
