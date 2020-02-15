
#include "besicmovement.h"
#include "common.h"
#include <math.h> 
#define Pi 3.141592
extern WHEEL_SPEED  EIT_ROBOT;					//机器人转态变量参数
void Runing_V_ST(int16_t V,int16_t jiaodu)     	//输入为X,Y方向速度,不能自身旋转
{
	int16_t Va;
	int16_t Vb;
	int16_t Vc;
	float hudu;
	hudu = 0.01745329*(jiaodu);
//	hudu = 0.01745329*(jiaodu+90);
//	Va = (int16_t)-V*arm_cos_f32(hudu);
//	Vb = (int16_t)(0.5*V*arm_cos_f32(hudu)-0.86602*V*arm_sin_f32(hudu));
//	Vc = (int16_t)(0.5*V*arm_cos_f32(hudu)+0.86602*V*arm_sin_f32(hudu));
//	EIT_ROBOT.wheel_aim_A = -Va;
//	EIT_ROBOT.wheel_aim_B = -Vb;
//	EIT_ROBOT.wheel_aim_C = -Vc;	
	Va = (int16_t)V*arm_cos_f32(hudu);
	Vb = (int16_t)V*arm_cos_f32(0.6666*Pi - hudu);
	Vc = (int16_t)V*arm_cos_f32(hudu - 0.3333*Pi);
	EIT_ROBOT.wheel_aim_A = Va;
	EIT_ROBOT.wheel_aim_B = Vb;
	EIT_ROBOT.wheel_aim_C = -Vc;
}

void Runing_rotat(int16_t st)
{
	float hudu;
	int16_t Va;
	int16_t Vb;
	int16_t Vc;
	hudu = 0.01745329*(st);
	Va = (int16_t)(hudu*464.932);
	Vb = (int16_t)(hudu*464.932);
	Vc = (int16_t)(hudu*464.932);
	EIT_ROBOT.wheel_aim_A = Va;
	EIT_ROBOT.wheel_aim_B = Vb;
	EIT_ROBOT.wheel_aim_C = Vc;
}

u8 Run_angle(int curren_angle,int aim_angle)
{
	u8 result = 0;
	int angle_cha = 0;
	//float *SPEED = 0;
	angle_cha = aim_angle - curren_angle;
	if(angle_cha <= -1800)
	{
		aim_angle = 3600 + aim_angle;					//重新计算目标角度
		angle_cha = aim_angle - curren_angle;			//更新差值
	}
	else if(angle_cha > 1800)
	{
		aim_angle = aim_angle - 3600;				//更新为负的角度
		angle_cha = aim_angle - curren_angle;
	}
	else
		;
	/*把差值绝对值，便于开方*/
	//if(angle_cha<0)
	//{
	//	*SPEED = -angle_cha;
	//}
	//arm_sqrt_f32(*SPEED, SPEED);
	if(angle_cha>=200&&angle_cha <=1800)
	{
		EIT_ROBOT.wheel_aim_A = 900;
		EIT_ROBOT.wheel_aim_B = 900;
		EIT_ROBOT.wheel_aim_C = 900;
	}
	else if(angle_cha >= -1800&&angle_cha <= -200)
	{
		EIT_ROBOT.wheel_aim_A = -900;
		EIT_ROBOT.wheel_aim_B = -900;
		EIT_ROBOT.wheel_aim_C = -900;
	}
	else if(angle_cha>=8&&angle_cha <200)
	{
		EIT_ROBOT.wheel_aim_A = 150;
		EIT_ROBOT.wheel_aim_B = 150;
		EIT_ROBOT.wheel_aim_C = 150;
	}
	else if(angle_cha>=-200&&angle_cha <=-8)
	{
		EIT_ROBOT.wheel_aim_A = -150;
		EIT_ROBOT.wheel_aim_B = -150;
		EIT_ROBOT.wheel_aim_C = -150;
	}
	else
	{
		EIT_ROBOT.wheel_aim_A = 0;
		EIT_ROBOT.wheel_aim_B = 0;
		EIT_ROBOT.wheel_aim_C = 0;
		result = 1;
	}
	return result;
}

