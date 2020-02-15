#include "sys.h"
#include "oled.h"
#include "oledfont.h"
u8 OLED_GRAM[128][8];
//OLED_SPI延迟函数

void OLED_delay(void)
{
	uint16_t i=1;
	while(i)
	{
		i--;
	}
}

//OLED_GPIO配置
void OLED_GPIO_Config(void)
{
//CS 推挽输出
	GPIO_InitTypeDef OLED_GPIO_InitStructure;		
	RCC_AHB1PeriphClockCmd(OLED_CS_RCC_AHB1Periph_GPIO,ENABLE);
	OLED_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	OLED_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	OLED_GPIO_InitStructure.GPIO_Pin = OLED_CS_GPIO_Pin;	
	OLED_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(OLED_CS_GPIO,&OLED_GPIO_InitStructure);
//DC 推挽输出
	RCC_AHB1PeriphClockCmd(OLED_DC_RCC_AHB1Periph_GPIO,ENABLE);
	OLED_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	OLED_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	OLED_GPIO_InitStructure.GPIO_Pin = OLED_DC_GPIO_Pin;
	OLED_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(OLED_DC_GPIO,&OLED_GPIO_InitStructure);
//SCLK 开漏输出加外部上拉
	RCC_AHB1PeriphClockCmd(OLED_SCLK_RCC_AHB1Periph_GPIO,ENABLE);
	OLED_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	OLED_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	OLED_GPIO_InitStructure.GPIO_Pin = OLED_SCLK_GPIO_Pin;	
	OLED_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(OLED_SCLK_GPIO,&OLED_GPIO_InitStructure);
//SDIN 开漏输出加外部上拉
	RCC_AHB1PeriphClockCmd(OLED_SDIN_RCC_AHB1Periph_GPIO,ENABLE);
	OLED_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	OLED_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	OLED_GPIO_InitStructure.GPIO_Pin = OLED_SDIN_GPIO_Pin;	
	OLED_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(OLED_SDIN_GPIO,&OLED_GPIO_InitStructure);	
//RES 推挽输出
	RCC_AHB1PeriphClockCmd(OLED_RES_RCC_AHB1Periph_GPIO,ENABLE);
	OLED_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	OLED_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	OLED_GPIO_InitStructure.GPIO_Pin = OLED_RES_GPIO_Pin;	
	OLED_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(OLED_RES_GPIO,&OLED_GPIO_InitStructure);
}

//OLED 4-wire SPI写一个字节
void OLED_Write_Byte(uint8_t data,uint8_t order)
{
	uint8_t i=0;
	if(order)
	{
		OLED_DC_H;
	}
	else
	{
		OLED_DC_L;
	}
	OLED_CS_L;
	OLED_delay();
	for(i=0;i<8;i++)
	{
		OLED_SCLK_L;
		OLED_delay();
		if(data & 0x80)
		{
			OLED_SDIN_H;
		}
		else
		{
			OLED_SDIN_L;
		}
		OLED_SCLK_H;
		data <<= 1;
		OLED_delay();
	}
	OLED_DC_H;
	OLED_delay();	
	OLED_CS_H;
	OLED_delay();
}

//写指令
void OLED_Write_CMD(uint8_t address)
{
	OLED_Write_Byte(address,CMD);
}

//写数据
void OLED_Write_DATA(uint8_t address,uint8_t data)
{
	OLED_Write_Byte(address,CMD);
	OLED_Write_Byte(data,DATA);
}

//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_Write_Byte (0xb0+i,CMD);    //设置页地址（0~7）
		OLED_Write_Byte (0x02,CMD);      //设置显示位置—列低地址
		OLED_Write_Byte (0x10,CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_Write_Byte(0,DATA); 
	} //更新显示
}

//自己加的，X1>X0(0~7)
//Y1>Y0(0~127)
//清除指定位置的显示
void OLED_CLEAR_AREA(uint8_t X0,uint8_t Y0,uint8_t X1,uint8_t Y1)
{
	uint8_t i,n;		    
	for(i=0;i<X1-X0;i++)  
	{  
		OLED_Write_Byte (0xb0+X0+i,CMD);    //设置页地址（0~7）
		OLED_Write_Byte (0x02,CMD);      //设置显示位置—列低地址
		OLED_Write_Byte (0x10,CMD);      //设置显示位置—列高地址   
		for(n=Y0;n<Y1;n++)OLED_Write_Byte(0,DATA); 
	} //更新显示
}



