#include "main.h"

TIM_CAPTURE TIM5CH1;
TIM_CAPTURE TIM5CH3;
u32 temp=0;
void TIM5_Cap_Init(u32 arr,u16 psc)
{
GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_ICInitTypeDef TIM5_ICInitStructure;
NVIC_InitTypeDef NVIC_InitStructure;

RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE); //TIM5 ????
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //?? PORTA ??

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //GPIOA0
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//????
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //?? 100MHz
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //??????
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //??
GPIO_Init(GPIOA,&GPIO_InitStructure); //??? PA0

GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //PA0 ?????? 5

TIM_TimeBaseStructure.TIM_Prescaler=psc; //?????
TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
TIM_TimeBaseStructure.TIM_Period=arr; //??????
TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);

TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //????? IC1 ??? TI1 ?
TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; //?????
TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //??? TI1 ?
TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; //??????,???
TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ??????????
TIM_ICInit(TIM5, &TIM5_ICInitStructure); //??? TIM5 ??????

TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//?????????
TIM_Cmd(TIM5,ENABLE ); //????? 5

NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//????? 2
NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;//????? 0
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ ????
NVIC_Init(&NVIC_InitStructure); //?????????? VIC ????
}

void SingleChannelHandler(TIM_CAPTURE * tch )
{

	if((tch->CAPTURE_STA&0X80)==0)//还未成功捕获	
	{
		if(TIM_GetITStatus(tch->timX, TIM_IT_Update) != RESET)//溢出
		{	     
			if(tch->CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((tch->CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					tch->CAPTURE_STA|=0X80;		//标记成功捕获了一次
					tch->CAPTURE_VAL=0XFFFFFFFF;
				}else tch->CAPTURE_VAL++;
			}	 
		}
		if(TIM_GetITStatus(tch->timX, tch->TIM_IT_CCX) != RESET)//捕获1发生捕获事件
		{	
			if(tch->CAPTURE_STA&0X40)		//已经捕获到高电平，本次捕获到下降沿		
			{	  			
				tch->CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
			  //tch->CAPTURE_VAL=TIM_GetCapture1(tch->timX);//获取当前的捕获值.
				
				switch( tch->TIM_IT_CCX ) // 根据不同通道选择函数
				{
					case TIM_IT_CC1:						
						tch->CAPTURE_VAL=TIM_GetCapture1(tch->timX);//获取当前的捕获值.
						TIM_OC1PolarityConfig(tch->timX,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
						break;
					case TIM_IT_CC3:
						tch->CAPTURE_VAL=TIM_GetCapture3(tch->timX);//获取当前的捕获值.
						TIM_OC3PolarityConfig(tch->timX,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
						break;
					default:
						break;
				}
				//printf(" tch->TIM_IT_CCX = %d ",tch->TIM_IT_CCX); //打印总的高点平时间
	 			//TIM_OC1PolarityConfig(tch->timX,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获

			}
			else  								//还未开始,第一次捕获上升沿
			{
				tch->CAPTURE_STA=0;			//清空
				tch->CAPTURE_VAL=0;
				tch->CAPTURE_STA|= 0X40;		//标记捕获到了上升沿
				TIM_Cmd(tch->timX,DISABLE ); 	//关闭定时器
	 			TIM_SetCounter(tch->timX,0);
				
//				printf(" tch->CAPTURE_STA = %d ",tch->CAPTURE_STA); //打印总的高点平时间
	 			//TIM_OC1PolarityConfig(tch->timX,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
				switch( tch->TIM_IT_CCX )
				{
					case TIM_IT_CC1:
						TIM_OC1PolarityConfig(tch->timX,TIM_ICPolarity_Falling); 
						break;
					case TIM_IT_CC3:
						TIM_OC3PolarityConfig(tch->timX,TIM_ICPolarity_Falling); 
						break;
					default:
						break;
				}
			
				TIM_Cmd(tch->timX,ENABLE ); 	//使能定时器s
			}		    
		}	
temp=	TIM5CH1.CAPTURE_VAL;
 	}
	TIM_ClearITPendingBit(tch->timX, tch->TIM_IT_CCX | TIM_IT_Update); //清除中断标志位
}
void TIM5_IRQHandler(void)
{ 
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update); //清除中断标志位
	if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET) 
   {								       
		  SingleChannelHandler( &TIM5CH1);
	 }
		if(TIM_GetITStatus(TIM5, TIM_IT_CC3) !=RESET) 
	 {								   
			SingleChannelHandler( &TIM5CH3); 
	 }
}


