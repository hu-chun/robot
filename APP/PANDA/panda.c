
#include "panda.h"
#include "common.h"
extern int16_t var[8];
extern u8 A_CRAW_NUMBER ;
extern u8 B_CRAW_NUMBER ;
extern u8 C_CRAW_NUMBER ;
uint8_t  steep = 0;
uint8_t JS_FLAG=0;
uint8_t JS_TIME=0;
uint8_t timefinish_flag = 0;
uint8_t JS_FLAG2=0;
uint8_t JS_TIME2=0;
uint8_t timefinish_flag2 = 0;
u8 RED_STEP = 0;
u8 RED_SMALL_STEP=0;
u8 GREED_STEP = 0;
u8 GREED_SMALL_STEP=0;
int16_t int16_semaphore[8]={0};
u8 Synchronization_semaphore[8]={0};  		//最多可以同布八个任务
/**************************建立地标信息***************************************/
PANDA_bamboo RED_BAMBOO[] = {{0,0,0},{1,-3354,2055},{2,-3354,2055},{3,-365,3200},{4,-1190,4307},{5,-513,5454},
                          {6,-975,5048},{7,907,3677},{8,3124,2138},{9,1289,648}};
PANDA_landmark RED_LANDMARK[] = {{0,0,0},{1,-2553,734},{2,-4232,2918},{3,4054,3229},{4,2509,820}};
PANDA_Transferpoint RED_POINT[] = {{0,0,4550},{1,-1750,4287},{2,-1450,5378},{3,-550,6075},{4,550,6075},{5,1450,5477},{6,1750,4394},
									{7,1450,3290},{8,570,2635},{9,-570,2600},{10,-1450,3197}};



//任务定时
void TIM7_IRQHandler(void)
{
	static uint8_t TIME=0;
	static uint8_t TIME2=0;
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) //溢出中断
	{
		
		if(JS_FLAG == 1)
		{
			TIME++;
			if(TIME ==JS_TIME)
			{
				TIME = 0;
				timefinish_flag = 1;
				JS_FLAG = 0;
			}
			else
			timefinish_flag = 0;
		}
		if(JS_FLAG2 == 1)
		{
			TIME2++;
			if(TIME2 ==JS_TIME2)
			{
				TIME2 = 0;
				timefinish_flag2 = 1;
				JS_FLAG2 = 0;
			}
			else
			timefinish_flag2 = 0;
		}
		SUM_YAW(MAP_data.YAW);
	}
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  //清除中断标志位
}
int16_t SET_AIM_ANGLE(int16_t currer_angle ,int16_t D_angle)   //大于零为逆时针，小于零为顺时针
{
	int16_t angle;
	angle =  currer_angle + D_angle;
	if(angle>3600)
	{
		angle = angle - 3600;
	}
	if(angle <0)
	{
		angle = 3600 + angle;
	}
	return angle;
	
}


