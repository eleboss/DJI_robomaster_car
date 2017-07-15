#ifndef __CAN_H__
#define __CAN_H__

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

void CAN_Configuration(void);
void CANOnLineClaim(unsigned char switch1, unsigned char switch2, unsigned char switch3, unsigned char switch4);

#endif 
