
 
#ifndef __MOTOR_H__
#define __MOTOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

void Updown_Move(u32 wheel,u32 dir,u32 delay);
void Fetch_Move(u32 wheel,u32 dir,u32 delay);
void Push_Move(u32 wheel,u32 dir,u32 delay);
void Wheel_Move(u32 wheel,u32 dir,u32 delay);	
void MOTOR_Configuration(void);
	
#ifdef __cplusplus
}
#endif
	
#endif