/************************/
void SET_TIME(u16 TIME_10ms)  //10整数倍
{
	JS_TIME = TIME_10ms/10;
	JS_FLAG = 1;
	timefinish_flag = 0;
}
/***************************************/
TIME_FINISH CHEAK_TIMEFINISH()
{
	if(timefinish_flag == 1)
		return TIME_YES;
	else
		return TIME_ON;
}
/*****************************************/
void SET_TIME2(u16 TIME_10ms)  //10整数倍
{
	JS_TIME2 = TIME_10ms/10;
	JS_FLAG2 = 1;
	timefinish_flag2 = 0;
}
/***************************************/
TIME_FINISH CHEAK_TIMEFINISH2(void)
{
	if(timefinish_flag2 == 1)
		return TIME_YES;
	else
		return TIME_ON;
}
/*****************************/
void PANDA_INIT(COLOR_CHOOSE color_choose)
{

	if(color_choose == R_party)
	{
		PANDA_RED();
	}
	if(color_choose == G_party)
	{
		PANDA_GREED();
	}
	TIMERx_init(TIME_7,10000,84-1);//10ms
}
/**************************************/
void PANDA_RED(void)
{
	
	OLED_ShowNum(100,5,RED_SMALL_STEP,2,12);
	var[4] = RED_SMALL_STEP*100;
	var[5] = read_usetime();
	if(RED_STEP == 0)
	{
		
		/*****************************************/
		if(RED_SMALL_STEP == 0)
		{
			SET_TIME(180);   //1S
			gd_control(100);
			claw_control(C2_CLAW,CLAW_OPEN);
			claw_control(C1_CLAW,CLAW_OPEN);
			RED_SMALL_STEP = 1;
		}
		if(RED_SMALL_STEP == 1)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				//Runing_V_ST(1200,180);
				move_rotat_angle(1300,180,MAP_data.YAW,1439);
			}
			else
			{
				Runing_V_ST(0,180);
				RED_SMALL_STEP = 2;
			}
		}
		/*****************************************/
		if(RED_SMALL_STEP == 2)
		{
			SET_TIME(20);   //1S
			gd_control(100);
			RED_SMALL_STEP = 3;
		}
		if(RED_SMALL_STEP == 3)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Run_angle(MAP_data.YAW,1439);
			}
			else
			{
				Runing_V_ST(0,180);
				RED_SMALL_STEP = 4;
			}
			
		}
		if(RED_SMALL_STEP == 4)
		{
			SET_TIME(128);   //1S
			gd_control(30);
			RED_SMALL_STEP = 5;
		}
		if(RED_SMALL_STEP == 5)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Runing_V_ST(1550,90);
			}
			else
			{
				Runing_V_ST(0,180);
				RED_SMALL_STEP = 6;
			}
		}
		if(RED_SMALL_STEP == 6)
		{
			if(Close_move(Direction_C,100) == 1)
			{
				RED_SMALL_STEP = 7;
				//BEEP_ON;
				gd_control(10);
			}
		}
		if(RED_SMALL_STEP == 7)
		{
			BEEP_ON;
			SET_TIME(20);
			RED_SMALL_STEP = 8;
		}
		if(RED_SMALL_STEP == 8)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Close_move(Direction_C,105);
				BEEP_OFF;
			}
			else
			{
				if((-4<(10-TOP_STATUS.TOP_GD))&&((10-TOP_STATUS.TOP_GD)<4))
				{
					claw_control(C2_CLAW,CLAW_CLOSE);
					claw_control(C1_CLAW,CLAW_CLOSE);        //抓起第一个地标
					BEEP_ON;
					RED_SMALL_STEP = 9;
					delay_ms(500);
				}
				
			}
		}
		if(RED_SMALL_STEP == 9)
		{
			gd_control(255);
			Runing_V_ST(0,180);
			RED_SMALL_STEP = 10;
			BEEP_OFF;
		}
		if(RED_SMALL_STEP == 10)
		{
			//SET_TIME(180);
			RED_SMALL_STEP = 11;
		}
		if(RED_SMALL_STEP == 11)
		{
			if(ROAT_AIMANGLE(RA_WHEEL,MAP_data.YAW,125) == 1)
			{
				Runing_V_ST(800,90);
				delay_ms(500);
				Runing_V_ST(0,90);
				//Close_move(Direction_C,70);
				RED_SMALL_STEP = 12;
			}
			else
			{
				BEEP_ON;
			}
		}
		if(RED_SMALL_STEP == 12)
		{
			BEEP_OFF;
			Close_move(Direction_C,70);
			if(near_read(near_C)==0)
			{
				BEEP_ON;
				Runing_V_ST(0,180);
				RED_SMALL_STEP = 13;
			}
		}
		if(RED_SMALL_STEP == 13)
		{
			BEEP_OFF;
			gd_control(130);
			RED_SMALL_STEP = 14;
		}
		if(RED_SMALL_STEP == 14)
		{
			if((-5<=(TOP_STATUS.TOP_GD-130))&&((TOP_STATUS.TOP_GD-130)<=5))
			{
				Runing_V_ST(0,270);
				BEEP_OFF;
				claw_control(C2_CLAW,CLAW_OPEN);
				RED_SMALL_STEP = 15;
			}
			else 
			{
				if(near_read(near_C)==0)     //退一点，防止掉落
				{
					Runing_V_ST(150,270);
				}
				else
				{
					Runing_V_ST(0,270);
				}
				BEEP_ON;
			}
			
		}
		if(RED_SMALL_STEP == 15)
		{
			
			SET_TIME(80);		
			gd_control(135);
			RED_SMALL_STEP = 16;
		}
		if(RED_SMALL_STEP == 16)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				BEEP_ON;
			}
			else
			{
				claw_control(C2_CLAW,CLAW_CLOSE);
				delay_ms(550);
				gd_control(255);
				RED_SMALL_STEP = 17;
			}
				
		}
		if(RED_SMALL_STEP == 17)
		{
			if((-5<=(TOP_STATUS.TOP_GD-255))&&((TOP_STATUS.TOP_GD-255)<=5))
			{
				BEEP_OFF;
				RED_SMALL_STEP = 18;
			}
			else
			{
				;//BEEP_ON;
			}
		}
		if(RED_SMALL_STEP == 18)
		{
			SET_TIME(60);	
			Runing_V_ST(500,270);
			RED_SMALL_STEP = 19;
		}
		if(RED_SMALL_STEP == 19)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Runing_V_ST(1000,270);
			}
			else
			{
				Runing_V_ST(0,270);
				RED_SMALL_STEP = 20;
			}
			
		}
		if(RED_SMALL_STEP == 20)
		{
			if(ROAT_AIMANGLE(RA_WHEEL,MAP_data.YAW,1185) == 1)
			{
				BEEP_OFF;
				RED_SMALL_STEP = 21;
			}
			else
			{
				BEEP_ON;
			}
		}
		if(RED_SMALL_STEP == 21)
		{
			SET_TIME(145);	
			RED_SMALL_STEP = 22;
			Runing_V_ST(800,90);
		}
		if(RED_SMALL_STEP == 22)
		{
			if(CHEAK_TIMEFINISH() !=TIME_YES)
			{
				Runing_V_ST(1400,90);
			}
			else
			{
				Runing_V_ST(0,90);
				RED_SMALL_STEP = 23;
			}
		}
		if(RED_SMALL_STEP == 23)
		{
			BEEP_ON;
			if(Close_move(Direction_C,80) == 1)
			{
				BEEP_OFF;
				Runing_V_ST(0,90);
				gd_control(130);
				RED_SMALL_STEP = 24;
			}
			
			
		}
		if(RED_SMALL_STEP == 24)
		{
			if((-5<=(TOP_STATUS.TOP_GD-130))&&((TOP_STATUS.TOP_GD-130)<=5))
			{
				Runing_V_ST(0,270);
				claw_control(C2_CLAW,CLAW_OPEN);
				RED_SMALL_STEP = 25;
			}
			else 
			{
				if(near_read(near_C)==0)     //退一点，防止掉落
				{
					Runing_V_ST(100,270);
				}
				else
				{
					Runing_V_ST(0,270);
				}
			}
		}
		if(RED_SMALL_STEP == 25)
		{
			if(near_read(near_C)==0)
			{
				Runing_V_ST(0,90);
				gd_control(200);
				RED_SMALL_STEP = 26;
			}
			else
			{
				Runing_V_ST(100,90);
				BEEP_ON;
			}
			//Runing_V_ST(0,270);
		}
		if(RED_SMALL_STEP == 26)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,3524) == 1)
			{
				BEEP_OFF;
				RED_SMALL_STEP = 27;
			}
		}
		if(RED_SMALL_STEP == 27)
		{
			SET_TIME(70);
			Runing_V_ST(1000,260);
			claw_control(A_CLAW,CLAW_OPEN);
			RED_SMALL_STEP = 28;
		}
		if(RED_SMALL_STEP == 28)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				BEEP_ON;
				Runing_V_ST(1300,260);
			}
			else
			{
				gd_control(80);
				BEEP_OFF;
				RED_SMALL_STEP = 29;
			}
		}
		if(RED_SMALL_STEP == 29)
		{
			SET_TIME(80);
			gd_control(30);      //降低高度
			Runing_V_ST(600,230);
			RED_SMALL_STEP = 30;
		}
		if(RED_SMALL_STEP == 30)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Runing_V_ST(900,210);
			}
			else
			{
				RED_SMALL_STEP = 31;
			}
		}
		if(RED_SMALL_STEP == 31)
		{
			if(Close_move(Direction_A,85) == 1)
			{
				Runing_V_ST(0,210);
				gd_control(10);
				RED_SMALL_STEP = 32;
			}
		}
		if(RED_SMALL_STEP == 32)
		{
			if((-4<(10-TOP_STATUS.TOP_GD))&&((10-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(A_CLAW,CLAW_CLOSE);        //抓起第二个地标
				//BEEP_ON;
				RED_SMALL_STEP = 33;
				delay_ms(500);
				gd_control(250);
			}
			
		}
		if(RED_SMALL_STEP == 33)
		{
			SET_TIME(177);
			Runing_V_ST(1850,112);
			RED_SMALL_STEP = 34;
		}
		if(RED_SMALL_STEP == 34)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Runing_V_ST(1950,112);
			}
			else
			{
				RED_SMALL_STEP = 35;
			}
		}
		if(RED_SMALL_STEP == 35)
		{
			SET_TIME(155);
			//Runing_V_ST(500,90);
			RED_SMALL_STEP = 36;
		}
		if(RED_SMALL_STEP == 36)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Runing_V_ST(1450,112);
			}
			else
			{
				Runing_V_ST(0,112);
				RED_SMALL_STEP = 37;
			}
		}
		if(RED_SMALL_STEP == 37)
		{
			//Close_move(Direction_C,70);
			if(Close_move(Direction_C,90)==1)
			{
				BEEP_OFF;
				Runing_V_ST(0,90);
				gd_control(100);
				RED_SMALL_STEP = 38;
			}
		}
		if(RED_SMALL_STEP == 38)
		{
			if((-5<=(TOP_STATUS.TOP_GD-100))&&((TOP_STATUS.TOP_GD-100)<=5))
			{
				Runing_V_ST(0,270);
				claw_control(C1_CLAW,CLAW_OPEN);
				SET_TIME(50);
				RED_SMALL_STEP = 39;
			}
			else
			{
				if(near_read(near_C)==0)     //退一点，防止掉落
				{
					Runing_V_ST(150,270);
				}
				else
				{
					Runing_V_ST(0,270);
					
				}
			}
			
		}
		if(RED_SMALL_STEP == 39)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				BEEP = !BEEP;
			}
			else
			{
				BEEP_OFF;
				gd_control(255);
				RED_SMALL_STEP = 40;
			}
		}
		if(RED_SMALL_STEP == 40)
		{
			if(near_read(near_C)==0)
			{
				Runing_V_ST(0,90);
				gd_control(250);
				RED_SMALL_STEP = 41;
			}
			else
			{
				Runing_V_ST(100,90);
				BEEP_ON;
			}
		}
		if(RED_SMALL_STEP == 41)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,3540) == 1)
			{
				BEEP_OFF;
				RED_SMALL_STEP = 42;
			}
		}
		if(RED_SMALL_STEP == 42)
		{
			SET_TIME(40);
			RED_SMALL_STEP = 43;
		}
		if(RED_SMALL_STEP == 43)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Runing_V_ST(500,270);
			}
			else
			{
				Runing_V_ST(0,270);
				RED_SMALL_STEP = 44;
			}
		}
		if(RED_SMALL_STEP == 44)
		{
			SET_TIME(80);
			RED_SMALL_STEP = 45;
		}
		if(RED_SMALL_STEP == 45)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Runing_V_ST(1400,210);
			}
			else
			{
				Runing_V_ST(0,210);
				RED_SMALL_STEP = 46;
			}
		}
		if(RED_SMALL_STEP == 46)
		{
			if(Close_move(Direction_A,90) == 1)
			{
				Runing_V_ST(0,210);
				gd_control(200);						//放公共区第二个地标
				RED_SMALL_STEP = 47;
			}
		}
		if(RED_SMALL_STEP == 47)
		{
			if((-5<=(TOP_STATUS.TOP_GD-200))&&((TOP_STATUS.TOP_GD-200)<=5))
			{
				Runing_V_ST(0,270);
				claw_control(A_CLAW,CLAW_OPEN);
				SET_TIME(80);
				RED_SMALL_STEP = 48;
			}
		}
		if(RED_SMALL_STEP == 48)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				;
			}
			else
			{
				//claw_control(A_CLAW,CLAW_CLOSE);
				gd_control(240);
				RED_SMALL_STEP = 49;
			}
			
		}
		if(RED_SMALL_STEP == 49)
		{
			if((-5<=(TOP_STATUS.TOP_GD-240))&&((TOP_STATUS.TOP_GD-240)<=5))
			{
				claw_control(A_CLAW,CLAW_CLOSE);
				SET_TIME(80);
				RED_SMALL_STEP = 50;
			}
		}
		if(RED_SMALL_STEP == 50)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				;
			}
			else
			{
				gd_control(255);
				RED_SMALL_STEP = 51;
			}
		}
		if(RED_SMALL_STEP == 51)
		{
			if(ROAT_AIMANGLE(RA_SIDE,MAP_data.YAW,370) == 1)
			{
				//BEEP_OFF;
				RED_SMALL_STEP = 52;
			}
		}
		if(RED_SMALL_STEP == 52)
		{
			SET_TIME(80);
			RED_SMALL_STEP = 53;
			Runing_V_ST(850,30);
		}
		if(RED_SMALL_STEP == 53)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				;
			}
			else
			{
				Runing_V_ST(0,30);
				RED_SMALL_STEP = 54;
			}
			
		}
		if(RED_SMALL_STEP == 54)
		{
			SET_TIME(202);
			RED_SMALL_STEP = 55;
			move_rotat_init(MAP_data.YAW);
		}
		if(RED_SMALL_STEP == 55)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				move_rotat_angle(1200,87,MAP_data.YAW,2750);
			}
			else
			{
				Runing_V_ST(0,210);
				RED_SMALL_STEP = 56;
			}
			
		}
		if(RED_SMALL_STEP == 56)
		{
			if(Close_move(Direction_A,90) == 1)
			{
				Runing_V_ST(0,210);
				gd_control(200);						
				RED_SMALL_STEP = 57;
			}
		}
		if(RED_SMALL_STEP == 57)
		{
			if((-5<=(TOP_STATUS.TOP_GD-200))&&((TOP_STATUS.TOP_GD-200)<=5))
			{
				Runing_V_ST(0,210);
				claw_control(A_CLAW,CLAW_OPEN);
				SET_TIME(80);
				RED_SMALL_STEP = 58;
			}
		}
		if(RED_SMALL_STEP == 58)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				;
			}
			else
			{
				//claw_control(A_CLAW,CLAW_CLOSE);
				gd_control(250);
				RED_SMALL_STEP = 59;
			}
		}
		if(RED_SMALL_STEP == 59)
		{
			if((-5<=(TOP_STATUS.TOP_GD-250))&&((TOP_STATUS.TOP_GD-250)<=5))
			{
				RED_SMALL_STEP = 60;
			}
			//Runing_V_ST(0,210);
			//Clear_VBB();
		}
		if(RED_SMALL_STEP == 60)
		{
			TIME_SHOW();
			Runing_V_ST(0,210);;//X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,0,0,900,1500);
		}
	}
	if(RED_STEP == 1)
	{
		/*****************************************/
		if(RED_SMALL_STEP == 0)
		{
			SET_TIME(180);   //1S
			gd_control(100);
			claw_control(C2_CLAW,CLAW_OPEN);
			claw_control(C1_CLAW,CLAW_OPEN);
			RED_SMALL_STEP = 1;
		}
		if(RED_SMALL_STEP == 1)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				//Runing_V_ST(1200,180);
				move_rotat_angle(1280,0,MAP_data.YAW,353);
			}
			else
			{
				Runing_V_ST(0,180);
				RED_SMALL_STEP = 2;
			}
		}
		if(RED_SMALL_STEP == 2)
		{
			if(Run_angle(MAP_data.YAW,353)==1)
			{
				RED_SMALL_STEP = 3;
			}
		}
		if(RED_SMALL_STEP == 3)
		{
			SET_TIME(128);
			gd_control(20);
			Runing_V_ST(1560,90);
			RED_SMALL_STEP = 4;
		}
		if(RED_SMALL_STEP == 4)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				BEEP = !BEEP;
			}
			else
			{
				Runing_V_ST(0,90);
				RED_SMALL_STEP = 5;
			}
		}
		if(RED_SMALL_STEP == 5)
		{
			if(Close_move(Direction_C,95) == 0)
			{
				BEEP = !BEEP;
			}
			else
			{
				BEEP_OFF;
				gd_control(10);
				RED_SMALL_STEP = 6;
			}
		}
		if(RED_SMALL_STEP == 6)
		{
			if((-3<(10-TOP_STATUS.TOP_GD))&&((10-TOP_STATUS.TOP_GD)<3))
			{
				claw_control(C2_CLAW,CLAW_CLOSE);
				delay_ms(50);
				claw_control(C1_CLAW,CLAW_CLOSE);        //抓起第一个地标
				RED_SMALL_STEP = 7;
				SET_TIME(60);            //爪子响应慢，需要多100MS
			}
		}
		if(RED_SMALL_STEP == 7)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(255);
				RED_SMALL_STEP = 8;
			}	
		}
		if(RED_SMALL_STEP == 8)
		{
			if(ROAT_AIMANGLE(RA_WHEEL,MAP_data.YAW,1679) == 1)
			{
				SET_TIME(45);
				RED_SMALL_STEP = 9;
			}
		}
		if(RED_SMALL_STEP == 9)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Runing_V_ST(1300,90);
			}
			else
			{
				RED_SMALL_STEP = 10;
			}
		}
		if(RED_SMALL_STEP == 10)
		{
			if(Close_move(Direction_C,70) == 1)
			{
				Runing_V_ST(0,90);
				RED_SMALL_STEP = 11;
			}
		}
		if(RED_SMALL_STEP == 11)
		{
			if(near_read(near_C) == 0)
			{
				Runing_V_ST(380,270);
			}
			else
			{
				Runing_V_ST(0,270);
				gd_control(140);
				RED_SMALL_STEP = 12;
			}
			
		}
		if(RED_SMALL_STEP == 12)
		{
			if((-4<(140-TOP_STATUS.TOP_GD))&&((140-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_OPEN);    //放置第一个地标
				SET_TIME(30);						//爪子等待时间
				RED_SMALL_STEP = 13;
			}
		}
		if(RED_SMALL_STEP == 13)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				claw_control(C2_CLAW,CLAW_CLOSE); 
				SET_TIME(30);						//爪子等待时间
				RED_SMALL_STEP = 14;
			}
		}
		if(RED_SMALL_STEP == 14)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(253);
				RED_SMALL_STEP = 15;
			}
		}
		if(RED_SMALL_STEP == 15)
		{
			if((-4<(253-TOP_STATUS.TOP_GD))&&((253-TOP_STATUS.TOP_GD)<4))
			{
				RED_SMALL_STEP = 16;
				SET_TIME(40);
			}
		}
		if(RED_SMALL_STEP == 16)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				RED_SMALL_STEP = 17;
			}
			else
			{
				Runing_V_ST(1200,270);
			}
		
		}
		if(RED_SMALL_STEP == 17)
		{
			SET_TIME(200);
			move_rotat_init(MAP_data.YAW);
			move_rotat_angle(1000,-25,MAP_data.YAW,355);
			RED_SMALL_STEP = 18;
		}
		if(RED_SMALL_STEP == 18)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				RED_SMALL_STEP = 19;
			}
			else
			{
				move_rotat_angle(1450,-25,MAP_data.YAW,355);
			}
		}
		if(RED_SMALL_STEP == 19)
		{
			if(Run_angle(MAP_data.YAW,355) == 1)
			{
				Runing_V_ST(0,270);
				RED_SMALL_STEP = 20;
			}
		}
		if(RED_SMALL_STEP == 20)
		{
			if(Close_move(Direction_C,75) == 1)			//靠近第二个竹子
			{
				Runing_V_ST(0,90);
				RED_SMALL_STEP = 21;
				//TIME_SHOW();
			}
		}
		if(RED_SMALL_STEP == 21)
		{
			if(near_read(near_C) != 0)
			{
				Runing_V_ST(100,90);
			}
			else
			{
				Runing_V_ST(0,270);
				gd_control(150);
				RED_SMALL_STEP = 22;
			}
		}
		if(RED_SMALL_STEP == 22)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,2512) == 1)
			{
				Synchronization_semaphore[0] = 1;
			}
			if((-4<(150-TOP_STATUS.TOP_GD))&&((150-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_OPEN);    //放置第2个地标
				SET_TIME(30);						//爪子等待时间
				RED_SMALL_STEP = 23;
				
			}
		}
		if(RED_SMALL_STEP == 23)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,2512) == 1)
			{
				Synchronization_semaphore[0] = 1;
			}
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Synchronization_semaphore[1] = 1;
			}
			if(Synchronization_semaphore[0] == 1&&Synchronization_semaphore[1] == 1)
			{
				Synchronization_semaphore[0] = 0;
				Synchronization_semaphore[1] = 1;
				SET_TIME(71);
				claw_control(A_CLAW,CLAW_OPEN);
				RED_SMALL_STEP = 24;
			}
		}
		if(RED_SMALL_STEP == 24)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				gd_control(60);
				RED_SMALL_STEP = 25;
				
			}
			else
			{
				Runing_V_ST(1410,270);
			}
		}
		if(RED_SMALL_STEP == 25)
		{
			SET_TIME(44);             //43可用
			gd_control(50);
			Runing_V_ST(0,210);
			RED_SMALL_STEP = 26;
		}
		if(RED_SMALL_STEP == 26)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,210);
				delay_ms(100);
				RED_SMALL_STEP = 27;
				
			}
			else
			{
				Runing_V_ST(1250,210);
			}
		}
		if(RED_SMALL_STEP == 27)
		{
			if(Close_move(Direction_A,98) == 1)      //找到第二个竹子
			{
				
				if((-4<(10-TOP_STATUS.TOP_GD))&&((10-TOP_STATUS.TOP_GD)<4))
				{
					claw_control(A_CLAW,CLAW_CLOSE);
					SET_TIME(45);
					RED_SMALL_STEP = 28;
					
				}
				else
				{
					gd_control(10);
				}
				
			}
		}
		if(RED_SMALL_STEP == 28)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(180);
				RED_SMALL_STEP = 29;
				
			}
		}
		if(RED_SMALL_STEP == 29)
		{
			SET_TIME(240);
			move_rotat_init(MAP_data.YAW);
			move_rotat_angle(1000,18,MAP_data.YAW,1420);
			RED_SMALL_STEP = 30;
		}
		if(RED_SMALL_STEP == 30)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				RED_SMALL_STEP = 31;
				Runing_V_ST(0,270);
			}
			else
			{
				move_rotat_angle(1900,18,MAP_data.YAW,1420);
			}
		}
		if(RED_SMALL_STEP == 31)
		{
			if(Run_angle(MAP_data.YAW,1420) == 1)
			{
				Runing_V_ST(0,270);
				SET_TIME(15);
				RED_SMALL_STEP = 32;
				//TIME_SHOW();
			}
		}
		if(RED_SMALL_STEP == 32)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				RED_SMALL_STEP = 33;
			}
			
		}
		if(RED_SMALL_STEP == 33)
		{
			if(Close_move(Direction_C,80) == 1)
			{
				Runing_V_ST(0,270);
				gd_control(60);
				SET_TIME(50);
				RED_SMALL_STEP = 34;
			}
			
		}
		if(RED_SMALL_STEP == 34)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				
				RED_SMALL_STEP = 35;
			}
			

		}
		if(RED_SMALL_STEP == 35)
		{
			if((-4<(60-TOP_STATUS.TOP_GD))&&((60-TOP_STATUS.TOP_GD)<4))    //公共区第一个竹子
			{
				claw_control(C1_CLAW,CLAW_OPEN);
				SET_TIME(30);
				RED_SMALL_STEP = 36;
			}
			else
			{
				if(near_read(near_C) == 0)   //触碰到了	
				{
					Runing_V_ST(450,270);
				}
				else
				{
					Runing_V_ST(0,270);
				}
			}
		}
		if(RED_SMALL_STEP == 36)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(255);
				RED_SMALL_STEP = 37;
			}
			
			
		}
		if(RED_SMALL_STEP == 37)
		{
			if(near_read(near_C) != 0)     //未触碰到，等待触碰到了再旋转
			{
				Runing_V_ST(100,90);
			}
			else
			{
				Runing_V_ST(0,90);
				RED_SMALL_STEP = 38;
			}
		}
		if(RED_SMALL_STEP == 38)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,600) == 1)
			{
				Runing_V_ST(0,270);
				RED_SMALL_STEP = 39;
				
			}
		}
		if(RED_SMALL_STEP == 39)
		{
			SET_TIME(35);
			Runing_V_ST(1360,270);
			RED_SMALL_STEP = 40;
		}
		if(RED_SMALL_STEP == 40)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				SET_TIME(70);
				Runing_V_ST(1650,210);
				RED_SMALL_STEP = 41;
			}
		}
		if(RED_SMALL_STEP == 41)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,210);
				RED_SMALL_STEP = 42;
				
			}
		}
		if(RED_SMALL_STEP == 42)
		{
			if(Close_move(Direction_A,95) == 1)    //公共区域第二个竹子
			{
				gd_control(140);
				RED_SMALL_STEP = 43;
			}
		}
		if(RED_SMALL_STEP == 43)
		{
			if((-4<(140-TOP_STATUS.TOP_GD))&&((140-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(A_CLAW,CLAW_OPEN);
				SET_TIME(30);
				RED_SMALL_STEP = 44;
			}
		}
		if(RED_SMALL_STEP == 44)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(210);
				if((-4<(210-TOP_STATUS.TOP_GD))&&((210-TOP_STATUS.TOP_GD)<4))
				{
					claw_control(A_CLAW,CLAW_CLOSE);
					gd_control(245);
					RED_SMALL_STEP = 45;
				}
				
			}
		}
		if(RED_SMALL_STEP == 45)
		{
			if((-4<(245-TOP_STATUS.TOP_GD))&&((245-TOP_STATUS.TOP_GD)<4))
			{
				Runing_V_ST(1500,30);
				SET_TIME(40);
				RED_SMALL_STEP = 46;
			}
			else
			{
				if(ROAT_AIMANGLE(RA_SIDE,MAP_data.YAW,600) == 1)
				{
					Runing_V_ST(0,270);	
				}
			}
		}
		if(RED_SMALL_STEP == 46)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(250);
				Runing_V_ST(0,30);
				SET_TIME(200);
				move_rotat_init(MAP_data.YAW);
				move_rotat_angle(1000,143,MAP_data.YAW,3370);
				RED_SMALL_STEP  = 47;
			}
		}
		if(RED_SMALL_STEP == 47)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				move_rotat_angle(1680,144,MAP_data.YAW,3370);
			}
			else
			{
				
				Runing_V_ST(0,210);
				RED_SMALL_STEP = 48;
			}
		}
		if(RED_SMALL_STEP == 48)
		{
			if(Close_move(Direction_A,90) == 1)    //公共区域第二个竹子
			{
				gd_control(140);
				RED_SMALL_STEP = 49;
			}
		}
		if(RED_SMALL_STEP == 49)
		{
			if((-4<(140-TOP_STATUS.TOP_GD))&&((140-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(A_CLAW,CLAW_OPEN);
				SET_TIME(50);
				RED_SMALL_STEP = 50;
			}
			
		}
		if(RED_SMALL_STEP == 50)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				gd_control(255);			
			}
			else
			{
				if(ROAT_AIMANGLE(RA_SIDE,MAP_data.YAW,3370) == 1)
				{
					SET_TIME(20);
					RED_SMALL_STEP=51;
				}
			}
		}
		if(RED_SMALL_STEP == 51)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,30);
				RED_SMALL_STEP=52;
				SET_TIME(50);
			}
			else
			{
				Runing_V_ST(1500,30);
			}
		}
		if(RED_SMALL_STEP == 52)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,330);
				RED_SMALL_STEP=53;
				gd_control(75);
			}
			else
			{
				Runing_V_ST(2000,330);
			}
		}
		if(RED_SMALL_STEP == 53)
		{
			if(Close_move(Direction_B,90) == 1)
			{
				Runing_V_ST(0,330);
				claw_control(B_CLAW,CLAW_CLOSE);
				SET_TIME(50);
				RED_SMALL_STEP = 54;
			}
		}
		if(RED_SMALL_STEP == 54)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(255);
				TIME_SHOW();
				RED_SMALL_STEP = 100;
			}
		}
		if(RED_SMALL_STEP == 100)
		{
			;
		}
	}
	if(RED_STEP == 2)
	{
		/*****************************************/
		if(RED_SMALL_STEP == 0)
		{
			SET_TIME(180);   //1S
			gd_control(100);
			claw_control(C2_CLAW,CLAW_OPEN);
			claw_control(C1_CLAW,CLAW_OPEN);
			RED_SMALL_STEP = 1;
		}
		if(RED_SMALL_STEP == 1)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				//Runing_V_ST(1200,180);
				move_rotat_angle(1280,0,MAP_data.YAW,353);
			}
			else
			{
				Runing_V_ST(0,180);
				RED_SMALL_STEP = 2;
			}
		}
		if(RED_SMALL_STEP == 2)
		{
			if(Run_angle(MAP_data.YAW,353)==1)
			{
				RED_SMALL_STEP = 3;
			}
		}
		if(RED_SMALL_STEP == 3)
		{
			SET_TIME(128);
			gd_control(20);
			Runing_V_ST(1560,90);
			RED_SMALL_STEP = 4;
		}
		if(RED_SMALL_STEP == 4)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				BEEP = !BEEP;
			}
			else
			{
				Runing_V_ST(0,90);
				RED_SMALL_STEP = 5;
			}
		}
		if(RED_SMALL_STEP == 5)
		{
			if(Close_move(Direction_C,95) == 0)
			{
				BEEP = !BEEP;
			}
			else
			{
				BEEP_OFF;
				gd_control(10);
				RED_SMALL_STEP = 6;
			}
		}
		if(RED_SMALL_STEP == 6)
		{
			if((-3<(10-TOP_STATUS.TOP_GD))&&((10-TOP_STATUS.TOP_GD)<3))
			{
				claw_control(C2_CLAW,CLAW_CLOSE);
				delay_ms(50);
				claw_control(C1_CLAW,CLAW_CLOSE);        //抓起第一个地标
				RED_SMALL_STEP = 7;
				SET_TIME(60);            //爪子响应慢，需要多100MS
			}
		}
		if(RED_SMALL_STEP == 7)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(255);
				RED_SMALL_STEP = 8;
			}	
		}
		if(RED_SMALL_STEP == 8)
		{
			if(ROAT_AIMANGLE(RA_WHEEL,MAP_data.YAW,1679) == 1)
			{
				SET_TIME(45);
				RED_SMALL_STEP = 9;
			}
		}
		if(RED_SMALL_STEP == 9)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Runing_V_ST(1200,90);
			}
			else
			{
				RED_SMALL_STEP = 10;
			}
		}
		if(RED_SMALL_STEP == 10)
		{
			if(Close_move(Direction_C,70) == 1)
			{
				Runing_V_ST(0,90);
				RED_SMALL_STEP = 11;
			}
		}
		if(RED_SMALL_STEP == 11)
		{
			if(near_read(near_C) == 0)
			{
				Runing_V_ST(380,270);
			}
			else
			{
				Runing_V_ST(0,270);
				gd_control(140);
				RED_SMALL_STEP = 12;
			}
			
		}
		if(RED_SMALL_STEP == 12)
		{
			if((-4<(140-TOP_STATUS.TOP_GD))&&((140-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_OPEN);    //放置第一个地标
				SET_TIME(30);						//爪子等待时间
				RED_SMALL_STEP = 13;
			}
		}
		if(RED_SMALL_STEP == 13)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				claw_control(C2_CLAW,CLAW_CLOSE); 
				SET_TIME(30);						//爪子等待时间
				RED_SMALL_STEP = 14;
			}
		}
		if(RED_SMALL_STEP == 14)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(253);
				RED_SMALL_STEP = 15;
			}
		}
		if(RED_SMALL_STEP == 15)
		{
			if((-4<(253-TOP_STATUS.TOP_GD))&&((253-TOP_STATUS.TOP_GD)<4))
			{
				RED_SMALL_STEP = 16;
				SET_TIME(40);
			}
		}
		if(RED_SMALL_STEP == 16)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				RED_SMALL_STEP = 17;
			}
			else
			{
				Runing_V_ST(1200,270);
			}
		
		}
		if(RED_SMALL_STEP == 17)
		{
			SET_TIME(200);
			move_rotat_init(MAP_data.YAW);
			move_rotat_angle(1000,-25,MAP_data.YAW,355);
			RED_SMALL_STEP = 18;
		}
		if(RED_SMALL_STEP == 18)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				RED_SMALL_STEP = 19;
			}
			else
			{
				move_rotat_angle(1450,-25,MAP_data.YAW,355);
			}
		}
		if(RED_SMALL_STEP == 19)
		{
			if(Run_angle(MAP_data.YAW,355) == 1)
			{
				Runing_V_ST(0,270);
				RED_SMALL_STEP = 20;
			}
		}
		if(RED_SMALL_STEP == 20)
		{
			if(Close_move(Direction_C,75) == 1)			//靠近第二个竹子
			{
				Runing_V_ST(0,90);
				RED_SMALL_STEP = 21;
				//TIME_SHOW();
			}
		}
		if(RED_SMALL_STEP == 21)
		{
			if(near_read(near_C) != 0)
			{
				Runing_V_ST(100,90);
			}
			else
			{
				Runing_V_ST(0,270);
				gd_control(150);
				RED_SMALL_STEP = 22;
			}
		}
		if(RED_SMALL_STEP == 22)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,2512) == 1)
			{
				Synchronization_semaphore[0] = 1;
			}
			if((-4<(150-TOP_STATUS.TOP_GD))&&((150-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_OPEN);    //放置第2个地标
				SET_TIME(30);						//爪子等待时间
				RED_SMALL_STEP = 23;
				
			}
		}
		if(RED_SMALL_STEP == 23)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,2512) == 1)
			{
				Synchronization_semaphore[0] = 1;
			}
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Synchronization_semaphore[1] = 1;
			}
			if(Synchronization_semaphore[0] == 1&&Synchronization_semaphore[1] == 1)
			{
				Synchronization_semaphore[0] = 0;
				Synchronization_semaphore[1] = 1;
				SET_TIME(71);
				claw_control(A_CLAW,CLAW_OPEN);
				RED_SMALL_STEP = 24;
			}
		}
		if(RED_SMALL_STEP == 24)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				gd_control(60);
				RED_SMALL_STEP = 25;
				
			}
			else
			{
				Runing_V_ST(1410,270);
			}
		}
		if(RED_SMALL_STEP == 25)
		{
			SET_TIME(44);             //43可用
			gd_control(50);
			Runing_V_ST(0,210);
			RED_SMALL_STEP = 26;
		}
		if(RED_SMALL_STEP == 26)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,210);
				delay_ms(100);
				RED_SMALL_STEP = 27;
				
			}
			else
			{
				Runing_V_ST(1250,210);
			}
		}
		if(RED_SMALL_STEP == 27)
		{
			if(Close_move(Direction_A,98) == 1)      //找到第二个竹子
			{
				
				if((-4<(10-TOP_STATUS.TOP_GD))&&((10-TOP_STATUS.TOP_GD)<4))
				{
					claw_control(A_CLAW,CLAW_CLOSE);
					SET_TIME(45);
					RED_SMALL_STEP = 28;
					
				}
				else
				{
					gd_control(10);
				}
				
			}
		}
		if(RED_SMALL_STEP == 28)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(150);
				RED_SMALL_STEP = 29;
				
			}
		}
		if(RED_SMALL_STEP == 29)
		{
			SET_TIME(250);
			move_rotat_init(MAP_data.YAW);
			move_rotat_angle(1000,357,MAP_data.YAW,1049);
			RED_SMALL_STEP = 30;
		}
		if(RED_SMALL_STEP == 30)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				RED_SMALL_STEP = 31;
				Runing_V_ST(0,270);
			}
			else
			{
				move_rotat_angle(2300,357,MAP_data.YAW,1049);
			}
		}
		if(RED_SMALL_STEP == 31)
		{
			if(Run_angle(MAP_data.YAW,1049) == 1)
			{
				//camear_cmd(OV_TARGET);
				camear_color(TARGET_GREED);        //识别绿色指令
				Runing_V_ST(0,270);
				RED_SMALL_STEP = 32;
				TIME_SHOW();
			}
		}
		if(RED_SMALL_STEP == 32)
		{
			if(Close_move(Direction_C,90) == 1)
			{
				gd_control(110);	
				RED_SMALL_STEP = 33;	
			}
			else
			{
				Close_move(Direction_C,90);
			}
			
		}
		if(RED_SMALL_STEP == 33)
		{
			if((-4<(110-TOP_STATUS.TOP_GD))&&((110-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C1_CLAW,CLAW_OPEN);
				SET_TIME(50);
				gd_control(255);
				RED_SMALL_STEP = 34;	
			}
			else
			{
				if(near_read(near_C) == 0)
				{
					Runing_V_ST(150,270);
				}
				else
				{
					Runing_V_ST(0,90);
				}
			}
			
		}
		if(RED_SMALL_STEP == 34)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				if(near_read(near_C) == 0)
				{
					Runing_V_ST(0,90);
					RED_SMALL_STEP = 35;
				}
				else
				{
					Runing_V_ST(100,90);
				}
				
			}
			
			
		}
		if(RED_SMALL_STEP == 35)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,234)==1)
			{
				SET_TIME(50);
				Runing_V_ST(1000,270);
				RED_SMALL_STEP = 36;
			}
			else
			{
				ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,234);
			}	
		}
		if(RED_SMALL_STEP == 36)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				SET_TIME(75);
				RED_SMALL_STEP = 37;
			}
			
			
		}
		if(RED_SMALL_STEP == 37)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,210);
				RED_SMALL_STEP = 38;
			}
			else
			{
				Runing_V_ST(1200,210);
			}
		}
		if(RED_SMALL_STEP == 38)
		{
			if(Objective_cheak(TARGET_READ.object_x,TARGET_READ.object_y) == 1)
			{
				BEEP_ON;
				Synchronization_semaphore[2]++;
				if(Synchronization_semaphore[2] == 50)
				{
					Synchronization_semaphore[3] = 0;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[1] = 1;       //有目标
					int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,-1200);
					RED_SMALL_STEP = 39;
					
				}
				
			}
			else
			{
				Synchronization_semaphore[3]++;
				if(Synchronization_semaphore[3] == 50)
				{
					RED_SMALL_STEP = 39;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[3] = 0;			//回复为0
					Synchronization_semaphore[1] = 2;			//没有目标
					BEEP_OFF;
				}
				
			}
		}
		
		if(RED_SMALL_STEP == 39)
		{
			if(Synchronization_semaphore[1] == 1)
			{
				if(Synchronization_semaphore[4] == 0)      //目标处理
				{
					if(Run_angle(MAP_data.YAW,int16_semaphore[0]) == 1)
					{
						BEEP_OFF;
						Synchronization_semaphore[4] = 1;
					}
					else
					{
						Run_angle(MAP_data.YAW,int16_semaphore[0]);
					}
				}	
				if(Synchronization_semaphore[4] == 1)
				{
					if(GRAB_BAMBOO(b_craw,85,100,85,250)==1)
					{
						SET_TIME(50);
						Runing_V_ST(1200,150);
						Synchronization_semaphore[4]  = 2;
					}	
				}
				if(Synchronization_semaphore[4] == 2)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,150);
						int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,1200);
						Synchronization_semaphore[4] = 3;
					}
					else
					{
						Runing_V_ST(1200,150);
					}
				}
				if(Synchronization_semaphore[4] == 3)
				{
					if(Run_angle(MAP_data.YAW,int16_semaphore[0]) == 1)
					{
						Synchronization_semaphore[4] = 4;
						SET_TIME(50);
						Runing_V_ST(900,210);
					}
					else
					{
						Run_angle(MAP_data.YAW,int16_semaphore[0]);
					}
					
				}
				if(Synchronization_semaphore[4] == 4)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,210);
						Synchronization_semaphore[4] = 5;
					}
					else
					{
						Runing_V_ST(900,210);
					}
				}
				if(Synchronization_semaphore[4] == 5)
				{
					if(PUT_BAMBOO(a_craw,85,150,220) == 1)
					{
						SET_TIME(75);
						Runing_V_ST(900,30);
						Synchronization_semaphore[4] = 6;
					}
					
				}
				if(Synchronization_semaphore[4] == 6)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						RED_SMALL_STEP = 40;
						Runing_V_ST(0,30);
						//Synchronization_semaphore[4] = 7;
					}
					else
					{
						Runing_V_ST(900,30);
					}
					
				}
			}
			if(Synchronization_semaphore[1] == 2)
			{
				if(Synchronization_semaphore[4] == 0)
				{
					if(PUT_BAMBOO(a_craw,85,150,220) == 1)
					{
						SET_TIME(75);
						Runing_V_ST(900,30);
						Synchronization_semaphore[4] = 1;
					}
					
				}
				if(Synchronization_semaphore[4] == 1)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						RED_SMALL_STEP = 40;
						Runing_V_ST(0,30);
						//Synchronization_semaphore[4] = 7;
					}
					else
					{
						Runing_V_ST(900,30);
					}
					
				}
				
				
			}
			
			
		}
		if(RED_SMALL_STEP == 40)
		{
			SET_TIME(160);
			move_rotat_init(MAP_data.YAW);
			move_rotat_angle(1000,311,MAP_data.YAW,1384);
			RED_SMALL_STEP = 41;
					
		}
		if(RED_SMALL_STEP == 41)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,30);
				Synchronization_semaphore[4] = 8;
				RED_SMALL_STEP = 42;
						
			}
			else
			{
				move_rotat_angle(1550,311,MAP_data.YAW,1384);
			}
			
		}
		if(RED_SMALL_STEP == 42)
		{
			if(PUT_BAMBOO(a_craw,85,180,250) == 1)
			{
				RED_SMALL_STEP = 43;
				claw_control(A_CLAW,CLAW_OPEN);
			}
		}
		if(RED_SMALL_STEP == 43)
		{
			
		}
		if(RED_SMALL_STEP == 100)
		{
			;
		}
	}
	if(RED_STEP == 3)
	{
		if(RED_SMALL_STEP == 0)
		{
			SET_TIME(180);   //1S
			gd_control(100);
			claw_control(C2_CLAW,CLAW_OPEN);
			claw_control(C1_CLAW,CLAW_OPEN);
			RED_SMALL_STEP = 1;
		}
		if(RED_SMALL_STEP == 1)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				//Runing_V_ST(1200,180);
				move_rotat_angle(1280,0,MAP_data.YAW,353);
			}
			else
			{
				Runing_V_ST(0,180);
				RED_SMALL_STEP = 2;
			}
		}
		if(RED_SMALL_STEP == 2)
		{
			if(Run_angle(MAP_data.YAW,353)==1)
			{
				RED_SMALL_STEP = 3;
			}
		}
		if(RED_SMALL_STEP == 3)
		{
			SET_TIME(128);
			gd_control(20);
			Runing_V_ST(1560,90);
			RED_SMALL_STEP = 4;
		}
		if(RED_SMALL_STEP == 4)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				BEEP = !BEEP;
			}
			else
			{
				Runing_V_ST(0,90);
				RED_SMALL_STEP = 5;
			}
		}
		if(RED_SMALL_STEP == 5)
		{
			if(Close_move(Direction_C,95) == 0)
			{
				BEEP = !BEEP;
			}
			else
			{
				BEEP_OFF;
				gd_control(10);
				RED_SMALL_STEP = 6;
			}
		}
		if(RED_SMALL_STEP == 6)
		{
			if((-3<(10-TOP_STATUS.TOP_GD))&&((10-TOP_STATUS.TOP_GD)<3))
			{
				claw_control(C2_CLAW,CLAW_CLOSE);
				delay_ms(50);
				claw_control(C1_CLAW,CLAW_CLOSE);        //抓起第一个地标
				RED_SMALL_STEP = 7;
				SET_TIME(60);            //爪子响应慢，需要多100MS
			}
		}
		if(RED_SMALL_STEP == 7)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(255);
				RED_SMALL_STEP = 8;
			}	
		}
		if(RED_SMALL_STEP == 8)
		{
			if(ROAT_AIMANGLE(RA_WHEEL,MAP_data.YAW,1679) == 1)
			{
				SET_TIME(45);
				RED_SMALL_STEP = 9;
			}
		}
		if(RED_SMALL_STEP == 9)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Runing_V_ST(1200,90);
			}
			else
			{
				RED_SMALL_STEP = 10;
			}
		}
		if(RED_SMALL_STEP == 10)
		{
			if(Close_move(Direction_C,70) == 1)
			{
				Runing_V_ST(0,90);
				RED_SMALL_STEP = 11;
			}
		}
		if(RED_SMALL_STEP == 11)
		{
			if(near_read(near_C) == 0)
			{
				Runing_V_ST(380,270);
			}
			else
			{
				Runing_V_ST(0,270);
				gd_control(140);
				RED_SMALL_STEP = 12;
			}
			
		}
		if(RED_SMALL_STEP == 12)
		{
			if((-4<(140-TOP_STATUS.TOP_GD))&&((140-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_OPEN);    //放置第一个地标
				SET_TIME(30);						//爪子等待时间
				RED_SMALL_STEP = 13;
			}
		}
		if(RED_SMALL_STEP == 13)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				claw_control(C2_CLAW,CLAW_CLOSE); 
				SET_TIME(30);						//爪子等待时间
				RED_SMALL_STEP = 14;
			}
		}
		if(RED_SMALL_STEP == 14)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(253);
				RED_SMALL_STEP = 15;
			}
		}
		if(RED_SMALL_STEP == 15)
		{
			if((-4<(253-TOP_STATUS.TOP_GD))&&((253-TOP_STATUS.TOP_GD)<4))
			{
				RED_SMALL_STEP = 16;
				SET_TIME(40);
			}
		}
		if(RED_SMALL_STEP == 16)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				RED_SMALL_STEP = 17;
			}
			else
			{
				Runing_V_ST(1200,270);
			}
		
		}
		if(RED_SMALL_STEP == 17)
		{
			SET_TIME(200);
			move_rotat_init(MAP_data.YAW);
			move_rotat_angle(1000,-25,MAP_data.YAW,355);
			RED_SMALL_STEP = 18;
		}
		if(RED_SMALL_STEP == 18)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				RED_SMALL_STEP = 19;
			}
			else
			{
				move_rotat_angle(1450,-25,MAP_data.YAW,355);
			}
		}
		if(RED_SMALL_STEP == 19)
		{
			if(Run_angle(MAP_data.YAW,355) == 1)
			{
				Runing_V_ST(0,270);
				RED_SMALL_STEP = 20;
			}
		}
		if(RED_SMALL_STEP == 20)
		{
			if(Close_move(Direction_C,75) == 1)			//靠近第二个竹子
			{
				Runing_V_ST(0,90);
				RED_SMALL_STEP = 21;
				//TIME_SHOW();
			}
		}
		if(RED_SMALL_STEP == 21)
		{
			if(near_read(near_C) != 0)
			{
				Runing_V_ST(100,90);
			}
			else
			{
				Runing_V_ST(0,270);
				gd_control(150);
				RED_SMALL_STEP = 22;
			}
		}
		if(RED_SMALL_STEP == 22)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,2512) == 1)
			{
				Synchronization_semaphore[0] = 1;
			}
			if((-4<(150-TOP_STATUS.TOP_GD))&&((150-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_OPEN);    //放置第2个地标
				SET_TIME(30);						//爪子等待时间
				RED_SMALL_STEP = 23;
				
			}
		}
		if(RED_SMALL_STEP == 23)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,2512) == 1)
			{
				Synchronization_semaphore[0] = 1;
			}
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Synchronization_semaphore[1] = 1;
			}
			if(Synchronization_semaphore[0] == 1&&Synchronization_semaphore[1] == 1)
			{
				Synchronization_semaphore[0] = 0;
				Synchronization_semaphore[1] = 1;
				SET_TIME(71);
				claw_control(A_CLAW,CLAW_OPEN);
				RED_SMALL_STEP = 24;
			}
		}
		if(RED_SMALL_STEP == 24)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				gd_control(60);
				RED_SMALL_STEP = 25;
				
			}
			else
			{
				Runing_V_ST(1410,270);
			}
		}
		if(RED_SMALL_STEP == 25)
		{
			SET_TIME(44);             //43可用
			gd_control(50);
			Runing_V_ST(0,210);
			RED_SMALL_STEP = 26;
		}
		if(RED_SMALL_STEP == 26)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,210);
				delay_ms(100);
				RED_SMALL_STEP = 27;
				camear_color(TARGET_GREED);                       /********************颜色指令***********************/
			}
			else
			{
				Runing_V_ST(1250,210);
			}
		}
		if(RED_SMALL_STEP == 27)
		{
			if(Close_move(Direction_A,98) == 1)      //找到第二个竹子
			{
				
				if((-4<(10-TOP_STATUS.TOP_GD))&&((10-TOP_STATUS.TOP_GD)<4))
				{
					claw_control(A_CLAW,CLAW_CLOSE);
					SET_TIME(45);
					RED_SMALL_STEP = 28;
					
				}
				else
				{
					gd_control(10);
				}
				
			}
		}
		if(RED_SMALL_STEP == 28)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(190);
				RED_SMALL_STEP = 29;
				//Clear_VBB(MAP_data.YAW);
			}
		}
		if(RED_SMALL_STEP == 29)
		{
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,1270,4878,1380,1500)==1)
			{
				RED_SMALL_STEP = 30;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,1270,4878,1380,1500);
			}
		}
		if(RED_SMALL_STEP == 30)
		{
			if(Close_move(Direction_C,85) == 1)			
			{
				Runing_V_ST(0,90);
				gd_control(120);
				RED_SMALL_STEP = 31;
			}
		}
		if(RED_SMALL_STEP == 31)
		{
			if((-4<(120-TOP_STATUS.TOP_GD))&&((120-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C1_CLAW,CLAW_OPEN);
				SET_TIME(50);
				RED_SMALL_STEP = 32;
			}
			else
			{
				if(near_read(near_C) == 0)
				{
					Runing_V_ST(200,270);
				}
				else
				{
					Runing_V_ST(0,90);
				}
			}
		}
		if(RED_SMALL_STEP == 32)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				if(near_read(near_C) == 0)
				{
					gd_control(220);
					Runing_V_ST(0,90);
					RED_SMALL_STEP = 33;
				}
				else
				{
					Runing_V_ST(100,90);
				}
			}
			
		}
		if(RED_SMALL_STEP == 33)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,214)==1)
			{
				SET_TIME(50);
				Runing_V_ST(1000,270);
				RED_SMALL_STEP = 35;
			}
			else
			{
				ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,214);
			}
		}
		if(RED_SMALL_STEP == 35)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				RED_SMALL_STEP = 36;
			}
			else
			{
				Runing_V_ST(1000,270);
			}
		}
		if(RED_SMALL_STEP == 36)
		{
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-115,5009,336,1500)==1)
			{
				RED_SMALL_STEP = 37;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-115,5009,336,1500);
			}
		}
		if(RED_SMALL_STEP == 37)
		{
			if(Objective_cheak(TARGET_READ.object_x,TARGET_READ.object_y) == 1)
			{
				BEEP_ON;
				Synchronization_semaphore[4]=0;
				Synchronization_semaphore[2]++;
				if(Synchronization_semaphore[2] == 30)
				{
					Synchronization_semaphore[3] = 0;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[1] = 1;       //有目标
					int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,-1200);
					RED_SMALL_STEP = 38;
					
				}
				
			}
			else
			{
				Synchronization_semaphore[3]++;
				if(Synchronization_semaphore[3] == 30)
				{
					RED_SMALL_STEP = 38;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[3] = 0;			//回复为0
					Synchronization_semaphore[1] = 2;			//没有目标
					BEEP_OFF;
				}
				
			}
		}
		
		if(RED_SMALL_STEP == 38)
		{
			if(Synchronization_semaphore[1] == 1)
			{
				if(Synchronization_semaphore[4] == 0)      //目标处理
				{
					if(Run_angle(MAP_data.YAW,int16_semaphore[0]) == 1)
					{
						BEEP_OFF;
						Synchronization_semaphore[4] = 1;
					}
					else
					{
						Run_angle(MAP_data.YAW,int16_semaphore[0]);
					}
				}	
				if(Synchronization_semaphore[4] == 1)
				{
					if(GRAB_BAMBOO(b_craw,85,100,85,250)==1)
					{
						SET_TIME(50);
						Runing_V_ST(1200,150);
						Synchronization_semaphore[4]  = 2;
					}	
				}
				if(Synchronization_semaphore[4] == 2)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,150);
						int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,1200);
						Synchronization_semaphore[4] = 3;
					}
					else
					{
						Runing_V_ST(1200,150);
					}
				}
				if(Synchronization_semaphore[4] == 3)
				{
					if(Run_angle(MAP_data.YAW,int16_semaphore[0]) == 1)
					{
						Synchronization_semaphore[4] = 4;
						SET_TIME(50);
						Runing_V_ST(900,210);
					}
					else
					{
						Run_angle(MAP_data.YAW,int16_semaphore[0]);
					}
					
				}
				if(Synchronization_semaphore[4] == 4)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,210);
						Synchronization_semaphore[4] = 5;
					}
					else
					{
						Runing_V_ST(900,210);
					}
				}
				if(Synchronization_semaphore[4] == 5)
				{
					if(PUT_BAMBOO(a_craw,87,150,220) == 1)
					{
						SET_TIME(75);
						Runing_V_ST(900,30);
						Synchronization_semaphore[4] = 6;
					}
					
				}
				if(Synchronization_semaphore[4] == 6)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						RED_SMALL_STEP = 39;
						Runing_V_ST(0,30);
						//Synchronization_semaphore[4] = 7;
					}
					else
					{
						Runing_V_ST(900,30);
					}
					
				}
			}
			if(Synchronization_semaphore[1] == 2)
			{
				if(Synchronization_semaphore[4] == 0)
				{
					if(PUT_BAMBOO(a_craw,87,150,220) == 1)
					{
						SET_TIME(75);
						Runing_V_ST(900,30);
						Synchronization_semaphore[4] = 1;
					}
					
				}
				if(Synchronization_semaphore[4] == 1)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						RED_SMALL_STEP = 39;
						Runing_V_ST(0,30);
						//Synchronization_semaphore[4] = 7;
					}
					else
					{
						Runing_V_ST(900,30);
					}
					
				}
			}
			
			
		}
		if(RED_SMALL_STEP == 39)
		{
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-330,3850,1435,1500)==1)
			{
				RED_SMALL_STEP = 40;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-330,3850,1435,1500);
			}
			
		}
		if(RED_SMALL_STEP == 40)
		{
			if(PUT_BAMBOO(a_craw,90,180,250) == 1)
			{
				RED_SMALL_STEP = 41;
				claw_control(A_CLAW,CLAW_OPEN);
			}
		}
		if(RED_SMALL_STEP == 41)
		{
			if(ROAT_AIMANGLE(RA_SIDE,MAP_data.YAW,2497)==1)
			{
				SET_TIME(75);
				Runing_V_ST(900,30);
				RED_SMALL_STEP = 42;
			}
			else
			{
				ROAT_AIMANGLE(RA_SIDE,MAP_data.YAW,2497);
			}
		}
		if(RED_SMALL_STEP == 42)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,30);
				gd_control(45);
				RED_SMALL_STEP = 43;
			}
			
		}
		if(RED_SMALL_STEP == 43)
		{
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-2355,1292,1124,1500)==1)
			{
				RED_SMALL_STEP = 44;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-2355,1292,1124,1500);
			}
			
		}
		if(RED_SMALL_STEP == 44)
		{
			if(GRAB_BAMBOO(a_craw,85,45,10,250)==1)
			{
				Synchronization_semaphore[4] = 0;
				claw_control(B_CLAW,CLAW_OPEN);
				Runing_V_ST(1200,150);
				Synchronization_semaphore[4] = 2;
				RED_SMALL_STEP = 45;
			}
			
		}
		if(RED_SMALL_STEP == 45)
		{
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-1425,3993,3083,1500)==1)
			{
				RED_SMALL_STEP = 46;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-1425,3993,3083,1500);
			}
		}
		if(RED_SMALL_STEP == 46)
		{
			if(Objective_cheak(TARGET_READ.object_x,TARGET_READ.object_y) == 1)
			{
				BEEP_ON;
				Synchronization_semaphore[4]=0;
				Synchronization_semaphore[2]++;
				if(Synchronization_semaphore[2] == 30)
				{
					Synchronization_semaphore[4] = 0;
					Synchronization_semaphore[3] = 0;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[1] = 1;       //有目标
					int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,-1200);
					RED_SMALL_STEP = 47;
					
				}
				
			}
			else
			{
				Synchronization_semaphore[3]++;
				if(Synchronization_semaphore[3] == 30)
				{
					RED_SMALL_STEP = 47;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[3] = 0;			//回复为0
					Synchronization_semaphore[1] = 2;			//没有目标
					Synchronization_semaphore[4] = 0;
					BEEP_OFF;
				}
				
			}
			
		}
		if(RED_SMALL_STEP == 47)
		{
			if(Synchronization_semaphore[1] == 1)
			{
				if(Synchronization_semaphore[4] == 0)      //目标处理
				{
					if(Run_angle(MAP_data.YAW,int16_semaphore[0]) == 1)
					{
						BEEP_OFF;
						Synchronization_semaphore[4] = 1;
					}
					else
					{
						Run_angle(MAP_data.YAW,int16_semaphore[0]);
					}
				}	
				if(Synchronization_semaphore[4] == 1)
				{
					if(GRAB_BAMBOO(b_craw,85,100,85,250)==1)
					{
						SET_TIME(50);
						Runing_V_ST(1200,150);
						Synchronization_semaphore[4]  = 2;
					}	
				}
				if(Synchronization_semaphore[4] == 2)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,150);
						int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,1200);
						Synchronization_semaphore[4] = 3;
					}
					else
					{
						Runing_V_ST(1200,150);
					}
				}
				if(Synchronization_semaphore[4] == 3)
				{
					if(Run_angle(MAP_data.YAW,int16_semaphore[0]) == 1)
					{
						Synchronization_semaphore[4] = 4;
						SET_TIME(50);
						Runing_V_ST(900,210);
					}
					else
					{
						Run_angle(MAP_data.YAW,int16_semaphore[0]);
					}
					
				}
				if(Synchronization_semaphore[4] == 4)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,210);
						Synchronization_semaphore[4] = 5;
					}
					else
					{
						Runing_V_ST(900,210);
					}
				}
				if(Synchronization_semaphore[4] == 5)
				{
					if(PUT_BAMBOO(a_craw,87,150,220) == 1)
					{
						//SET_TIME(75);
						//Runing_V_ST(900,30);
						Synchronization_semaphore[4] =0;
						claw_control(A_CLAW,CLAW_OPEN);
						Synchronization_semaphore[4] = 6;
					}
					
				}
