#ifndef _OLED__H
#define _OLED__H

#include "sys.h"

#define OLED_CS_GPIO						GPIOD	
#define OLED_DC_GPIO						GPIOD	
#define OLED_SCLK_GPIO					    GPIOD	
#define OLED_SDIN_GPIO						GPIOD	
#define OLED_RES_GPIO						GPIOD

#define OLED_CS_RCC_AHB1Periph_GPIO			RCC_AHB1Periph_GPIOD
#define OLED_DC_RCC_AHB1Periph_GPIO 		RCC_AHB1Periph_GPIOD
#define OLED_SCLK_RCC_AHB1Periph_GPIO	 	RCC_AHB1Periph_GPIOD
#define OLED_SDIN_RCC_AHB1Periph_GPIO	 	RCC_AHB1Periph_GPIOD
#define OLED_RES_RCC_AHB1Periph_GPIO		RCC_AHB1Periph_GPIOD

#define OLED_CS_GPIO_Pin	                GPIO_Pin_4
#define OLED_DC_GPIO_Pin	                GPIO_Pin_3
#define OLED_SCLK_GPIO_Pin	                GPIO_Pin_0
#define OLED_SDIN_GPIO_Pin	                GPIO_Pin_1
#define OLED_RES_GPIO_Pin	                GPIO_Pin_2

#define OLED_CS_H				GPIO_SetBits(OLED_CS_GPIO, OLED_CS_GPIO_Pin)
#define OLED_CS_L				GPIO_ResetBits(OLED_CS_GPIO, OLED_CS_GPIO_Pin)

#define OLED_DC_H				GPIO_SetBits(OLED_DC_GPIO,OLED_DC_GPIO_Pin)
#define OLED_DC_L				GPIO_ResetBits(OLED_DC_GPIO,OLED_DC_GPIO_Pin)

#define OLED_SCLK_H				GPIO_SetBits(OLED_SCLK_GPIO,OLED_SCLK_GPIO_Pin)
#define OLED_SCLK_L				GPIO_ResetBits(OLED_SCLK_GPIO,OLED_SCLK_GPIO_Pin)

#define OLED_SDIN_H				GPIO_SetBits(OLED_SDIN_GPIO,OLED_SDIN_GPIO_Pin)
#define OLED_SDIN_L				GPIO_ResetBits(OLED_SDIN_GPIO,OLED_SDIN_GPIO_Pin)

#define OLED_SET				GPIO_SetBits(OLED_RES_GPIO, OLED_RES_GPIO_Pin)
#define OLED_CLR				GPIO_ResetBits(OLED_RES_GPIO,OLED_RES_GPIO_Pin)

#define CMD																	0
#define DATA																1


void OLED_delay(void);	//OLED_SPI延迟函数
void OLED_DrawPoint(u8 x,u8 y,u8 t);//  画点函数
void OLED_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);//画线函数
void OLED_Draw_Circle(u16 x0,u16 y0,u8 r);
//void OLED_GPIO_Config(void);								//OLED_GPIO配置
void OLED_Init(void);												//OLED初始化函数
//void OLED_Write_Byte(uint8_t data,uint8_t order);//OLED 4-wire SPI写一个字节
//void OLED_Write_CMD(uint8_t address);				//写指令
//void OLED_Write_DATA(uint8_t address,uint8_t data);//写数据
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot); //填充
void OLED_Clear(void);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Set_Pos(uint8_t x,uint8_t y);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,unsigned char size);
void OLED_ShowNum(uint8_t x,uint8_t y,int32_t num,uint8_t len,uint8_t size);
uint32_t oled_pow(uint8_t m,uint8_t n);
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,unsigned char size);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_CLEAR_AREA(uint8_t X0,uint8_t Y0,uint8_t X1,uint8_t Y1);

#endif
