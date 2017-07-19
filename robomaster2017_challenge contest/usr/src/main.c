#include "main.h"

extern HG900MotorRecvmsg HG900MotorData[4];
extern unsigned char TB[TBPackSize];

PID PID_Speed[4];
PID PID_Position;
PID PID_YawControl;
ENCODER ENCODER_CAN[4];
Speed SpeedSet;
float SpeedSend[4];
float AverageDistance=0.0f;
int ms10,ms50,ms500;

int main()
{
	//PID 初始化
	PIDInit_Speed(&PID_Speed[0]);
	PIDInit_Speed(&PID_Speed[1]);
	PIDInit_Speed(&PID_Speed[2]);
	PIDInit_Speed(&PID_Speed[3]);
	PIDInit_Position(&PID_Position);
	PIDInit_YawControl(&PID_YawControl);
	//系统初始化
	CAN1_Configuration();
	CAN2_Configuration();
	LED_Configuration();
	USART2_Configuration();
	SysTick_Config(180000);//1ms
  LED_GREEN_ON();
	LED_RED_ON();
	Delay_Ms(10);
	//串口发送数据初始化
	TB[0] = '!';
	TB[1] = '0';
	TB[2] = (uint8_t)HG900MotorData[0].Angle;
	TB[3] = (uint8_t)HG900MotorData[1].Angle;
	TB[4] = (uint8_t)HG900MotorData[2].Angle;
	TB[5] = (uint8_t)HG900MotorData[3].Angle;
	TB[TBPackSize-1] = '#';
	//编码器初始化
	ENCODER_CAN[0].SumEncoder = 0;
	ENCODER_CAN[1].SumEncoder = 0;
	ENCODER_CAN[2].SumEncoder = 0;
	ENCODER_CAN[3].SumEncoder = 0;
	EncoderUpdate(&ENCODER_CAN[0],HG900MotorData[0].Angle);
	EncoderUpdate(&ENCODER_CAN[1],HG900MotorData[1].Angle);
	EncoderUpdate(&ENCODER_CAN[2],HG900MotorData[2].Angle);
	EncoderUpdate(&ENCODER_CAN[3],HG900MotorData[3].Angle);

	PID_Position.SetPoint=10;
	while(1)
	{

	}
}
void SysTick_Handler(void)
{
	EncoderUpdate(&ENCODER_CAN[0],HG900MotorData[0].Angle);
	EncoderUpdate(&ENCODER_CAN[1],HG900MotorData[1].Angle);
	EncoderUpdate(&ENCODER_CAN[2],HG900MotorData[2].Angle);
	EncoderUpdate(&ENCODER_CAN[3],HG900MotorData[3].Angle);
	//速度换PID控制
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
	//位置环PID控制
	AverageDistance=EncoderDistanceSum(&ENCODER_CAN[0],&ENCODER_CAN[1],&ENCODER_CAN[2],&ENCODER_CAN[3])/100;
	MECANUM_MOVE(&SpeedSet,0,PIDCalc(&PID_Position,AverageDistance),0);
	PID_Speed[0].SetPoint = -SpeedSet.RightSpeed_1*0.16;
	PID_Speed[1].SetPoint = SpeedSet.LeftSpeed_1*0.16;
	PID_Speed[2].SetPoint = SpeedSet.LeftSpeed_2*0.16;
	PID_Speed[3].SetPoint = -SpeedSet.RightSpeed_2*0.16;
	SpeedSend[0] += PIDCalc(&PID_Speed[0], ENCODER_CAN[0].DifferEncoder);
	SpeedSend[1] += PIDCalc(&PID_Speed[1], ENCODER_CAN[1].DifferEncoder);
	SpeedSend[2] += PIDCalc(&PID_Speed[2], ENCODER_CAN[2].DifferEncoder);
	SpeedSend[3] += PIDCalc(&PID_Speed[3], ENCODER_CAN[3].DifferEncoder);
	CAN1MotorSpeedSet(SpeedSend[0], SpeedSend[1], SpeedSend[2], SpeedSend[3]);
}
