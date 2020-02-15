
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
u8 PUT_BAMBOO(craw_w SIDE_X,u8 Dis,u8 min_gd,u8 out_gd);    //CRAW_X:�Ǹ�צ��  Dis�������ľ���  min_gd:�½��ĸ߶ȷ�  out_gd�������ĸ߶�ץ
//SIDE_X ���Ǹ�צ��Dis������ init_dis���߶��ǵĸ߶�  min_gd;�½��ĸ߶� out_dis���˳�ʱ�ĸ߶�
u8 GRAB_BAMBOO(craw_w SIDE_X,u8 Dis,u8 init_dis,u8 min_gd,u8 out_gd);  


#endif


