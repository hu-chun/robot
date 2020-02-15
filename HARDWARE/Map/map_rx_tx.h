#ifndef		__MAP_RX_TX_H
#define 	__MAP_RX_TX_H
#include "sys.h"
typedef struct MAP_struct
{
	float X;
	float Y;
	int	YAW; 
}MAP_struct;

typedef struct ULTRSONIC_DATA
{
	uint16_t  U_A1;
	uint16_t  U_A2;
	uint16_t  U_B1;
	uint16_t  U_B2;
	uint16_t  U_C1;
	uint16_t  U_C2;
}ULTRSONIC_DATA;
#endif
