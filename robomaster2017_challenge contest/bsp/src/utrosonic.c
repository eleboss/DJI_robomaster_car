#include "main.h"

u16 Temperature = 0;
float Distance=0,FliterReturnData=0;
float FliterData[5];
u16 c=0,k=0;
//	接口说明 
//echo-PI9
//trig-PF10
//中断优先级自行按需修改
//使用流程：
//1.调用 Ult_Init()
//2.读取FliterReturnData（滤波后的数据）  Distance（原始数据）
//编写人员 ：林诗杰 转载请注明
/******中值滤波函数********/
float GetMedianNum(float * bArray, u8 iFilterLen)  
{  
    int i,j;// 交换用变量  
    float bTemp;  
      
    // 冒泡排序 
    for (j = 0; j < iFilterLen - 1; j ++)  
    {  
        for (i = 0; i < iFilterLen - j - 1; i ++)  
        {  
            if (bArray[i] > bArray[i + 1])  
            {  
                // 交换 
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


/****** 超声波接口初始化 ********/
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

/****** 外部中断初始化 ********/
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	Ult_IO_Init();	//此处调用超声波IO的初始化函数

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,GPIO_PinSource1);  
	EXTI_ClearITPendingBit(EXTI_Line1);       
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00;	//中断优先级，按需更改
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	
}
/****** 超声波初始化********/
void Ult_Init()
{
	EXTIX_Init();
	UltrasonicWave_StartMeasure();	//触发一次超声波作为开始
}



//Tout=((arr+1)*(psc+1)/Tclk)
//温度补偿公式 V=331.4 + 0.61 T ；T是摄氏度。用25度，331.4+51*0.61=346.65m/s
void EXTI1_IRQHandler(void)//PTB12外部中断函数
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
			//读超声波所测得距离
			Distance=SystickCount0*0.173325;	//结果为厘米
			Mid_Fliter();
			Delay_Ms(60);
			UltrasonicWave_StartMeasure();	//触发下一次超声波
		}
		
	}
	EXTI_ClearITPendingBit(EXTI_Line1); 	//清除中断标志
}

void UltrasonicWave_StartMeasure(void)
{
	
  GPIO_SetBits(GPIOF,GPIO_Pin_10); 
  Delay_Us(100);                   //延时20US
  GPIO_ResetBits(GPIOF,GPIO_Pin_10);
	
}
