#ifndef __CAN2_H__
#define __CAN2_H__

#define CAN_ID_SPEED_MODE_ALL        0x04 //speed mode
#define CAN_ID_SPEED_MODE_NUM01      0x14
#define CAN_ID_SPEED_MODE_NUM02      0x24
#define CAN_ID_SPEED_MODE_NUM03      0x34
#define CAN_ID_SPEED_MODE_NUM04      0x44
#define CAN_ID_SPEED_MODE_NUM05      0x54
#define CAN_ID_SPEED_MODE_NUM06      0x64
#define CAN_ID_SPEED_MODE_NUM07      0x74
#define CAN_ID_SPEED_MODE_NUM08      0x84
#define CAN_ID_SPEED_MODE_NUM09      0x94
#define CAN_ID_SPEED_MODE_NUM10      0xA4
#define CAN_ID_SPEED_MODE_NUM11      0xB4
#define CAN_ID_SPEED_MODE_NUM12      0xC4
#define CAN_ID_SPEED_MODE_NUM13      0xD4
#define CAN_ID_SPEED_MODE_NUM14      0xE4
#define CAN_ID_SPEED_MODE_NUM15      0xF4

#define LimitedSpeed 4000

typedef struct{
	unsigned short Angle;//0~8191(0x1fff)
	short RealCurrent;//-13000~13000
	short Current;
	short Hall;//1~6
}HG900MotorRecvmsg;

void CAN1_Configuration(void);
void CAN1MotorSpeedSet(int speed1,int speed2,int speed3,int speed4);
#endif 
