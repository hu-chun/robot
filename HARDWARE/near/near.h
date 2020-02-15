
#ifndef __NEAR_H
#define __NEAR_H
#include "sys.h"

typedef enum
{
	near_A,
	near_B,
	near_C,
	
}NEAR_TYPl;

u8 near_read(NEAR_TYPl near_typ);
void near_inint(void);

#endif




