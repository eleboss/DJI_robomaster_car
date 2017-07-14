#include "main.h"

void BEEP_Configuration(void)
{
    GPIO_InitTypeDef gpio;   

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
		
		gpio.GPIO_Pin = GPIO_Pin_12 ;	
		gpio.GPIO_Mode = GPIO_Mode_Out_PP;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &gpio); 	
}

void Beep(int BeepMode)
{
		int j=0;
		switch(BeepMode)
		{
			case BEEP_SystemOK:
					BEEP_ON();
					delay_ms(500);
					BEEP_OFF() ;
				break;
			case BEEP_ACK:
					BEEP_ON();
					delay_ms(40);
					BEEP_OFF() ;
				break;
			case BEEP_SystemError:
					
				break;
			case BEEP_MotorReady:
				for(j=0;j<3;j++)
				{
					BEEP_ON();
					delay_ms(50);
					BEEP_OFF() ;
					delay_ms(50);
				}
				break;
			case BEEP_CANError:
				break;
			case BEEP_EncoderError:
				break;
		}
}
