
#include "map_rx_tx.h"
#include "common.h"
ULTRSONIC_DATA ULTRSONIC_DIS;
/*定义共同体用来储存定位模块发过来的数据*/
union date
{
	char date1[4];
	float date2;
}X1,Y1,YAW1;
MAP_struct	MAP_data;
unsigned char RE_date[27];
unsigned char WEI = 0;
unsigned char RE_flag;
extern int16_t var[8];
void USART2_IRQHandler(void)                	
{
	unsigned char date;
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
	{
		USART_ClearFlag(USART2,USART_FLAG_RXNE);
		date = USART_ReceiveData(USART2);
		RE_date[WEI++] = date;
		if(WEI == 1)
		{
			if(RE_date[0] != 0XCC)
			{
				WEI = 0;	
			}
		}
		if(WEI == 2)
		{
			if(RE_date[1] != 0XAA)
			{
				WEI = 0;
			}
		}
		if(WEI > 2)
		{
			if(WEI<7)
			{
				X1.date1[WEI - 3] = RE_date[WEI - 1];
			}
			else if(WEI>=7&&WEI<11)
			{
				Y1.date1[WEI - 7] = RE_date[WEI - 1];
			}
			else if(WEI>=11&&WEI<15)
			{
				YAW1.date1[WEI - 11] = RE_date[WEI - 1];
			}
			if(WEI == 27)
			{
				if(RE_date[WEI - 1] == 0XAA)
				{
					WEI = 0;
					RE_flag = 1;
					MAP_data.X=X1.date2;
					MAP_data.Y=Y1.date2;
					MAP_data.YAW=YAW1.date2;
					ULTRSONIC_DIS.U_A1 = RE_date[15]<<8|RE_date[14];
					ULTRSONIC_DIS.U_A2 = RE_date[17]<<8|RE_date[16];
					ULTRSONIC_DIS.U_B1 = RE_date[19]<<8|RE_date[18];
					ULTRSONIC_DIS.U_B2 = RE_date[21]<<8|RE_date[20];
					ULTRSONIC_DIS.U_C1 = RE_date[23]<<8|RE_date[22];
					ULTRSONIC_DIS.U_C2 = RE_date[25]<<8|RE_date[24];
					var[6] = ULTRSONIC_DIS.U_C1;
					var[7] = ULTRSONIC_DIS.U_C2;
					LED0 =~LED0;
				}	
				else
				{
					WEI = 0;
					RE_flag = 0;
				}
			}
		}
		//USART_SendData(USART2, date);//把接受到的发送回去
	}
}




