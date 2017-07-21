#ifndef __LED_H__
#define __LED_H__

#define LED_GREEN_OFF()  GPIO_SetBits(GPIOB,GPIO_Pin_13)
#define LED_GREEN_ON()   GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define LED_GREEN_TOGGLE()  GPIOB->ODR ^= GPIO_Pin_13

#define LED_BLUE_OFF()  GPIO_SetBits(GPIOB,GPIO_Pin_14)
#define LED_BLUE_ON()   GPIO_ResetBits(GPIOB,GPIO_Pin_14)
#define LED_BLUE_TOGGLE()  GPIOB->ODR ^= GPIO_Pin_14

void LED_Configuration(void);

#endif 
