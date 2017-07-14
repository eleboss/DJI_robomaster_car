#include "main.h"
#define Pos1ChangeMax 30.0f
#define Pos2ChangeMax 0.5f

#define Pos1MaxDistance 1120
#define Pos2MaxDistance 2050//2050
#define Pos1MinDistance 2000
#define Pos2MinDistance 918 //880

#define Pos1OriDistance Pos1MinDistance
#define Pos2OriDistance 1170

#define BodanRightPos 30700
#define BodanRoad		  9500

extern RC_Ctl_t RC_Ctl; 
extern HG900MotorRecvmsg HG900MotorData[4];
extern AUTOCONTROL AutoControl;
extern GYRO gyro;
extern unsigned char TB[TBPackSize];

PID PID_Speed[4];
PID PID_Position[4];
PID PID_YawControl;
PID PID_BodanMotor;
ENCODER ENCODER_CAN[4];
Speed SpeedSet;
float SpeedSend[4];
int ms10,ms50,ms500;

int CountForPC = 0;
int CountForSystick = 0;
int CountForStatus = 0;
int CountForAction = 0;
int CountForWall = 1;

float Pos1 = Pos1OriDistance, Pos2 = Pos2OriDistance;
float PosLast1 = Pos1OriDistance, PosLast2 = Pos2OriDistance;
float YawOffset = 0;

int test1 = 0, test2 = 0;
int test3 = 0, test4 = 0;

