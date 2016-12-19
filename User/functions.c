#include "functions.h"
#include "main.h"


//Otpravka baita v USART1
void send_to_USART1(uint8_t data)  
{ 
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)== RESET){} 			//Zdem zaversheniya otpravki prediduschego baita
		USART_SendData(USART1, data); 																		//peredat bayt data
}



void read_bufer(void)
{
	command = buffer[receive_read++]; 
	data = buffer[receive_read++]; 
	receive_count = receive_count - 2;	
}

void error(void)
{
	GPIO_SetBits(GPIOD, GPIO_Pin_14);
	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	receive_count = 0;
	receive_write = 0;
	receive_read = 0;
	delay = 0;
	state = 0x00;
	send_to_USART1(0x00);
	send_to_USART1(0xff);
}

void blink_LED(void)
{
	static int i = 0;
	if (i)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		i = 0;
	}
	else
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		i = 1;
	}
}

