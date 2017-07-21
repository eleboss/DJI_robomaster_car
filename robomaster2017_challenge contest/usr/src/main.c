#include "main.h"

extern HG900MotorRecvmsg HG900MotorData[4];
extern unsigned char TB[TBPackSize];
extern float CarDirectionAngel;

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
  LED_GREEN_ON();
	LED_RED_ON();
  Startup_music();
	//���ڷ������ݳ�ʼ��
	TB[0] = '!';
	TB[1] = '0';
	TB[2] = (uint8_t)HG900MotorData[0].Angle;
	TB[3] = (uint8_t)HG900MotorData[1].Angle;
	TB[4] = (uint8_t)HG900MotorData[2].Angle;
	TB[5] = (uint8_t)HG900MotorData[3].Angle;
	TB[TBPackSize-1] = '#';
	//��������ʼ��
	ENCODER_CAN[0].SumEncoder = 0;
	ENCODER_CAN[1].SumEncoder = 0;
	ENCODER_CAN[2].SumEncoder = 0;
	ENCODER_CAN[3].SumEncoder = 0;
	EncoderUpdate(&ENCODER_CAN[0],HG900MotorData[0].Angle);
	EncoderUpdate(&ENCODER_CAN[1],HG900MotorData[1].Angle);
	EncoderUpdate(&ENCODER_CAN[2],HG900MotorData[2].Angle);
	EncoderUpdate(&ENCODER_CAN[3],HG900MotorData[3].Angle);

	//PID_Position.SetPoint=10;
	//Push_Move(2000,0,1000);
	while(1)
	{
		//MOTOR_Move();
			//send_com(0x45);
		
		Delay_Ms(100);
	}
}
void SysTick_Handler(void)
{
	//���±���������
	EncoderUpdate(&ENCODER_CAN[0],HG900MotorData[0].Angle);
	EncoderUpdate(&ENCODER_CAN[1],HG900MotorData[1].Angle);
	EncoderUpdate(&ENCODER_CAN[2],HG900MotorData[2].Angle);
	EncoderUpdate(&ENCODER_CAN[3],HG900MotorData[3].Angle);
	//�ٶȻ�PID����
//	MECANUM_MOVE(&SpeedSet,0,0,0);
//	PID_Speed[0].SetPoint = -SpeedSet.RightSpeed_1*0.16;
//	PID_Speed[1].SetPoint = SpeedSet.LeftSpeed_1*0.16;
//	PID_Speed[2].SetPoint = SpeedSet.LeftSpeed_2*0.16;
//	PID_Speed[3].SetPoint = -SpeedSet.RightSpeed_2*0.16;
//	SpeedSend[0] += PIDCalc(&PID_Speed[0], ENCODER_CAN[0].DifferEncoder);
//	SpeedSend[1] += PIDCalc(&PID_Speed[1], ENCODER_CAN[1].DifferEncoder);
//	SpeedSend[2] += PIDCalc(&PID_Speed[2], ENCODER_CAN[2].DifferEncoder);
//	SpeedSend[3] += PIDCalc(&PID_Speed[3], ENCODER_CAN[3].DifferEncoder);
//	CAN1MotorSpeedSet(SpeedSend[0], SpeedSend[1], SpeedSend[2], SpeedSend[3]);
	//λ�û�PID����
//	AverageDistance=EncoderDistanceSum(&ENCODER_CAN[0],&ENCODER_CAN[1],&ENCODER_CAN[2],&ENCODER_CAN[3])/100;
//	MECANUM_MOVE(&SpeedSet,0,PIDCalc(&PID_Position,AverageDistance),0);
//	PID_Speed[0].SetPoint = -SpeedSet.RightSpeed_1*0.16;
//	PID_Speed[1].SetPoint = SpeedSet.LeftSpeed_1*0.16;
//	PID_Speed[2].SetPoint = SpeedSet.LeftSpeed_2*0.16;
//	PID_Speed[3].SetPoint = -SpeedSet.RightSpeed_2*0.16;
//	SpeedSend[0] += PIDCalc(&PID_Speed[0], ENCODER_CAN[0].DifferEncoder);
//	SpeedSend[1] += PIDCalc(&PID_Speed[1], ENCODER_CAN[1].DifferEncoder);
//	SpeedSend[2] += PIDCalc(&PID_Speed[2], ENCODER_CAN[2].DifferEncoder);
//	SpeedSend[3] += PIDCalc(&PID_Speed[3], ENCODER_CAN[3].DifferEncoder);
//	CAN1MotorSpeedSet(SpeedSend[0], SpeedSend[1], SpeedSend[2], SpeedSend[3]);
	//yawλ�û�����
//	MECANUM_MOVE(&SpeedSet,0,PIDCalc(&PID_YawControl,CarDirectionAngel),0);
//	PID_Speed[0].SetPoint = -SpeedSet.RightSpeed_1*0.16;
//	PID_Speed[1].SetPoint = SpeedSet.LeftSpeed_1*0.16;
//	PID_Speed[2].SetPoint = SpeedSet.LeftSpeed_2*0.16;
//	PID_Speed[3].SetPoint = -SpeedSet.RightSpeed_2*0.16;
//	SpeedSend[0] += PIDCalc(&PID_Speed[0], ENCODER_CAN[0].DifferEncoder);
//	SpeedSend[1] += PIDCalc(&PID_Speed[1], ENCODER_CAN[1].DifferEncoder);
//	SpeedSend[2] += PIDCalc(&PID_Speed[2], ENCODER_CAN[2].DifferEncoder);
//	SpeedSend[3] += PIDCalc(&PID_Speed[3], ENCODER_CAN[3].DifferEncoder);
//	CAN1MotorSpeedSet(SpeedSend[0], SpeedSend[1], SpeedSend[2], SpeedSend[3]);
}