int main(void)
{
	/* 参数初始化 */
	PIDInit_Speed(&PID_Speed[0]);
	PIDInit_Speed(&PID_Speed[1]);
	PIDInit_Speed(&PID_Speed[2]);
	PIDInit_Speed(&PID_Speed[3]);
	PIDInit_Position(&PID_Position[0]);
	PIDInit_Position(&PID_Position[1]);
	PIDInit_Position(&PID_Position[2]);
	PIDInit_Position(&PID_Position[3]);
	PIDInit_YawControl(&PID_YawControl);
	PIDInit_BodanMotor(&PID_BodanMotor);
	RCInit();
	AutoControlInit();
	
	/* 外设初始化 */
	SystemConfiguration();
	
	TB[0] = '!';
	TB[1] = '0';
	TB[2] = 0x55;
	TB[3] = 0x55;
	TB[4] = 0x55;
	TB[5] = 0x55;
	TB[TBPackSize-1] = '#';
	
	CountForStatus = -2;
	
	while(1)
	{	
		switch(CountForStatus)
		{
			case -2:
				delay_ms(1000);
				CountForStatus =  -1;
				break;
			
			case -1:
				for(CountForAction = 0; CountForAction < 3000; CountForAction++)
				{
					delay_ms(1);
					Pos2 = Pos2OriDistance;
					Pos1 = Pos1OriDistance;
				}
				PID_BodanMotor.SetPoint = BodanRightPos;
				while(abs(PID_BodanMotor.SetPoint - BodanMotorPos()) > 70);
				CountForStatus =  0;
				break;
			
			case 0://Ready
				if(RC_Ctl.rc.s2 == 1)
				{
					/* 速度环PID控制 */
					if(RC_Ctl.rc.s1 == 1)
					{
						MECANUM_MOVE(&SpeedSet,-offset_0(),-offset_1(),offset_2());
					}
					else if(RC_Ctl.rc.s1 == 2)
					{
						MECANUM_MOVE(&SpeedSet,-(AutoControl.X_Auto-1024.0f)/660.0f*MAXSPEED,
											-(AutoControl.Y_Auto-1024.0f)/660.0f*MAXSPEED,
											(AutoControl.Yaw_Auto-1024.0f)/660.0f*MAXSPEED);
						
						if(AutoControl.Grab_Auto == 1)
						{
							if(CountForWall > 3)
							{
								CountForStatus =  1;
							}
							else
							{
								MECANUM_MOVE(&SpeedSet,16,0,0);
								delay_ms(100);
								CountForStatus =  7;
								CountForWall++;
							}
							TB[1] = '1';
							MECANUM_MOVE(&SpeedSet,0,0,0);
							CAN2MotorSpeedSet(0, 0, 0, 0);
							delay_ms(500);
						}
					}
				}
				break;
				
			case 1://向前走
				MECANUM_MOVE(&SpeedSet,0,-14,0);
				if(test3&&test4)		CountForStatus = 4;
				else if(test3)			CountForStatus = 2;
				else if(test4)			CountForStatus = 3;
				else 								CountForStatus = 1;
				break;
				
			case 2://判断右侧开关
				MECANUM_MOVE(&SpeedSet,0,0,4);
				if(test3&&test4)		CountForStatus = 4;
				else if(test3)			CountForStatus = 2;
				else if(test4)			CountForStatus = 3;
				else 								CountForStatus = 1;
				break;
				
			case 3://判断左侧开关
				MECANUM_MOVE(&SpeedSet,0,0,-4);
				if(test3&&test4)		CountForStatus = 4;
				else if(test3)			CountForStatus = 2;
				else if(test4)			CountForStatus = 3;
				else 								CountForStatus = 1;
				break;
				
			case 4://开关判决1
				delay_ms(500);
				if(test3&&test4)		CountForStatus = 5;
				else if(test3)			CountForStatus = 2;
				else if(test4)			CountForStatus = 3;
				else								CountForStatus = 1;
				break;
			
			case 5://开关判决2
				delay_ms(500);
				if(test3&&test4)		CountForStatus = 6;
				else if(test3)			CountForStatus = 2;
				else if(test4)			CountForStatus = 3;
				else								CountForStatus = 1;
				break;
			
			case 6://保持静止
				MECANUM_MOVE(&SpeedSet,0,0,0);
				delay_ms(100);
				CountForStatus = 20;
				break;
			
			case 7://向前走
				MECANUM_MOVE(&SpeedSet,0,-14,0);
				if(test3||test4)		CountForStatus = 8;
				else 								CountForStatus = 7;
				break;
			
			case 8://开关判决
				delay_ms(500);
				if(test3||test4)		CountForStatus = 6;
				else 								CountForStatus = 7;
				break;
			
			case 20://放下机械臂
				for(CountForAction = 0; CountForAction < 600; CountForAction++)
				{
					delay_ms(2);
					Pos1 = Pos1MaxDistance;
					Pos2 = Pos2MinDistance;
				}
				CountForStatus = 21;
				break;
				
			case 21://向左轮询公仔
				for(CountForAction = 0; CountForAction < BodanRoad; CountForAction++)
				{
					delay_us(500);
					Pos1 = Pos1MaxDistance;
					PID_BodanMotor.SetPoint += 1;
					if(test1 || test2)
					{
						delay_ms(100);
						CountForStatus = 22;
						break;
					}
				}
				CountForStatus = 22;
				break;
			
			case 22://抓住公仔
				for(CountForAction = 0; CountForAction < 300; CountForAction++)
				{
					delay_ms(1);
					Pos1 = Pos1MinDistance;
				}
				CountForStatus = 23;
				break;
				
			case 23://拔起公仔	
				for(CountForAction = 0; CountForAction < 600; CountForAction++)
				{
					delay_ms(1);
					Pos2 = Pos2OriDistance;
				}
				CountForStatus = 24;
				break;
				
			case 24://机械臂归位
				PID_BodanMotor.SetPoint = 32767;
				while(abs(PID_BodanMotor.SetPoint - BodanMotorPos()) > 70);
				CountForStatus = 25;
				break;
			
			case 25://机械臂翻转
				for(CountForAction = 0; CountForAction < 3500; CountForAction++)
				{
					delay_ms(1);
					Pos2 = Pos2MaxDistance;
				}
				CountForStatus = 40;
				TB[1] = '2';
				break;
				
			case 40:
				if(RC_Ctl.rc.s2 == 1)
				{
					/* 速度环PID控制 */
					if(RC_Ctl.rc.s1 == 1)
					{
						MECANUM_MOVE(&SpeedSet,-offset_0(),-offset_1(),offset_2());
					}
					else if(RC_Ctl.rc.s1 == 2)
					{
						MECANUM_MOVE(&SpeedSet,-(AutoControl.X_Auto-1024.0f)/660.0f*MAXSPEED,
											-(AutoControl.Y_Auto-1024.0f)/660.0f*MAXSPEED,
											(AutoControl.Yaw_Auto-1024.0f)/660.0f*MAXSPEED);
					}
				}
				
				if(AutoControl.Finished == 1)
				{
					for(CountForAction = 0; CountForAction < 300; CountForAction++)
					{
						delay_ms(1);
						Pos1 = Pos1MaxDistance;
					}
					TB[1] = '3';
					break;
				}
				else if(AutoControl.Finished == 2)
				{
					TB[1] = '0';
					CountForStatus = -1;
				}
				break;
				
			default:
				MECANUM_MOVE(&SpeedSet,0,0,0);
				break;
		}
		
		/* 其他控制模式初始化 */
		if(RC_Ctl.rc.s2 == 1)
		{
			if(RC_Ctl.rc.s1 == 1)
			{
				PID_Position[0].SetPoint = 0;
				PID_Position[1].SetPoint = 0;
				PID_Position[2].SetPoint = 0;
				PID_Position[3].SetPoint = 0;
				ENCODER_CAN[0].SumEncoder = 0;
				ENCODER_CAN[1].SumEncoder = 0;
				ENCODER_CAN[2].SumEncoder = 0;
				ENCODER_CAN[3].SumEncoder = 0;
			}
			if(RC_Ctl.rc.s1 == 3)
			{
				PID_Speed[0].SetPoint = 0;
				PID_Speed[1].SetPoint = 0;
				PID_Speed[2].SetPoint = 0;
				PID_Speed[3].SetPoint = 0;
				AutoControlInit();
			}
			else
			{
				PID_Position[0].SetPoint = 0;
				PID_Position[1].SetPoint = 0;
				PID_Position[2].SetPoint = 0;
				PID_Position[3].SetPoint = 0;
				ENCODER_CAN[0].SumEncoder = 0;
				ENCODER_CAN[1].SumEncoder = 0;
				ENCODER_CAN[2].SumEncoder = 0;
				ENCODER_CAN[3].SumEncoder = 0;
			}
		}
	}
}


