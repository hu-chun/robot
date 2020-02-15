#include "crawmanger.h"
#include "common.h"
#define MAX(a,b,c) (a>b?(a>c?a:c):(b>c?b:c))
u8 A_CRAW_NUMBER =0;
u8 B_CRAW_NUMBER =0;
u8 C_CRAW_NUMBER =0;

/***************************那个爪子放or拿的数量*************************************/
void CRAW_INPUT(craw_w CRAW,craw_MODE mode,u8 num)
{
	if(CRAW == a_craw)
	{
		if(mode == FANG)
		{
			A_CRAW_NUMBER = A_CRAW_NUMBER + num;
		}
		else
		{
			A_CRAW_NUMBER = A_CRAW_NUMBER - num;			
		}
	}
	if(CRAW == b_craw)
	{
		if(mode == FANG)
		{
			B_CRAW_NUMBER = B_CRAW_NUMBER + num;
		}
		else
		{
			B_CRAW_NUMBER = B_CRAW_NUMBER - num;
		}
	}
	if(CRAW == c_craw)
	{
		if(mode == FANG)
		{
			C_CRAW_NUMBER = C_CRAW_NUMBER + num;
		}
		else
		{
			C_CRAW_NUMBER = C_CRAW_NUMBER - num;
		}
	}
}

/*********************查找最多的和查找最少的*******************************/
craw_w CRAW_RUN(craw_MODE mode)
{
	u8 max = 0;
	//u8 min = 0;
	if(mode == FANG)
	{
		max = MAX(A_CRAW_NUMBER,B_CRAW_NUMBER,C_CRAW_NUMBER);
		if(max == A_CRAW_NUMBER)
		{
			return a_craw;
		}
		else if(max == B_CRAW_NUMBER)
		{
			return b_craw;
		}
		else if(max == C_CRAW_NUMBER)
		{
			return c_craw;
		}
		else
		{
			return a_craw;
		}
	}
	else
	{
		if(A_CRAW_NUMBER == 0)
		{
			return a_craw;
		}
		else if(B_CRAW_NUMBER == 0)
		{
			return b_craw;
		}
		else if(C_CRAW_NUMBER == 0)
		{
			return c_craw;
		}	
		else
		{
			return c_craw;
		}
	}
}

