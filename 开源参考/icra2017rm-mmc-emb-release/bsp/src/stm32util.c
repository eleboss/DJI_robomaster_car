#include "stm32util.h"

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
	if (grp == GPIOJ) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOJ, ENABLE);
	}
	if (grp == GPIOK) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOK, ENABLE);
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
	GPIO_Config(gpio, GPIO_Mode_IN, GPIO_Fast_Speed, GPIO_OType_OD, GPIO_PuPd_NOPULL);
}

void GPIO_Out(GPIO gpio)
{
	GPIO_Config(gpio, GPIO_Mode_OUT, GPIO_Fast_Speed, GPIO_OType_PP, GPIO_PuPd_NOPULL);
}

void GPIO_Af(GPIO gpio, u8 af)
{
	GPIO_Config(gpio, GPIO_Mode_AF, GPIO_Fast_Speed, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	GPIO_PinAFConfig(GPIO_PIN_GRP(gpio), GPIO_PIN_NUM(gpio), af);
}

void Encoder_Bind(GPIO A, GPIO B, TIM_TypeDef* timx, u16 mode, u16 p1, u16 p2)
{
	if (timx == TIM1) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		GPIO_Af(A, GPIO_AF_TIM1);
		GPIO_Af(B, GPIO_AF_TIM1);
	}
	if (timx == TIM2) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		GPIO_Af(A, GPIO_AF_TIM2);
		GPIO_Af(B, GPIO_AF_TIM2);
	}
	if (timx == TIM3) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		GPIO_Af(A, GPIO_AF_TIM3);
		GPIO_Af(B, GPIO_AF_TIM3);
	}
	if (timx == TIM4) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		GPIO_Af(A, GPIO_AF_TIM4);
		GPIO_Af(B, GPIO_AF_TIM4);
	}
	if (timx == TIM5) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
		GPIO_Af(A, GPIO_AF_TIM5);
		GPIO_Af(B, GPIO_AF_TIM5);
	}
	/*
	if (timx == TIM6) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
		GPIO_Af(A, GPIO_AF_TIM6);
		GPIO_Af(B, GPIO_AF_TIM6);
	}
	*/
	/*
	if (timx == TIM7) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
		GPIO_Af(A, GPIO_AF_TIM7);
		GPIO_Af(B, GPIO_AF_TIM7);
	}
	*/
	if (timx == TIM8) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
		GPIO_Af(A, GPIO_AF_TIM8);
		GPIO_Af(B, GPIO_AF_TIM8);
	}
	if (timx == TIM9) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
		GPIO_Af(A, GPIO_AF_TIM9);
		GPIO_Af(B, GPIO_AF_TIM9);
	}
	if (timx == TIM10) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
		GPIO_Af(A, GPIO_AF_TIM10);
		GPIO_Af(B, GPIO_AF_TIM10);
	}
	if (timx == TIM11) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
		GPIO_Af(A, GPIO_AF_TIM11);
		GPIO_Af(B, GPIO_AF_TIM11);
	}
	if (timx == TIM12) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
		GPIO_Af(A, GPIO_AF_TIM12);
		GPIO_Af(B, GPIO_AF_TIM12);
	}
	if (timx == TIM13) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
		GPIO_Af(A, GPIO_AF_TIM13);
		GPIO_Af(B, GPIO_AF_TIM13);
	}
	if (timx == TIM14) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
		GPIO_Af(A, GPIO_AF_TIM14);
		GPIO_Af(B, GPIO_AF_TIM14);
	}
	TIM_EncoderInterfaceConfig(timx, mode, p1, p2);
}

void USART_Bind(GPIO rx, GPIO tx, USART_TypeDef* usartx, u32 br, u8 wl, s8 parity, float sb, s8 fc)
{
	if (usartx == USART1) {
		USART_BIND(rx, tx, USART1, br, wl, parity, sb, fc);
	}
	if (usartx == USART2) {
		USART_BIND(rx, tx, USART2, br, wl, parity, sb, fc);
	}
	if (usartx == USART3) {
		USART_BIND(rx, tx, USART3, br, wl, parity, sb, fc);
	}
	if (usartx == UART4) {
		USART_BIND(rx, tx, UART4, br, wl, parity, sb, fc);
	}
	if (usartx == UART5) {
		USART_BIND(rx, tx, UART5, br, wl, parity, sb, fc);
	}
	if (usartx == USART6) {
		USART_BIND(rx, tx, USART6, br, wl, parity, sb, fc);
	}
	if (usartx == UART7) {
		USART_BIND(rx, tx, UART7, br, wl, parity, sb, fc);
	}
	if (usartx == UART8) {
		USART_BIND(rx, tx, UART8, br, wl, parity, sb, fc);
	}
}