void OLED_Clear_FF(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_Write_Byte (0xb0+i,CMD);    //设置页地址（0~7）
		OLED_Write_Byte (0x02,CMD);      //设置显示位置—列低地址
		OLED_Write_Byte (0x10,CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_Write_Byte(0xff,DATA); 
	} //更新显示
}
//开启OLED显示
void OLED_Display_On(void)
{
	OLED_Write_Byte(0x8D,CMD);  //SET DCDC命令
	OLED_Write_Byte(0x14,CMD);  //DCDC ON
	OLED_Write_Byte(0xAF,CMD);  //DISPLAY ON
}

//关闭OLED显示
void OLED_Display_Off(void)
{
	OLED_Write_Byte(0x8D,CMD);  //SET DCDC命令
	OLED_Write_Byte(0x10,CMD);  //DCDC OFF
	OLED_Write_Byte(0xAE,CMD);  //DISPLAY OFF
}

//设置起始坐标（x,y）
void OLED_Set_Pos(uint8_t x,uint8_t y) 
{ 
	OLED_Write_Byte(0xb0 + y, CMD);
	OLED_Write_Byte(((x & 0xf0)>>4) | 0x10, CMD);
	OLED_Write_Byte((x & 0x0f)|0x01, CMD); 
}

//在指定位置显示一个字符，包括部分字符
//x:0~127 
//y:0~7
//x,y 坐标
//size：选择字体 24/16/12
void OLED_ShowChar(u8 x,u8 y,u8 chr,unsigned char size)
{      	
	unsigned char c=0,i=0;	
	c=chr-' ';	
	if(x>127)
	{
	 	 x=0;y=y+2;
	}

	if(size ==	16)
	{
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
		{
			OLED_Write_Byte(F8X16[c*16+i],DATA);
		}
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		{
			OLED_Write_Byte(F8X16[c*16+i+8],DATA);
		}
	}
	if(size == 12) 
	{	
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		{
			OLED_Write_Byte(F6x8[c][i],DATA);
		}				
	}
	if(size == 24)
	{
		OLED_Set_Pos(x,y);	
		for(i=0;i<12;i++)
		{
			OLED_Write_Byte(asc2_2412[c*16+i],DATA);
		}
		OLED_Set_Pos(x,y+1);
		for(i=0;i<12;i++)
		{
			OLED_Write_Byte(asc2_2412[c*16+i+24],DATA);
		}
	}
}

//m^noˉêy
u32 oled_pow(u8 m, u8 n)
{
	u32 result=1;	 
	while(n--)
	{
		result *= m;    
	}
		return result;
}	
/**************************************************************
//在指定位置显示一串数字
//x:0~127
//y:0~7
//num 要显示的数字
//len 数字的位数
//size：选择字体 24/16/12;	 		  
***************************************************************/
void OLED_ShowNum(u8 x, u8 y, int32_t num, u8 len, u8 size)
{         	
	u8 t,temp,i=0;//i=0
	u8 enshow=0;
  //uint32_t num1;  
  if(num < 0)
  {
    OLED_ShowChar(x,y,'-',size);
    x= x+size/2;
    num= -1 * num;
    //len;
  }    
  
	for(t=0;t<len;t++)
	{
		temp=(num / oled_pow(10, len-t-1))%10;
		if(enshow==0 && t < (len-1))
		{
			if(temp==0)
			{
        
				OLED_ShowChar(x+(size/2)*t,y,' ',size);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*(t),y,temp+'0',size); 
	}
} 

//在指定位置显示字符串
//x:0~127
//y:0~7
//size：选择字体 24/16/12;
void OLED_ShowString(u8 x, u8 y, u8 *chr, unsigned char size) // *char为字符串对应的地址
{
	unsigned char j=0;
	while (chr[j]!='\0')				//'\0'为储存数组的结束标志
	{		OLED_ShowChar(x,y,chr[j],size);
			x+=8;
		if(x>124){x=0;y+=2;}
			j++;
	}
}

//在指定位置显示一个汉字
//x:0~127
//y:0~7
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
			OLED_Write_Byte(Hzk[2*no][t],DATA);
			adder+=1;
     }	
	OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
	{	
		OLED_Write_Byte(Hzk[2*no+1][t],DATA);
		adder+=1;
    }					
}

/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_Write_Byte(BMP[j++],DATA);	    	
	    }
	}
} 

