#ifndef __LED_H__
#define __LED_H__

#define LEDToggle() GPIOC->ODR ^= GPIO_Pin_13

void LED_Configuration(void);

#endif 
