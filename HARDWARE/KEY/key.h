#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 


/*����ķ�ʽ��ͨ��ֱ�Ӳ����⺯����ʽ��ȡIO*/
#define KEY1 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4) //PF1
#define KEY2 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5)	// 
#define KEY3 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6) //
#define KEY4 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7)	//


/*���淽ʽ��ͨ��λ��������ʽ��ȡIO*/
/*
#define KEY0 		PFin(4)   
#define KEY1 		PFin(5)		
#define KEY2 		PFin(6)		
#define KEY4 		PFin(7)		
*/


#define KEY0_PRES 	1
#define KEY1_PRES	2
#define KEY2_PRES	3
#define KEY4_PRES   4

void KEY_Init(void);	//IO��ʼ��
u8 KEY_Scan(u8);  		//����ɨ�躯��	

#endif
