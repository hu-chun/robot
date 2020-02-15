#include "sys.h"
#include "delay.h"
#include "common.h"
extern int16_t var[8];
extern u8 RED_STEP ;
extern u8 GREED_STEP ;
u8 Map_Coordinate[102][102];
u8 fgg = 0;
RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;
u8 PLAN_flag=0;
u8 MODE_CHOSE = 0;              // 1:红 2：绿 3:遥控 4：测试
int8_t KEY_CHOSE = 0;				//红方绿方对应的模式。遥控和测试没有
void text_program(void);
void DATA_SHOW(void);
int main(void)
{ 
	u8 tmp_buf[12];	
 	u16 key;
	u8 flag = 0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  			//初始化延时函数
	//my_mem_init(SRAMEX);		//初始化外部内存池
	//my_mem_init(SRAMCCM);		//初始化CCM内存池
	Peripherals_init();
	NRF24L01_RX_Mode();	
	while(flag == 0)
	{
		if(MODE_CHOSE == 1)
		{
				if(KEY_CHOSE == 1)        //1
				{
					RED_STEP = 0;
					if(PLAN_flag==1)
					{
						flag = 1;
					}
					
				}
				else if(KEY_CHOSE == 2)
				{
					RED_STEP = 1;
					if(PLAN_flag==1)
					{
						flag = 1;
					}
				}
				else if(KEY_CHOSE == 3)
				{
					RED_STEP = 2;
					if(PLAN_flag==1)
					{
						flag = 1;
					}
				}
				else if(KEY_CHOSE == 4)
				{
					RED_STEP = 3;
					if(PLAN_flag==1)
					{
						flag = 1;
					}
				}
				else if(KEY_CHOSE == 5)
				{
					RED_STEP = 4;
					if(PLAN_flag==1)
					{
						flag = 1;
					}
				}
				else
				{
					PLAN_flag  = 0;
					flag = 0;
				}
			OLED_ShowString(30,0,"red mode   ",16);
			OLED_ShowString(0,2,"RED_STEP:   ",16);
			OLED_ShowNum(100,2,RED_STEP,1,16);
			
		}
		if(MODE_CHOSE == 2)
		{
				if(KEY_CHOSE == 1)        //1
				{
					GREED_STEP = 0;
					if(PLAN_flag==1)
					{
						flag = 1;
					}
				}
				else if(KEY_CHOSE == 2)
				{
					GREED_STEP = 1;
					if(PLAN_flag==1)
					{
						flag = 1;
					}
				}
				else if(KEY_CHOSE == 3)
				{
					GREED_STEP = 2;
					if(PLAN_flag==1)
					{
						flag = 1;
					}
				}
				else if(KEY_CHOSE == 4)
				{
					GREED_STEP = 3;
					if(PLAN_flag==1)
					{
						flag = 1;
					}
				}
				else if(KEY_CHOSE == 5)
				{
					GREED_STEP = 4;
					if(PLAN_flag==1)
					{
						flag = 1;
					}
				}
				else
				{
					PLAN_flag  = 0;
					flag = 0;
				}
			OLED_ShowString(30,0,"greed mode ",16);
			OLED_ShowString(0,2,"GREED_STEP: ",16);
			OLED_ShowNum(100,2,GREED_STEP,1,16);
		}
		if(MODE_CHOSE == 3)
		{
			if(PLAN_flag == 1)
			{
				flag = 1;
			}
			OLED_ShowString(30,0,"remote mode  ",16);
		}
		if(MODE_CHOSE == 4)
		{
			if(PLAN_flag == 1)
			{
				flag = 1;
			}
			OLED_ShowString(30,0,"test mode   ",16);
		}
		if(MODE_CHOSE == 0)
		{
			OLED_ShowString(30,0,"place chose ",16);
			//delay_ms(200);
			//OLED_Clear();
		}
		OLED_ShowNum(100,4,MODE_CHOSE,1,16);
	}
	BEEP_OFF;
	gd_control(200);
	move_rotat_init(MAP_data.YAW);
	Clear_VBB(MAP_data.YAW);
	camear_color(TARGET_GREED);
	OLED_Clear();
	BEEP_OFF;
	delay_ms(1000);
	usetime_clear();
 	while(1)
	{
		if(MODE_CHOSE == 1)
		{
			PANDA_RED();
		}
		if(MODE_CHOSE == 2)
		{
			PANDA_GREED();
		}
		if(MODE_CHOSE == 3)
		{
			Remote_control();
		}
		if(MODE_CHOSE == 4)
		{
			text_program();
		}
		key=KEY_Scan(0);
//		if(key == 1)
//		{
//			camear_cmd(OV_TARGET);
//		}
//		else if(key == 2)
//		{
//			camear_cmd(OV_COLOR);
//		}
//		else if(key == 3)
//		{
//			camear_cmd(OV_CHOOSE);
//		}
		//LED1=!LED1;	
		var[3]=MAP_data.YAW;
		//var[4]=MAP_data.X;
		//var[5]=MAP_data.Y;
		USART_SendWare((u16 *)var,sizeof(var));    //发送到上位机
		fgg++;
		if(fgg == 255)
		{
			fgg = 0;
		}
		if(fgg%100 == 0)
		{
			RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
			sprintf((char*)tmp_buf,"%02d:%02d:%02d",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds); 
			OLED_ShowString(0,7,tmp_buf,12);
		}
		if(fgg%20 == 0)
		{
			DATA_SHOW();
		}
		delay_ms(5);
	}
}