void Run_X_Y(int16_t Vx,int16_t Vy)
{
	int16_t Va;
	int16_t Vb;
	int16_t Vc;
	Va = Vx;
	Vb = 0.5*Vx - 0.866*Vy;
	Vc = 0.5*Vx + 0.866*Vy;
	EIT_ROBOT.wheel_aim_A = Va;
	EIT_ROBOT.wheel_aim_B = -Vb;
	EIT_ROBOT.wheel_aim_C = -Vc;
}

//int16_t D_yaw = 0;
int16_t YAW_after=900 ;
int16_t Vbb = 0;       //旋转角度总合
/********************使用平移旋转之前必须加****************************/
void move_rotat_init(int16_t curren_angle)   //上电是防止之前的角度为0
{
	if(curren_angle == 0||curren_angle == 3599)
	{
		YAW_after = 900;
	}
	else
	YAW_after = curren_angle;
	Vbb = 0;
}

static int16_t YAW_after_angle=0 ;
static int16_t sum_angle = 0; 
void Clear_VBB(int16_t curren_angle)
{
	if(curren_angle == 0||curren_angle == 3600)
	{
		YAW_after_angle = 900;
	}
	else
	YAW_after_angle = curren_angle;
	sum_angle = 0;
}
void SUM_YAW(int16_t curren_angle)
{
	int16_t D_yaw = 0;
	if((YAW_after_angle > 2700&&YAW_after_angle<=3600)&&(curren_angle >= 0&&curren_angle<900))
	{
		D_yaw = (3600-YAW_after_angle)+curren_angle;
	}
	else if((YAW_after_angle >= 0&&YAW_after_angle<900)&&(curren_angle > 2700&&curren_angle<=3600))
	{
		D_yaw = (3600-curren_angle) + YAW_after_angle;
		D_yaw = -D_yaw;
	}
	else
	{
		D_yaw = curren_angle - YAW_after_angle;	
	}
	sum_angle = sum_angle + D_yaw;
	YAW_after_angle = curren_angle;
	if(sum_angle > 28800)
	{
		sum_angle = 0;
	}
	if(sum_angle < -28800)
	{
		sum_angle = 0;
	}
}
void move_X_Y_roata(int16_t Vx,int16_t Vy,int16_t curren_angle,int16_t st)
{
	int16_t Va;
	int16_t Vb;
	int16_t Vc;
	int16_t D_yaw = 0;
	
//	if((YAW_after_angle > 2700&&YAW_after_angle<=3600)&&(curren_angle >= 0&&curren_angle<900))
//	{
//		D_yaw = (3600-YAW_after_angle)+curren_angle;
//	}
//	else if((YAW_after_angle >= 0&&YAW_after_angle<900)&&(curren_angle > 2700&&curren_angle<=3600))
//	{
//		D_yaw = (3600-curren_angle) + YAW_after_angle;
//		D_yaw = -D_yaw;
//	}
//	else
//	{
//		D_yaw = curren_angle - YAW_after_angle;	
//	}
//	sum_angle = sum_angle + D_yaw;
//	YAW_after_angle = curren_angle;
//	if(sum_angle > 28800)
//	{
//		sum_angle = 0;
//	}
//	if(sum_angle < -28800)
//	{
//		sum_angle = 0;
//	}
	Va = (int16_t)Vx*arm_cos_f32(0.0017453*sum_angle) + Vy*arm_sin_f32(0.0017453*sum_angle)+st;
	Vb = -(int16_t)Vx*arm_cos_f32(0.0017453*(600-sum_angle)) + Vy*arm_cos_f32(0.0017453*(300+sum_angle)) + st;
	Vc = -(int16_t)Vx*arm_cos_f32(0.0017453*(600+sum_angle)) - Vy*arm_cos_f32(0.0017453*(300-sum_angle)) + st;
	EIT_ROBOT.wheel_aim_A = Va;
	EIT_ROBOT.wheel_aim_B = Vb;
	EIT_ROBOT.wheel_aim_C = Vc;
}

