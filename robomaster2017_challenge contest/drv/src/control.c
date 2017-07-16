#include "main.h"

void PIDInit_Speed(PID *P)
{
	P->P = 0.28f;
	P->I = 0.0f;
	P->D = 30.0f;//40
	P->IMax = 500.0f;
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

void PIDInit_BodanMotor(PID *P)
{
	P->P = 16.0;
	P->I = 0.0f;
	P->D = 80.0f;
	P->IMax = 500.0f;
	P->SetPoint = 32767.0f;
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
	E->DistanceFromEncoder = E->DistanceFromEncoder + E->DifferEncoder;
}





void MECANUM_MOVE(Speed *Sp,int x,int y,int w)
{
	Sp->LeftSpeed_1 = x+y-w;
	Sp->RightSpeed_1 = -x+y+w;
	Sp->LeftSpeed_2 = -x+y+-w;
	Sp->RightSpeed_2 = x+y+w;
}