/*************************************************************************/
/*函数功能: 更新显存到OLED                                                 */
/*************************************************************************/
void OLED_Refresh_Gram(void)
{
    u8 i,n;         
    for(i=0;i<8;i++)  
    {  
        OLED_Write_Byte(0xb0+i,CMD);   //设置页地址（0~7）
        OLED_Write_Byte(0x00,CMD);      //设置显示位置—列低地址
        OLED_Write_Byte(0x10,CMD);      //设置显示位置—列高地址   
        for(n=0;n<128;n++)OLED_Write_Byte(OLED_GRAM[n][i],DATA); 
    }   
}

/*************************************************************************/
/*函数功能: 画点                                                          */
/*入口参数：                                                             */
/*                      x：横坐标       0~127                               */
/*                      y：纵坐标               0~63                     */
/*                      dot:0,清空;1,填充                                                                                */             
/*************************************************************************/
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
    u8 pos,bx,temp=0;
    if(x>127||y>63)return;//超出范围了.
    pos=7-y/8;
    bx=y%8;
    temp=1<<(7-bx);
    if(t)OLED_GRAM[x][pos]|=temp;
    else OLED_GRAM[x][pos]&=~temp;  
	//OLED_Refresh_Gram();//更新显示	
}

/*************************************************************************/
/*函数功能: 填充                                                          */
/*入口参数：                                                                                                                          */
/*                      x1,y1,x2,y2 填充区域的对角坐标                              */
/*                      确保x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63                                         */
/*                      dot:0,清空;1,填充                                                                                */             
/*************************************************************************/
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
    u8 x,y;  
    for(x=x1;x<=x2;x++)
    {
        for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
    }                                                       
    OLED_Refresh_Gram();//更新显示
}
/*画线函数*/
void OLED_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		OLED_DrawPoint(uRow,uCol,1);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	} 
	OLED_Refresh_Gram();//更新显示	
}
/*画圆函数*/
void OLED_Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		OLED_DrawPoint(x0+a,y0-b,1);             //5
 		OLED_DrawPoint(x0+b,y0-a,1);             //0           
		OLED_DrawPoint(x0+b,y0+a,1);             //4               
		OLED_DrawPoint(x0+a,y0+b,1);             //6 
		OLED_DrawPoint(x0-a,y0+b,1);             //1       
 		OLED_DrawPoint(x0-b,y0+a,1);             
		OLED_DrawPoint(x0-a,y0-b,1);             //2             
  		OLED_DrawPoint(x0-b,y0-a,1);             //7     	         
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
	OLED_Refresh_Gram();//更新显示
}

