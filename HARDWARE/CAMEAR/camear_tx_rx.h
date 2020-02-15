
#ifndef __CAMEAR_TX_RX_H
#define __CAMEAR_TX_RX_H
#include "sys.h"
#define red_color    11
#define greed_color  22
#define blue_color   33
#define dont_color	 44
#define BAM_BOO 		 55
#define LAND_MARK     66

typedef struct Color_struct
{
	char hord;			//地标还是竹子
	char bottom;		//第一层
	char middle;
	char top; 
}Color_struct;
typedef enum
{
	OV_TARGET,
	OV_COLOR,
	OV_CHOOSE,
}ov_mode;

typedef enum
{
	TARGET_RED = 'R',
	TARGET_GREED = 'G',
	TARGET_BLUE = 'B',
}TARGET_COLOR;	

typedef struct
{
	u16 object_x;
	u16 object_y;
	u16 object_w;
	u16 object_h;
}TARGET_struct;
typedef struct
{
	u16 object_x;
	u16 object_y;
	u16 object_w;
	u16 object_h;
}TARGET_struct2;
void camear_cmd(ov_mode mode);
void camear_color(TARGET_COLOR target_color);
#endif


