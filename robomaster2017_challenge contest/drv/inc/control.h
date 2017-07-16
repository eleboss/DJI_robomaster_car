#ifndef __CONTROL_H__
#define __CONTROL_H__

#define MAXSPEED 200

typedef struct PID{
	float SetPoint;			//PID设定值
	
	float P;						
	float I;						
	float D;						
	
	float LastError;		
	float SumError;			

	float IMax;					//积分上限
	
	float POut;					
	float IOut;					
	float DOut;					
}PID;

typedef struct ENCODER{
	int DifferEncoder;
	int LastEncoder;
	int SumEncoder;
	int DistanceFromEncoder;
}ENCODER;



typedef struct Speed
{
	int LeftSpeed_1;
	int RightSpeed_1;
	int LeftSpeed_2;
	int RightSpeed_2;
}Speed;

void MECANUM_MOVE(Speed *Sp,int x,int y,int w);

void PIDInit_Speed(PID *P);
void PIDInit_Position(PID *P);
void PIDInit_YawControl(PID *P);
void PIDInit_BodanMotor(PID *P);
float PIDCalc(PID *P, float NextPoint);

void EncoderUpdate(ENCODER *E,int Encoder);
void SWITCH_Configuration(void);

#endif
