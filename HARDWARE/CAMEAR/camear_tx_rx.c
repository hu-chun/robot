#include "camear_tx_rx.h"
#include "common.h"
Color_struct COLOR_READ;
TARGET_struct TARGET_READ;
TARGET_struct2 TARGET_READ2;
u8 color_wei=0;
u8 color_date[21]={0};
u8 OV2640_mode = OV_CHOOSE;
u8 ov_frame;
u8 OV_TARGET_COLOTR = 0;    //追踪模式的追踪颜色。0：没有意义，1：红色，2：绿色，3：蓝色
void camear_cmd(ov_mode mode)
{
	if(mode == OV_TARGET)
	{
		USART_Send_String(USART_4,"hTc");    //目标追踪
	}
	if(mode == OV_COLOR)
	{
		USART_Send_String(USART_4,"hCc");   //颜色识别
	}
	if(mode == OV_CHOOSE)
	{
		USART_Send_String(USART_4,"hPc"); //选择模式
	}
}
void camear_color(TARGET_COLOR target_color)
{
	if(target_color == TARGET_RED)
	{
		USART_Send_String(USART_4,"hRc");
	}
	if(target_color == TARGET_GREED)
	{
		USART_Send_String(USART_4,"hGc");
	}
	if(target_color == TARGET_BLUE)
	{
		USART_Send_String(USART_4,"hBc");
	}
	
}
void UART4_IRQHandler(void)                	
{
	unsigned char date;
	if(USART_GetITStatus(UART4,USART_IT_RXNE))
	{
		USART_ClearFlag(UART4,USART_FLAG_RXNE);
		date = USART_ReceiveData(UART4);
		//USART_SendData(USART3, date);//把接受到的发送回去
		color_date[color_wei++] = date;
		if(color_wei == 1)
		{
			if(color_date[0] != 0xCC)
			{
				color_wei = 0;
			}
		}
		if(color_wei == 21)
		{
			if(color_date[20] != 0xa9)
			{
				color_wei = 0;
			}
			else
			{
				OV2640_mode = color_date[1];
				TARGET_READ.object_x = color_date[2]<<8|color_date[3];
				TARGET_READ.object_y = color_date[4]<<8|color_date[5];
				TARGET_READ.object_w = color_date[6]<<8|color_date[7];
				TARGET_READ.object_h = color_date[8]<<8|color_date[9];
				COLOR_READ.hord = color_date[10];
				COLOR_READ.bottom = color_date[11];
				COLOR_READ.middle = color_date[12];
				COLOR_READ.top  = color_date[13];
				ov_frame = color_date[14];
				ov_frame = color_date[15];
				TARGET_READ2.object_x = color_date[16]<<8|color_date[17];
				TARGET_READ2.object_y = color_date[18]<<8|color_date[19];
				LED1=!LED1;
				color_wei = 0;
			}
			
		}
	}
}










