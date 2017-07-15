#ifndef __LED_H__
#define __LED_H__

#define LED_GREEN_PIN						GPIO_Pin_4
#define LED_RED_PIN							GPIO_Pin_5

#define LED_GREEN_GPIO					GPIOA
#define LED_RED_GPIO						GPIOA

#define LED_GREEN_OFF()  GPIO_SetBits(LED_GREEN_GPIO,LED_GREEN_PIN)
#define LED_GREEN_ON()   GPIO_ResetBits(LED_GREEN_GPIO,LED_GREEN_PIN)
#define LED_GREEN_TOGGLE()  LED_GREEN_GPIO->ODR ^= LED_GREEN_PIN

#define LED_RED_OFF()  GPIO_SetBits(LED_RED_GPIO,LED_RED_PIN)
#define LED_RED_ON()   GPIO_ResetBits(LED_RED_GPIO,LED_RED_PIN)
#define LED_RED_TOGGLE()  LED_RED_GPIO->ODR ^= LED_RED_PIN

void LED_Configuration(void);

#endif
