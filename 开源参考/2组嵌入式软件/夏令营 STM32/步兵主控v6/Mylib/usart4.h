#ifndef __USART4_H__
#define __USART4_H__

typedef struct GYRO{
		float AX;
		float AY;
		float AZ;
		float GX;
		float GY;
		float GZ;
		float PITCH;
		float ROLL;
		float YAW;
		float Temperature;
}GYRO;
//陀螺仪配置
void UART4_Configuration(void);

#endif
