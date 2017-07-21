#include "main.h"

void PIDInit_Motor(PID *P)
{
	P->P = 4.0;
	P->I = 0.0f;
	P->D = 40.0f;
	P->IMax = 500.0f;
	//P->SetPoint = 32767.0f;
	P->SetPoint = 0.0f;
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
