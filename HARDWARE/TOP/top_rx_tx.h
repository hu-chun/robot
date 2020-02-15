#ifndef __TOP_RX_TX_H
#define __TOP_RX_TX_H
#include "sys.h"
#define GD_FLAG  0X51
#define A_CLAW   0X52
#define B_CLAW   0X53
#define C1_CLAW  0X54
#define C2_CLAW  0X55
typedef enum
{
	CLAW_OPEN = 1,
	CLAW_CLOSE = 0,
}CLAW_SW; 

typedef enum
{
	CLAW_A,
	CLAW_B,
	CLAW_C1,
	CLAW_C2,
	
}CLAW_X;

typedef struct CLAW_STATUS  //×¦×Ó×´Ì¬
{
	u16 TOP_GD;
	u8 A_FLAG;
	u8 B_FLAG;
	u8 C1_FLAG;
	u8 C2_FLAG;
	
	
}CLAW_STATUS;

void claw_control(u8 claw_x,CLAW_SW claw_sw);
void gd_control(u8 high);
#endif