void USART_Config(USART_TypeDef* usartx, s8 mode, u32 br, u8 wl, s8 parity, float sb, s8 fc)
{
	USART_InitTypeDef usart;
	if (usartx == USART1) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	}
	if (usartx == USART2) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	}
	if (usartx == USART3) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	}
	if (usartx == UART4) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	}
	if (usartx == UART5) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
	}
	if (usartx == USART6) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	}
	if (usartx == UART7) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);
	}
	if (usartx == UART8) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8, ENABLE);
	}
	// mode
	if (CHECK_EQ(mode, 'r', 'R')) {
		usart.USART_Mode = USART_Mode_Rx;
	} else if (CHECK_EQ(mode, 't', 'T')) {
		usart.USART_Mode = USART_Mode_Tx;
	} else {
		usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	}
	// baud rate
	usart.USART_BaudRate = br;
	// word length
	if (wl == 9) {
		usart.USART_WordLength = USART_WordLength_9b;
	} else {
		usart.USART_WordLength = USART_WordLength_8b;
	}
	// parity
	if (CHECK_EQ(parity, 'o', 'O')) {
		usart.USART_Parity = USART_Parity_Odd;
	} else if (CHECK_EQ(parity, 'e', 'E')) {
		usart.USART_Parity = USART_Parity_Even;
	} else {
		usart.USART_Parity = USART_Parity_No;
	}
	// stop bits
	if (sb == 0.5f) {
		usart.USART_StopBits = USART_StopBits_0_5;
	} else if (sb == 1.5f) {
		usart.USART_StopBits = USART_StopBits_1_5;
	} else if (sb == 2.0f) {
		usart.USART_StopBits = USART_StopBits_2;
	} else {
		usart.USART_StopBits = USART_StopBits_1;
	}
	// flow control
	if (CHECK_EQ(fc, 'r', 'R')) {
		usart.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS;
	} else if (CHECK_EQ(fc, 'c', 'C')) {
		usart.USART_HardwareFlowControl = USART_HardwareFlowControl_CTS;
	} else if (CHECK_EQ(fc, 'a', 'A')) {
		usart.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;
	} else {
		usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	}
	USART_Init(usartx, &usart);
}

void PWM_Bind(GPIO A, GPIO B, GPIO C, GPIO D, TIM_TypeDef* timx, u16 ps, u32 pd, u32 pw)
{
	if (timx == TIM1) {
		PWM_BIND(A, B, C, D, TIM1, ps, pd, pw);
	}
	if (timx == TIM2) {
		PWM_BIND(A, B, C, D, TIM2, ps, pd, pw);
	}
	if (timx == TIM3) {
		PWM_BIND(A, B, C, D, TIM3, ps, pd, pw);
	}
	if (timx == TIM4) {
		PWM_BIND(A, B, C, D, TIM4, ps, pd, pw);
	}
	if (timx == TIM5) {
		PWM_BIND(A, B, C, D, TIM5, ps, pd, pw);
	}
	if (timx == TIM6) {
		//PWM_BIND(A, B, C, D, TIM6, ps, period, pulse);
	}
	if (timx == TIM7) {
		//PWM_BIND(A, B, C, D, TIM7, ps, period, pulse);
	}
	if (timx == TIM8) {
		PWM_BIND(A, B, C, D, TIM8, ps, pd, pw);
	}
	if (timx == TIM9) {
		PWM_BIND(A, B, C, D, TIM9, ps, pd, pw);
	}
	if (timx == TIM10) {
		PWM_BIND(A, B, C, D, TIM10, ps, pd, pw);
	}
	if (timx == TIM11) {
		PWM_BIND(A, B, C, D, TIM11, ps, pd, pw);
	}
	if (timx == TIM12) {
		PWM_BIND(A, B, C, D, TIM12, ps, pd, pw);
	}
	if (timx == TIM13) {
		PWM_BIND(A, B, C, D, TIM13, ps, pd, pw);
	}
	if (timx == TIM14) {
		PWM_BIND(A, B, C, D, TIM14, ps, pd, pw);
	}
}