void SystemConfiguration(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	LED_Configuration();   				
	USART1_Configuration();				//DBUS
	USART2_Configuration();				//ZIGBEE
	USART3_Configuration();				//PC
	UART4_Configuration();				//MPU6050
	CAN1_Configuration();	
	CAN2_Configuration();			
	BODAN_Configuration();			  
	SWITCH_Configuration();	
	RubWheelPWMConfiguration();
	
	SysTick_Config(168000);
}


void SysTick_Handler(void)
{
	/* 初始化中………… */
	if(CountForSystick < 1500)
	{
		CountForSystick++;
		EncoderUpdate(&ENCODER_CAN[0],HG900MotorData[0].Angle);
		EncoderUpdate(&ENCODER_CAN[1],HG900MotorData[1].Angle);
		EncoderUpdate(&ENCODER_CAN[2],HG900MotorData[2].Angle);
		EncoderUpdate(&ENCODER_CAN[3],HG900MotorData[3].Angle);
		ENCODER_CAN[0].SumEncoder = 0;
		ENCODER_CAN[1].SumEncoder = 0;
		ENCODER_CAN[2].SumEncoder = 0;
		ENCODER_CAN[3].SumEncoder = 0;
		ENCODER_CAN[0].DistanceFromEncoder = 0;
		ENCODER_CAN[1].DistanceFromEncoder = 0;
		ENCODER_CAN[2].DistanceFromEncoder = 0;
		ENCODER_CAN[3].DistanceFromEncoder = 0;
		SpeedSend[0] = PIDCalc(&PID_Position[0], ENCODER_CAN[0].SumEncoder);
		SpeedSend[1] = PIDCalc(&PID_Position[1], ENCODER_CAN[1].SumEncoder);
		SpeedSend[2] = PIDCalc(&PID_Position[2], ENCODER_CAN[2].SumEncoder);
		SpeedSend[3] = PIDCalc(&PID_Position[3], ENCODER_CAN[3].SumEncoder);
		CAN2MotorSpeedSet(SpeedSend[0], SpeedSend[1], SpeedSend[2], SpeedSend[3]);
		return;
	}
	
	/* 编码器更新 */
	EncoderUpdate(&ENCODER_CAN[0],HG900MotorData[0].Angle);
	EncoderUpdate(&ENCODER_CAN[1],HG900MotorData[1].Angle);
	EncoderUpdate(&ENCODER_CAN[2],HG900MotorData[2].Angle);
	EncoderUpdate(&ENCODER_CAN[3],HG900MotorData[3].Angle);
	
	BodanMotorSpeed(-PIDCalc(&PID_BodanMotor, BodanMotorPos()));
	//BodanMotorSpeed(0);
	
	if(RC_Ctl.rc.s2 == 1)
	{
		/* 速度环PID控制 */
		if(RC_Ctl.rc.s1 == 1)
		{
			PID_Speed[0].SetPoint = SpeedSet.RightSpeed_1*0.16;
			PID_Speed[1].SetPoint = -SpeedSet.LeftSpeed_1*0.16;
			PID_Speed[2].SetPoint = -SpeedSet.LeftSpeed_2*0.16;
			PID_Speed[3].SetPoint = SpeedSet.RightSpeed_2*0.16;
			SpeedSend[0] += PIDCalc(&PID_Speed[0], ENCODER_CAN[0].DifferEncoder);
			SpeedSend[1] += PIDCalc(&PID_Speed[1], ENCODER_CAN[1].DifferEncoder);
			SpeedSend[2] += PIDCalc(&PID_Speed[2], ENCODER_CAN[2].DifferEncoder);
			SpeedSend[3] += PIDCalc(&PID_Speed[3], ENCODER_CAN[3].DifferEncoder);
			CAN2MotorSpeedSet(SpeedSend[0], SpeedSend[1], SpeedSend[2], SpeedSend[3]);
		}
		
		/* 位置环PID控制 */
		else if(RC_Ctl.rc.s1 == 3)
		{
			SpeedSend[0] = PIDCalc(&PID_Position[0], ENCODER_CAN[0].SumEncoder);
			SpeedSend[1] = PIDCalc(&PID_Position[1], ENCODER_CAN[1].SumEncoder);
			SpeedSend[2] = PIDCalc(&PID_Position[2], ENCODER_CAN[2].SumEncoder);
			SpeedSend[3] = PIDCalc(&PID_Position[3], ENCODER_CAN[3].SumEncoder);
			CAN2MotorSpeedSet(SpeedSend[0], SpeedSend[1], SpeedSend[2], SpeedSend[3]);
		}
		
		/* PC自动控制
			 PID速度环控制 */
		else if(RC_Ctl.rc.s1 == 2)
		{
			if(AutoControl.Yaw_Reset==1)
			{
				AutoControl.Yaw_Auto = -PIDCalc(&PID_YawControl, gyro.YAW - YawOffset) + 1024;
			}
			else if(AutoControl.Yaw_Reset==2)
			{
				AutoControl.Yaw_Auto = -PIDCalc(&PID_YawControl, gyro.YAW) + 1024;
			}
			else
			{
				AutoControl.Yaw_Auto = 1024;
			}
			//AutoControl.Slide_Auto = LIMIT_MIN_MAX((short)AutoControl.Slide_Auto, -30, 30);
			PID_Speed[0].SetPoint = SpeedSet.RightSpeed_1*0.1;
			PID_Speed[1].SetPoint = -SpeedSet.LeftSpeed_1*0.1;
			PID_Speed[2].SetPoint = -SpeedSet.LeftSpeed_2*0.1;
			PID_Speed[3].SetPoint = SpeedSet.RightSpeed_2*0.1;
			SpeedSend[0] += PIDCalc(&PID_Speed[0], ENCODER_CAN[0].DifferEncoder);
			SpeedSend[1] += PIDCalc(&PID_Speed[1], ENCODER_CAN[1].DifferEncoder);
			SpeedSend[2] += PIDCalc(&PID_Speed[2], ENCODER_CAN[2].DifferEncoder);
			SpeedSend[3] += PIDCalc(&PID_Speed[3], ENCODER_CAN[3].DifferEncoder);
			CAN2MotorSpeedSet(SpeedSend[0], SpeedSend[1], SpeedSend[2], SpeedSend[3]);
		}
			else
		{
			CAN2MotorSpeedSet(0, 0, 0, 0);
		}
	}
	/* 预防乱码炸车 */
	else
	{
		CAN2MotorSpeedSet(0, 0, 0, 0);
	}
	
//-----------------------------------50ms--------------------------------------------	

	if(ms50 <= 50)	ms50 ++;
	{
		ms50 = 0;	
		
		if(RC_Ctl.rc.s2 == 3 && RC_Ctl.rc.s1 != 2)
		{
			Pos1 += (abs(RC_Ctl.rc.ch3-1024)<100 ? 0 : (RC_Ctl.rc.ch3-1024)*0.005);
			Pos2 += (abs(RC_Ctl.rc.ch1-1024)<100 ? 0 : (RC_Ctl.rc.ch1-1024)*0.005);
		}
		
		Pos1 = LIMIT_MIN_MAX(Pos1, PosLast1-Pos1ChangeMax, PosLast1+Pos1ChangeMax);
		Pos2 = LIMIT_MIN_MAX(Pos2, PosLast2-Pos2ChangeMax, PosLast2+Pos2ChangeMax);
		
		Pos1 = LIMIT_MIN_MAX(Pos1, Pos1MaxDistance, Pos1MinDistance);
		Pos2 = LIMIT_MIN_MAX(Pos2, Pos2MinDistance, Pos2MaxDistance);
		
		PosLast1 = Pos1;
		PosLast2 = Pos2;
	}

//-----------------------------------10ms--------------------------------------------
	
	if(ms10 <= 10)	ms10 ++;
	else 			
	{
		ms10 = 0;
		CountForPC++;
		if(CountForPC > 10)
		{
			AutoControlInit();
		}
		
		CAN1SendMessage(Pos1, 3200 - Pos1, 3400 - Pos1);
		TIM_SetCompare1(TIM8,Pos2);
		if(RC_Ctl.rc.s2 == 3)
		{
			PID_BodanMotor.SetPoint += RC_Ctl.rc.ch0>1354?-9:(RC_Ctl.rc.ch0<694?9:0);
		}
	}


//-----------------------------------500ms--------------------------------------------
	
	if(ms500 <= 500)	ms500 ++;
	else
	{
		ms500 = 0;
		
		if(RC_Ctl.rc.s2 == 1)
		{
		/* 位置环PID控制 */
			if(RC_Ctl.rc.s1 == 3)
			{
				MECANUM_MOVE(&SpeedSet,-(RC_Ctl.rc.ch0>1354?8192:(RC_Ctl.rc.ch0<694?-8192:0)),
															-(RC_Ctl.rc.ch1>1354?8192:(RC_Ctl.rc.ch1<694?-8192:0)),
															(RC_Ctl.rc.ch2>1354?4096:(RC_Ctl.rc.ch2<694?-4096:0)));
				PID_Position[0].SetPoint += SpeedSet.RightSpeed_1;
				PID_Position[1].SetPoint += -SpeedSet.LeftSpeed_1;
				PID_Position[2].SetPoint += -SpeedSet.LeftSpeed_2;
				PID_Position[3].SetPoint += SpeedSet.RightSpeed_2;
			}
		}
	}
}
