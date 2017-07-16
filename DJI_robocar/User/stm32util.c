#include "main.h"

ExtiHandler extiHandlers[EXTI_LINE_NUM];

#define CHECK_EQ(a,v1,v2) ((a) == (v1) || (a) == (v2))

GPIO_TypeDef* GPIO_GetGroup(GPIO gpio)
{
	return GPIO_PIN_GRP(gpio);
}

uint16_t GPIO_GetMask(GPIO gpio)
{
	return GPIO_PIN_MSK(gpio);
}

uint8_t GPIO_GetNum(GPIO gpio)
{
	return GPIO_PIN_NUM(gpio);
}

uint8_t GPIO_ReadIn(GPIO gpio)
{
	return GPIO_READ_IN(gpio);
}

uint8_t GPIO_ReadOut(GPIO gpio)
{
	return GPIO_READ_OUT(gpio);
}

void GPIO_WriteOut(GPIO gpio, uint8_t newState)
{
	GPIO_WRITE(gpio, newState);
}

void GPIO_Set(GPIO gpio)
{
	GPIO_SET(gpio);
}

void GPIO_Rst(GPIO gpio)
{
	GPIO_RST(gpio);
}

void GPIO_Tog(GPIO gpio)
{
	GPIO_TOG(gpio);
}

void GPIO_Config(GPIO gpio, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed, GPIOOType_TypeDef otype, GPIOPuPd_TypeDef pupd)
{
	GPIO_InitTypeDef io;
	GPIO_TypeDef* grp = GPIO_PIN_GRP(gpio);
	if (grp == GPIOA) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	}
	if (grp == GPIOB) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	}
	if (grp == GPIOC) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	}
	if (grp == GPIOD) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	}
	if (grp == GPIOE) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	}
	if (grp == GPIOF) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	}
	if (grp == GPIOG) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	}
	if (grp == GPIOH) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	}
	if (grp == GPIOI) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
	}
	io.GPIO_Pin = GPIO_PIN_MSK(gpio);
	io.GPIO_Mode = mode;
	io.GPIO_Speed = speed;
	io.GPIO_OType = otype;
	io.GPIO_PuPd = pupd;
	GPIO_Init(grp, &io);
}

void GPIO_In(GPIO gpio)
{
	GPIO_Config(gpio, GPIO_Mode_IN, GPIO_Speed_50MHz, GPIO_OType_OD, GPIO_PuPd_NOPULL);
}

void GPIO_Out(GPIO gpio)
{
	GPIO_Config(gpio, GPIO_Mode_OUT, GPIO_Speed_50MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);
}

void GPIO_Af(GPIO gpio, u8 af)
{
	GPIO_Config(gpio, GPIO_Mode_AF, GPIO_Speed_50MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	GPIO_PinAFConfig(GPIO_PIN_GRP(gpio), GPIO_PIN_NUM(gpio), af);
}


