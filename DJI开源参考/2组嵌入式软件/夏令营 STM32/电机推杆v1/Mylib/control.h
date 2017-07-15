#ifndef __CONTROL_H__
#define __CONTROL_H__

typedef struct PID{
	float SetPoint;		
	
	float P;					
	float I;					
	float D;					
	
	float LastError;	
	float SumError;		

	float IMax;				
	
	float POut;				
	float IOut;			
	float DOut;					
}PID;

void PIDInit_Motor(PID *P);
float PIDCalc(PID *P, float NextPoint);

#endif
