#ifndef __BEEP_H__
#define __BEEP_H__

#define BEEP_ON()        GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define BEEP_OFF()       GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define BEEP_TOGGLE()    GPIOB->ODR ^= GPIO_Pin_12
#define BEEP_SystemOK		 0		//系统上电自检成功
#define BEEP_ACK				 1		//收到上位机消息回应
#define BEEP_SystemError 3		//系统异常
#define BEEP_MotorReady	 4		//电机驱动就绪
#define BEEP_CANError		 5		//CAN线无连接
#define BEEP_EncoderError 6		//编码器异常

void BEEP_Configuration(void);
void Beep(int BeepMode);

#endif
