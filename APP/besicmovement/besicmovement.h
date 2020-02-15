#ifndef  __BESICMOVEMENT_H
#define  __BESICMOVEMENT_H
#include "common.h"
#define ALL_L 464.932

typedef enum
{
	RA_WHEEL,
	RA_SIDE,
	RB_WHEEL,
	RB_SIDE,
	RC_WHEEL,
	RC_SIDE
}ROATA_POINT;

void Runing_V_ST(int16_t V,int16_t jiaodu);    	 	//����ΪX,Y�����ٶ�,����������ת
void Runing_rotat(int16_t st);						//stΪһ����ת���ٽǶȣ�+��Ϊ��ʱ�룻-��Ϊ˳ʱ��
u8 Run_angle(int curren_angle,int aim_angle);		//δʵ��
void Run_X_Y(int16_t Vx,int16_t Vy);
void move_rotat(int16_t V,int16_t jiaodu,int16_t curren_angle,int16_t st);
void move_rotat_init(int16_t curren_angle);
u8 move_rotat_angle(int16_t V,int16_t jiaodu,int16_t curren_angle,int16_t aim_angle);
void ROAT_POINT(ROATA_POINT roata_point,int16_t speed); //��ĳ����ת+��Ϊ��ʱ�룻-��Ϊ˳ʱ��
u8 ROAT_AIMANGLE(ROATA_POINT roata_point,uint16_t curren_angle,int16_t aim_angle);
void move_X_Y_roata(int16_t Vx,int16_t Vy,int16_t curren_angle,int16_t st);
void Clear_VBB(int16_t curren_angle);
void SUM_YAW(int16_t curren_angle);                               //������ת�ǶȺ�
#endif
