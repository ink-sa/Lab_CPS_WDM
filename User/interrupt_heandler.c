#include "stm32f4xx.h"
#include "interrupt_heandler.h"
#include "functions.h"
#include "main.h"
//*********************************************************************************************************
//TIM3 HEANDLER
//*********************************************************************************************************
void TIM3_IRQHandler(void) 
{ 
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //Proverca flaga prerivaniya po perepolneniyu
  { 
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 		 //Sbros flaga prerivaniya po perepolneniyu
		
		//Mesto dlya coda:
		if (delay > 1)
		{
			--delay;
		}
		else if (delay)
		{
			error();
		}				
  } 
} 



//*********************************************************************************************************
//SYSTIMER HEANDLER
//*********************************************************************************************************
void SysTick_Handler(void) 
{ 
	 
}

//*********************************************************************************************************
//USART1 IRQ HANDLER
//*********************************************************************************************************
void USART1_IRQHandler(void)
{
   if (USART_GetITStatus(USART1, USART_IT_TC) != RESET) //Esli otpravka zavershena
   {
      USART_ClearITPendingBit(USART1, USART_IT_TC); 		//Ochistit flag prerivaniya
        //Code po zaversheniyu otpravki:
   }
	 
	 if(USART_GetITStatus(USART1, USART_IT_RXNE)!=RESET) //Esli priem zavershena
   {
     USART_ClearITPendingBit(USART1, USART_IT_RXNE);
				//Code po zaversheniyu priema:
				buffer[receive_write] = USART_ReceiveData(USART1);//Zapis baita v bufer priema
				receive_write++; 
				receive_count++;			
   }
}



