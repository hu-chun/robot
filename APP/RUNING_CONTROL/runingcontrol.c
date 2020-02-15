
#include "runingcontrol.h"
#include "common.h"
#include "sys.h"
void Independ_run(float curret_x,float current_y,float aim_x,float aim_y)
{
	float DX = 0;
	float DY = 0;
	int16_t V_x;
	int16_t V_y;
	DX = aim_x - curret_x;
	DY = aim_y - current_y;
	if(DX > 800)
	{
		V_x = 1500;
	}
	else if(DX > 200&&DX <= 800)
	{
		V_x = 1000;
	}
	else if(DX <= 200&&DX > 80)
	{
		V_x = 500;
	}
	else if(DX <= 80&&DX > 20)
	{
		V_x = 100;
	}
	
	else if(DX < -800)
	{
		V_x = -1500;
	}
	else if(DX >= -800&&DX < -200)
	{
		V_x = -1000;
	}
	else if(DX >= -200&&DX < -50)
	{
		V_x = -500;
	}
	else if(DX >= -50&&DX < -20)
	{
		V_x = -100;
	}
	else
		V_x = 0;
	if(DY > 800)
	{
		V_y = 1500;
	}
	else if(DY <= 800&&DY > 200)
	{
		V_y = 1000;
	}
	else if(DY <= 200&&DY > 50)
	{
		V_y = 500;
	}
	else if(DY <= 50&&DY > 20)
	{
		V_y = 100;
	}
	else if(DY < -800)
	{
		V_y = -1500;
	}
	else if(DY >= -800&&DY < -200)
	{
		V_y = -500;
	}
	else if(DY >= -200&&DY < -80)
	{
		V_y = -500;
	}
	else if(DY >= -80&&DY < -20)
	{
		V_y = -100;
	}
	else
		V_y = 0;
	Run_X_Y(V_x,V_y);
}

uint16_t CHA_A;
uint16_t CHA_B;
uint16_t CHA_C;

