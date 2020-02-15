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
	u16 number;				//���
	float X_coordinate;		//X����
	float Y_coordinate;		//Y����
	u8 Count;              //���õĵر����
}PANDA_bamboo;

typedef struct PANDA_landmark
{
	u16 number;				//���
	float X_coordinate;		//X����
	float Y_coordinate;		//Y����
}PANDA_landmark;
typedef struct PANDA_Transferpoint
{
	u16 number;				//���
	float X_coordinate;		//X����
	float Y_coordinate;		//Y����
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




