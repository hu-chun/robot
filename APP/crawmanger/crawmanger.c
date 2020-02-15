#include "crawmanger.h"
#include "common.h"
#define MAX(a,b,c) (a>b?(a>c?a:c):(b>c?b:c))
u8 A_CRAW_NUMBER =0;
u8 B_CRAW_NUMBER =0;
u8 C_CRAW_NUMBER =0;

/***************************�Ǹ�צ�ӷ�or�õ�����*************************************/
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

/*********************�������ĺͲ������ٵ�*******************************/
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

/*****************************************������***************************************************************/
u8 PUT_BAMBOO(craw_w SIDE_X,u8 Dis,u8 min_gd,u8 out_gd)    //CRAW_X:�Ǹ�צ��  Dis�������ľ���  min_gd:�½��ĸ߶ȷ�  out_gd�������ĸ߶�ץ
{
	u8 result = 0;
	static u8 setp_flag = 0;
	if(SIDE_X == a_craw)
	{
		if(setp_flag == 0)
		{
			gd_control(255);
			if(Close_move(Direction_A,Dis)==1)		//���������Ӿ���
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
				claw_control(A_CLAW,CLAW_OPEN);         //��צ��
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
				claw_control(A_CLAW,CLAW_CLOSE);         //�ر�צ��
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
			if(Close_move(Direction_B,Dis)==1)		//���������Ӿ���
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
				claw_control(B_CLAW,CLAW_OPEN);         //��צ��
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
				claw_control(B_CLAW,CLAW_CLOSE);         //�ر�צ��
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
			if(Close_move(Direction_C,Dis)==1)		//���������Ӿ���
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
				claw_control(C1_CLAW,CLAW_OPEN);         //��צ��
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
				claw_control(C2_CLAW,CLAW_CLOSE);         //�ر�צ��
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
/********************************************ץĿ��******************************************/
u8 GRAB_BAMBOO(craw_w SIDE_X,u8 Dis,u8 init_dis,u8 min_gd,u8 out_gd)   //SIDE_X ���Ǹ�צ��Dis������ init_dis���߶��ǵĸ߶�  min_gd;�½��ĸ߶� out_dis���˳�ʱ�ĸ߶�
{
	u8 result = 0;
	static u8 setp_flag = 0;
	if(SIDE_X == a_craw)
	{
		if(setp_flag == 0)
		{
			claw_control(A_CLAW,CLAW_OPEN);
			gd_control(init_dis);
			if(Close_move(Direction_A,Dis)==1)		//���������Ӿ���
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
				claw_control(A_CLAW,CLAW_CLOSE);         //�ر�צ��
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
			if(Close_move(Direction_B,Dis)==1)		//���������Ӿ���
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
				claw_control(B_CLAW,CLAW_CLOSE);         //��צ��
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
			if(Close_move(Direction_C,Dis)==1)		//���������Ӿ���
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
				claw_control(C2_CLAW,CLAW_CLOSE);         //�ر�צ��
				claw_control(C1_CLAW,CLAW_CLOSE);         //�ر�צ��
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