void move_rotat(int16_t V,int16_t jiaodu,int16_t curren_angle,int16_t st)
{
	int16_t Va;
	int16_t Vb;
	int16_t Vc;
	int16_t D_yaw = 0;
	float hudu_jiao;
	float jiao_b;
	hudu_jiao = 0.01745329*(jiaodu);
//	if((YAW_after > 2700&&YAW_after<=3600)&&(curren_angle >= 0&&curren_angle<900))
//	{
//		D_yaw = (3600-YAW_after)+curren_angle;
//	}
//	else if((YAW_after >= 0&&YAW_after<900)&&(curren_angle > 2700&&curren_angle<=3600))
//	{
//		D_yaw = (3600-curren_angle) + YAW_after;
//		D_yaw = -D_yaw;
//	}
//	else
//	{
//		D_yaw = curren_angle - YAW_after;	
//	}
//	Vbb = Vbb + D_yaw;
//	YAW_after = curren_angle;
//	
//	if(Vbb > 7200)
//	{
//		Vbb = 0;
//	}
//	if(Vbb < -7200)
//	{
//		Vbb = 0;
//	}
	jiao_b = hudu_jiao - 0.0017453*sum_angle;    //important
	YAW_after = curren_angle;
	Va = (int16_t)V*arm_cos_f32(jiao_b) + st;
	Vb = (int16_t)V*arm_cos_f32(0.6666*Pi - jiao_b) + st;
	Vc = (int16_t)V*arm_cos_f32(jiao_b + 0.6666*Pi) + st;
	EIT_ROBOT.wheel_aim_A = Va;
	EIT_ROBOT.wheel_aim_B = Vb;
	EIT_ROBOT.wheel_aim_C = Vc;
	//OLED_ShowNum(0,7,D_yaw,4,12);
}
// 平移速度，方向，实时角度，目标角度；返回值为1说明达到了目标角度，0：说明没有
u8 move_rotat_angle(int16_t V,int16_t jiaodu,int16_t curren_angle,int16_t aim_angle)
{
	int16_t Va;
	int16_t Vb;
	int16_t Vc;
	int16_t roata_speed;
	int16_t angle_cha = 0;
	int16_t D_yaw = 0;
	float hudu_jiao;
	float jiao_b;
	u8 result = 0;
	hudu_jiao = 0.01745329*(jiaodu);
	if((YAW_after > 2700&&YAW_after<=3600)&&(curren_angle >= 0&&curren_angle<900))
	{
		D_yaw = (3600-YAW_after)+curren_angle;
	}
	else if((YAW_after >= 0&&YAW_after<900)&&(curren_angle > 2700&&curren_angle<=3600))
	{
		D_yaw = (3600-curren_angle) + YAW_after;
		D_yaw = -D_yaw;
	}
	else
	{
		D_yaw = curren_angle - YAW_after;	
	}
	Vbb = Vbb + D_yaw;
	if(Vbb > 3600)
	{
		Vbb = 0;
	}
	if(Vbb < -3600)
	{
		Vbb = 0;
	}
	jiao_b = hudu_jiao - 0.0017454*Vbb;
	YAW_after = curren_angle;
	
	angle_cha = aim_angle - curren_angle;
	if(angle_cha <= -1800)
	{
		aim_angle = 3600 + aim_angle;					//重新计算目标角度
		angle_cha = aim_angle - curren_angle;			//更新差值
	}
	else if(angle_cha > 1800)
	{
		aim_angle = aim_angle - 3600;				//更新为负的角度
		angle_cha = aim_angle - curren_angle;
	}
	else
		;
	if(angle_cha>=200&&angle_cha <=1800)
	{
		roata_speed = 800;
	}
	else if(angle_cha >= -1800&&angle_cha <= -200)
	{
		roata_speed = -800;
	}
	else if(angle_cha>=8&&angle_cha <200)
	{
		roata_speed = 100;
	}
	else if(angle_cha>=-200&&angle_cha <=-8)
	{
		roata_speed = -100;
	}
	else
	{
		roata_speed = 0;
		result = 1;
	}
	Va = (int16_t)V*arm_cos_f32(jiao_b) + roata_speed;
	Vb = (int16_t)V*arm_cos_f32(0.6666*Pi - jiao_b) + roata_speed;
	Vc = (int16_t)V*arm_cos_f32(jiao_b + 0.6666*Pi) + roata_speed;
	EIT_ROBOT.wheel_aim_A = Va;
	EIT_ROBOT.wheel_aim_B = Vb;
	EIT_ROBOT.wheel_aim_C = Vc;
	return result;
}