u8 Close_proximity(robot_dir faxian)
{
	static uint16_t gong_time;
	int16_t Dis_Cha = 0;
	int16_t dis_avg = 0;
	if(faxian == Direction_A)
	{
		if((ULTRSONIC_DIS.U_A1 > 500&&ULTRSONIC_DIS.U_A2<500)||(ULTRSONIC_DIS.U_A2>500&&ULTRSONIC_DIS.U_A1 < 500))
		{
			gong_time = 0;
			if(ULTRSONIC_DIS.U_A1 > 500)
			{
				if(ULTRSONIC_DIS.U_A2 > 430)
				{
					ROAT_POINT(RB_WHEEL,200);
				}
				else 
				{
					ROAT_POINT(RC_WHEEL,150);
				}
			}
			if(ULTRSONIC_DIS.U_A2 > 500)
			{
				if(ULTRSONIC_DIS.U_A1 > 430)
				{
					ROAT_POINT(RB_WHEEL,-200);
				}
				else 
				{
					ROAT_POINT(RA_WHEEL,-150);
				}
			}
			return 0;
		}
		else if(ULTRSONIC_DIS.U_A1 > 500&&ULTRSONIC_DIS.U_A2>500)
		{
			gong_time++;
			if(gong_time <=200)
			{
				Runing_V_ST(300,210);
			}
			else if(gong_time>200&&gong_time <=1000)
			{
				Runing_rotat(-25);
			}
			else if(gong_time>1000&&gong_time <=2600)
			{
				Runing_rotat(25);
			}
			else
			{
				Runing_rotat(0);	
			}
			if(gong_time>3000)
			{
				gong_time = 0;
			}
			return 0;
		}
		else		
		{
			gong_time = 0;       //刷新未找到目标累加值
			Dis_Cha = ULTRSONIC_DIS.U_A1  - ULTRSONIC_DIS.U_A2;
			dis_avg = (ULTRSONIC_DIS.U_A1  + ULTRSONIC_DIS.U_A2)/2;
			if(dis_avg > 200)
			{
				if(Dis_Cha > 30)
				{
					Runing_V_ST(250,120);
				}
				if(Dis_Cha < -25)
				{
					Runing_V_ST(250,300);
				}	
				if(Dis_Cha > -15&&Dis_Cha < 15)
				{
					Runing_V_ST(0,300);
					return 1;
				}	
				else 
					return 0;
			}
			else
			{
			 	if(Dis_Cha > 20)
				{
					Runing_V_ST(150,120);
				}
				if(Dis_Cha < -20)
				{
					Runing_V_ST(150,300);
				}	
				if(Dis_Cha > -20&&Dis_Cha < 20)
				{
					Runing_V_ST(0,300);
					return 1;
				}	
				else 
				{
					//delay_ms(20);
					return 0;
				}
					
			}
		}	
	}
	if(faxian == Direction_B)
	{
		if((ULTRSONIC_DIS.U_B1 > 1000&&ULTRSONIC_DIS.U_B2<1000)||(ULTRSONIC_DIS.U_B2>1000&&ULTRSONIC_DIS.U_B1 < 1000))
		{
			gong_time = 0;
			if(ULTRSONIC_DIS.U_B1 > 1000)
			{
				if(ULTRSONIC_DIS.U_B2 > 430)
				{
					ROAT_POINT(RC_WHEEL,200);
				}
				else 
				{
					ROAT_POINT(RA_WHEEL,150);
				}
			}
			if(ULTRSONIC_DIS.U_B2 > 1000)
			{
				if(ULTRSONIC_DIS.U_B1 > 430)
				{
					ROAT_POINT(RC_WHEEL,-200);
				}
				else 
				{
					ROAT_POINT(RB_WHEEL,-150);
				}
			}
			return 0;
		}
		else if(ULTRSONIC_DIS.U_B1>1000&&ULTRSONIC_DIS.U_B2>1000)
		{
			gong_time++;
			if(gong_time <=200)
			{
				Runing_V_ST(400,330);
			}
			else if(gong_time>200&&gong_time <=500)
			{
				Runing_rotat(-25);
			}
			else if(gong_time>500&&gong_time <=1100)
			{
				Runing_rotat(25);
			}
			else
			{
				Runing_rotat(0);	
			}
			if(gong_time>2200)
			{
				gong_time = 0;
			}
			return 0;
		}
		else
		{
			gong_time = 0;
			Dis_Cha = ULTRSONIC_DIS.U_B1  - ULTRSONIC_DIS.U_B2;
			dis_avg = (ULTRSONIC_DIS.U_B1  + ULTRSONIC_DIS.U_B2)/2;
			if(dis_avg>180)
			{
				if(Dis_Cha > 25)
				{
					Runing_V_ST(250,240);
				}
				if(Dis_Cha < -25)
				{
					Runing_V_ST(250,60);
				}	
				if(Dis_Cha > -25&&Dis_Cha < 25)
				{
					Runing_V_ST(0,60);
					return 1;
				}
				else 
					return 0;
			}
			else
			{
				if(Dis_Cha > 20)
				{
					Runing_V_ST(150,240);
				}
				if(Dis_Cha < -20)
				{
					Runing_V_ST(150,60);
				}	
				if(Dis_Cha > -20&&Dis_Cha < 20)
				{
					Runing_V_ST(0,60);
					return 1;
				}
				else
				{
					//delay_ms(20);
					return 0;
				}
			}
			
		}
		
	}
	if(faxian == Direction_C)
	{
		if((ULTRSONIC_DIS.U_C1 > 1000&&ULTRSONIC_DIS.U_C2<1000)||(ULTRSONIC_DIS.U_C2>1000&&ULTRSONIC_DIS.U_C1 < 1000))
		{
			gong_time = 0;
			if(ULTRSONIC_DIS.U_C1 > 1000)
			{
				if(ULTRSONIC_DIS.U_C2 > 430)
				{
					ROAT_POINT(RA_WHEEL,200);
				}
				else 
				{
					ROAT_POINT(RB_WHEEL,150);
				}
			}
			if(ULTRSONIC_DIS.U_C2 > 1000)
			{
				if(ULTRSONIC_DIS.U_C1 > 430)
				{
					ROAT_POINT(RA_WHEEL,-200);
				}
				else 
				{
					ROAT_POINT(RC_WHEEL,-150);
				}
			}
			return 0;
		}
		else if(ULTRSONIC_DIS.U_C1 > 1000&&ULTRSONIC_DIS.U_C2>1000)
		{
			gong_time++;
			if(gong_time <=200)
			{
				Runing_V_ST(400,90);
			}
			else if(gong_time>200&&gong_time <=500)
			{
				Runing_rotat(-25);
			}
			else if(gong_time>500&&gong_time <=1100)
			{
				Runing_rotat(25);
			}
			else
			{
				Runing_rotat(0);	
			}
			if(gong_time>2200)
			{
				gong_time = 0;
			}
			return 0;
		}
		else
		{
			Dis_Cha = ULTRSONIC_DIS.U_C1  - ULTRSONIC_DIS.U_C2;
			dis_avg = (ULTRSONIC_DIS.U_C1  + ULTRSONIC_DIS.U_C2)/2;
			if(dis_avg > 170)
			{
				if(Dis_Cha > 26)
				{
					Runing_V_ST(220,0);
				}
				if(Dis_Cha < -26)
				{
					Runing_V_ST(220,180);
				}	
				if(Dis_Cha > -26&&Dis_Cha < 26)
				{
					Runing_V_ST(0,180);
					return 1;
				}	
				else 
					return 0;
			}
			else
			{
				if(Dis_Cha > 20)
				{
					Runing_V_ST(130,0);
				}
				if(Dis_Cha < -20)
				{
					Runing_V_ST(130,180);
				}	
				if(Dis_Cha > -20&&Dis_Cha < 20)
				{
					Runing_V_ST(0,180);
					return 1;
				}	
				else 
				{
					//delay_ms(20);
					return 0;
				}
			}
		}
		
	}
	else
		return 2;
}
int16_t keep_speed_limit(int16_t Speed,uint16_t Max_speed)
{
	int16_t lim_Speed = 0;
	lim_Speed = Speed;
	if(lim_Speed >= 0)
	{
		if(lim_Speed > Max_speed)
		{
			lim_Speed = Max_speed;
			return lim_Speed;
		}
		else
			return lim_Speed;
	}
	else
	{
		if(lim_Speed < -Max_speed)
		{
			lim_Speed = Max_speed;
			return lim_Speed;
		}
		else
			return lim_Speed;
	}
}
u8 Keep_distance(robot_dir faxian,uint16_t aim_dis)
{
	int16_t dis_cha = 0;
	int16_t speed = 0;
	uint16_t avg_dis = 0;
	if(faxian == Direction_A)
	{
		avg_dis = (ULTRSONIC_DIS.U_A1+ULTRSONIC_DIS.U_A2)/2;
		dis_cha = aim_dis - avg_dis;
		if(dis_cha > 10)
		{ 
			if(Close_proximity(Direction_A) == 1)
			{
				speed = 3*dis_cha;
				speed = keep_speed_limit(speed,1000);
				Runing_V_ST(speed,30);
				return 0;
			}
			
		}
		else if(dis_cha < -10)
		{
			if(Close_proximity(Direction_A) == 1)
			{
				speed = 3*dis_cha;
				speed = keep_speed_limit(speed,1000);
				Runing_V_ST(speed,30);
				return 0;
			}
			
		}
		else
		{
			Runing_V_ST(0,210);
			Close_proximity(Direction_A);
			return 1;
		}
	}
	if(faxian == Direction_B)
	{
		avg_dis = (ULTRSONIC_DIS.U_B1+ULTRSONIC_DIS.U_B2)/2;
		dis_cha = aim_dis - avg_dis;
		if(dis_cha > 10)
		{ 
			speed = 3*dis_cha;
			speed = keep_speed_limit(speed,1000);
			Runing_V_ST(speed,150);
			return 0;
		}
		else if(dis_cha < -10)
		{
			if(Close_proximity(Direction_B) == 1)
			{
				speed = 3*dis_cha;
				speed = keep_speed_limit(speed,1000);
				Runing_V_ST(speed,150);
				return 0;
			}
			
		}
		else
		{
			Runing_V_ST(0,150);
			Close_proximity(Direction_B);
			return 1;
		}
	}
	if(faxian == Direction_C)
	{
		avg_dis = (ULTRSONIC_DIS.U_C1+ULTRSONIC_DIS.U_C2)/2;
		dis_cha = aim_dis - avg_dis;
		if(dis_cha > 15)
		{ 
			speed = 3*dis_cha;
			speed = keep_speed_limit(speed,1000);
			Runing_V_ST(speed,270);
			return 0;
		}
		else if(dis_cha < -15)
		{
			if(Close_proximity(Direction_C) == 1)
			{
				speed = 3*dis_cha;
				speed = keep_speed_limit(speed,1000);
				Runing_V_ST(speed,270);
				return 0;
			}
			
		}
		else
		{
			Runing_V_ST(0,270);
			Close_proximity(Direction_C);
			return 1;
		}
	}
}
u8 Close_move(robot_dir faxian,uint8_t min_dis)   //min_dis<150
{
	u8 result = 0;
	if(faxian == Direction_A)
	{
		if(Close_proximity(Direction_A) == 1)
		{
			if(ULTRSONIC_DIS.U_A1>500||ULTRSONIC_DIS.U_A2>500)
			{
				Runing_V_ST(500,210);
				result = 0;
			}
			else if((ULTRSONIC_DIS.U_A1>200&&ULTRSONIC_DIS.U_A1<=500)||(ULTRSONIC_DIS.U_A2>200&&ULTRSONIC_DIS.U_A2<=500))
			{
				Runing_V_ST(300,210);
				result = 0;
			}
			else if((ULTRSONIC_DIS.U_A1>min_dis&&ULTRSONIC_DIS.U_A1<=200)||(ULTRSONIC_DIS.U_A2>min_dis&&ULTRSONIC_DIS.U_A2<=200))
			{
				Runing_V_ST(150,210);
				result = 0;
			}
			else if(ULTRSONIC_DIS.U_A1<min_dis||ULTRSONIC_DIS.U_A2<min_dis)
			{
				Runing_V_ST(0,210);
				result = 1;
			}
			//delay_ms(5);
		}	
		
	}
	if(faxian == Direction_B)
	{
		if(Close_proximity(Direction_B) == 1)
		{
			if(ULTRSONIC_DIS.U_B1>500||ULTRSONIC_DIS.U_B2>500)
			{
				Runing_V_ST(500,330);
				result = 0;
			}
			else if((ULTRSONIC_DIS.U_B1>200&&ULTRSONIC_DIS.U_B1<=500)||(ULTRSONIC_DIS.U_B2>200&&ULTRSONIC_DIS.U_B2<=500))
			{
				Runing_V_ST(300,330);
				result = 0;
			}
			else if((ULTRSONIC_DIS.U_B1>min_dis&&ULTRSONIC_DIS.U_B1<=200)||(ULTRSONIC_DIS.U_B2>min_dis&&ULTRSONIC_DIS.U_B2<=200))
			{
				Runing_V_ST(150,330);
				result = 0;
			}
			else if(ULTRSONIC_DIS.U_B1<min_dis||ULTRSONIC_DIS.U_B2<min_dis)
			{
				Runing_V_ST(0,330);
				result = 1;
			}
			//delay_ms(5);
		}
		
	}
	if(faxian == Direction_C)
	{
		if(Close_proximity(Direction_C) == 1)
		{
			if(ULTRSONIC_DIS.U_C1>500||ULTRSONIC_DIS.U_C2>500)
			{
				Runing_V_ST(500,90);
				result = 0;
			}
			else if((ULTRSONIC_DIS.U_C1>200&&ULTRSONIC_DIS.U_C1<=500)||(ULTRSONIC_DIS.U_C2>200&&ULTRSONIC_DIS.U_C2<=500))
			{
				Runing_V_ST(300,90);
				result = 0;
			}
			else if((ULTRSONIC_DIS.U_C1>min_dis&&ULTRSONIC_DIS.U_C1<=200)||(ULTRSONIC_DIS.U_C2>min_dis&&ULTRSONIC_DIS.U_C2<=200))
			{
				Runing_V_ST(150,90);
				result = 0;
			}
			else if(ULTRSONIC_DIS.U_C1<min_dis||ULTRSONIC_DIS.U_C2<min_dis)
			{
				Runing_V_ST(0,90);
				result = 1;
			}
			//delay_ms(5);
		}
		
	}
	return result;	
}

