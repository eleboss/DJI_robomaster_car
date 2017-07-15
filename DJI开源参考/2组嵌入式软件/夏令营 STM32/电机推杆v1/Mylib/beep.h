#ifndef __BEEP_H__
#define __BEEP_H__

#define BEEP_ON()        GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define BEEP_OFF()       GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define BEEP_TOGGLE()    GPIOB->ODR ^= GPIO_Pin_12
#define BEEP_SystemOK		 0		//ϵͳ�ϵ��Լ�ɹ�
#define BEEP_ACK				 1		//�յ���λ����Ϣ��Ӧ
#define BEEP_SystemError 3		//ϵͳ�쳣
#define BEEP_MotorReady	 4		//�����������
#define BEEP_CANError		 5		//CAN��������
#define BEEP_EncoderError 6		//�������쳣

void BEEP_Configuration(void);
void Beep(int BeepMode);

#endif