//				if(Synchronization_semaphore[4] == 6)
//				{
//					if(CHEAK_TIMEFINISH() == TIME_YES)
//					{
//						RED_SMALL_STEP = 48;
//						Runing_V_ST(0,30);
//						Synchronization_semaphore[4] = 0;
//					}
//					else
//					{
//						Runing_V_ST(900,30);
//					}
//					
//				}
			}
			if(Synchronization_semaphore[1] == 2)
			{
				if(Synchronization_semaphore[4] == 0)
				{
					if(PUT_BAMBOO(a_craw,87,150,220) == 1)
					{
						//SET_TIME(75);
						//Runing_V_ST(900,30);
						RED_SMALL_STEP = 48;
						Synchronization_semaphore[4] = 1;
					}
					
				}
//				if(Synchronization_semaphore[4] == 1)
//				{
//					if(CHEAK_TIMEFINISH() == TIME_YES)
//					{
//						RED_SMALL_STEP = 48;
//						Runing_V_ST(0,30);
//						Synchronization_semaphore[4] =0;
//						claw_control(A_CLAW,CLAW_OPEN);
//						//Synchronization_semaphore[4] = 7;
//					}
//					else
//					{
//						Runing_V_ST(900,30);
//					}
//				}
			}
		}
		if(RED_SMALL_STEP == 48)
		{
			TIME_SHOW();
			
		}
		if(RED_SMALL_STEP == 100)
		{
			;
		}
			
	}
	if(RED_STEP == 4)
	{
		if(RED_SMALL_STEP == 0)
		{
			SET_TIME(180);   //1S
			gd_control(100);
			claw_control(C2_CLAW,CLAW_OPEN);
			claw_control(C1_CLAW,CLAW_OPEN);
			RED_SMALL_STEP = 1;
		}
		if(RED_SMALL_STEP == 1)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				//Runing_V_ST(1200,180);
				move_rotat_angle(1280,0,MAP_data.YAW,353);
			}
			else
			{
				Runing_V_ST(0,180);
				RED_SMALL_STEP = 2;
			}
		}
		if(RED_SMALL_STEP == 2)
		{
			if(Run_angle(MAP_data.YAW,353)==1)
			{
				RED_SMALL_STEP = 3;
			}
		}
		if(RED_SMALL_STEP == 3)
		{
			SET_TIME(128);
			gd_control(20);
			Runing_V_ST(1560,90);
			RED_SMALL_STEP = 4;
		}
		if(RED_SMALL_STEP == 4)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				BEEP = !BEEP;
			}
			else
			{
				Runing_V_ST(0,90);
				RED_SMALL_STEP = 5;
			}
		}
		if(RED_SMALL_STEP == 5)
		{
			if(Close_move(Direction_C,95) == 0)
			{
				BEEP = !BEEP;
			}
			else
			{
				BEEP_OFF;
				gd_control(10);
				RED_SMALL_STEP = 6;
			}
		}
		if(RED_SMALL_STEP == 6)
		{
			if((-3<(10-TOP_STATUS.TOP_GD))&&((10-TOP_STATUS.TOP_GD)<3))
			{
				claw_control(C2_CLAW,CLAW_CLOSE);
				delay_ms(50);
				claw_control(C1_CLAW,CLAW_CLOSE);        //抓起第一个地标
				RED_SMALL_STEP = 7;
				SET_TIME(60);            //爪子响应慢，需要多100MS
			}
		}
		if(RED_SMALL_STEP == 7)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(255);
				RED_SMALL_STEP = 8;
			}	
		}
		if(RED_SMALL_STEP == 8)
		{
			if(ROAT_AIMANGLE(RA_WHEEL,MAP_data.YAW,1679) == 1)
			{
				SET_TIME(45);
				camear_color(TARGET_GREED);                         //发送颜色指令
				RED_SMALL_STEP = 9;
			}
		}
		if(RED_SMALL_STEP == 9)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Runing_V_ST(1200,90);
			}
			else
			{
				RED_SMALL_STEP = 10;
			}
		}
		if(RED_SMALL_STEP == 10)
		{
			if(Close_move(Direction_C,70) == 1)
			{
				Runing_V_ST(0,90);
				RED_SMALL_STEP = 11;
			}
		}
		if(RED_SMALL_STEP == 11)
		{
			if(near_read(near_C) == 0)
			{
				Runing_V_ST(380,270);
			}
			else
			{
				Runing_V_ST(0,270);
				gd_control(140);
				RED_SMALL_STEP = 12;
			}
				
		}
		if(RED_SMALL_STEP == 12)
		{
			if((-4<(140-TOP_STATUS.TOP_GD))&&((140-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_OPEN);    //放置第一个地标
				SET_TIME(30);						//爪子等待时间
				RED_SMALL_STEP = 13;
			}
		}
		if(RED_SMALL_STEP == 13)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				claw_control(C2_CLAW,CLAW_CLOSE); 
				SET_TIME(30);						//爪子等待时间
				RED_SMALL_STEP = 14;
			}
		}
		if(RED_SMALL_STEP == 14)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(253);
				RED_SMALL_STEP = 15;
			}
		}
		if(RED_SMALL_STEP == 15)
		{
			if((-4<(253-TOP_STATUS.TOP_GD))&&((253-TOP_STATUS.TOP_GD)<4))
			{
				C_CRAW_NUMBER = 3;
				RED_SMALL_STEP = 16;
			}
		}
		if(RED_SMALL_STEP == 16)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,2879)== 1)
			{
				SET_TIME(75);
				Runing_V_ST(1000,270);
				RED_SMALL_STEP = 17;
			}
		}
		if(RED_SMALL_STEP == 17)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(180);
			}
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,365,3329,2686,1500)==1)
			{
				RED_SMALL_STEP = 18;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,365,3329,2686,1500);
			}
		}	
		if(RED_SMALL_STEP == 18)
		{
			if(Objective_cheak(TARGET_READ.object_x,TARGET_READ.object_y) == 1)
			{
				BEEP_ON;
				Synchronization_semaphore[4]=0;
				Synchronization_semaphore[2]++;
				if(Synchronization_semaphore[2] == 30)
				{
					Synchronization_semaphore[4] = 0;
					Synchronization_semaphore[3] = 0;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[1] = 1;       //有目标
					//int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,-1200);
					RED_SMALL_STEP = 19;
				}
			}
			else
			{
				Synchronization_semaphore[3]++;
				if(Synchronization_semaphore[3] == 30)
				{
					RED_SMALL_STEP = 19;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[3] = 0;			//回复为0
					Synchronization_semaphore[1] = 2;			//没有目标
					Synchronization_semaphore[4] = 0;
					BEEP_OFF;
				}
				
			}
		}
		if(RED_SMALL_STEP == 19)
		{
			if(Synchronization_semaphore[1] == 1)       //有目标
			{
				BEEP_OFF;
				if(Synchronization_semaphore[4] == 0)
				{
					if(GRAB_BAMBOO(a_craw,85,110,80,250) == 1)
					{
						SET_TIME(50);
						Runing_V_ST(1200,30);
						//delay_ms(50);
						Synchronization_semaphore[4] = 1;
					}
				}
				if(Synchronization_semaphore[4] == 1)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,30);
						//claw_control(A_CLAW,CLAW_OPEN);
						gd_control(200);
						Synchronization_semaphore[4] = 2;
					}
				}
				if(Synchronization_semaphore[4] == 2)
				{
					if(Run_angle(MAP_data.YAW,1906) == 1)
					{
						Runing_V_ST(0,30);
						claw_control(A_CLAW,CLAW_OPEN);
						Synchronization_semaphore[4] = 3;
						SET_TIME(50);
						Runing_V_ST(1000,30);
						//RED_SMALL_STEP = 20;
					}
				}
				if(Synchronization_semaphore[4] == 3)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,30);
						
						Synchronization_semaphore[4] = 4;
						RED_SMALL_STEP = 20;
					}
				}
			} 
			if(Synchronization_semaphore[1] == 2)		// 没有目标
			{
				RED_SMALL_STEP = 20;
			}
		}
		if(RED_SMALL_STEP == 20)
		{
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,464,4544,2931,1500)==1)
			{
				RED_SMALL_STEP = 21;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,464,4544,2931,1500);
			}
		}
		if(RED_SMALL_STEP == 21)
		{
			if(Objective_cheak(TARGET_READ.object_x,TARGET_READ.object_y) == 1)
			{
				BEEP_ON;
				Synchronization_semaphore[4]=0;
				Synchronization_semaphore[2]++;
				if(Synchronization_semaphore[2] == 30)
				{
					Synchronization_semaphore[4] = 0;
					Synchronization_semaphore[3] = 0;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[1] = 1;       //有目标
					
					RED_SMALL_STEP = 22;
				}
			}
			else
			{
				Synchronization_semaphore[3]++;
				if(Synchronization_semaphore[3] == 30)
				{
					RED_SMALL_STEP = 22;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[3] = 0;			//回复为0
					Synchronization_semaphore[1] = 2;			//没有目标
					Synchronization_semaphore[4] = 0;
					int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,1200);
					BEEP_OFF;
				}
				
			}
		}
		if(RED_SMALL_STEP == 22)
		{
			if(Synchronization_semaphore[1] == 1)
			{
					if(Synchronization_semaphore[4] == 0)
					{
						BEEP_OFF;
						if(GRAB_BAMBOO(a_craw,85,110,80,250) == 1)
						{
							SET_TIME(50);
							Runing_V_ST(1200,30);
							delay_ms(300);
							Synchronization_semaphore[4] = 1;
						}
					}
					if(Synchronization_semaphore[4] == 1)
					{
						if(CHEAK_TIMEFINISH() == TIME_YES)
						{
							Runing_V_ST(0,30);
							claw_control(A_CLAW,CLAW_OPEN);
							Synchronization_semaphore[4] = 2;
							int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,1200);
							RED_SMALL_STEP = 23;
						}
					}					
			}
			if(Synchronization_semaphore[1] == 2)
			{
				RED_SMALL_STEP = 23;
			}
			
		}
		if(RED_SMALL_STEP == 23)
		{
			if(Run_angle(MAP_data.YAW,int16_semaphore[0]) == 1)
			{
				SET_TIME(50);
				Runing_V_ST(850,90);
				RED_SMALL_STEP = 24;
			}
			
		}
		if(RED_SMALL_STEP == 24)
		{
			if(CHEAK_TIMEFINISH() ==TIME_YES)
			{
				Runing_V_ST(0,210);
				RED_SMALL_STEP = 25;
			}
		}
		if(RED_SMALL_STEP == 25)
		{
			if(PUT_BAMBOO(c_craw,95,120,220) == 1)
			{
				SET_TIME(50);
				Runing_V_ST(800,270);
				RED_SMALL_STEP = 26;
			}
		}
		if(RED_SMALL_STEP == 26)
		{
			if(CHEAK_TIMEFINISH() ==TIME_YES)
			{
				Runing_V_ST(0,270);
				RED_SMALL_STEP = 27;
			}
		}
		if(RED_SMALL_STEP == 27)
		{
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-790,3877,201,1500)==1)
			{
				RED_SMALL_STEP = 28;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-790,3877,201,1500);
			}
		}
		if(RED_SMALL_STEP == 28)
		{
			if(Objective_cheak(TARGET_READ.object_x,TARGET_READ.object_y) == 1)
			{
				BEEP_ON;
				Synchronization_semaphore[4]=0;
				Synchronization_semaphore[2]++;
				if(Synchronization_semaphore[2] == 30)
				{
					Synchronization_semaphore[4] = 0;
					Synchronization_semaphore[3] = 0;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[1] = 1;       //有目标
					
					RED_SMALL_STEP = 29;
				}
			}
			else
			{
				Synchronization_semaphore[3]++;
				if(Synchronization_semaphore[3] == 30)
				{
					RED_SMALL_STEP = 29;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[3] = 0;			//回复为0
					Synchronization_semaphore[1] = 2;			//没有目标
					Synchronization_semaphore[4] = 0;
					int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,1200);
					BEEP_OFF;
				}
				
			}
		}
		if(RED_SMALL_STEP == 29)
		{
			if(Synchronization_semaphore[1] == 1)
			{
					if(Synchronization_semaphore[4] == 0)
					{
						BEEP_OFF;
						if(GRAB_BAMBOO(a_craw,85,110,80,250) == 1)
						{
							SET_TIME(50);
							Runing_V_ST(1200,30);
							delay_ms(300);
							Synchronization_semaphore[4] = 1;
						}
					}
					if(Synchronization_semaphore[4] == 1)
					{
						if(CHEAK_TIMEFINISH() == TIME_YES)
						{
							Runing_V_ST(0,30);
							//claw_control(A_CLAW,CLAW_OPEN);
							Synchronization_semaphore[4] = 2;
							int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,1200);
							RED_SMALL_STEP = 30;
						}
					}					
			}
			if(Synchronization_semaphore[1] == 2)
			{
				RED_SMALL_STEP = 30;
			}
		}
		if(RED_SMALL_STEP == 30)
		{
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-2917,2218,2211,1500)==1)
			{
				claw_control(A_CLAW,CLAW_OPEN);  
				RED_SMALL_STEP = 31;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-2917,2218,2211,1500);
			}
		}
		if(RED_SMALL_STEP == 31)
		{
			if(Close_move(Direction_C,95) == 0)
			{
				BEEP = !BEEP;
			}
			else
			{
				BEEP_OFF;
				gd_control(140);
				RED_SMALL_STEP = 32;
			}
		}
		if(RED_SMALL_STEP == 32)
		{
			if((-4<(140-TOP_STATUS.TOP_GD))&&((140-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_OPEN);    //放置第一个地标
				SET_TIME(30);						//爪子等待时间
				RED_SMALL_STEP = 33;
			}
		}
		if(RED_SMALL_STEP == 33)
		{
			if(near_read(near_C)==0)
			{
				Runing_V_ST(0,90);
				gd_control(220);
				RED_SMALL_STEP = 34;
			}
			else
			{
				Runing_V_ST(100,90);
				BEEP_ON;
			}
			//Runing_V_ST(0,270);
		}
		if(RED_SMALL_STEP == 34)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,3504) == 1)
			{
				BEEP_OFF;
				RED_SMALL_STEP = 35;
			}
		}
		if(RED_SMALL_STEP == 35)
		{
			SET_TIME(70);
			Runing_V_ST(1000,260);
			claw_control(A_CLAW,CLAW_OPEN);
			RED_SMALL_STEP = 36;
		}
		if(RED_SMALL_STEP == 36)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				BEEP_ON;
				Runing_V_ST(1200,260);
			}
			else
			{
				gd_control(80);
				BEEP_OFF;
				RED_SMALL_STEP = 37;
			}
		}
		if(RED_SMALL_STEP == 37)
		{
			SET_TIME(80);
			gd_control(30);      //降低高度
			Runing_V_ST(600,230);
			RED_SMALL_STEP = 38;
		}
		if(RED_SMALL_STEP == 38)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Runing_V_ST(900,210);
			}
			else
			{
				RED_SMALL_STEP = 39;
			}
		}
		if(RED_SMALL_STEP == 39)
		{
			if(Close_move(Direction_A,85) == 1)
			{
				Runing_V_ST(0,210);
				gd_control(10);
				RED_SMALL_STEP = 39;
			}
		}
		if(RED_SMALL_STEP == 39)
		{
			if((-4<(10-TOP_STATUS.TOP_GD))&&((10-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(A_CLAW,CLAW_CLOSE);        //抓起第二个地标
				//BEEP_ON;
				RED_SMALL_STEP = 40;
				delay_ms(500);
				gd_control(250);
			}
			
		}
		if(RED_SMALL_STEP == 40)
		{
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-1493,3798,3009,1500)==1)
			{
				RED_SMALL_STEP = 41;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-1493,3798,3009,1500);
			}
		}
		if(RED_SMALL_STEP == 41)
		{
			if(PUT_BAMBOO(a_craw,90,150,220) == 1)
			{
				SET_TIME(70);
				Runing_V_ST(1200,30);
				RED_SMALL_STEP = 42;
			}
		}
		if(RED_SMALL_STEP == 42)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,210);
				RED_SMALL_STEP = 43;
			}
		}
		if(RED_SMALL_STEP == 43)
		{
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-890,3105,2377,1500)==1)
			{
				RED_SMALL_STEP = 44;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-890,3105,2377,1500);
			}
		}
		if(RED_SMALL_STEP == 44)
		{
			if(PUT_BAMBOO(a_craw,90,180,220) == 1)
			{
				//Runing_V_ST(1200,30);
				claw_control(A_CLAW,CLAW_OPEN);
				RED_SMALL_STEP = 85;
				TIME_SHOW();
			}
		}
		if(RED_SMALL_STEP == 85)
		{
			;
		}
	
	}
	
	
}