u8 X_Y_ANGELE_AIM(float curren_x,float curren_y,int16_t curren_yaw,float aim_x,float aim_y,int16_t aim_yaw,uint16_t max_speed)
{
	float X_cha;
	float Y_cha;
	int16_t yaw_cha;
	int16_t X_speed;
	int16_t Y_speed;
	int16_t Yaw_speed;
	u8 x_flag = 0;
	u8 y_flag = 0;
	u8 yaw_flag = 0;
	u8 finish_flag=0;
	/****************x方向**********************/
	X_cha = aim_x - curren_x;
	if(X_cha>-15&&X_cha<15)
	{
		X_speed = 0;
		x_flag = 1;
	}
	else
	{
		X_speed = 1.9*X_cha;
		x_flag = 0;
	}
	if(X_speed>1500)
	{
		X_speed = 1500;
	}
	if(X_speed < -1500)
	{
		X_speed = -1500;
	}
	/*******************y方向*******************************/
	Y_cha = aim_y - curren_y;
	if(Y_cha>-15&&Y_cha<15)
	{
		Y_speed = 0;
		y_flag = 1;
	}
	else
	{
		Y_speed = 1.9*Y_cha;
		y_flag = 0;
	}
	if(Y_speed>1500)
	{
		Y_speed = 1500;
	}
	if(Y_speed < -1500)
	{
		Y_speed = -1500;
	}
	/*******************角度*******************************/
	yaw_cha = aim_yaw - curren_yaw;
	if(yaw_cha < -1800)
	{
		aim_yaw = 3600 + aim_yaw;					//重新计算目标角度
		yaw_cha = aim_yaw - curren_yaw;			//更新差值
	}
	else if(yaw_cha > 1800)
	{
		aim_yaw = aim_yaw - 3600;				//更新为负的角度
		yaw_cha = aim_yaw - curren_yaw;
	}
	else
		;
	if(yaw_cha>=200&&yaw_cha <=1800)
	{
		Yaw_speed = 700;
		yaw_flag = 0;
	}
	else if(yaw_cha >= -1800&&yaw_cha <= -200)
	{
		Yaw_speed = -700;
		yaw_flag = 0;
	}
	else if(yaw_cha>=5&&yaw_cha <200)
	{
		Yaw_speed = 150;
		yaw_flag = 0;
	}
	else if(yaw_cha>=-200&&yaw_cha <=-5)
	{
		Yaw_speed = -150;
		yaw_flag = 0;
	}
	else
	{
		Yaw_speed = 0;
		yaw_flag = 1;
	}
	move_X_Y_roata(X_speed,Y_speed,curren_yaw,Yaw_speed);
	if(x_flag==1&&y_flag==1&&yaw_flag==1)
	{
		finish_flag = 1;
	}
	else
	{
		finish_flag = 0;
	}
	return finish_flag;
}