void ROAT_POINT(ROATA_POINT roata_point,int16_t speed) //绕某点旋转
{
	if(roata_point == RA_SIDE)
	{
		if(speed>=0)
		{
			EIT_ROBOT.wheel_aim_A = 0.95*speed;
			EIT_ROBOT.wheel_aim_B = 2.505*speed;
			EIT_ROBOT.wheel_aim_C = speed;
		}
		else
		{
			EIT_ROBOT.wheel_aim_A = speed;
			EIT_ROBOT.wheel_aim_B = 2.505*speed;
			EIT_ROBOT.wheel_aim_C = 0.95*speed;
		}
		
	}
	else if(roata_point == RB_SIDE)
	{
		if(speed>=0)
		{
			EIT_ROBOT.wheel_aim_A = speed;
			EIT_ROBOT.wheel_aim_B = 0.95*speed;
			EIT_ROBOT.wheel_aim_C = 2.505*speed;
		}
		else
		{
			EIT_ROBOT.wheel_aim_A = 0.94*speed;
			EIT_ROBOT.wheel_aim_B = speed;
			EIT_ROBOT.wheel_aim_C = 2.505*speed;
		}
		
	}
	else if(roata_point == RC_SIDE)
	{
		if(speed>=0)
		{
			EIT_ROBOT.wheel_aim_A = 2.505*speed;
			EIT_ROBOT.wheel_aim_B = speed;
			EIT_ROBOT.wheel_aim_C = 0.92*speed;
		}
		else
		{
			EIT_ROBOT.wheel_aim_A = 2.505*speed;
			EIT_ROBOT.wheel_aim_B = 0.95*speed;
			EIT_ROBOT.wheel_aim_C = speed;
		}
		
	}
	else if(roata_point == RA_WHEEL)
	{
		EIT_ROBOT.wheel_aim_A = 0;
		EIT_ROBOT.wheel_aim_B = speed;
		EIT_ROBOT.wheel_aim_C = speed;
	}
	else if(roata_point == RB_WHEEL)
	{
		EIT_ROBOT.wheel_aim_A = speed;
		EIT_ROBOT.wheel_aim_B = 0;
		EIT_ROBOT.wheel_aim_C = speed;
	}
	else if(roata_point == RC_WHEEL)
	{
		EIT_ROBOT.wheel_aim_A = speed;
		EIT_ROBOT.wheel_aim_B = speed;
		EIT_ROBOT.wheel_aim_C = 0;
	}
}
/*************************绕某一点或边旋转到输入角度********************/
u8 ROAT_AIMANGLE(ROATA_POINT roata_point,uint16_t curren_angle,int16_t aim_angle)
{
	int angle_cha = 0;
	int speed = 0;
	u8 flag = 0;
	//float *SPEED = 0;
	angle_cha = aim_angle - curren_angle;
	if(angle_cha < -1800)
	{
		aim_angle = 3600 + aim_angle;					//重新计算目标角度
		angle_cha = aim_angle - curren_angle;			//更新差值
	}
	else if(angle_cha > 1800)
	{
		aim_angle = aim_angle - 3600;				//更新为负的角度
		angle_cha = aim_angle - curren_angle;
	}
	else
		;
	if(angle_cha>=200&&angle_cha <=1800)
	{
		speed = 550;
		flag = 0;
	}
	else if(angle_cha >= -1800&&angle_cha <= -200)
	{
		speed = -550;
		flag = 0;
	}
	else if(angle_cha>=8&&angle_cha <200)
	{
		speed = 150;
		flag = 0;
	}
	else if(angle_cha>=-200&&angle_cha <=-8)
	{
		speed = -150;
		flag = 0;
	}
	else
	{
		speed = 0;
		flag = 1;
	}
	if(roata_point == RA_SIDE)
	{
		ROAT_POINT(RA_SIDE,speed);
	}
	else if(roata_point == RB_SIDE)
	{
		ROAT_POINT(RB_SIDE,speed);
	}
	else if(roata_point == RC_SIDE)
	{
		ROAT_POINT(RC_SIDE,speed);
	}
	else if(roata_point == RA_WHEEL)
	{
		ROAT_POINT(RA_WHEEL,2*speed);
	}
	else if(roata_point == RB_WHEEL)
	{
		ROAT_POINT(RB_WHEEL,2*speed);
	}
	else if(roata_point == RC_WHEEL)
	{
		ROAT_POINT(RC_WHEEL,2*speed);
	}
	return flag;
}










