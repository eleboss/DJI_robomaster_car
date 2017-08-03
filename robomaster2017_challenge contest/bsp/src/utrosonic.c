#include "main.h"

u16 Temperature = 0;
float Distance=0,FliterReturnData=0;
float FliterData[5];
u16 c=0,k=0;
//	�ӿ�˵�� 
//echo-PI9
//trig-PF10
//�ж����ȼ����а����޸�
//ʹ�����̣�
//1.���� Ult_Init()
//2.��ȡFliterReturnData���˲�������ݣ�  Distance��ԭʼ���ݣ�
//��д��Ա ����ʫ�� ת����ע��
/******��ֵ�˲�����********/
float GetMedianNum(float * bArray, u8 iFilterLen)  
{  
    int i,j;// �����ñ���  
    float bTemp;  
      
    // ð������ 
    for (j = 0; j < iFilterLen - 1; j ++)  
    {  
        for (i = 0; i < iFilterLen - j - 1; i ++)  
        {  
            if (bArray[i] > bArray[i + 1])  
            {  
                // ���� 
                bTemp = bArray[i];  
                bArray[i] = bArray[i + 1];  
                bArray[i + 1] = bTemp;  
            }  
        }  
    }   
    bTemp = bArray[(iFilterLen + 1) / 2];  


    return bTemp;  
}  
void Mid_Fliter(void)
{
			if(c>4) c=0;
			FliterData[c]=Distance;
			c++;
			if(c==4) FliterReturnData=GetMedianNum(FliterData,5);
}


/****** �������ӿڳ�ʼ�� ********/
void Ult_IO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOF,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOF,GPIO_Pin_10);
	
}

/****** �ⲿ�жϳ�ʼ�� ********/
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	Ult_IO_Init();	//�˴����ó�����IO�ĳ�ʼ������

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,GPIO_PinSource1);  
	EXTI_ClearITPendingBit(EXTI_Line1);       
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00;	//�ж����ȼ����������
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	
}
/****** ��������ʼ��********/
void Ult_Init()
{
	EXTIX_Init();
	UltrasonicWave_StartMeasure();	//����һ�γ�������Ϊ��ʼ
}



//Tout=((arr+1)*(psc+1)/Tclk)
//�¶Ȳ�����ʽ V=331.4 + 0.61 T ��T�����϶ȡ���25�ȣ�331.4+51*0.61=346.65m/s
void EXTI1_IRQHandler(void)//PTB12�ⲿ�жϺ���
{
	Delay_Us(10);
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1))
		{
			SystickCount0=0;
		}
		else
		{
			//������������þ���
			Distance=SystickCount0*0.173325;	//���Ϊ����
			Mid_Fliter();
			Delay_Ms(60);
			UltrasonicWave_StartMeasure();	//������һ�γ�����
		}
		
	}
	EXTI_ClearITPendingBit(EXTI_Line1); 	//����жϱ�־
}

void UltrasonicWave_StartMeasure(void)
{
	
  GPIO_SetBits(GPIOF,GPIO_Pin_10); 
  Delay_Us(100);                   //��ʱ20US
  GPIO_ResetBits(GPIOF,GPIO_Pin_10);
	
}
