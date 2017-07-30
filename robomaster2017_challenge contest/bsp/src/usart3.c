#include "main.h"

/*-----USART3_TX-----PD8-----*/
/*-----USART3_RX-----PD9-----*/
u8 InfraredReceivedBuf[8]={0};
u32 InfraredDistance=0;



void USART3_Configuration(void)
{
    USART_InitTypeDef usart3;
    GPIO_InitTypeDef  gpio;
    NVIC_InitTypeDef  nvic;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);

    GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3); 

    gpio.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD,&gpio);

    usart3.USART_BaudRate = 9600;          // speed 10byte/ms
    usart3.USART_WordLength = USART_WordLength_8b;
    usart3.USART_StopBits = USART_StopBits_1;
    usart3.USART_Parity = USART_Parity_No;
    usart3.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
    usart3.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART3,&usart3);

    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART3,ENABLE);

    nvic.NVIC_IRQChannel = USART3_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&nvic);
}
//发送一个字节数据
//input:byte,待发送的数据
void USART3_send_byte(uint8_t byte)
{
	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);//等待发送完成
	USART3->DR=byte;	
}
//发送多字节数据+校验和
void USART_Send(uint8_t *Buffer, uint8_t Length)
{
	uint8_t i=0;
	while(i<Length)
	{
		if(i<(Length-1))
		Buffer[Length-1]+=Buffer[i];//累加Length-1前的数据
		USART3_send_byte(Buffer[i++]);
	}
}

void send_com(u8 data)
{
	u8 bytes[3]={0xEA};
	bytes[0]=0xA5;
	bytes[1]=data;//功能字节
	USART_Send(bytes,3);//发送帧头、功能字节、校验和
}

void Infraed_Configuration(void)
{
	USART3_Configuration();
	send_com(0x45);
}




void USART3_IRQHandler(void)
{
	static uint8_t i=0,rebuf[20]={0};
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)    //接收中断
	{
		rebuf[i++]=USART_ReceiveData(USART3);//读取串口数据，同时清接收标志
		if (rebuf[0]!=0x5A)//帧头不对
			i=0;	
		if ((i==2)&&(rebuf[1]!=0x5A))//帧头不对
			i=0;
		if(i>3)//i等于4时，已经接收到数据量字节rebuf[3]
		{
			if(i!=(rebuf[3]+5))//判断是否接收一帧数据完毕
				return;	
			switch(rebuf[2])//接收完毕后处理
			{
				case 0x15:
						memcpy(InfraredReceivedBuf,rebuf,8);//拷贝接收到的数据
						InfraredDistance=InfraredReceivedBuf[4]<<8|InfraredReceivedBuf[5];

					break;
			}
			i=0;//缓存清0
		}
	}
}

