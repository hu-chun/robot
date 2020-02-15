#include "remotecontrol.h"
#include "common.h"
int16_t x0 = 2000;
int16_t y0 = 2000;
u16 yaw0 = 0;
static u8 tmp_buf[12];	
/*************************遥控器控制程序****************************/
u8 Remote_control(void)
{
	if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息
	{
		//OLED_ShowString(0,6,tmp_buf,12);
		if(tmp_buf[0]==0x55)
		{
			y0=tmp_buf[2]<<8|tmp_buf[3];
			x0=tmp_buf[4]<<8|tmp_buf[5];
			yaw0=tmp_buf[6]<<8|tmp_buf[7];
//			OLED_ShowNum(64,0,x0,4,12);					//0-4000
//			OLED_ShowNum(64,1,y0,4,12);					//0-4000
//			OLED_ShowNum(64,2,yaw0,4,12);				//0-720
			LED0=!LED0;	 
			if(x0>1950&&x0<2050)
			{
				x0 = 0;
			}
			else if(x0>=2550)
			{
				x0 =2550 - x0;
			}
			else
			{
				x0 = 1950 - x0;
			}
			if(y0>1950&&y0<2050)
			{
				y0 = 0;
			}
			else if(y0>=2550)
			{
				y0 = 2550 - y0;
			}
			else
			{
				y0 = 1950 - y0;
			}
			if(yaw0 < 2)
			{
				Run_X_Y(x0,y0);
			}
			else
			{
				if(y0 == 0)
				{
					if(x0 >20)
					{
						Runing_rotat(-yaw0);
					}
					else if(x0 < -20)
					{
						Runing_rotat(yaw0);
					}
					else
						;
					
					}
					if(y0 == 0&&x0==0)
					{
						Runing_rotat(0);
					}
			}		
		}
		return 1;
	}
	else
		return 0;
}













