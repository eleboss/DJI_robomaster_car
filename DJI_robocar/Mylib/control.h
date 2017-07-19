#ifndef __CONTROL_H__
#define __CONTROL_H__

typedef struct PID{
	float SetPoint;			//PID设定值
	
	float P;						//比例常数
	float I;						//积分常熟
	float D;						//微分常数
	
	float LastError;		//前次误差
	float SumError;			//累积误差

	float IMax;					//积分上限
	
	float POut;					//比例输出
	float IOut;					//积分输出
	float DOut;					//微分输出

}PID;

typedef struct ENCODER{
	int DifferEncoder;
	int LastEncoder;
	int SumEncoder;
	int DistanceFromEncoder;
}ENCODER;

void PIDInit_Speed(PID *P);
void PIDInit_Position(PID *P);
void PIDInit_YawControl(PID *P);
void PIDInit_BodanMotor(PID *P);
float PIDCalc(PID *P, float NextPoint);

void EncoderUpdate(ENCODER *E,int Encoder);
void SWITCH_Configuration(void);

#endif