void TIM_Config(TIM_TypeDef* timx, u16 ps, u16 mode, u32 period, u16 div, u8 re)
{
	TIM_TimeBaseInitTypeDef tim;
	if (timx == TIM1) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	}
	if (timx == TIM2) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}
	if (timx == TIM3) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	}
	if (timx == TIM4) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	}
	if (timx == TIM5) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	}
	if (timx == TIM6) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	}
	if (timx == TIM7) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	}
	if (timx == TIM8) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	}
	if (timx == TIM9) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	}
	if (timx == TIM10) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
	}
	if (timx == TIM11) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
	}
	if (timx == TIM12) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
	}
	if (timx == TIM13) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
	}
	if (timx == TIM14) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	}
	tim.TIM_Prescaler = ps;
	tim.TIM_CounterMode = mode;
	tim.TIM_Period = period;
	tim.TIM_ClockDivision = div;
	tim.TIM_RepetitionCounter = re;
	TIM_TimeBaseInit(timx,&tim);
}

void TIM_OC_Config(TIM_TypeDef* timx, u8 channel, u16 mode, u32 pulse)
{
	TIM_OCInitTypeDef oc;
	oc.TIM_OCMode = mode;
	oc.TIM_OutputState = TIM_OutputState_Enable;
	oc.TIM_OutputNState = TIM_OutputState_Disable;
	oc.TIM_Pulse = pulse;
	oc.TIM_OCPolarity = TIM_OCPolarity_Low;
	oc.TIM_OCNPolarity = TIM_OCPolarity_High;
	oc.TIM_OCIdleState = TIM_OCIdleState_Reset;
	oc.TIM_OCNIdleState = TIM_OCIdleState_Set;
	if(channel & 0x01){
		TIM_OC1Init(timx,&oc);
		TIM_OC1PreloadConfig(timx,TIM_OCPreload_Enable);
	}
	if(channel & 0x02){
		TIM_OC2Init(timx,&oc);
		TIM_OC2PreloadConfig(timx,TIM_OCPreload_Enable);
	}
	if(channel & 0x04){
		TIM_OC3Init(timx,&oc);
		TIM_OC3PreloadConfig(timx,TIM_OCPreload_Enable);
	}
	if(channel & 0x08){
		TIM_OC4Init(timx,&oc);
		TIM_OC4PreloadConfig(timx,TIM_OCPreload_Enable);
	}
}

void NVIC_Config(u8 channel, u8 pre, u8 sub)
{
	NVIC_InitTypeDef nvic;
	nvic.NVIC_IRQChannel = channel;
	nvic.NVIC_IRQChannelPreemptionPriority = pre;
	nvic.NVIC_IRQChannelSubPriority = sub;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
}

void CAN_Config(CAN_TypeDef* canx, u16 ps, u8 mode, u8 sjw, u8 bs1, u8 bs2)
{
	CAN_InitTypeDef can;
	if (canx == CAN1) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	}
	if (canx == CAN2) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
	}
	can.CAN_Prescaler = ps;
	can.CAN_Mode = mode;
	can.CAN_SJW = sjw;
	can.CAN_BS1 = bs1;
	can.CAN_BS2 = bs2;
	can.CAN_TTCM = DISABLE;
	can.CAN_ABOM = DISABLE;
	can.CAN_AWUM = DISABLE;
	can.CAN_RFLM = DISABLE;
	can.CAN_TXFP = ENABLE;
	CAN_Init(canx, &can);
}

