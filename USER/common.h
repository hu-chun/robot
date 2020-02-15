#ifndef __COMMON_H
#define __COMMON_H

#include "stdio.h"
#include "sys.h"
#include "delay.h" 
#include "led.h"        //led��
#include "key.h"		//����
#include "TIMES.h"		//��ʱ��
#include "oled.h"		//��ʾ
#include "EXIT.h"		//�ⲿ�ж�
#include "myusart.h"
#include "PWM.h"
#include "encode.h"
#include "24l01.h"
#include "map_rx_tx.h"
#include "camear_tx_rx.h"
#include "top_rx_tx.h"
#include "near.h"
#include "RTC.h"

#include <math.h> 
#include "arm_math.h"  

#include "malloc.h"	 

#include "control.h"
#include "pid.h"
#include "besicmovement.h"
#include "runingcontrol.h"
#include "panda.h"
#include "remotecontrol.h"
#include "crawmanger.h"



#define  Shou_or_Computer_uart    	1       //0;���ֻ�9600��1��������115200
#define  Cmera_uart     	 	 	1       //1:����ͷģ����װ�ã�0����������ͷ
#define  TopBoard_uart				1		//1:������װ�ã�0�����޶���
extern MAP_struct	MAP_data;				//��λ����
extern Color_struct COLOR_READ;				//����ͷ����
extern TARGET_struct TARGET_READ;			//����ͷ����
extern TARGET_struct2 TARGET_READ2;
extern CLAW_STATUS TOP_STATUS;
//extern WHEEL_SPEED  EIT_ROBOT;					//����ٶ�
extern ULTRSONIC_DATA ULTRSONIC_DIS;
extern uint16_t USED_TIME;					//��ʱ����
extern u8 A_CRAW_NUMBER;         //���צ�ӵĸ���
extern u8 B_CRAW_NUMBER;
extern u8 C_CRAW_NUMBER;

void Peripherals_init(void);

#endif
