
#include "EXIT.h"
#include "common.h"

extern u16 amount;
/**********需要用的中断引脚在这里添加初始化******/
void GPIO_PIN_INIT()
{
	  GPIO_InitTypeDef  GPIO_InitStructure;

	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOA,GPIOE时钟
	 
	  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; //KEY0 KEY1 KEY2对应引脚
	  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;//普通输入模式
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;//上拉
	  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIOE2,3,4
}

/**************要加其他外部中断修改****************/
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	GPIO_PIN_INIT(); 			//初始化需要用到的引脚
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟,一定要使能，第一次忘了
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource0);// 连接到中断线0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource1);// 连接到中断线1
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource2);// 连接到中断线2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource3);// 连接到中断线3

	/* 配置EXTI_Line0,2,3,4 */
   EXTI_InitStructure.EXTI_Line 	= EXTI_Line0|EXTI_Line1 | EXTI_Line2 | EXTI_Line3;
   EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;//中断事件
   EXTI_InitStructure.EXTI_Trigger  = EXTI_Trigger_Rising; //下降沿触发
   EXTI_InitStructure.EXTI_LineCmd  = ENABLE;//中断线使能
   EXTI_Init(&EXTI_InitStructure);//配置
 
   NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//外部中断0
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级0
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//子优先级2
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
   NVIC_Init(&NVIC_InitStructure);//配置
	
   NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//外部中断2
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级3
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//子优先级2
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
   NVIC_Init(&NVIC_InitStructure);//配置
	
   NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//外部中断3
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级2
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//子优先级2
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
   NVIC_Init(&NVIC_InitStructure);//配置
	
	
   NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//外部中断4
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级1
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//子优先级2
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
   NVIC_Init(&NVIC_InitStructure);//配置
}
extern u8 PLAN_flag;
//extern u8 RED_STEP;
//extern u8 GREED_STEP;
extern u8 MODE_CHOSE ;              // 1:红 2：绿 3:遥控 4：测试
extern u8 KEY_CHOSE ;				//红方绿方对应的模式。遥控和测试没有
//外部中断0服务程序
void EXTI0_IRQHandler(void)
{
	 //printf("0\r\n");	
	 delay_ms(5);
	 //BEEP=!BEEP;
	MODE_CHOSE++;
	BEEP =!BEEP;
	if(MODE_CHOSE > 4)
	{
		MODE_CHOSE = 0;
	}
	 EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
}	
//外部中断1服务程序
void EXTI1_IRQHandler(void)
{
	 delay_ms(5);
	 //BEEP=!BEEP;
	BEEP =!BEEP;
	 if(MODE_CHOSE == 1)
	 {
		 KEY_CHOSE++;
		 if(KEY_CHOSE > 5)
		 {
			 KEY_CHOSE = 1;
		 }
		 
	 }
	 if(MODE_CHOSE == 2)
	 {
		 KEY_CHOSE++;
		 if(KEY_CHOSE > 4)
		 {
			 KEY_CHOSE = 1;
		 }
	 }
	 else
	 {
		 ;
	 }
	 EXTI_ClearITPendingBit(EXTI_Line1);//清除LINE4上的中断标志位  
}
//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	 delay_ms(5);
	BEEP =!BEEP;
	 if(MODE_CHOSE == 1)
	 {
		 KEY_CHOSE--;
		 if(KEY_CHOSE < 1)
		 {
			 KEY_CHOSE = 5;
		 }
		 
	 }
	 if(MODE_CHOSE == 2)
	 {
		 KEY_CHOSE--;
		 if(KEY_CHOSE < 1)
		 {
			 KEY_CHOSE = 4;
		 }
	 }
	 else
	 {
		 ;
	 }
	 //BEEP=!BEEP;
	 EXTI_ClearITPendingBit(EXTI_Line2);//清除LINE2上的中断标志位 
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	 delay_ms(5);
	BEEP =!BEEP;
	 //BEEP=!BEEP;
     PLAN_flag = 1;	
	 EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}


