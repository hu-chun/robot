#ifndef __TIMES_H
#define __TIMES_H

#include "sys.h"

#define  ADV_TIM     		1
#define  GENERL_TIM  		2
#define  BASIC_TIM	 		3

typedef enum
{
	TIME_1,
	TIME_2,
	TIME_3,
	TIME_4,
	TIME_5,
	TIME_6,
	TIME_7,
	TIME_8,
	TIME_9,
	TIME_10,
	TIME_11,
	TIME_12,
	TIME_13,
	TIME_14,
} TIME_CH;

void TIMERx_init(TIME_CH Tim_x,u16 arr,u16 psc);			//定时器初始化
#endif
