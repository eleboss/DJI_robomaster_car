#include "main.h"

const uint16_t BEEP_TONE_TABLE[BEEP_TONE_TABLE_LEN] = BEEP_TONE_TABLE_DEF;
const BeepTone_t BEEP_START_UP_MUSIC[BEEP_START_UP_MUSIC_LEN] = BEEP_START_UP_MUSIC_DEF;

void Beep_Sing(BeepTone_t tone)
{
  if(Silent == tone) {
    BEEP_CCR = 0;
	} else {
    BEEP_ARR = BEEP_TONE_TABLE[tone];
    BEEP_CCR = BEEP_TONE_TABLE[tone] / 2;
  }
}

//play the start up music
void Beep_SingStartupMusic(uint32_t index)
{
  if(index < BEEP_START_UP_MUSIC_LEN)
    Beep_Sing(BEEP_START_UP_MUSIC[index]);
}
void TIM3_OC_Config(TIM_TypeDef* timx, u16 mode, u32 pulse)
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
	TIM_OC3Init(timx,&oc);
	TIM_OC3PreloadConfig(timx,TIM_OCPreload_Enable);
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
	tim.TIM_Prescaler = ps;
	tim.TIM_CounterMode = mode;
	tim.TIM_Period = period;
	tim.TIM_ClockDivision = div;
	tim.TIM_RepetitionCounter = re;
	TIM_TimeBaseInit(timx,&tim);
}
void GPIO_Config(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	gpio.GPIO_Pin = GPIO_Pin_4 ;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Fast_Speed;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&gpio);
}
void BEEP_Configuration(void)
{
	GPIO_Config();
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3 , GPIO_AF_TIM3);
	TIM_Config(BEEP_TIM, BEEP_TIM_PS, TIM_CounterMode_Up, BEEP_TIM_PD, TIM_CKD_DIV1, 0); \
	TIM3_OC_Config(BEEP_TIM, TIM_OCMode_PWM2, BEEP_TIM_PW); \
  TIM_Cmd(BEEP_TIM, ENABLE);
}