void text_program(void)
{
	int static a =0;
	//		if(fgg>128)
//		{
//			Runing_V_ST(300,270);//(-50);
//		}
//		else
//		{
//			Runing_V_ST(300,90);//Runing_rotat(50);
//		}
		//Runing_rotat(0);
		//Runing_V_ST(500,270);
		//Run_angle(MAP_data.YAW,1500);
		//Independ_run(MAP_data.X,MAP_data.Y,0,1000);
		//move_rotat(500,90,MAP_data.YAW,400);
		//move_rotat_angle(0,90,MAP_data.YAW,900); 
		//Close_move(Direction_B,125);
		//ROAT_POINT(RA_SIDE,-400);
		//Run_X_Y(100,100);
		//move_X_Y_roata(500,0,MAP_data.YAW,100);
		//X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,0,1000,0,1500);
//		Camear_control_run(200);
		if(near_read(near_C)==0)
		{
			BEEP_ON; 
		}
		else
		{
			BEEP_OFF;
		}
		//Close_proximity(Direction_C);
		//Close_move(Direction_A,100);
		//ROAT_AIMANGLE(RA_WHEEL,MAP_data.YAW,2100);
		//Keep_distance(Direction_A,320);
//		if(Objective_cheak(TARGET_READ.object_x,TARGET_READ.object_y) == 1)
//		{
//			BEEP_ON;
//		}
//		else
//		{
//			BEEP_OFF;
//		}
		//Camear_jiaozheng();
		SUM_YAW(MAP_data.YAW);
		if(a == 0)
		{
			//a = PUT_BAMBOO(b_craw,80,120,210);
			//a = GRAB_BAMBOO(c_craw,80,100,80,250); 
			a=X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,2000,2000,2400,1500);
			//BEEP_ON;
		}
		if(a == 1)
		{
			X_Y_ANGELE_AIM(MAP_data.X,MAP_data.Y,MAP_data.YAW,0,0,900,1500);
			//BEEP_OFF;
		}
		
}


void DATA_SHOW(void)
{
	
	OLED_ShowNum(0,0,var[0],4,12);
	OLED_ShowNum(0,1,var[1],4,12);
	OLED_ShowNum(0,2,var[2],4,12);
	OLED_ShowNum(0,3,MAP_data.X,7,12);
	OLED_ShowNum(0,4,MAP_data.Y,7,12);
	OLED_ShowNum(0,5,MAP_data.YAW,4,12);
	OLED_ShowNum(0,6,TOP_STATUS.TOP_GD,3,12);
	OLED_ShowNum(64,0,ULTRSONIC_DIS.U_A1,4,12);					
	OLED_ShowNum(64,1,ULTRSONIC_DIS.U_A2,4,12);					
	OLED_ShowNum(64,2,ULTRSONIC_DIS.U_B1,4,12);
	OLED_ShowNum(64,3,ULTRSONIC_DIS.U_B2,4,12);					
	OLED_ShowNum(64,4,ULTRSONIC_DIS.U_C1,4,12);					
	OLED_ShowNum(64,5,ULTRSONIC_DIS.U_C2,4,12);
	OLED_ShowNum(100,7,TARGET_READ.object_x,4,12);
	OLED_ShowNum(80,7,PLAN_flag,1,12);
	
}






