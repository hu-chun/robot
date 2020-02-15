#include "common.h"
#include "near.h"

void near_inint(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOA,GPIOE时钟
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15; //KEY0 KEY1 KEY2对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIOE2,3,4GPIO_Pin_14
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIOE2,3,4GPIO_Pin_14
}

/*************************返回1为为触碰，0：为触碰****************************/
u8 near_read(NEAR_TYPl near_typ)
{
	if(near_typ ==near_A)
	{
		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_14) == 1)
			return 1;
		else
			return 0;
	}
	if(near_typ ==near_B)
	{
		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_13) == 0)
			return 1;
		else
			return 0;
	}
	if(near_typ ==near_C)
	{
		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_15) == 0)
			return 1;
		else
			return 0;
	}
		
}

