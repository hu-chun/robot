#ifndef __MYUSART_H
#define __MYUSART_H
#include "sys.h"

typedef enum 
{
	USART_1,
	USART_2,
	USART_3,
	USART_4,
	USART_5,
	USART_6,
		
} USART_x;

void USART_INIT(USART_x usart,u32 bound);
void USART_Send_Char(USART_x usart_x,u8 ch);
void USART_Send_String(USART_x usart_x,uint8_t *str);
void USART_Send_Leng_String(USART_x usart_x,uint8_t *str,u8 leng);
void USART_SendWare(void *wareaddr,uint32_t waresize);
#endif
