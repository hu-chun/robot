#include "top_rx_tx.h"
#include "common.h"
u8 TOP_DATA[2];
CLAW_STATUS TOP_STATUS;
void claw_control(u8 claw_x,CLAW_SW claw_sw)
{
	uint8_t cmdf[2] = {0xAA,0xA9};    				//串口调试 使用的前命令
	uint8_t cmdr[1] = {0x5A};    				//串口调试 使用的后命令
	TOP_DATA[0] = claw_x;
	TOP_DATA[1] =  claw_sw;
	USART_Send_Leng_String(USART_3,cmdf,sizeof(cmdf));    				//先发送前命令
	USART_Send_Leng_String(USART_3,(uint8_t *)TOP_DATA,sizeof(TOP_DATA));//发送数据
	USART_Send_Leng_String(USART_3,cmdr,sizeof(cmdr));    				//发送后命令
}
void gd_control(u8 high)
{
	uint8_t cmdf[2] = {0xAA,0xA9};    				//串口调试 使用的前命令
	uint8_t cmdr[1] = {0x5A};    				//串口调试 使用的后命令
	TOP_DATA[0] = GD_FLAG;
	TOP_DATA[1] =  high;
	USART_Send_Leng_String(USART_3,cmdf,sizeof(cmdf));    				//先发送前命令
	USART_Send_Leng_String(USART_3,(uint8_t *)TOP_DATA,sizeof(TOP_DATA));//发送数据
	USART_Send_Leng_String(USART_3,cmdr,sizeof(cmdr));    				//发送后命令
}
u8 top_wei = 0;
u8 top_data[8];
void USART3_IRQHandler(void)                	
{
	unsigned char date;
	if(USART_GetITStatus(USART3,USART_IT_RXNE))
	{
		USART_ClearFlag(USART3,USART_FLAG_RXNE);
		date = USART_ReceiveData(USART3);
		//USART_SendData(USART3, date);//把接受到的发送回去
		top_data[top_wei++] = date;
		if(top_wei == 1)
		{
			if(top_data[0] != 0xAA)
			{
				top_wei = 0;
			}
		}
		if(top_wei == 8)
		{
			if(top_data[7] != 0x55)
			{
				top_wei = 0;
			}
			else
			{
				TOP_STATUS.TOP_GD  = top_data[1]*256+top_data[2];
				TOP_STATUS.A_FLAG  = top_data[3];
				TOP_STATUS.B_FLAG = top_data[4];
				TOP_STATUS.C1_FLAG  = top_data[5];
				TOP_STATUS.C2_FLAG = top_data[6];
				top_wei = 0;
			}
		}
		
		
	}
}

