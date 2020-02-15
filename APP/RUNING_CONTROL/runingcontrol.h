#ifndef __RUNING_CONTROL_H
#define __RUNING_CONTROL_H
#include "sys.h"
#include "common.h"
#include "crawmanger.h"
typedef enum
{
	Direction_A,
	Direction_B,
	Direction_C,
}robot_dir;
typedef enum
{
	a_side,
	b_side,
	c_side,
}side_w;
void Independ_run(float curret_x,float current_y,float aim_x,float aim_y);
u8 Close_proximity(robot_dir faxian);
u8 Close_move(robot_dir faxian,uint8_t min_dis);
u8 X_Y_ANGELE_AIM(float curren_x,float curren_y,int16_t curren_yaw,float aim_x,float aim_y,int16_t aim_yaw,uint16_t max_speed);
u8 Objective_cheak(u16 x, u16 y);   //目标判断
u8 Camear_control_init(void);
u8 Camear_control_run(u16 camear_dis);
u8 Camear_jiaozheng(void) ;       //摄像头反馈摆正车体
u8 Keep_distance(robot_dir faxian,uint16_t mim_dis);

#endif
