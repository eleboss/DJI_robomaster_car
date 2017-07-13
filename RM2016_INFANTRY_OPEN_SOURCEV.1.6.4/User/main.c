#include "main.h"
uint32_t Upload_Speed = 1;   //数据上传速度  单位 Hz
#define upload_time (1000000/Upload_Speed)  //计算上传的时间。单位为us   可以通过调整赫兹来改变上传速度，现在是1HZ对应1S上传一次
uint16_t  power1=0,power2=0;
uint32_t system_micrsecond;   //系统时间 单位ms
int main(void)
{     			
	ControtLoopTaskInit();   //app init
	RemoteTaskInit();
	delay_ms(800);     
	BSP_Init();	//Board support 
	system_micrsecond = Get_Time_Micros();				
	while(1)
	{   
		IMU_getYawPitchRoll(angle);
		if((Get_Time_Micros() - system_micrsecond) > upload_time)//如果大于上传时间，就上传一次参数
		{
			system_micrsecond = Get_Time_Micros();
			UploadParameter();   //upload data to the PC			
			delay_ms(1);//上传结束后延时1S
		}
    }
}
