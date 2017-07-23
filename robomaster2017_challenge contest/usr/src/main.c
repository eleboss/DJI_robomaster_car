#include "main.h"

PID PID_Speed[4];
PID PID_Position;
PID PID_YawControl;
ENCODER ENCODER_CAN[4];
Speed SpeedSet;
float SpeedSend[4];
double AverageDistance=0.0f;
int ms10,ms50,ms500;

int main()
{
	//PID ��ʼ��
 	PIDInit_Speed(&PID_Speed[0]);
	PIDInit_Speed(&PID_Speed[1]);
	PIDInit_Speed(&PID_Speed[2]);
	PIDInit_Speed(&PID_Speed[3]);
	PIDInit_Position(&PID_Position);
	PIDInit_YawControl(&PID_YawControl);
	//ϵͳ��ʼ��
	CAN1_Configuration();
	CAN2_Configuration();
	LED_Configuration();
	BEEP_Init();
	MOTOR_Configuration();
	USART2_Configuration();
	Infraed_Configuration();
	SysTick_Config(180000);//1ms
	TIM6_Configuration();
  LED_GREEN_ON();
	LED_RED_ON();
	//���ڷ������ݳ�ʼ��

	//��������ʼ��
	ENCODER_CAN[0].SumEncoder = 0;
	ENCODER_CAN[1].SumEncoder = 0;
	ENCODER_CAN[2].SumEncoder = 0;
	ENCODER_CAN[3].SumEncoder = 0;
	EncoderUpdate(&ENCODER_CAN[0],HG900MotorData[0].Angle);
	EncoderUpdate(&ENCODER_CAN[1],HG900MotorData[1].Angle);
	EncoderUpdate(&ENCODER_CAN[2],HG900MotorData[2].Angle);
	EncoderUpdate(&ENCODER_CAN[3],HG900MotorData[3].Angle);
	//����
  Startup_music();
	TIM6_Start();//��ʼ����
	//PID_Position.SetPoint=10;
	while(1)
	{

	}
}
void SysTick_Handler(void)
{

}
