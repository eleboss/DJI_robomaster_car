#include "main.h"

/*-----USART6_TX-----PG14-----*/
/*-----USART6_RX-----PG9-----*/


void USART6_Configuration(void)
{
    USART_InitTypeDef usart6;
    GPIO_InitTypeDef  gpio;
    NVIC_InitTypeDef  nvic;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);

    GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_USART6);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART6); 

    gpio.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_9;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOG,&gpio);

    usart6.USART_BaudRate = 115200;          // speed 10byte/ms
    usart6.USART_WordLength = USART_WordLength_8b;
    usart6.USART_StopBits = USART_StopBits_1;
    usart6.USART_Parity = USART_Parity_No;
    usart6.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
    usart6.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART6,&usart6);

    USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART6,ENABLE);

    nvic.NVIC_IRQChannel = USART6_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&nvic);
}

int fputc(int ch, FILE *f)
{
    while (USART_GetFlagStatus(USART6,USART_FLAG_TC) == RESET);
    USART_SendData(USART6, (uint8_t)ch);
    return ch;
}

void USART6_IRQHandler(void)
{
	static uint8_t i=0,rebuf[20]={0};
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)    //接收中断
	{
		rebuf[i++]=USART_ReceiveData(USART3);//读取串口数据，同时清接收标志
	}
}

