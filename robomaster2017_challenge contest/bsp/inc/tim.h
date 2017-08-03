
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif
	
extern unsigned int SystickCount0,SystickCount1;
	
// Tick timer
#define TICK_TIM TIM2
#define TICK_TIM_PS 89
#define TICK_TIM_PD 0xffffffff //1
#define TICK_TIM_NVIC IRQ(TIM2)
#define TICK_TIM_NVIC_PRE_PRIORITY 0
#define TICK_TIM_NVIC_SUB_PRIORITY 0
#define TICK_TIM_IRQ_HANDLER IRQ_HANDLER(TIM2)
#define TICK_US() TICK_TIM->CNT

// Sync timer
#define SYNC_TIM TIM6
#define SYNC_TIM_PS 89
#define SYNC_TIM_PD 1000
#define SYNC_TIM_NVIC IRQ(TIM6_DAC)
#define SYNC_TIM_NVIC_PRE_PRIORITY 1
#define SYNC_TIM_NVIC_SUB_PRIORITY 0
#define SYNC_TIM_IRQ_HANDLER IRQ_HANDLER(TIM6_DAC)


void TIM6_Configuration(void);
void TIM7_Configuration(void);
void TIM6_Start(void);
void TIM7_Start(void);
void TIM6_Stop(void);


#ifdef __cplusplus
}
#endif

#endif