/*************************************************运用摄像头进行导航********************************************/

/*返回0为没有发现目标 1：发现目标*/
u8 Objective_cheak(u16 x, u16 y)
{
	if(x==0&&y==0)
	{
		return 0;
	}
	else
		return 1;
}
void Camear_FX(int16_t ZY,int16_t QH)
{
	int x = 0;
	int y = 0;
	if(ZY > 1000)
	{
		ZY = 1000;
	}
	if(ZY < -1000)
	{
		ZY = -1000;
	}
	if(QH > 1800)
	{
		QH = 1800;
	}
	if(QH < -1800)
	{
		QH = -1800;
	}
	x = QH*arm_cos_f32(0.523598)+ZY*arm_cos_f32(1.047197);
	y = QH*arm_sin_f32(0.523598)-ZY*arm_sin_f32(1.047197);
	x = -x;
	y = -y;
	Run_X_Y(x,y);
}
PID_Struct Camear_run;
//u16 camear_dis = 100;
/******************图像控制初始化*****************************/
u8 Camear_control_init()
{
	PID_Init(&Camear_run,0,-8.52,0,-3.9,500);
	//camear_dis = 270;
	return 1;
}
/*************图像控制运行****************************/
u8 Camear_control_run(u16 camear_dis)
{
	int16_t RL_speed = 0;
	int16_t QH_speed = 0;
	int16_t Error = 0;
	if(Objective_cheak(TARGET_READ.object_x,TARGET_READ.object_y) != 1)
	{
		Camear_FX(0,0);
		return 0;
	}
	else
	{
		PID_SetAim(&Camear_run,160);
		RL_speed = PID_Out(&Camear_run,TARGET_READ.object_x);
//		if(-3<(160-TARGET_READ.object_x)||(160-TARGET_READ.object_x)<3)
//		{
//			RL_speed = 0;
//		}
		Error = TARGET_READ.object_y - camear_dis;
		if(camear_dis < 175)
		{
			Error = 2*Error;
		}
		if(Error>=5&&Error < 120)
		{
			QH_speed = -12*Error;
		}
		else if(Error>-120&&Error <= -5)
		{
			QH_speed = -12*Error;
		}
		else if(Error > -5&&Error < 5)
		{
			QH_speed = 0;
		}
		else
		{
			QH_speed = -15*Error;
		}
		Camear_FX(RL_speed,QH_speed);
		return 1;
	}
	
}

u8 Camear_jiaozheng(void)
{
	u8 result = 0;
	int16_t Error = 0;
	int16_t speed =0;
	Error = 160 - TARGET_READ.object_x;
	if(Error>-3&&Error<3)
	{
		Error = 0;
		result = 1; 
	}
	else
	{
		result = 0;
	}
	speed = 3.5*Error;
	ROAT_POINT(RB_WHEEL,speed); 
	return result;
}


