#ifndef __USART3_H__
#define __USART3_H__

typedef struct{
	struct
	{
		unsigned short ch0;
		unsigned short ch1;
		unsigned short ch2;
		unsigned short ch3;
		unsigned char s1;
		unsigned char s2;
	}rc;
	struct
	{
		short x;
		short y;
		short z;
		unsigned char press_l;
		unsigned char press_r;
	}mouse;
	struct
	{
		unsigned short v;
	}key;
}RC_Ctl_t;


void USART3_Configuration(void);

#endif
