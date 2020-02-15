
#ifndef __CRARMANGER_H
#define __CRARMANGER_H
#include "common.h"
typedef enum
{
	a_craw,
	b_craw,
	c_craw,
}craw_w;

typedef enum
{
	FANG,
	ZHUA,
}craw_MODE;

void CRAW_INPUT(craw_w CRAW,craw_MODE mode,u8 num);
u8 PUT_BAMBOO(craw_w SIDE_X,u8 Dis,u8 min_gd,u8 out_gd);    //CRAW_X:那个爪子  Dis：靠近的距离  min_gd:下降的高度放  out_gd：提升的高度抓
//SIDE_X ：那个爪，Dis：距离 init_dis：高度是的高度  min_gd;下降的高度 out_dis：退出时的高度
u8 GRAB_BAMBOO(craw_w SIDE_X,u8 Dis,u8 init_dis,u8 min_gd,u8 out_gd);  


#endif


