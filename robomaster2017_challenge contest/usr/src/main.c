#include "main.h"

PID PID_Speed[4];
PID PID_Position;
PID PID_YawControl;
ENCODER ENCODER_CAN[4];
Speed SpeedSet;
float SpeedSend[4];
double AverageDistance=0.0f;
int ms10,ms50,ms500;
extern float Distance;


int main()
{
	//PID ³õÊ¼»¯
 	PIDInit_Speed(&PID_Speed[0],1);
	PIDInit_Speed(&PID_Speed[1],1);
	PIDInit_Speed(&PID_Speed[2],1);
	PIDInit_Speed(&PID_Speed[3],1);
	PIDInit_Position(&PID_Position);
	PIDInit_YawControl(&PID_YawControl);
	//ÏµÍ³³õÊ¼»
	CAN1_Configuration();
	CAN2_Configuration();
	LED_Configuration();
	BEEP_Init();
	MOTOR_Configuration();
	USART2_Configuration();
	Infraed_Configuration();
	TIM6_Configuration();
	//TIM5_Cap_Init(0xffffffff,89);
	//TIM7_Configuration();

  LED_GREEN_ON();
	LED_RED_ON();
	//´®¿Ú·¢ËÍÊý¾Ý³õÊ¼»¯

	//±àÂëÆ÷³õÊ¼»¯
	ENCODER_CAN[0].SumEncoder = 0;
	ENCODER_CAN[1].SumEncoder = 0;
	ENCODER_CAN[2].SumEncoder = 0;
	ENCODER_CAN[3].SumEncoder = 0;
	EncoderUpdate(&ENCODER_CAN[0],HG900MotorData[0].Angle);
	EncoderUpdate(&ENCODER_CAN[1],HG900MotorData[1].Angle);
	EncoderUpdate(&ENCODER_CAN[2],HG900MotorData[2].Angle);
	EncoderUpdate(&ENCODER_CAN[3],HG900MotorData[3].Angle);
	//¿ª»ú
  Startup_music();
	TIM6_Start();//¿ªÊ¼¿ØÖÆ
	//Ult_Init();
	//PID_Position.SetPoint=10;
	//Push_Move(600,1,2000);
	xspeed=0;
	yspeed=0;
	zspeed=0;

	while(1)
	{

	}
}