void CAN_Filter_Config(u16 id_h, u16 id_l, u16 msk_h, u16 msk_l, u16 fifo, u8 num)
{
	CAN_FilterInitTypeDef can_filter;
	can_filter.CAN_FilterIdHigh = id_h;
	can_filter.CAN_FilterIdLow = id_l;
	can_filter.CAN_FilterMaskIdHigh = msk_h;
	can_filter.CAN_FilterMaskIdLow = msk_l;
	can_filter.CAN_FilterFIFOAssignment = fifo;
	can_filter.CAN_FilterNumber = num;
	can_filter.CAN_FilterMode = CAN_FilterMode_IdMask;
	can_filter.CAN_FilterScale = CAN_FilterScale_32bit;
	can_filter.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&can_filter);
}

void DMA_Config(DMA_Stream_TypeDef* DMAy_Streamx, u32 channel, u32 pba, u32 mba, u32 dir, u32 bs)
{
	DMA_InitTypeDef dma;
	if ((DMA1_BASE & ((u32)DMAy_Streamx)) == DMA1_BASE) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	}
	if ((DMA2_BASE & ((u32)DMAy_Streamx)) == DMA2_BASE) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	}
	dma.DMA_Channel = channel;
	dma.DMA_PeripheralBaseAddr = pba;
	dma.DMA_Memory0BaseAddr = mba;
	dma.DMA_DIR = dir;
	dma.DMA_BufferSize = bs;
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dma.DMA_Mode = DMA_Mode_Circular;
	dma.DMA_Priority = DMA_Priority_Medium;
	dma.DMA_FIFOMode = DMA_FIFOMode_Disable;
	dma.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	dma.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	dma.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMAy_Streamx, &dma);
}

void EXTI_Config(u32 line, EXTIMode_TypeDef mode, EXTITrigger_TypeDef trigger)
{
	EXTI_InitTypeDef exti;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	exti.EXTI_Line = line;
	exti.EXTI_Mode = mode;
	exti.EXTI_Trigger = trigger;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);
}

void EXTI_SetHandler(uint8_t num, ExtiHandler handler)
{
	if (num < EXTI_LINE_NUM) {
		extiHandlers[num] = handler;
	}
}

void EXTI0_IRQHandler(void)
{
	EXIT_N_IRQ_HANDLER(0);
}

void EXTI1_IRQHandler(void)
{
	EXIT_N_IRQ_HANDLER(1);
}

void EXTI2_IRQHandler(void)
{
	EXIT_N_IRQ_HANDLER(2);
}

void EXTI3_IRQHandler(void)
{
	EXIT_N_IRQ_HANDLER(3);
}

void EXTI4_IRQHandler(void)
{
	EXIT_N_IRQ_HANDLER(4);
}

void EXTI9_5_IRQHandler(void)
{
	EXIT_N_IRQ_HANDLER(5);
	EXIT_N_IRQ_HANDLER(6);
	EXIT_N_IRQ_HANDLER(7);
	EXIT_N_IRQ_HANDLER(8);
	EXIT_N_IRQ_HANDLER(9);
}

void EXTI15_10_IRQHandler(void)
{
	EXIT_N_IRQ_HANDLER(10);
	EXIT_N_IRQ_HANDLER(11);
	EXIT_N_IRQ_HANDLER(12);
	EXIT_N_IRQ_HANDLER(13);
	EXIT_N_IRQ_HANDLER(14);
	EXIT_N_IRQ_HANDLER(15);
}

void EXTI_Bind(GPIO gpio, uint8_t pre_priority, uint8_t sub_priority, EXTITrigger_TypeDef trigger, ExtiHandler handler)
{
	uint32_t pinGrp = GPIO_PIN_GRP_NUM(gpio);
	uint32_t pinNum = GPIO_PIN_NUM(gpio);
	uint32_t pinMsk = GPIO_PIN_MSK(gpio);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIO_In(gpio);
	SYSCFG_EXTILineConfig(pinGrp, pinNum);
	EXTI_Config(pinMsk, EXTI_Mode_Interrupt, trigger);
	
	EXTI_SetHandler(pinNum, handler);
	if (pinNum == 0) {
		NVIC_Config(EXTI0_IRQn, pre_priority, sub_priority);
	}
	else if (pinNum == 1) {
		NVIC_Config(EXTI1_IRQn, pre_priority, sub_priority);
	}
	else if (pinNum == 2) {
		NVIC_Config(EXTI2_IRQn, pre_priority, sub_priority);
	}
	else if (pinNum == 3) {
		NVIC_Config(EXTI2_IRQn, pre_priority, sub_priority);
	}
	else if (pinNum == 4) {
		NVIC_Config(EXTI2_IRQn, pre_priority, sub_priority);
	}
	else if (pinNum < 10) {
		NVIC_Config(EXTI9_5_IRQn, pre_priority, sub_priority);
	}
	else if (pinNum < 16) {
		NVIC_Config(EXTI15_10_IRQn, pre_priority, sub_priority);
	}
}

