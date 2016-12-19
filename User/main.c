//BEGIN
#include "stm32f4xx.h"
#include "periph_init.h"
#include "interrupt_heandler.h"
#include "functions.h"

//*********************************************************************************************************
//VARIABLES
//*********************************************************************************************************

uint8_t buffer[256] = {0}; 																	//Buffer priema
uint8_t receive_write=0, receive_read=0, receive_count=0; 	//Ukazatel na mesto dlya zapisi dannih v bufer
uint8_t command, data; 																			//Peremennaya dlya comand, dlya dannih i peremennaya, skolco gorit/negorit svetodiod
uint8_t state = 0;																					//Id sostoyaniya sistemi
uint32_t delay = 0;																					//Timeout dlya sostoyaniya




//*********************************************************************************************************
//MAIN
//*********************************************************************************************************
int main(void)
{
		Periph_init();

		while(1)
		{
			switch (state){
				case 0x00:
				{
					while (receive_count < 2);
					read_bufer();
					if (command == 0x00 && data == 0x00)
					{
						GPIO_ResetBits(GPIOD, GPIO_Pin_14);
						state = 0x01;
					}
					break;
				}

//BEGIN end

//COMPILE PART:
case 1:
{
delay = 1400;
while (receive_count < 2);
read_bufer();
if (!(command == 0xFF && (data == 2)))
{
 error();
 break;
}
state = data;
break;
}
case 2:
{
delay = 1500;
while (receive_count < 2);
read_bufer();
if (!(command == 1 && (data == 1)))
{
 error();
 break;
}
blink_LED();
while (receive_count < 2);
read_bufer();
if (!(command == 0xFF && (data == 2 || data == 3)))
{
 error();
 break;
}
state = data;
break;
}
case 3:
{
delay = 1500;
while (receive_count < 2);
read_bufer();
if (!(command == 2 && (data > 5)))
{
 error();
 break;
}
blink_LED();
while (receive_count < 2);
read_bufer();
if (!(command == 0xFF && (data == 1 || data == 2)))
{
 error();
 break;
}
state = data;
break;
}
//COMPILE PART end

//END				
				default:
					error();
			}	
		}
}
//END end
