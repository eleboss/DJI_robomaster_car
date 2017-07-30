#include "main.h"

void PIDInit_Speed(PID *P)
{
	P->P = 0.28f;
	P->I = 0.0f;
	P->D = 20.0f;//40
	P->IMax = 100.0f;
	P->SetPoint = 0.0f;
}

void PIDInit_Position(PID *P)
{
	P->P = 0.2f;
	P->I = 0.006f;
	P->D = 120.0f;
	P->IMax = 40000.0f;
	P->SetPoint = 0.0f;
}
void PIDInit_YawControl(PID *P)
{
	P->P = 3.8f;
	P->I = 0.0f;
	P->D = 21.0f;
	P->IMax = 500.0f;
	P->SetPoint = 0.0f;
}

void PID_Rx(PID *PS0,PID *PS1,PID *PS2,PID *PS3, PID *PP, PID *PY)
{
	PS0->P = PID_RxSpeed[0];
	PS0->I = PID_RxSpeed[1];
	PS0->D = PID_RxSpeed[2];
	
	PS1->P = PID_RxSpeed[0];
	PS1->I = PID_RxSpeed[1];
	PS1->D = PID_RxSpeed[2];
	
	PS2->P = PID_RxSpeed[0];
	PS2->I = PID_RxSpeed[1];
	PS2->D = PID_RxSpeed[2];

	PS3->P = PID_RxSpeed[0];
	PS3->I = PID_RxSpeed[1];
	PS3->D = PID_RxSpeed[2];
	
	PP->P = PID_RxPosition[0];
	PP->I = PID_RxPosition[1];
	PP->D = PID_RxPosition[2];
	
	PY->P = PID_RxYaw[0];
	PY->I = PID_RxYaw[1];
	PY->D = PID_RxYaw[2];
	
}
float PIDCalc(PID *P, float NextPoint)
{
		float dError,Error;
		Error = P->SetPoint - NextPoint;
		
		dError = Error-P->LastError;
		P->LastError = Error;
		P->SumError +=  Error;
		
		if(P->SumError >= P->IMax)
			P->SumError = P->IMax;
		else if(P->SumError <= -P->IMax)
			P->SumError = -P->IMax;
		
		P->POut = P->P*Error;
		P->IOut = P->I*P->SumError;
		P->DOut = P->D*dError;
		
		return P->POut+P->IOut+P->DOut;
}

void EncoderUpdate(ENCODER *E,int Encoder)
{
	E->DifferEncoder = Encoder - E->LastEncoder;
	if(E->DifferEncoder > 4096)
	{
		E->DifferEncoder = E->DifferEncoder - 8192;
	}
	else if(E->DifferEncoder < -4096)
	{
		E->DifferEncoder = E->DifferEncoder + 8192;
	}
	E->LastEncoder = Encoder;
	E->SumEncoder = E->SumEncoder + E->DifferEncoder;
	E->Distance = (double)E->SumEncoder*0.058084;//轮子直径D=151.46MM   SumEncoder/8192*3.14159*151.46  距离的单位是MM
	
}
float EncoderDistanceSum(ENCODER *E0,ENCODER *E1,ENCODER *E2,ENCODER *E3)
{
	return (E1->Distance+E2->Distance-E3->Distance-E0->Distance)/4;
}

void MECANUM_MOVE(Speed *Sp,int x,int y,int w)
{
	Sp->LeftSpeed_1 = x+y-w;
	Sp->RightSpeed_1 = -x+y+w;
	Sp->LeftSpeed_2 = -x+y+-w;
	Sp->RightSpeed_2 = x+y+w;
}

void Control_Task(void)
{
	//更新编码器数据
	EncoderUpdate(&ENCODER_CAN[0],HG900MotorData[0].Angle);
	EncoderUpdate(&ENCODER_CAN[1],HG900MotorData[1].Angle);
	EncoderUpdate(&ENCODER_CAN[2],HG900MotorData[2].Angle);
	EncoderUpdate(&ENCODER_CAN[3],HG900MotorData[3].Angle);
	//速度换PID控制
	MECANUM_MOVE(&SpeedSet,0,0,30);
	PID_Speed[0].SetPoint = -SpeedSet.RightSpeed_1*0.16;
	PID_Speed[1].SetPoint = SpeedSet.LeftSpeed_1*0.16;
	PID_Speed[2].SetPoint = SpeedSet.LeftSpeed_2*0.16;
	PID_Speed[3].SetPoint = -SpeedSet.RightSpeed_2*0.16;
	SpeedSend[0] += PIDCalc(&PID_Speed[0], ENCODER_CAN[0].DifferEncoder);
	SpeedSend[1] += PIDCalc(&PID_Speed[1], ENCODER_CAN[1].DifferEncoder);
	SpeedSend[2] += PIDCalc(&PID_Speed[2], ENCODER_CAN[2].DifferEncoder);
	SpeedSend[3] += PIDCalc(&PID_Speed[3], ENCODER_CAN[3].DifferEncoder);
	CAN1MotorSpeedSet(SpeedSend[0], SpeedSend[1], SpeedSend[2], SpeedSend[3]);
	//位置环PID控制
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
	//yaw位置环控制
//	MECANUM_MOVE(&SpeedSet,0,0,PIDCalc(&PID_YawControl,CarDirectionAngel));
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
