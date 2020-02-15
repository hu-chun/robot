#ifndef __PANDA_H
#define __PANDA_H
#include "sys.h"

typedef enum
{
	TIME_YES,
	TIME_ON,
}TIME_FINISH;


typedef enum
{
	SLEF_EARA,
	PBLIC_EARA,
}EARA;

typedef enum
{
	LANDMARK,
	BAMBOO,
}AIM_TYPE;

typedef enum
{
	RED_party,
	GREED_party,
}R_Gparty;

typedef struct PANDA_bamboo
{
	u16 number;				//编号
	float X_coordinate;		//X坐标
	float Y_coordinate;		//Y坐标
	u8 Count;              //放置的地标个数
}PANDA_bamboo;

typedef struct PANDA_landmark
{
	u16 number;				//编号
	float X_coordinate;		//X坐标
	float Y_coordinate;		//Y坐标
}PANDA_landmark;
typedef struct PANDA_Transferpoint
{
	u16 number;				//编号
	float X_coordinate;		//X坐标
	float Y_coordinate;		//Y坐标
}PANDA_Transferpoint;
typedef enum
{
	R_party,
	G_party,
}COLOR_CHOOSE;

void SET_TIME2(u16 TIME_10ms);
TIME_FINISH CHEAK_TIMEFINISH2(void);
void PANDA_RED(void);
void PANDA_GREED(void);
void PANDA_INIT(COLOR_CHOOSE color_choose);


#endif




