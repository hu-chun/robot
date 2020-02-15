#ifndef __TCS3200_H
#define __TCS3200_H
#include "sys.h"

//extern u16 Rgena,Ggena,Bgena;//���ڵ��ڰ�ƽ��
extern u16 Ramount,Gamount,Bamount;//���ڴ�Ŷ�ȡ��RGBֵ
extern u16 amount;//�жϼ���

typedef struct   
{
	u16 Rgena;
	u16 Ggena;
	u16 Bgena;
}_RGB;

extern _RGB RGB;

#define S0 PEout(5)
#define S1 PEout(6)
#define S2 PFout(2)
#define S3 PFout(3)
#define OUT PEin(4)

void TCS3200_Init(u8 s0,u8 s1);
void WhiteBalance(void);
u16 tcs3200_RED(void);
u16 tcs3200_GREEN(void);
u16 tcs3200_BLUE(void);
//int *RGBtoHSV(u8 RED,u8 GREEN,u8 BLUE);
//u16 Actualcolor(u8 RED,u8 GREEN,u8 BLUE);


#endif