void SPI_Config(SPI_TypeDef* spix, uint16_t mode, uint16_t dir, uint16_t ds, uint16_t cpol, uint16_t cpha, uint16_t nss, uint16_t ps, uint16_t fb, uint16_t crcp)
{
	SPI_InitTypeDef spi;
	
	if (spix == SPI1) {
		RCC_CLK_ENABLE(APB2, SPI1);
	}
	if (spix == SPI2) {
		RCC_CLK_ENABLE(APB1, SPI2);
	}
	if (spix == SPI3) {
		RCC_CLK_ENABLE(APB1, SPI3);
	}
	if (spix == SPI4) {
		RCC_CLK_ENABLE(APB2, SPI4);
	}
	if (spix == SPI5) {
		RCC_CLK_ENABLE(APB2, SPI5);
	}
	if (spix == SPI6) {
		RCC_CLK_ENABLE(APB2, SPI6);
	}
	
	spi.SPI_Mode = mode;
	spi.SPI_Direction = dir;
	spi.SPI_DataSize = ds;
	spi.SPI_CPOL = cpol;
	spi.SPI_CPHA = cpha;
	spi.SPI_NSS = nss;
	spi.SPI_BaudRatePrescaler = ps;
	spi.SPI_FirstBit = fb;
	spi.SPI_CRCPolynomial = crcp;
	
	SPI_Init(spix, &spi);
}

void SPI_Bind(GPIO nssPin, GPIO sckPin, GPIO misoPin, GPIO mosiPin, SPI_TypeDef* spix, uint16_t mode, uint16_t dir, uint16_t ds, uint16_t cpol, uint16_t cpha, uint16_t nss, uint16_t ps, uint16_t fb, uint16_t crcp)
{
	if (spix == SPI1) {
		SPI_BIND(nssPin, sckPin, misoPin, mosiPin, SPI1, mode, dir, ds, cpol, cpha, nss, ps, fb, crcp);
	}
	if (spix == SPI2) {
		SPI_BIND(nssPin, sckPin, misoPin, mosiPin, SPI2, mode, dir, ds, cpol, cpha, nss, ps, fb, crcp);
	}
	if (spix == SPI3) {
		SPI_BIND(nssPin, sckPin, misoPin, mosiPin, SPI3, mode, dir, ds, cpol, cpha, nss, ps, fb, crcp);
	}
	if (spix == SPI4) {
		SPI_BIND(nssPin, sckPin, misoPin, mosiPin, SPI4, mode, dir, ds, cpol, cpha, nss, ps, fb, crcp);
	}
	if (spix == SPI5) {
		SPI_BIND(nssPin, sckPin, misoPin, mosiPin, SPI5, mode, dir, ds, cpol, cpha, nss, ps, fb, crcp);
	}
	if (spix == SPI6) {
		SPI_BIND(nssPin, sckPin, misoPin, mosiPin, SPI6, mode, dir, ds, cpol, cpha, nss, ps, fb, crcp);
	}
}

uint8_t SPI_TxRxByte(SPI_TypeDef* spix, uint8_t txData, uint8_t* rxData, uint32_t timeout)
{
	spix->DR = txData;
	while (!(spix->SR & SPI_SR_RXNE)) {
		if (timeout == 0) {
			return 0;
		} else {
			timeout--;
		}
	}
	*rxData = spix->DR;
	return 1;
}

uint32_t SPI_TxRx(SPI_TypeDef* spix, const uint8_t* txData, uint8_t* rxData, uint32_t len, uint32_t timeout)
{
	uint32_t i = 0;
	uint8_t tmp = 0;
	for (; i < len; i++) {
		tmp = SPI_TxRxByte(spix, txData[i], &rxData[i], timeout);
		if (!tmp) break;
	}
	return i;
}