/*****************************************放竹子***************************************************************/
u8 PUT_BAMBOO(craw_w SIDE_X,u8 Dis,u8 min_gd,u8 out_gd)    //CRAW_X:那个爪子  Dis：靠近的距离  min_gd:下降的高度放  out_gd：提升的高度抓
{
	u8 result = 0;
	static u8 setp_flag = 0;
	if(SIDE_X == a_craw)
	{
		if(setp_flag == 0)
		{
			gd_control(255);
			if(Close_move(Direction_A,Dis)==1)		//靠近个竹子距离
			{
				Runing_V_ST(0,210);
				setp_flag = 1;
					//TIME_SHOW();
				gd_control(min_gd);
			}
			else
			{
				Close_move(Direction_A,Dis);
			}
			result = 0;
		}
		if(setp_flag == 1)
		{
			if((-3<(min_gd-TOP_STATUS.TOP_GD))&&((min_gd-TOP_STATUS.TOP_GD)<3))
			{
				claw_control(A_CLAW,CLAW_OPEN);         //打开爪子
				SET_TIME2(50);
				setp_flag = 2;
			}
			else
			{
				;
			}
			result = 0;
		}
		if(setp_flag == 2)
		{
			if(CHEAK_TIMEFINISH2() == TIME_YES)
			{
				gd_control(out_gd);
				setp_flag = 3;
			}
			result = 0;
		}
		if(setp_flag == 3)
		{
			if((-3<(out_gd-TOP_STATUS.TOP_GD))&&((out_gd-TOP_STATUS.TOP_GD)<3))
			{
				claw_control(A_CLAW,CLAW_CLOSE);         //关闭爪子
				SET_TIME2(30);
				setp_flag = 4;
			}
			result = 0;
		}
		if(setp_flag == 4)
		{
			if(CHEAK_TIMEFINISH2() == TIME_YES)
			{
				gd_control(255);
				setp_flag = 5;
			}
			result = 0;
		}
		if(setp_flag == 5)
		{
			result = 0;
			if((-3<(255-TOP_STATUS.TOP_GD))&&((255-TOP_STATUS.TOP_GD)<3))
			{
				setp_flag = 0;
				result = 1;
			}
			
		}
		return result;
	}
	
	if(SIDE_X == b_craw)
	{
		if(setp_flag == 0)
		{
			gd_control(255);
			if(Close_move(Direction_B,Dis)==1)		//靠近个竹子距离
			{
				Runing_V_ST(0,330);
				setp_flag = 1;
					//TIME_SHOW();
				gd_control(min_gd);
			}
			else
			{
				setp_flag = 0;
			}
			result = 0;
		}
		if(setp_flag == 1)
		{
			if((-3<(min_gd-TOP_STATUS.TOP_GD))&&((min_gd-TOP_STATUS.TOP_GD)<3))
			{
				claw_control(B_CLAW,CLAW_OPEN);         //打开爪子
				SET_TIME2(50);
				setp_flag = 2;
			}
			else
			{
				;
			}
			result = 0;
		}
		if(setp_flag == 2)
		{
			if(CHEAK_TIMEFINISH2() == TIME_YES)
			{
				gd_control(out_gd);
				setp_flag = 3;
			}
			result = 0;
		}
		if(setp_flag == 3)
		{
			if((-3<(out_gd-TOP_STATUS.TOP_GD))&&((out_gd-TOP_STATUS.TOP_GD)<3))
			{
				claw_control(B_CLAW,CLAW_CLOSE);         //关闭爪子
				SET_TIME2(30);
				setp_flag = 4;
			}
			result = 0;
		}
		if(setp_flag == 4)
		{
			if(CHEAK_TIMEFINISH2() == TIME_YES)
			{
				gd_control(255);
				setp_flag = 5;
			}
			result = 0;
		}
		if(setp_flag == 5)
		{
			result = 0;
			if((-3<(255-TOP_STATUS.TOP_GD))&&((255-TOP_STATUS.TOP_GD)<3))
			{
				setp_flag = 0;
				result = 1;
			}
			
		}
		return result;
	}
	
	if(SIDE_X == c_craw)
	{
		if(setp_flag == 0)
		{
			gd_control(255);
			if(Close_move(Direction_C,Dis)==1)		//靠近个竹子距离
			{
				Runing_V_ST(0,90);
				setp_flag = 1;
					//TIME_SHOW();
				gd_control(min_gd);
			}
			else
			{
				Close_move(Direction_C,Dis);
				setp_flag = 0;
			}
			result = 0;
		}
		if(setp_flag == 1)
		{
			if((-3<(min_gd-TOP_STATUS.TOP_GD))&&((min_gd-TOP_STATUS.TOP_GD)<3))
			{
				claw_control(C1_CLAW,CLAW_OPEN);         //打开爪子
				delay_ms(10);
				claw_control(C2_CLAW,CLAW_OPEN); 
				SET_TIME2(50);
				setp_flag = 2;
			}
			else
			{
				;
			}
			result = 0;
		}
		if(setp_flag == 2)
		{
			if(CHEAK_TIMEFINISH2() == TIME_YES)
			{
				gd_control(out_gd);
				setp_flag = 3;
			}
			result = 0;
		}
		if(setp_flag == 3)
		{
			if((-3<(out_gd-TOP_STATUS.TOP_GD))&&((out_gd-TOP_STATUS.TOP_GD)<3))
			{
				claw_control(C2_CLAW,CLAW_CLOSE);         //关闭爪子
				delay_ms(1);
				claw_control(C1_CLAW,CLAW_CLOSE); 
				SET_TIME2(30);
				setp_flag = 4;
			}
			result = 0;
		}
		if(setp_flag == 4)
		{
			if(CHEAK_TIMEFINISH2() == TIME_YES)
			{
				gd_control(255);
				setp_flag = 5;
			}
			result = 0;
		}
		if(setp_flag == 5)
		{
			result = 0;
			if((-3<(255-TOP_STATUS.TOP_GD))&&((255-TOP_STATUS.TOP_GD)<3))
			{
				setp_flag = 0;
				result = 1;
			}
			
		}
		return result;
	}

}
/********************************************抓目标******************************************/
u8 GRAB_BAMBOO(craw_w SIDE_X,u8 Dis,u8 init_dis,u8 min_gd,u8 out_gd)   //SIDE_X ：那个爪，Dis：距离 init_dis：高度是的高度  min_gd;下降的高度 out_dis：退出时的高度
{
	u8 result = 0;
	static u8 setp_flag = 0;
	if(SIDE_X == a_craw)
	{
		if(setp_flag == 0)
		{
			claw_control(A_CLAW,CLAW_OPEN);
			gd_control(init_dis);
			if(Close_move(Direction_A,Dis)==1)		//靠近个竹子距离
			{
				Runing_V_ST(0,210);
				setp_flag = 1;
					//TIME_SHOW();
				gd_control(min_gd);
			}
			else
			{
				Close_move(Direction_A,Dis);
			}
			result = 0;
		}
		if(setp_flag == 1)
		{
			if((-3<(min_gd-TOP_STATUS.TOP_GD))&&((min_gd-TOP_STATUS.TOP_GD)<3))
			{
				claw_control(A_CLAW,CLAW_CLOSE);         //关闭爪子
				SET_TIME2(40);
				setp_flag = 2;
			}
			else
			{
				;
			}
			result = 0;
			
		}
		if(setp_flag == 2)
		{
			if(CHEAK_TIMEFINISH2() == TIME_YES)
			{
				gd_control(out_gd);
				setp_flag = 3;
			}
			result = 0;
		}
		if(setp_flag == 3)
		{
			result = 0;
			if((-3<(out_gd-TOP_STATUS.TOP_GD))&&((out_gd-TOP_STATUS.TOP_GD)<3))
			{
				setp_flag = 0;
				result = 1;
			}
		}
		return result;
	}
	
	if(SIDE_X == b_craw)
	{
		if(setp_flag == 0)
		{
			claw_control(B_CLAW,CLAW_OPEN);
			gd_control(init_dis);
			if(Close_move(Direction_B,Dis)==1)		//靠近个竹子距离
			{
				Runing_V_ST(0,330);
				setp_flag = 1;
					//TIME_SHOW();
				gd_control(min_gd);
			}
			else
			{
				Close_move(Direction_B,Dis);
			}
			result = 0;
		}
		if(setp_flag == 1)
		{
			if((-3<(min_gd-TOP_STATUS.TOP_GD))&&((min_gd-TOP_STATUS.TOP_GD)<3))
			{
				claw_control(B_CLAW,CLAW_CLOSE);         //打开爪子
				SET_TIME2(40);
				setp_flag = 2;
			}
			else
			{
				;
			}
			result = 0;
			
		}
		if(setp_flag == 2)
		{
			if(CHEAK_TIMEFINISH2() == TIME_YES)
			{
				gd_control(out_gd);
				setp_flag = 3;
			}
			result = 0;
		}
		if(setp_flag == 3)
		{
			result = 0;
			if((-3<(out_gd-TOP_STATUS.TOP_GD))&&((out_gd-TOP_STATUS.TOP_GD)<3))
			{
				setp_flag = 0;
				result = 1;
			}
		}
		return result;
	}

	if(SIDE_X == c_craw)
	{
		if(setp_flag == 0)
		{
			claw_control(C1_CLAW,CLAW_OPEN);
			claw_control(C2_CLAW,CLAW_OPEN);
			gd_control(init_dis);
			if(Close_move(Direction_C,Dis)==1)		//靠近个竹子距离
			{
				Runing_V_ST(0,330);
				setp_flag = 1;
					//TIME_SHOW();
				gd_control(min_gd);
			}
			else
			{
				Close_move(Direction_C,Dis);
			}
			result = 0;
		}
		if(setp_flag == 1)
		{
			if((-3<(min_gd-TOP_STATUS.TOP_GD))&&((min_gd-TOP_STATUS.TOP_GD)<3))
			{
				claw_control(C2_CLAW,CLAW_CLOSE);         //关闭爪子
				claw_control(C1_CLAW,CLAW_CLOSE);         //关闭爪子
				SET_TIME2(60);
				setp_flag = 2;
			}
			else
			{
				;
			}
			result = 0;
			
		}
		if(setp_flag == 2)
		{
			if(CHEAK_TIMEFINISH2() == TIME_YES)
			{
				gd_control(out_gd);
				setp_flag = 3;
			}
			result = 0;
		}
		if(setp_flag == 3)
		{
			result = 0;
			if((-3<(out_gd-TOP_STATUS.TOP_GD))&&((out_gd-TOP_STATUS.TOP_GD)<3))
			{
				setp_flag = 0;
				result = 1;
			}
		}
		return result;
	}

}