//OLED初始化函数
void OLED_Init(void)
{
	OLED_GPIO_Config();
	OLED_SCLK_H;
	OLED_SDIN_H;
	OLED_DC_H;
	OLED_CS_H;
	OLED_SET;
	OLED_delay();
	OLED_CLR;
	OLED_delay();
	OLED_SET;	
	OLED_delay();

	///*				  
	OLED_Write_Byte(0xAE,CMD);//--turn off oled panel
	OLED_Write_Byte(0x02,CMD);//---set low column address
	OLED_Write_Byte(0x10,CMD);//---set high column address
	OLED_Write_Byte(0xb0,CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_Write_Byte(0xc8,CMD);//--set contrast control register
	OLED_Write_Byte(0x00,CMD); // Set SEG Output Current Brightness
	OLED_Write_Byte(0x10,CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_Write_Byte(0x40,CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_Write_Byte(0x81,CMD);//--set normal display
	OLED_Write_Byte(0xff,CMD);//--set multiplex ratio(1 to 64)
	OLED_Write_Byte(0xa1,CMD);//--1/64 duty
	OLED_Write_Byte(0xa6,CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_Write_Byte(0xa8,CMD);//-not offset
	OLED_Write_Byte(0x3f,CMD);//--set display clock divide ratio/oscillator frequency
	OLED_Write_Byte(0xa4,CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_Write_Byte(0xd3,CMD);//--set pre-charge period
	OLED_Write_Byte(0x00,CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_Write_Byte(0xd5,CMD);//--set com pins hardware configuration
	OLED_Write_Byte(0xf0,CMD);
	OLED_Write_Byte(0xd9,CMD);//--set vcomh
	OLED_Write_Byte(0x22,CMD);//Set VCOM Deselect Level
	OLED_Write_Byte(0xda,CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_Write_Byte(0x12,CMD);//
	OLED_Write_Byte(0xdb,CMD);//--set Charge Pump enable/disable
	OLED_Write_Byte(0x20,CMD);//--set(0x10) disable
	OLED_Write_Byte(0x8d,CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_Write_Byte(0x14,CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_Write_Byte(0xaf,CMD);//--turn on oled panel
	/*				  
	OLED_Write_Byte(0xAE,CMD);//--turn off oled panel
	OLED_Write_Byte(0x00,CMD);//---set low column address
	OLED_Write_Byte(0x10,CMD);//---set high column address
	OLED_Write_Byte(0x40,CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_Write_Byte(0x81,CMD);//--set contrast control register
	OLED_Write_Byte(0xCF,CMD); // Set SEG Output Current Brightness
	OLED_Write_Byte(0xA1,CMD);//--Set SEG/Column Mapping     0xa0???? 0xa1??
	OLED_Write_Byte(0xC8,CMD);//Set COM/Row Scan Direction   0xc0???? 0xc8??
	OLED_Write_Byte(0xA6,CMD);//--set normal display
  OLED_Write_Byte(0xA8,CMD);//--set multiplex ratio(1 to 64)
	OLED_Write_Byte(0x3f,CMD);//--1/64 duty
	OLED_Write_Byte(0xD3,CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
  OLED_Write_Byte(0x00,CMD);//-not offset
	OLED_Write_Byte(0xd5,CMD);//--set display clock divide ratio/oscillator frequency
	OLED_Write_Byte(0x80,CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_Write_Byte(0xD9,CMD);//--set pre-charge period
	OLED_Write_Byte(0xF1,CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_Write_Byte(0xDA,CMD);//--set com pins hardware configuration
	OLED_Write_Byte(0x12,CMD);
	OLED_Write_Byte(0xDB,CMD);//--set vcomh
	OLED_Write_Byte(0x40,CMD);//Set VCOM Deselect Level
	OLED_Write_Byte(0x20,CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_Write_Byte(0x02,CMD);//
  OLED_Write_Byte(0x8D,CMD);//--set Charge Pump enable/disable
	OLED_Write_Byte(0x14,CMD);//--set(0x10) disable
	OLED_Write_Byte(0xA4,CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_Write_Byte(0xA6,CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_Write_Byte(0xAF,CMD);//--turn on oled panel
	OLED_Write_Byte(0xAF,CMD); 
	//display ON
	/*
	OLED_Write_Byte(0xAE,CMD);//--turn off oled panel
	OLED_Write_Byte(0x00,CMD);//---set low column address
	OLED_Write_Byte(0x10,CMD);//---set high column address
	OLED_Write_Byte(0x40,CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_Write_Byte(0x81,CMD);//--set contrast control register
	OLED_Write_Byte(0xCF,CMD); // Set SEG Output Current Brightness
	OLED_Write_Byte(0xA1,CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_Write_Byte(0xC8,CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_Write_Byte(0xA6,CMD);//--set normal display
	OLED_Write_Byte(0xA8,CMD);//--set multiplex ratio(1 to 64)
	OLED_Write_Byte(0x3f,CMD);//--1/64 duty
	OLED_Write_Byte(0xD3,CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_Write_Byte(0x00,CMD);//-not offset
	OLED_Write_Byte(0xd5,CMD);//--set display clock divide ratio/oscillator frequency
	OLED_Write_Byte(0x80,CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_Write_Byte(0xD9,CMD);//--set pre-charge period
	OLED_Write_Byte(0xF1,CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_Write_Byte(0xDA,CMD);//--set com pins hardware configuration
	OLED_Write_Byte(0x12,CMD);
	OLED_Write_Byte(0xDB,CMD);//--set vcomh
	OLED_Write_Byte(0x40,CMD);//Set VCOM Deselect Level
	OLED_Write_Byte(0x20,CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_Write_Byte(0x02,CMD);//
	OLED_Write_Byte(0x8D,CMD);//--set Charge Pump enable/disable
	OLED_Write_Byte(0x14,CMD);//--set(0x10) disable
	OLED_Write_Byte(0xA4,CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_Write_Byte(0xA6,CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_Write_Byte(0xAF,CMD);//--turn on oled panel
	//OLED_Write_Byte(0xAF,CMD); display ON*/ 
	OLED_Clear();
}

