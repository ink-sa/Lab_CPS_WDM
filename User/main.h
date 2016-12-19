#ifndef MAIN_H
#define MAIN_H

extern uint8_t buffer[]; 													//Buffer priema
extern uint8_t receive_write, receive_read, receive_count; 			//Ukazatel na mesto dlya zapisi dannih v bufer
extern uint8_t command, data; 										//Peremennaya dlya comand, dlya dannih i peremennaya, skolco gorit/negorit svetodiod
extern uint8_t state;															//Id sostoyaniya sistemi
extern uint32_t delay;														//Timeout dlya sostoyaniya


#endif
