#include "stm32f4xx.h"

static GPIO_InitTypeDef GPIO_ini_struct;												//Structura dlya inicializacii porta GPIO
static USART_InitTypeDef USART_ini_struct;											//Structura dlya inicializacii USART
static TIM_TimeBaseInitTypeDef TIMER_ini_struct; 								//Structura dlya inicializacii taimera


void Periph_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);						//Vkluchit tactirovanie porta GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);					//Vkluchit tactirovanie USART1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  					//Vkluchenie tactirovania timera TIM3 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 					//Vkluchenie tactirovania shini s LED

//*********************************************************************************************************
//Nastroika USART1
//*********************************************************************************************************

	//Nastroika alternativnoi raboti vivodov porta
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);				//PB6 = USART1_TX
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);				//PB7 = USART1_RX


	//Zapolnenie poley structuri dlya nastroiki porta GPIOA i primenenie nastroek
	GPIO_ini_struct.GPIO_Pin = GPIO_Pin_6; 													//Vkluchenie PB6
	GPIO_ini_struct.GPIO_Mode = GPIO_Mode_AF;								  			//Rezim vivoda
	GPIO_ini_struct.GPIO_Speed = GPIO_Speed_50MHz;					  			//Skorost
	GPIO_ini_struct.GPIO_OType = GPIO_OType_PP; 										//Podtyagivanie,tolko dlya vivoda
	GPIO_ini_struct.GPIO_PuPd = GPIO_PuPd_UP;                 			//Tolko dlya vvoda, UP-podtyagivanie k pitaniyu

	GPIO_Init(GPIOB, &GPIO_ini_struct);

	GPIO_ini_struct.GPIO_Pin = GPIO_Pin_7; 													//Vkluchenie PB7
	GPIO_Init(GPIOB, &GPIO_ini_struct);


	USART_ini_struct.USART_BaudRate = 115200; 										  //Skorost USART = 115200
	USART_ini_struct.USART_WordLength = USART_WordLength_8b; 				//Razmer posilki v 8 bit
	USART_ini_struct.USART_StopBits = USART_StopBits_1;							//Chislo Stop bit = 1 
	USART_ini_struct.USART_Parity = USART_Parity_No;								//Bit chetnosti - net 
	USART_ini_struct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;			//USART na priem i peredachu
	USART_ini_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 	//Otcluchit apparatnoie upravlenie potokom

	USART_Init(USART1, &USART_ini_struct);													//USART1 configuration

	NVIC_EnableIRQ(USART1_IRQn);																		//Razreshit prerivaniya ot USART1
	USART_ITConfig(USART1, USART_IT_TC, ENABLE); 										//Razreshit prerivanie po okonchanii peredachi
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 									//Razreshit prerivanie po okonchanii priema

	USART_Cmd(USART1, ENABLE);																			//Enable USART1 
//*********************************************************************************************************
//Nastroika USART1 END
//*********************************************************************************************************


//*********************************************************************************************************
//Nastroika LED
//*********************************************************************************************************
	GPIO_ini_struct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15; 					//Vkluchenie LED GREEN & RED
	GPIO_ini_struct.GPIO_Mode = GPIO_Mode_OUT;																				
	GPIO_ini_struct.GPIO_Speed = GPIO_Speed_2MHz;																		
	GPIO_ini_struct.GPIO_OType = GPIO_OType_PP; 																			
	GPIO_Init(GPIOD, &GPIO_ini_struct);
//*********************************************************************************************************
//Nastroika LED END
//*********************************************************************************************************

//*********************************************************************************************************
//Nastroika SYS_TIM
//*********************************************************************************************************
	SysTick_Config(SystemCoreClock / 1000); //INICIALIZACIA SISTEMNOGO TAIMERA 1ms 1/1000Hz
//*********************************************************************************************************
//Nastroika SYS_TIM END
//*********************************************************************************************************

//*********************************************************************************************************
//Nastroika TIM_3
//*********************************************************************************************************
	TIMER_ini_struct.TIM_Prescaler = 4-1; 								  // Delim PCLK1 na 4: 20 000 000 Hz/4 = 5 000 000Hz
	TIMER_ini_struct.TIM_CounterMode = TIM_CounterMode_Up; 	// Nastraivaem schetchik na inkrement
	TIMER_ini_struct.TIM_Period = 5000;											// Delim 5 000 000Hz / 5000 = 1000 Hz T.e. 5000 otschetov po 5 000 000 Hz
	TIMER_ini_struct.TIM_ClockDivision = TIM_CKD_DIV1; 			// Vneshii delitel = 1 => 1000 Hz/1ms

	TIM_TimeBaseInit(TIM3, &TIMER_ini_struct); 

	NVIC_EnableIRQ(TIM3_IRQn);  														//Razreshit prerivanie ot taimera
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 							//Razreshit prerivanie po perepolneniu
	TIM_Cmd(TIM3, ENABLE);	
//*********************************************************************************************************
//Nastroika TIM_3 END
//*********************************************************************************************************
}

