#include "main.h"
uint32_t Upload_Speed = 1;   //�����ϴ��ٶ�  ��λ Hz
#define upload_time (1000000/Upload_Speed)  //�����ϴ���ʱ�䡣��λΪus   ����ͨ�������������ı��ϴ��ٶȣ�������1HZ��Ӧ1S�ϴ�һ��
uint16_t  power1=0,power2=0;
uint32_t system_micrsecond;   //ϵͳʱ�� ��λms
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
		if((Get_Time_Micros() - system_micrsecond) > upload_time)//��������ϴ�ʱ�䣬���ϴ�һ�β���
		{
			system_micrsecond = Get_Time_Micros();
			UploadParameter();   //upload data to the PC			
			delay_ms(1);//�ϴ���������ʱ1S
		}
    }
}
