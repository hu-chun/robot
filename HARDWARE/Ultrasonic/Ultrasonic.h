

#ifndef  __ULTRASONIC_H
#define  __ULTRASONIC_H
#include "sys.h"

typedef enum
{
	ULT_A,
	ULT_B,
	ULT_C,
	ULT_D,
	
}ULTRASIONIC_X;


#define 	TX_A   							GPIO_SetBits(GPIOD,GPIO_Pin_0);
#define 	UTX_A   						GPIO_ResetBits(GPIOD,GPIO_Pin_0);
#define 	TX_B   							GPIO_SetBits(GPIOD,GPIO_Pin_1);
#define 	UTX_B   						GPIO_ResetBits(GPIOD,GPIO_Pin_1);
#define 	TX_C   							GPIO_SetBits(GPIOD,GPIO_Pin_2);
#define 	UTX_C   						GPIO_ResetBits(GPIOD,GPIO_Pin_2);
#define 	TX_D   							GPIO_SetBits(GPIOD,GPIO_Pin_3);
#define 	UTX_D   						GPIO_ResetBits(GPIOD,GPIO_Pin_3);
void ULTRASIONIC_INIT(void);

void Ultragionic_init(ULTRASIONIC_X ult_x);
uint16_t read_distance(ULTRASIONIC_X ult_x);

float get_distance(u32 TIME);			//超声波函数 调用时需定义外部变量extern u32	TIME;


#endif
