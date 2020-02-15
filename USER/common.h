#ifndef __COMMON_H
#define __COMMON_H

#include "stdio.h"
#include "sys.h"
#include "delay.h" 
#include "led.h"        //led灯
#include "key.h"		//按键
#include "TIMES.h"		//定时器
#include "oled.h"		//显示
#include "EXIT.h"		//外部中断
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



#define  Shou_or_Computer_uart    	1       //0;连手机9600，1：连电脑115200
#define  Cmera_uart     	 	 	1       //1:摄像头模块以装好，0：暂无摄像头
#define  TopBoard_uart				1		//1:顶板已装好，0：暂无顶板
extern MAP_struct	MAP_data;				//定位数据
extern Color_struct COLOR_READ;				//摄像头数据
extern TARGET_struct TARGET_READ;			//摄像头数据
extern TARGET_struct2 TARGET_READ2;
extern CLAW_STATUS TOP_STATUS;
//extern WHEEL_SPEED  EIT_ROBOT;					//电机速度
extern ULTRSONIC_DATA ULTRSONIC_DIS;
extern uint16_t USED_TIME;					//定时计数
extern u8 A_CRAW_NUMBER;         //监控爪子的个数
extern u8 B_CRAW_NUMBER;
extern u8 C_CRAW_NUMBER;

void Peripherals_init(void);

#endif