void PANDA_GREED(void)
{
	OLED_ShowNum(100,0,GREED_SMALL_STEP,2,12);
	var[4] = GREED_SMALL_STEP*100;
	var[5] = read_usetime();
	/*****************************************/
	if(GREED_STEP == 0)
	{
		/*****************************************/
		if(GREED_SMALL_STEP == 0)
		{
			SET_TIME(180);   //1S
			gd_control(100);
			claw_control(C2_CLAW,CLAW_OPEN);
			claw_control(C1_CLAW,CLAW_OPEN);
			GREED_SMALL_STEP = 1;
		}
		if(GREED_SMALL_STEP == 1)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				//Runing_V_ST(1200,180);
				move_rotat_angle(1280,0,MAP_data.YAW,353);
			}
			else
			{
				Runing_V_ST(0,180);
				GREED_SMALL_STEP = 2;
			}
		}
		if(GREED_SMALL_STEP == 2)
		{
			if(Run_angle(MAP_data.YAW,353)==1)
			{
				GREED_SMALL_STEP = 3;
			}
		}
		if(GREED_SMALL_STEP == 3)
		{
			SET_TIME(128);
			gd_control(20);
			Runing_V_ST(1560,90);
			GREED_SMALL_STEP = 4;
		}
		if(GREED_SMALL_STEP == 4)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				BEEP = !BEEP;
			}
			else
			{
				Runing_V_ST(0,90);
				GREED_SMALL_STEP = 5;
			}
		}
		if(GREED_SMALL_STEP == 5)
		{
			if(Close_move(Direction_C,95) == 0)
			{
				BEEP = !BEEP;
			}
			else
			{
				BEEP_OFF;
				gd_control(10);
				GREED_SMALL_STEP = 6;
			}
		}
		if(GREED_SMALL_STEP == 6)
		{
			if((-4<(10-TOP_STATUS.TOP_GD))&&((10-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_CLOSE);
				delay_ms(10);
				claw_control(C1_CLAW,CLAW_CLOSE);        //抓起第一个地标
				GREED_SMALL_STEP = 7;
				SET_TIME(60);            //爪子响应慢，需要多100MS
			}
		}
		if(GREED_SMALL_STEP == 7)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(255);
				GREED_SMALL_STEP = 8;
			}	
		}
		if(GREED_SMALL_STEP == 8)
		{
			if(ROAT_AIMANGLE(RA_WHEEL,MAP_data.YAW,1679) == 1)
			{
				SET_TIME(45);
				GREED_SMALL_STEP = 9;
			}
		}
		if(GREED_SMALL_STEP == 9)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Runing_V_ST(1200,90);
			}
			else
			{
				GREED_SMALL_STEP = 10;
			}
		}
		if(GREED_SMALL_STEP == 10)
		{
			if(Close_move(Direction_C,70) == 1)
			{
				Runing_V_ST(0,90);
				GREED_SMALL_STEP = 11;
			}
		}
		if(GREED_SMALL_STEP == 11)
		{
			if(near_read(near_C) == 0)
			{
				Runing_V_ST(360,270);
			}
			else
			{
				Runing_V_ST(0,270);
				gd_control(140);
				GREED_SMALL_STEP = 12;
			}
			
		}
		if(GREED_SMALL_STEP == 12)
		{
			if((-4<(140-TOP_STATUS.TOP_GD))&&((140-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_OPEN);    //放置第一个地标
				SET_TIME(30);						//爪子等待时间
				GREED_SMALL_STEP = 13;
			}
		}
		if(GREED_SMALL_STEP == 13)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				claw_control(C2_CLAW,CLAW_CLOSE); 
				SET_TIME(30);						//爪子等待时间
				GREED_SMALL_STEP = 14;
			}
		}
		if(GREED_SMALL_STEP == 14)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(253);
				GREED_SMALL_STEP = 15;
			}
		}
		if(GREED_SMALL_STEP == 15)
		{
			if((-4<(253-TOP_STATUS.TOP_GD))&&((253-TOP_STATUS.TOP_GD)<4))
			{
				GREED_SMALL_STEP = 16;
				SET_TIME(40);
			}
		}
		if(GREED_SMALL_STEP == 16)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				GREED_SMALL_STEP = 17;
			}
			else
			{
				Runing_V_ST(1200,270);
			}
		
		}
		if(GREED_SMALL_STEP == 17)
		{
			SET_TIME(200);
			move_rotat_init(MAP_data.YAW);
			move_rotat_angle(1000,-26,MAP_data.YAW,355);
			GREED_SMALL_STEP = 18;
		}
		if(GREED_SMALL_STEP == 18)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				GREED_SMALL_STEP = 19;
			}
			else
			{
				move_rotat_angle(1450,-25,MAP_data.YAW,355);
			}
		}
		if(GREED_SMALL_STEP == 19)
		{
			if(Run_angle(MAP_data.YAW,355) == 1)
			{
				Runing_V_ST(0,270);
				GREED_SMALL_STEP = 20;
			}
		}
		if(GREED_SMALL_STEP == 20)
		{
			if(Close_move(Direction_C,75) == 1)			//靠近第二个竹子
			{
				Runing_V_ST(0,90);
				GREED_SMALL_STEP = 21;
				//TIME_SHOW();
			}
		}
		if(GREED_SMALL_STEP == 21)
		{
			if(near_read(near_C) != 0)
			{
				Runing_V_ST(100,90);
			}
			else
			{
				Runing_V_ST(0,270);
				gd_control(150);
				GREED_SMALL_STEP = 22;
			}
		}
		if(GREED_SMALL_STEP == 22)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,2512) == 1)
			{
				Synchronization_semaphore[0] = 1;
			}
			if((-4<(150-TOP_STATUS.TOP_GD))&&((150-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_OPEN);    //放置第2个地标
				SET_TIME(30);						//爪子等待时间
				GREED_SMALL_STEP = 23;
				
			}
		}
		if(GREED_SMALL_STEP == 23)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,2512) == 1)
			{
				Synchronization_semaphore[0] = 1;
			}
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Synchronization_semaphore[1] = 1;
			}
			if(Synchronization_semaphore[0] == 1&&Synchronization_semaphore[1] == 1)
			{
				Synchronization_semaphore[0] = 0;
				Synchronization_semaphore[1] = 1;
				SET_TIME(71);
				claw_control(A_CLAW,CLAW_OPEN);
				GREED_SMALL_STEP = 24;
			}
		}
		if(GREED_SMALL_STEP == 24)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				gd_control(60);
				GREED_SMALL_STEP = 25;
				
			}
			else
			{
				Runing_V_ST(1410,270);
			}
		}
		if(GREED_SMALL_STEP == 25)
		{
			SET_TIME(44);             //43可用
			gd_control(50);
			Runing_V_ST(0,210);
			GREED_SMALL_STEP = 26;
		}
		if(GREED_SMALL_STEP == 26)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,210);
				delay_ms(100);
				GREED_SMALL_STEP = 27;
				
			}
			else
			{
				Runing_V_ST(1250,210);
			}
		}
		if(GREED_SMALL_STEP == 27)
		{
			if(Close_move(Direction_A,98) == 1)      //找到第二个竹子
			{
				
				if((-4<(10-TOP_STATUS.TOP_GD))&&((10-TOP_STATUS.TOP_GD)<4))
				{
					claw_control(A_CLAW,CLAW_CLOSE);
					SET_TIME(45);
					GREED_SMALL_STEP = 28;
					
				}
				else
				{
					gd_control(10);
				}
				
			}
			else
			{
				Close_move(Direction_A,98);
			}
		}
		if(GREED_SMALL_STEP == 28)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(180);
				GREED_SMALL_STEP = 29;
			}
		}
		if(GREED_SMALL_STEP == 29)
		{
			SET_TIME(200);
			move_rotat_init(MAP_data.YAW);
			move_rotat_angle(1000,21,MAP_data.YAW,1700);
			GREED_SMALL_STEP = 30;
		}
		if(GREED_SMALL_STEP == 30)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				GREED_SMALL_STEP = 31;
				Runing_V_ST(0,270);
				TIME_SHOW();
			}
			else
			{
				move_rotat_angle(2200,21,MAP_data.YAW,1700);
			}
		}
		if(GREED_SMALL_STEP == 31)
		{
			SET_TIME(81);
			move_rotat_angle(1500,21,MAP_data.YAW,1700);
			GREED_SMALL_STEP = 32;
		}
		if(GREED_SMALL_STEP == 32)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				GREED_SMALL_STEP = 33;
				Runing_V_ST(0,270);
				
			}
			else
			{
				move_rotat_angle(1500,21,MAP_data.YAW,1700);
			}
		}
		if(GREED_SMALL_STEP == 33)
		{
			if(Close_move(Direction_C,90) == 1)
			{
				Runing_V_ST(0,90);
				
				gd_control(60);
				GREED_SMALL_STEP = 34;
			}
			else
			{
				Close_move(Direction_C,98);
			}
		}
		if(GREED_SMALL_STEP == 34)
		{
			if((-4<(60-TOP_STATUS.TOP_GD))&&((60-TOP_STATUS.TOP_GD)<4))    //公共区第一个竹子
			{
				claw_control(C1_CLAW,CLAW_OPEN);
				SET_TIME(10);
				GREED_SMALL_STEP = 35;
			}
			else
			{
				if(near_read(near_C) == 0)   //触碰到了	
				{
					Runing_V_ST(450,270);
				}
				else
				{
					Runing_V_ST(0,270);
				}
			}
			
		}
		if(GREED_SMALL_STEP == 35)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(250);
				GREED_SMALL_STEP = 36;
			}
			
		}
		if(GREED_SMALL_STEP == 36)
		{
			if(near_read(near_C) == 1)   //为触碰到开关
			{
				Runing_V_ST(150,90);
			}
			else
			{
				Runing_V_ST(0,90);
				GREED_SMALL_STEP = 37;
			}
		}
		if(GREED_SMALL_STEP == 37)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,220) == 1)
			{
				GREED_SMALL_STEP = 38;
			}
			else
			{
				ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,220);
			}
		}
		if(GREED_SMALL_STEP == 38)
		{
			SET_TIME(50);
			Runing_V_ST(1000,270);
			GREED_SMALL_STEP = 39;
		}
		if(GREED_SMALL_STEP == 39)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				GREED_SMALL_STEP = 40;
			}
		}
		if(GREED_SMALL_STEP == 40)
		{
			SET_TIME(100);
			Runing_V_ST(1000,210);
			GREED_SMALL_STEP = 41;
		}
		if(GREED_SMALL_STEP == 41)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				GREED_SMALL_STEP = 42;
			}
		}
		if(GREED_SMALL_STEP == 42)
		{
			Synchronization_semaphore[0] = PUT_BAMBOO(a_craw,90,150,220);  //放置第二个竹子
			if(Synchronization_semaphore[0] == 1)
			{
				GREED_SMALL_STEP = 43;
				Synchronization_semaphore[0] = 0;
			}
		}
		if(GREED_SMALL_STEP == 43)
		{
			if(ROAT_AIMANGLE(RA_SIDE,MAP_data.YAW,1080) == 1)
			{
				SET_TIME(50);
				Runing_V_ST(1300,30);
				GREED_SMALL_STEP = 44;
			}
			else
			{
				ROAT_AIMANGLE(RA_SIDE,MAP_data.YAW,1080);
			}
		}
		if(GREED_SMALL_STEP == 44)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				GREED_SMALL_STEP = 45;
				Synchronization_semaphore[0] = 0;
				move_rotat_init(MAP_data.YAW);
				move_rotat_angle(200,270,MAP_data.YAW,2892);
			}
			else
			{
				Runing_V_ST(1000,30);
			}
		}
		if(GREED_SMALL_STEP == 45)
		{
			Synchronization_semaphore[1] = move_rotat_angle(600,30,MAP_data.YAW,2892);
			if(Synchronization_semaphore[1] == 1)
			{
				Synchronization_semaphore[1] = 0;
				Runing_V_ST(0,210);
				GREED_SMALL_STEP = 46;
				
			}
		}
		if(GREED_SMALL_STEP == 46)
		{
			Synchronization_semaphore[1] = PUT_BAMBOO(a_craw,80,150,220);  //放置第三个竹子
			if(Synchronization_semaphore[1] == 1)
			{
				GREED_SMALL_STEP = 100;
				TIME_SHOW();
			}
		}
		if(GREED_SMALL_STEP == 100)
		{
			;
		}
	}

	if(GREED_STEP == 1)
	{
		/*****************************************/
		if(GREED_SMALL_STEP == 0)
		{
			SET_TIME(180);   //1S
			gd_control(100);
			claw_control(C2_CLAW,CLAW_OPEN);
			claw_control(C1_CLAW,CLAW_OPEN);
			GREED_SMALL_STEP = 1;
		}
		if(GREED_SMALL_STEP == 1)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				//Runing_V_ST(1200,180);
				move_rotat_angle(1280,0,MAP_data.YAW,353);
			}
			else
			{
				Runing_V_ST(0,180);
				GREED_SMALL_STEP = 2;
			}
		}
		if(GREED_SMALL_STEP == 2)
		{
			if(Run_angle(MAP_data.YAW,353)==1)
			{
				GREED_SMALL_STEP = 3;
			}
		}
		if(GREED_SMALL_STEP == 3)
		{
			SET_TIME(128);
			gd_control(20);
			Runing_V_ST(1560,90);
			GREED_SMALL_STEP = 4;
		}
		if(GREED_SMALL_STEP == 4)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				BEEP = !BEEP;
			}
			else
			{
				Runing_V_ST(0,90);
				GREED_SMALL_STEP = 5;
			}
		}
		if(GREED_SMALL_STEP == 5)
		{
			if(Close_move(Direction_C,95) == 0)
			{
				BEEP = !BEEP;
			}
			else
			{
				BEEP_OFF;
				gd_control(10);
				GREED_SMALL_STEP = 6;
			}
		}
		if(GREED_SMALL_STEP == 6)
		{
			if((-4<(10-TOP_STATUS.TOP_GD))&&((10-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_CLOSE);
				delay_ms(10);
				claw_control(C1_CLAW,CLAW_CLOSE);        //抓起第一个地标
				GREED_SMALL_STEP = 7;
				SET_TIME(60);            //爪子响应慢，需要多100MS
			}
		}
		if(GREED_SMALL_STEP == 7)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(255);
				GREED_SMALL_STEP = 8;
			}	
		}
		if(GREED_SMALL_STEP == 8)
		{
			if(ROAT_AIMANGLE(RA_WHEEL,MAP_data.YAW,1679) == 1)
			{
				SET_TIME(45);
				GREED_SMALL_STEP = 9;
			}
		}
		if(GREED_SMALL_STEP == 9)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Runing_V_ST(1200,90);
			}
			else
			{
				GREED_SMALL_STEP = 10;
			}
		}
		if(GREED_SMALL_STEP == 10)
		{
			if(Close_move(Direction_C,70) == 1)
			{
				Runing_V_ST(0,90);
				GREED_SMALL_STEP = 11;
			}
		}
		if(GREED_SMALL_STEP == 11)
		{
			if(near_read(near_C) == 0)
			{
				Runing_V_ST(360,270);
			}
			else
			{
				Runing_V_ST(0,270);
				gd_control(140);
				GREED_SMALL_STEP = 12; 
			}
			
		}
		if(GREED_SMALL_STEP == 12)
		{
			if((-4<(140-TOP_STATUS.TOP_GD))&&((140-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_OPEN);    //放置第一个地标
				SET_TIME(30);						//爪子等待时间
				GREED_SMALL_STEP = 13;
			}
		}
		if(GREED_SMALL_STEP == 13)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				claw_control(C2_CLAW,CLAW_CLOSE); 
				SET_TIME(30);						//爪子等待时间
				GREED_SMALL_STEP = 14;
			}
		}
		if(GREED_SMALL_STEP == 14)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(253);
				GREED_SMALL_STEP = 15;
			}
		}
		if(GREED_SMALL_STEP == 15)
		{
			if((-4<(253-TOP_STATUS.TOP_GD))&&((253-TOP_STATUS.TOP_GD)<4))
			{
				GREED_SMALL_STEP = 16;
				SET_TIME(40);
			}
		}
		if(GREED_SMALL_STEP == 16)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				GREED_SMALL_STEP = 17;
			}
			else
			{
				Runing_V_ST(1200,270);
			}
		
		}
		if(GREED_SMALL_STEP == 17)
		{
			SET_TIME(200);
			move_rotat_init(MAP_data.YAW);
			move_rotat_angle(1000,-26,MAP_data.YAW,355);
			GREED_SMALL_STEP = 18;
		}
		if(GREED_SMALL_STEP == 18)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				GREED_SMALL_STEP = 19;
			}
			else
			{
				move_rotat_angle(1450,-25,MAP_data.YAW,355);
			}
		}
		if(GREED_SMALL_STEP == 19)
		{
			if(Run_angle(MAP_data.YAW,355) == 1)
			{
				Runing_V_ST(0,270);
				GREED_SMALL_STEP = 20;
			}
		}
		if(GREED_SMALL_STEP == 20)
		{
			if(Close_move(Direction_C,75) == 1)			//靠近第二个竹子
			{
				Runing_V_ST(0,90);
				GREED_SMALL_STEP = 21;
				//TIME_SHOW();
			}
		}
		if(GREED_SMALL_STEP == 21)
		{
			if(near_read(near_C) != 0)
			{
				Runing_V_ST(100,90);
			}
			else
			{
				Runing_V_ST(0,270);
				gd_control(150);
				GREED_SMALL_STEP = 22;
			}
		}
		if(GREED_SMALL_STEP == 22)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,2512) == 1)
			{
				Synchronization_semaphore[0] = 1;
			}
			if((-4<(150-TOP_STATUS.TOP_GD))&&((150-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_OPEN);    //放置第2个地标
				SET_TIME(30);						//爪子等待时间
				GREED_SMALL_STEP = 23;
				
			}
		}
		if(GREED_SMALL_STEP == 23)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,2512) == 1)
			{
				Synchronization_semaphore[0] = 1;
			}
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Synchronization_semaphore[1] = 1;
			}
			if(Synchronization_semaphore[0] == 1&&Synchronization_semaphore[1] == 1)
			{
				Synchronization_semaphore[0] = 0;
				Synchronization_semaphore[1] = 1;
				SET_TIME(71);
				claw_control(A_CLAW,CLAW_OPEN);
				GREED_SMALL_STEP = 24;
			}
		}
		if(GREED_SMALL_STEP == 24)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,270);
				gd_control(60);
				GREED_SMALL_STEP = 25;
				
			}
			else
			{
				Runing_V_ST(1410,270);
			}
		}
		if(GREED_SMALL_STEP == 25)
		{
			SET_TIME(44);             //43可用
			gd_control(50);
			Runing_V_ST(0,210);
			GREED_SMALL_STEP = 26;
		}
		if(GREED_SMALL_STEP == 26)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,210);
				delay_ms(100);
				GREED_SMALL_STEP = 27;
				
			}
			else
			{
				Runing_V_ST(1250,210);
			}
		}
		if(GREED_SMALL_STEP == 27)
		{
			if(Close_move(Direction_A,98) == 1)      //找到第二个竹子
			{
				
				if((-4<(10-TOP_STATUS.TOP_GD))&&((10-TOP_STATUS.TOP_GD)<4))
				{
					claw_control(A_CLAW,CLAW_CLOSE);
					SET_TIME(45);
					GREED_SMALL_STEP = 28;
					
				}
				else
				{
					gd_control(10);
				}
				
			}
			else
			{
				Close_move(Direction_A,98);
			}
		}
		if(GREED_SMALL_STEP == 28)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				camear_cmd(OV_TARGET);
				camear_color(TARGET_RED);
				gd_control(255);
				GREED_SMALL_STEP = 29;
			}
		}
		if(GREED_SMALL_STEP == 29)
		{
			SET_TIME(169);
			move_rotat_init(MAP_data.YAW);
			move_rotat_angle(1000,-11,MAP_data.YAW,274);
			GREED_SMALL_STEP = 30;
		}
		if(GREED_SMALL_STEP == 30)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				GREED_SMALL_STEP = 31;
				Runing_V_ST(0,270);
				TIME_SHOW();
			}
			else
			{
				move_rotat_angle(2200,-10,MAP_data.YAW,284);
			}
		}
		if(GREED_SMALL_STEP == 31)
		{
			SET_TIME(81);
			move_rotat_angle(1600,-11,MAP_data.YAW,284);
			GREED_SMALL_STEP = 32;
		}
		if(GREED_SMALL_STEP == 32)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{ 
				Runing_V_ST(0,270);
				//SET_TIME(100);
				GREED_SMALL_STEP = 33;	
			}
			else
			{
				CRAW_INPUT(a_craw,ZHUA,4);
				CRAW_INPUT(c_craw,ZHUA,2); 
				move_rotat_angle(1600,-11,MAP_data.YAW,284);
			}
		}
		if(GREED_SMALL_STEP == 33)
		{

			if(Objective_cheak(TARGET_READ.object_x,TARGET_READ.object_y) == 1)
			{
				BEEP_ON;
				Synchronization_semaphore[2]++;
				if(Synchronization_semaphore[2] == 20)
				{
					Synchronization_semaphore[3] = 0;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[1] = 1;       //有目标
					int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,1250);
					GREED_SMALL_STEP = 34;
				}
				
			}
			else
			{
				Synchronization_semaphore[3]++;
				if(Synchronization_semaphore[3] == 20)
				{
					GREED_SMALL_STEP = 34;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[3] = 0;			//回复为0
					Synchronization_semaphore[1] = 2;			//没有目标
					BEEP_OFF;
				}
				
			}
			
		}
		if(GREED_SMALL_STEP == 34)
		{
			if(Synchronization_semaphore[1] == 2)        //没有目标的处理，放地标
			{
				if(PUT_BAMBOO(a_craw,90,150,220)==1)
				{
					Synchronization_semaphore[2] = 0;
					GREED_SMALL_STEP = 35;
				}
			}
			if(Synchronization_semaphore[1] == 1)			//被对发方占领，用c放
			{
				gd_control(90);
				if(Run_angle(MAP_data.YAW,int16_semaphore[0]) == 1)
				{
					BEEP_OFF;
					if(Close_move(Direction_C,95) == 1)
					{
						if((-4<(90-TOP_STATUS.TOP_GD))&&((90-TOP_STATUS.TOP_GD)<4))
						{
							claw_control(C1_CLAW,CLAW_OPEN);
							Synchronization_semaphore[3] = 0;
							GREED_SMALL_STEP = 35;
						}
					}
					//int16_semaphore[0] = 0;    					 //恢复为0
					
				}
				else
				{
					BEEP_ON;
					Run_angle(MAP_data.YAW,int16_semaphore[0]);
				}
				
			}
		}
		
		if(GREED_SMALL_STEP == 35)
		{
			if(Synchronization_semaphore[1] == 2)  				 //假如上个主子上没有对方地标
			{
				if(Synchronization_semaphore[2] == 0)           
				{
					if(ROAT_AIMANGLE(RA_SIDE,MAP_data.YAW,1386) == 1)
					{

						SET_TIME(45);
						Runing_V_ST(1150,30);
						Synchronization_semaphore[2] = 1;		
						
					}
					else
					{
						ROAT_AIMANGLE(RA_SIDE,MAP_data.YAW,1386);			//旋转到1386
					}
				}
				if(Synchronization_semaphore[2] == 1)				
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,30);
						gd_control(150);
						Synchronization_semaphore[2] = 2;
					}
					else
					{
						Runing_V_ST(1200,30);							//脱离竹子
					}
				}
				if(Synchronization_semaphore[2] == 2)
				{
					SET_TIME(75);
					Runing_V_ST(1500,90);
					Synchronization_semaphore[2] = 3;
				}	
				if(Synchronization_semaphore[2] == 3)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,90);
						Synchronization_semaphore[2] = 4;
					}
					
				}
				if(Synchronization_semaphore[2] == 4)
				{
					if(Close_move(Direction_C,102) == 1)
					{
						claw_control(C1_CLAW,CLAW_OPEN);
						SET_TIME(50);
						Synchronization_semaphore[2] = 5;
					}
					else
					{
						Close_move(Direction_C,102);
					}
					
				}
				if(Synchronization_semaphore[2] == 5)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						gd_control(255);
						
						Synchronization_semaphore[2] = 6;
					}
				}
				if(Synchronization_semaphore[2] == 6)
				{
					if(near_read(near_C) == 0)
					{
						Synchronization_semaphore[2] = 7;
						Runing_V_ST(0,90);
					}
					else
					{
						Runing_V_ST(150,90);
					}
					
				}
				if(Synchronization_semaphore[2] == 7)
				{
					if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,534) == 1)
					{
						SET_TIME(50);
						Runing_V_ST(1200,270);
						Synchronization_semaphore[2] = 8;
					}
					else
					{
						ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,534);
					}
				}
				if(Synchronization_semaphore[2] == 8)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,270);
						move_rotat_init(MAP_data.YAW);
						move_rotat_angle(500,270,MAP_data.YAW,1147);
						//SET_TIME(150);
						Synchronization_semaphore[2] = 9;
						
					}
					else
					{
						Runing_V_ST(1200,270);
					}
				}
				if(Synchronization_semaphore[2] == 9)
				{
					if(move_rotat_angle(1300,270,MAP_data.YAW,1147) == 1)
					{
						Runing_V_ST(0,270);
						Synchronization_semaphore[2] = 10;
					}
					else
					{
						move_rotat_angle(1000,270,MAP_data.YAW,1147);
					}	
					
				}
				if(Synchronization_semaphore[2] == 10)
				{
					if(Close_move(Direction_A,90) == 1)
					{
						claw_control(A_CLAW,CLAW_OPEN);
						GREED_SMALL_STEP = 100;
					}
					else
					{
						Close_move(Direction_A,90);
					}
				}
			}
			if(Synchronization_semaphore[1] == 1)   				//假如有地标
			{
				if(Synchronization_semaphore[3] == 0)
				{
					if(near_read(near_C) == 0)
					{
						Runing_V_ST(0,90);
						Synchronization_semaphore[3] = 1;
						
					}
					else
					{
						Runing_V_ST(80,90);
					}
				}
				if(Synchronization_semaphore[3] == 1)				
				{
					if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,2630) == 1)
					{
						SET_TIME(40);
						Runing_V_ST(1150,270);
						
						Synchronization_semaphore[3] = 2;
					}
					else
					{
						ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,2630);
					}
				}
				if(Synchronization_semaphore[3] == 2)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,270);
						gd_control(150);
						Synchronization_semaphore[3] = 3;
					}
					else
					{
						Runing_V_ST(1200,270);							//脱离竹子
					}
				}
				if(Synchronization_semaphore[3] == 3)
				{
					SET_TIME(75);
					Runing_V_ST(1500,330);
					Synchronization_semaphore[3] = 4;
				}	
				if(Synchronization_semaphore[3] == 4)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,330);
						Synchronization_semaphore[3] = 5;
						
					}
					
				}
				if(Synchronization_semaphore[3] == 5)
				{
					if(GRAB_BAMBOO(b_craw,85,100,80,230) == 1)        //用B爪抓
					{
						Synchronization_semaphore[3] = 6;
					}
				}
				if(Synchronization_semaphore[3] == 6)
				{
					if(near_read(near_B) == 0)
					{
						Runing_V_ST(0,330);
						ROAT_AIMANGLE(RB_SIDE,MAP_data.YAW,1785);
						Synchronization_semaphore[3] = 7;
					}
					else
					{
						Runing_V_ST(150,330);
					}
				}
				if(Synchronization_semaphore[3] == 7)
				{
					if(ROAT_AIMANGLE(RB_SIDE,MAP_data.YAW,1785) == 1)   
					{
						SET_TIME(55);
						Runing_V_ST(1250,150);
						Synchronization_semaphore[3] = 8;
					}
					else
					{
						ROAT_AIMANGLE(RB_SIDE,MAP_data.YAW,1785);
					}
				}
				if(Synchronization_semaphore[3] == 8)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,150);
						int16_semaphore[1] = SET_AIM_ANGLE(MAP_data.YAW,-1200);  
						Synchronization_semaphore[3] = 9;
					}
					else
					{
						Runing_V_ST(1250,150);
					}
				}
				if(Synchronization_semaphore[3] == 9)
				{
					if(Run_angle(MAP_data.YAW,int16_semaphore[1]) ==1)
					{
						//GREED_SMALL_STEP = 100;
						Synchronization_semaphore[3] = 10;
					}
					else
					{
						Run_angle(MAP_data.YAW,int16_semaphore[1]);
					}
				}
				if(Synchronization_semaphore[3] == 10)
				{
					SET_TIME(60);
					Runing_V_ST(1200,210);
					Synchronization_semaphore[3] = 11;
				}
				if(Synchronization_semaphore[3] == 11)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						camear_color(TARGET_RED);
						Synchronization_semaphore[3] = 12;
						Runing_V_ST(0,210);
					}
					else
					{
						Runing_V_ST(1200,210);
					}
				}
				if(Synchronization_semaphore[3] == 12)            //下一个点
				{
					if(Objective_cheak(TARGET_READ.object_x,TARGET_READ.object_y) == 1)
					{
						BEEP_ON;
						Synchronization_semaphore[4]++;
						if(Synchronization_semaphore[4] == 20)
						{
							Synchronization_semaphore[3] = 0;
							Synchronization_semaphore[4] = 0;
							Synchronization_semaphore[5] = 0;
							Synchronization_semaphore[1] = 1;       //有目标
							int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,1200);
							GREED_SMALL_STEP = 36;
						}
						
					}
					else
					{
						Synchronization_semaphore[5]++;
						if(Synchronization_semaphore[5] == 20)
						{
							Synchronization_semaphore[3] = 0;
							GREED_SMALL_STEP = 36; 
							Synchronization_semaphore[5] = 0;
							Synchronization_semaphore[4] = 0;			//回复为0
							Synchronization_semaphore[1] = 2;			//没有目标
							BEEP_OFF;
						}
						
					}
				}
								
			}
		}
		if(GREED_SMALL_STEP == 36)
		{
			 if(Synchronization_semaphore[1] == 1)
			 {
				 if(Synchronization_semaphore[3] == 0)
				 {
					 if(Run_angle(MAP_data.YAW,int16_semaphore[0]) == 1)
					{
						BEEP_OFF;
						Synchronization_semaphore[3] = 1;
					}
					else
					{
						Run_angle(MAP_data.YAW,int16_semaphore[0]);
					}
				 }
				 if(Synchronization_semaphore[3] == 1)
				 {
					 if(GRAB_BAMBOO(c_craw,90,100,85,250) == 1)
					 {
						 SET_TIME(50);
						 Runing_V_ST(1200,270);
						Synchronization_semaphore[3] = 2;
					 }
					 else
					 {
						 ;
					 }
				 }
				 if(Synchronization_semaphore[3] == 2)
				 {
					 if(CHEAK_TIMEFINISH() == TIME_YES)
					 {
						Runing_V_ST(0,270);
						int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,-1200);
						 Synchronization_semaphore[3] = 3;
					 }
					 else
					 {
						 Runing_V_ST(1200,270); 
					 }
				 }
				 if(Synchronization_semaphore[3] == 3)
				 {
					 if(Run_angle(MAP_data.YAW,int16_semaphore[0]) == 1)
					 {
						 SET_TIME(50);
						 Runing_V_ST(800,210);
						 Synchronization_semaphore[3] = 4;
					 }
					 else
					 {
						Run_angle(MAP_data.YAW,int16_semaphore[0]); 
					 }
				 }
				 if(Synchronization_semaphore[3] == 4)
				 {
					 if(CHEAK_TIMEFINISH() == TIME_YES)
					 {
						 Synchronization_semaphore[3] = 5;
						 Runing_V_ST(0,210);
					 }
					 else
					 {
						 Runing_V_ST(800,210);
					 }
					 
				 }
				 if(Synchronization_semaphore[3] == 5)
				 {
					 if(PUT_BAMBOO(a_craw,90,150,215) ==1)
					 {
						 SET_TIME(50);
						 Runing_V_ST(1200,30);
						 Synchronization_semaphore[3] = 6;
					 }
					else
					{
						
					}
				 }
				 if(Synchronization_semaphore[3] == 6)
				 {
					 if(CHEAK_TIMEFINISH() == TIME_YES)
					 {
						 Runing_V_ST(0,30);
						 
						 int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,730);
						 GREED_SMALL_STEP = 37;
					 }
				 }
			}
			if(Synchronization_semaphore[1] == 2)    //没有地标
			{
				if(Synchronization_semaphore[3] == 0)
				{
					if(PUT_BAMBOO(a_craw,85,100,215) ==1)
					{
						 SET_TIME(50);
						 Runing_V_ST(1200,30);
						 Synchronization_semaphore[3] = 1;
					}
				}
				if(Synchronization_semaphore[3] == 1)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,30);						 
						int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,730);
						GREED_SMALL_STEP = 37;
					}
				}
			}
		}
		if(GREED_SMALL_STEP == 37)
		{
			if(Run_angle(MAP_data.YAW,int16_semaphore[0]) == 1)
			{
				SET_TIME(100);
				Runing_V_ST(1800,210);
				GREED_SMALL_STEP = 38;
				
			}
			else
			{
				Run_angle(MAP_data.YAW,int16_semaphore[0]);
			}
						
		}
		if(GREED_SMALL_STEP == 38)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,210);
				GREED_SMALL_STEP = 39;
			}
			else
			{
				Runing_V_ST(1800,210);
			}
		}
		if(GREED_SMALL_STEP == 39)
		{
			if(PUT_BAMBOO(a_craw,85,210,255) ==1)
			{
				claw_control(A_CLAW,CLAW_OPEN);
				GREED_SMALL_STEP = 100;
				TIME_SHOW();
			}
		}
		if(GREED_SMALL_STEP == 100)
		{
			;
		}
	}
	if(GREED_STEP == 2)
	{
		/*****************************************/
		if(GREED_SMALL_STEP == 0)
		{
			SET_TIME(180);   //1S
			gd_control(100);
			claw_control(C2_CLAW,CLAW_OPEN);
			claw_control(C1_CLAW,CLAW_OPEN);
			GREED_SMALL_STEP = 1;
		}
		if(GREED_SMALL_STEP == 1)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				//Runing_V_ST(1200,180);
				move_rotat_angle(1280,0,MAP_data.YAW,353);
			}
			else
			{
				Runing_V_ST(0,180);
				GREED_SMALL_STEP = 2;
			}
		}
		if(GREED_SMALL_STEP == 2)
		{
			if(Run_angle(MAP_data.YAW,353)==1)
			{
				GREED_SMALL_STEP = 3;
			}
		}
		if(GREED_SMALL_STEP == 3)
		{
			SET_TIME(128);
			gd_control(20);
			Runing_V_ST(1560,90);
			GREED_SMALL_STEP = 4;
		}
		if(GREED_SMALL_STEP == 4)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				BEEP = !BEEP;
			}
			else
			{
				Runing_V_ST(0,90);
				GREED_SMALL_STEP = 5;
			}
		}
		if(GREED_SMALL_STEP == 5)
		{
			if(Close_move(Direction_C,95) == 0)
			{
				BEEP = !BEEP;
			}
			else
			{
				BEEP_OFF;
				gd_control(10);
			    camear_color(TARGET_RED);                                 /**************************************************/
				GREED_SMALL_STEP = 6;
			}
		}
		if(GREED_SMALL_STEP == 6)
		{
			if((-4<(10-TOP_STATUS.TOP_GD))&&((10-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_CLOSE);
				delay_ms(10);
				claw_control(C1_CLAW,CLAW_CLOSE);        //抓起第一个地标
				GREED_SMALL_STEP = 7;
				SET_TIME(60);            //爪子响应慢，需要多100MS
			}
		}
		if(GREED_SMALL_STEP == 7)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(255);
				GREED_SMALL_STEP = 8;
			}	
		}
		if(GREED_SMALL_STEP == 8)
		{
			if(ROAT_AIMANGLE(RA_WHEEL,MAP_data.YAW,1679) == 1)
			{
				SET_TIME(45);
				GREED_SMALL_STEP = 9;
			}
		}
		if(GREED_SMALL_STEP == 9)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Runing_V_ST(1200,90);
			}
			else
			{
				GREED_SMALL_STEP = 10;
			}
		}
		if(GREED_SMALL_STEP == 10)
		{
			if(Close_move(Direction_C,75) == 1)
			{
				Runing_V_ST(0,90);
				GREED_SMALL_STEP = 11;
			}
		}
		if(GREED_SMALL_STEP == 11)
		{
			if(near_read(near_C) == 0)
			{
				Runing_V_ST(360,270);
			}
			else
			{
				Runing_V_ST(0,270);
				gd_control(140);
				GREED_SMALL_STEP = 12; 
			}
			
		}
		if(GREED_SMALL_STEP == 12)
		{
			if((-4<(140-TOP_STATUS.TOP_GD))&&((140-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_OPEN);    //放置第一个地标
				SET_TIME(30);						//爪子等待时间
				GREED_SMALL_STEP = 13;
			}
		}
		if(GREED_SMALL_STEP == 13)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				claw_control(C2_CLAW,CLAW_CLOSE); 
				SET_TIME(30);						//爪子等待时间
				GREED_SMALL_STEP = 14;
			}
		}
		if(GREED_SMALL_STEP == 14)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(253);
				GREED_SMALL_STEP = 15;
			}
		}
		if(GREED_SMALL_STEP == 15)
		{
			if((-4<(253-TOP_STATUS.TOP_GD))&&((253-TOP_STATUS.TOP_GD)<4))
			{
				GREED_SMALL_STEP = 16;
			}
		}
		if(GREED_SMALL_STEP == 16)
		{
			if(near_read(near_C) == 0)
			{
				Runing_V_ST(0,90);
			}
			else
			{
				Runing_V_ST(150,90);
				GREED_SMALL_STEP = 17; 
			}
		}
		if(GREED_SMALL_STEP == 17)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,2606) == 1)
			{
				SET_TIME(70);
				GREED_SMALL_STEP = 18;
			}
			else
			{
				ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,2606);
			}
			
		}
		if(GREED_SMALL_STEP == 18)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				gd_control(180);
			}
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,871,3761,3081,1500)==1)
			{
				GREED_SMALL_STEP = 19;
				Synchronization_semaphore[3] = 0;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,871,3761,3081,1500);
			}
		}
		if(GREED_SMALL_STEP == 19)
		{
			if(Objective_cheak(TARGET_READ.object_x,TARGET_READ.object_y) == 1)
			{
				//BEEP_ON;
				Synchronization_semaphore[4]=0;
				Synchronization_semaphore[2]++;
				if(Synchronization_semaphore[2] > 30)
				{
					Synchronization_semaphore[4] = 0;
					Synchronization_semaphore[3] = 0;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[1] = 1;       //有目标
					//int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,-1200);
					GREED_SMALL_STEP = 20;
				}
			}
			else
			{
				BEEP_ON;
				Synchronization_semaphore[3]++;
				if(Synchronization_semaphore[3] > 30)
				{
					GREED_SMALL_STEP = 20;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[3] = 0;			//回复为0
					Synchronization_semaphore[1] = 2;			//没有目标
					Synchronization_semaphore[4] = 0;
					BEEP_OFF;
				}
				
			}
		}
		if(GREED_SMALL_STEP == 20)
		{
			if(Synchronization_semaphore[1] == 1)       //有目标
			{
				BEEP_OFF;
				if(Synchronization_semaphore[4] == 0)
				{
					if(GRAB_BAMBOO(a_craw,85,110,80,250) == 1)
					{
						SET_TIME(50);
						Runing_V_ST(1200,30);
						//delay_ms(50);
						Synchronization_semaphore[4] = 1;
					}
				}
				if(Synchronization_semaphore[4] == 1)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,30);
						//claw_control(A_CLAW,CLAW_OPEN);
						gd_control(200);
						Synchronization_semaphore[4] = 2;
					}
				}
				if(Synchronization_semaphore[4] == 2)
				{
					if(Run_angle(MAP_data.YAW,1950) == 1)
					{
						Runing_V_ST(0,30);
						claw_control(A_CLAW,CLAW_OPEN);
						Synchronization_semaphore[4] = 3;
						SET_TIME(50);
						Runing_V_ST(1000,30);
						//RED_SMALL_STEP = 20;
					}
				}
				if(Synchronization_semaphore[4] == 3)
				{
					if(CHEAK_TIMEFINISH() == TIME_YES)
					{
						Runing_V_ST(0,30);
						
						Synchronization_semaphore[4] = 4;
						GREED_SMALL_STEP = 21;
					}
				}
			} 
			if(Synchronization_semaphore[1] == 2)		// 没有目标
			{
				GREED_SMALL_STEP = 21;
			}
		}
		if(GREED_SMALL_STEP == 21)
		{
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,249,4864,3263,1500)==1)
			{
				GREED_SMALL_STEP = 22;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,249,4864,3263,1500);
			}
		}
		if(GREED_SMALL_STEP == 22)
		{
			BEEP_ON;
			if(Objective_cheak(TARGET_READ.object_x,TARGET_READ.object_y) == 1)
			{
				BEEP=!BEEP;
				Synchronization_semaphore[4]=0;
				Synchronization_semaphore[2]++;
				if(Synchronization_semaphore[2] == 30)
				{
					Synchronization_semaphore[4] = 0;
					Synchronization_semaphore[3] = 0;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[1] = 1;       //有目标
					//int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,-1200);
					GREED_SMALL_STEP = 23;
				}
			}
			else
			{
				Synchronization_semaphore[3]++;
				Synchronization_semaphore[4] = 0;
				if(Synchronization_semaphore[3] == 30)
				{
					GREED_SMALL_STEP = 23;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[3] = 0;			//回复为0
					Synchronization_semaphore[1] = 2;			//没有目标
					Synchronization_semaphore[4] = 0;
					int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,1200);
					gd_control(250);
					BEEP_OFF;
				}
				
			}
		}
		if(GREED_SMALL_STEP == 23)
		{
			if(Synchronization_semaphore[1] == 1)
			{
					if(Synchronization_semaphore[4] == 0)
					{
						BEEP_OFF;
						if(GRAB_BAMBOO(a_craw,90,110,85,250) == 1)
						{
							SET_TIME(50);
							Runing_V_ST(1200,30);
							//delay_ms(300);
							Synchronization_semaphore[4] = 1;
						}
					}
					if(Synchronization_semaphore[4] == 1)
					{
						if(CHEAK_TIMEFINISH() == TIME_YES)
						{
							Runing_V_ST(0,30);
							claw_control(A_CLAW,CLAW_OPEN);
							Synchronization_semaphore[4] = 2;
							int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,1200);
							GREED_SMALL_STEP = 24;
						}
					}					
			}
			if(Synchronization_semaphore[1] == 2)
			{
				GREED_SMALL_STEP = 24;
			}
		}
		if(GREED_SMALL_STEP == 24)
		{
			if(Run_angle(MAP_data.YAW,int16_semaphore[0]) == 1)
			{
				SET_TIME(50);
				Runing_V_ST(750,90);
				GREED_SMALL_STEP = 25;
			}
		}
		if(GREED_SMALL_STEP == 25)
		{
			if(CHEAK_TIMEFINISH() ==TIME_YES)
			{
				Runing_V_ST(0,210);
				GREED_SMALL_STEP = 26;
			}
		}
		if(GREED_SMALL_STEP == 26)
		{
			if(PUT_BAMBOO(c_craw,95,120,220) == 1)
			{
				SET_TIME(50);
				Runing_V_ST(800,270);
				GREED_SMALL_STEP = 27;
			}
		}
		if(GREED_SMALL_STEP == 27)
		{
			if(CHEAK_TIMEFINISH() ==TIME_YES)
			{
				Runing_V_ST(0,270);
				GREED_SMALL_STEP = 28;
			}
		}
		if(GREED_SMALL_STEP == 28)
		{
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-1217,4191,1668,1500)==1)
			{
				GREED_SMALL_STEP = 29;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-1217,4191,1668,1500);
			}
		}
		if(GREED_SMALL_STEP == 29)
		{
			if(Objective_cheak(TARGET_READ.object_x,TARGET_READ.object_y) == 1)
			{
				BEEP=!BEEP;
				Synchronization_semaphore[4]=0;
				Synchronization_semaphore[2]++;
				if(Synchronization_semaphore[2] == 30)
				{
					Synchronization_semaphore[4] = 0;
					Synchronization_semaphore[3] = 0;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[1] = 1;       //有目标
					//int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,-1200);
					GREED_SMALL_STEP = 30;
				}
			}
			else
			{
				Synchronization_semaphore[3]++;
				Synchronization_semaphore[4] = 0;
				if(Synchronization_semaphore[3] == 30)
				{
					GREED_SMALL_STEP = 30;
					Synchronization_semaphore[2] = 0;
					Synchronization_semaphore[3] = 0;			//回复为0
					Synchronization_semaphore[1] = 2;			//没有目标
					Synchronization_semaphore[4] = 0;
					int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,1200);
					BEEP_OFF;
				}
			}
		}
		if(GREED_SMALL_STEP == 30)
		{
			if(Synchronization_semaphore[1] == 1)
			{
					if(Synchronization_semaphore[4] == 0)
					{
						BEEP_OFF;
						if(GRAB_BAMBOO(a_craw,85,110,80,250) == 1)
						{
							SET_TIME(50);
							Runing_V_ST(1200,30);
							delay_ms(300);
							Synchronization_semaphore[4] = 1;
						}
					}
					if(Synchronization_semaphore[4] == 1)
					{
						if(CHEAK_TIMEFINISH() == TIME_YES)
						{
							Runing_V_ST(0,30);
							//claw_control(A_CLAW,CLAW_OPEN);
							Synchronization_semaphore[4] = 2;
							int16_semaphore[0] = SET_AIM_ANGLE(MAP_data.YAW,1200);
							GREED_SMALL_STEP = 31;
						}
					}					
			}
			if(Synchronization_semaphore[1] == 2)
			{
				GREED_SMALL_STEP = 31;
			}
		}
		if(GREED_SMALL_STEP == 31)
		{
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-2804,2143,2180,1500)==1)
			{
				claw_control(A_CLAW,CLAW_OPEN);
				GREED_SMALL_STEP = 32;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-2804,2143,2180,1500);
			}
		}
		if(GREED_SMALL_STEP == 32)
		{
			if(Close_move(Direction_C,95) == 0)
			{
				BEEP = !BEEP;
			}
			else
			{
				BEEP_OFF;
				gd_control(140);
				GREED_SMALL_STEP = 33;
			}
		}
		if(GREED_SMALL_STEP == 33)
		{
			if((-4<(140-TOP_STATUS.TOP_GD))&&((140-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(C2_CLAW,CLAW_OPEN);    //放置第一个地标
				SET_TIME(30);						//爪子等待时间
				GREED_SMALL_STEP = 34;
			}
		}
		if(GREED_SMALL_STEP == 34)
		{
			if(near_read(near_C)==0)
			{
				Runing_V_ST(0,90);
				gd_control(220);
				GREED_SMALL_STEP = 35;
			}
			else
			{
				Runing_V_ST(100,90);
				BEEP_ON;
			}
			//Runing_V_ST(0,270);
		}
		if(GREED_SMALL_STEP == 35)
		{
			if(ROAT_AIMANGLE(RC_SIDE,MAP_data.YAW,3504) == 1)
			{
				BEEP_OFF;
				GREED_SMALL_STEP = 36;
			}
		}
		if(GREED_SMALL_STEP == 36)
		{
			SET_TIME(70);
			Runing_V_ST(1000,260);
			GREED_SMALL_STEP = 37;
		}
		if(GREED_SMALL_STEP == 37)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				BEEP_ON;
				Runing_V_ST(1100,260);
			}
			else
			{
				gd_control(80);
				BEEP_OFF;
				GREED_SMALL_STEP = 38;
			}
		}
		if(GREED_SMALL_STEP == 38)
		{
			SET_TIME(80);
			gd_control(30);      //降低高度
			Runing_V_ST(600,230);
			GREED_SMALL_STEP = 39;
		}
		if(GREED_SMALL_STEP == 39)
		{
			if(CHEAK_TIMEFINISH() != TIME_YES)
			{
				Runing_V_ST(900,210);
			}
			else
			{
				GREED_SMALL_STEP = 40;
			}
		}
		if(GREED_SMALL_STEP == 40)
		{
			if(Close_move(Direction_A,85) == 1)
			{
				Runing_V_ST(0,210);
				gd_control(10);
				GREED_SMALL_STEP = 41;
			}
		}
		if(GREED_SMALL_STEP == 41)
		{
			if((-4<(10-TOP_STATUS.TOP_GD))&&((10-TOP_STATUS.TOP_GD)<4))
			{
				claw_control(A_CLAW,CLAW_CLOSE);        //抓起第二个地标
				//BEEP_ON;
				GREED_SMALL_STEP = 42;
				delay_ms(500);
				gd_control(250);
			}
		}
		if(GREED_SMALL_STEP == 42)
		{
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-1000,3092,3309,1500)==1)
			{
				GREED_SMALL_STEP = 43;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-1000,3092,3309,1500);
			}
		}
		if(GREED_SMALL_STEP == 43)
		{
			if(PUT_BAMBOO(a_craw,90,150,220) == 1)
			{
				SET_TIME(70);
				Runing_V_ST(1200,30);
				GREED_SMALL_STEP = 44;
			}
		}
		if(GREED_SMALL_STEP == 44)
		{
			if(CHEAK_TIMEFINISH() == TIME_YES)
			{
				Runing_V_ST(0,210);
				GREED_SMALL_STEP = 45;
			}
		}
		if(GREED_SMALL_STEP == 45)
		{
			if(X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-44,2988,2804,1500)==1)
			{
				GREED_SMALL_STEP = 46;
			}
			else
			{
				X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,-44,2988,2804,1500);
			}
		}
		if(GREED_SMALL_STEP == 46)
		{
			if(PUT_BAMBOO(a_craw,90,180,220) == 1)
			{
				//Runing_V_ST(1200,30);
				claw_control(A_CLAW,CLAW_OPEN);
				GREED_SMALL_STEP = 85;
				TIME_SHOW();
			}
		}
		
		if(GREED_SMALL_STEP == 85)
		{
			;
		}			
	}
	

}





















