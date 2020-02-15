#include "TIMES.h"
#include "myusart.h"
#include "common.h"
u8 What_Tim(TIME_CH Tim_x)
{
	if(Tim_x==TIME_1||Tim_x==TIME_8)
		return ADV_TIM;
	else if(Tim_x==TIME_2 ||Tim_x==TIME_3 ||Tim_x==TIME_4 ||Tim_x==TIME_5 ||Tim_x==TIME_9||
		    Tim_x==TIME_10||Tim_x==TIME_11||Tim_x==TIME_12||Tim_x==TIME_13||Tim_x==TIME_14)
		return GENERL_TIM;
	else 
		return BASIC_TIM;
	
}


void TIMERx_init(TIME_CH Tim_x,u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

		switch(Tim_x)
		{
			case TIME_1:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
			
				TIM_TimeBaseInitStructure.TIM_Period = arr; 					//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
				TIM_TimeBaseInitStructure.TIM_Prescaler =psc; 					//设置用来作为TIMx时钟频率除数的预分频值
				TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 	//设置时钟分割:TDTS = Tck_tim
				TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
				TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;     		//重复计数周期
				TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure); 			//根据指定的参数初始化TIMx的时间基数单位
			 
				TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

				//中断优先级NVIC设置
				NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn ;  //TIM1中断
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
				NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级3级
				NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
				NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

				//TIM_ARRPreloadConfig(TIM1, ENABLE);
				TIM_Cmd(TIM1, ENABLE);  //使能TIMx
				break;
			case TIME_8:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); 
			
				TIM_TimeBaseInitStructure.TIM_Period = arr; 					//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
				TIM_TimeBaseInitStructure.TIM_Prescaler =psc; 					//设置用来作为TIMx时钟频率除数的预分频值
				TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 	//设置时钟分割:TDTS = Tck_tim
				TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
				TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;     		//重复计数周期
				TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStructure); 			//根据指定的参数初始化TIMx的时间基数单位
			 
				TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

				//中断优先级NVIC设置
				NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn ;  //TIM1中断
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
				NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级3级
				NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
				NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

				//TIM_ARRPreloadConfig(TIM1, ENABLE);
				TIM_Cmd(TIM8, ENABLE);  //使能TIMx
			break;
	
		case TIME_2:
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///使能TIM3时钟
				
				TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
				TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
				TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
				TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
				
				TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//初始化TIM3
				
				TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //允许定时器3更新中断
				TIM_Cmd(TIM2,ENABLE); //使能定时器3
				
				NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //定时器3中断
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级1
				NVIC_InitStructure.NVIC_IRQChannelSubPriority=0; //子优先级3
				NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
				NVIC_Init(&NVIC_InitStructure);
				break;
			
			case TIME_3:
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
				
				TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
				TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
				TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
				TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
				
				TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
				
				TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
				TIM_Cmd(TIM3,ENABLE); //使能定时器3
				
				NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级1
				NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; //子优先级3
				NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
				NVIC_Init(&NVIC_InitStructure);
				break;
			
			case TIME_4:
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///使能TIM3时钟
				
				TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
				TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
				TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
				TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
				
				TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//初始化TIM3
				
				TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允许定时器3更新中断
				TIM_Cmd(TIM4,ENABLE); //使能定时器3
				
				NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //定时器3中断
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级1
				NVIC_InitStructure.NVIC_IRQChannelSubPriority=2; //子优先级3
				NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
				NVIC_Init(&NVIC_InitStructure);
				break;
		    case TIME_5:
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///使能TIM3时钟
				
				TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
				TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
				TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
				TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
				
				TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//初始化TIM3
				
				TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //允许定时器3更新中断
				TIM_Cmd(TIM5,ENABLE); //使能定时器3
				
				NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //定时器3中断
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级1
				NVIC_InitStructure.NVIC_IRQChannelSubPriority=2; //子优先级3
				NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
				NVIC_Init(&NVIC_InitStructure);
				break;
			case TIME_9:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  ///使能TIM3时钟
				
				TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
				TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
				TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
				TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
				
				TIM_TimeBaseInit(TIM9,&TIM_TimeBaseInitStructure);//初始化TIM3
				
				TIM_ITConfig(TIM9,TIM_IT_Update,ENABLE); //允许定时器3更新中断
				TIM_Cmd(TIM9,ENABLE); //使能定时器3
				
				NVIC_InitStructure.NVIC_IRQChannel=TIM1_BRK_TIM9_IRQn; //定时器3中断
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级1
				NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; //子优先级3
				NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
				NVIC_Init(&NVIC_InitStructure);
				break;
		    case TIME_10:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);  ///使能TIM3时钟
				
				TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
				TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
				TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
				TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
				
				TIM_TimeBaseInit(TIM10,&TIM_TimeBaseInitStructure);//初始化TIM3
				
				TIM_ITConfig(TIM10,TIM_IT_Update,ENABLE); //允许定时器3更新中断
				TIM_Cmd(TIM10,ENABLE); //使能定时器3
				
				NVIC_InitStructure.NVIC_IRQChannel=TIM1_UP_TIM10_IRQn; //定时器3中断
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //抢占优先级1
				NVIC_InitStructure.NVIC_IRQChannelSubPriority=0; //子优先级3
				NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
				NVIC_Init(&NVIC_InitStructure);
				break;
			
			case TIME_11:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);  ///使能TIM3时钟
				
				TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
				TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
				TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
				TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
				
				TIM_TimeBaseInit(TIM11,&TIM_TimeBaseInitStructure);//初始化TIM3
				
				TIM_ITConfig(TIM11,TIM_IT_Update,ENABLE); //允许定时器3更新中断
				TIM_Cmd(TIM11,ENABLE); //使能定时器3
				
				NVIC_InitStructure.NVIC_IRQChannel=TIM1_TRG_COM_TIM11_IRQn; //定时器3中断
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //抢占优先级1
				NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; //子优先级3
				NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
				NVIC_Init(&NVIC_InitStructure);
				break;
			case TIME_12:
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  ///使能TIM3时钟
				
				TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
				TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
				TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
				TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
				
				TIM_TimeBaseInit(TIM12,&TIM_TimeBaseInitStructure);//初始化TIM3
				
				TIM_ITConfig(TIM12,TIM_IT_Update,ENABLE); //允许定时器3更新中断
				TIM_Cmd(TIM12,ENABLE); //使能定时器3
				
				NVIC_InitStructure.NVIC_IRQChannel=TIM8_BRK_TIM12_IRQn; //定时器3中断
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //抢占优先级1
				NVIC_InitStructure.NVIC_IRQChannelSubPriority=2; //子优先级3
				NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
				NVIC_Init(&NVIC_InitStructure);
				break;
			case TIME_13:
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);  ///使能TIM3时钟
				
				TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
				TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
				TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
				TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
				
				TIM_TimeBaseInit(TIM13,&TIM_TimeBaseInitStructure);//初始化TIM3
				
				TIM_ITConfig(TIM13,TIM_IT_Update,ENABLE); //允许定时器3更新中断
				TIM_Cmd(TIM13,ENABLE); //使能定时器3
				
				NVIC_InitStructure.NVIC_IRQChannel=TIM8_UP_TIM13_IRQn; //定时器3中断
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //抢占优先级1
				NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; //子优先级3
				NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
				NVIC_Init(&NVIC_InitStructure);
				break;
			case TIME_14:
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  ///使能TIM3时钟
				
				TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
				TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
				TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
				TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
				
				TIM_TimeBaseInit(TIM14,&TIM_TimeBaseInitStructure);//初始化TIM3
				
				TIM_ITConfig(TIM14,TIM_IT_Update,ENABLE); //允许定时器3更新中断
				TIM_Cmd(TIM14,ENABLE); //使能定时器3
				
				NVIC_InitStructure.NVIC_IRQChannel=TIM8_TRG_COM_TIM14_IRQn; //定时器3中断
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3; //抢占优先级1
				NVIC_InitStructure.NVIC_IRQChannelSubPriority=0; //子优先级3
				NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
				NVIC_Init(&NVIC_InitStructure);
				break;

			case TIME_6:
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);  ///使能TIM3时钟
				
				TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
				TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
				TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
				TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
				
				TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);//初始化TIM3
				
				TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); //允许定时器3更新中断
				TIM_Cmd(TIM6,ENABLE); //使能定时器3
				
				NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn; //定时器3中断
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3; //抢占优先级1
				NVIC_InitStructure.NVIC_IRQChannelSubPriority=2; //子优先级3
				NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
				NVIC_Init(&NVIC_InitStructure);
				break;
			
			case TIME_7:
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);  ///使能TIM3时钟
				
				TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
				TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
				TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
				TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
				
				TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);//初始化TIM3
				
				TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //允许定时器3更新中断
				TIM_Cmd(TIM7,ENABLE); //使能定时器3
				
				NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn; //定时器3中断
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级1
				NVIC_InitStructure.NVIC_IRQChannelSubPriority=2; //子优先级3
				NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
				NVIC_Init(&NVIC_InitStructure);
				break;
		}
}

void TIM1_UP_TIM10_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET) //溢出中断
	{
		
		
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);  //清除中断标志位
	}
	
	if(TIM_GetITStatus(TIM10,TIM_IT_Update)==SET)
	{
		
		TIM_ClearITPendingBit(TIM10,TIM_IT_Update);  //清除中断标志位
	}
		
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
	{
		
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //溢出中断
	{
		
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //清除中断标志位
}

void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //溢出中断
	{
		
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志位
}

//void TIM6_DAC_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==SET) //溢出中断
//	{
//		
//	}
//	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);  //清除中断标志位
//}

//void TIM7_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) //溢出中断
//	{
//		
//	}
//	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  //清除中断标志位
//}


void TIM8_UP_TIM13_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM8,TIM_IT_Update)==SET) //溢出中断
	{
		
		//printf("tim8\r\n");
		TIM_ClearITPendingBit(TIM8,TIM_IT_Update);  //清除中断标志位
	}
	//TIM_ClearITPendingBit(TIM8,TIM_IT_Update);  //清除中断标志位
	if(TIM_GetITStatus(TIM13,TIM_IT_Update)==SET)
	{
		
		TIM_ClearITPendingBit(TIM13,TIM_IT_Update);  //清除中断标志位
	}
		
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM9,TIM_IT_Update)==SET) //溢出中断
	{
		
	}
	TIM_ClearITPendingBit(TIM9,TIM_IT_Update);  //清除中断标志位
}

void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM11,TIM_IT_Update)==SET) //溢出中断
	{
		
	}
	TIM_ClearITPendingBit(TIM11,TIM_IT_Update);  //清除中断标志位
}
	
void TIM8_BRK_TIM12_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM12,TIM_IT_Update)==SET) //溢出中断
	{
		
	}
	TIM_ClearITPendingBit(TIM12,TIM_IT_Update);  //清除中断标志位
}	

void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM14,TIM_IT_Update)==SET) //溢出中断
	{
		
	}
	TIM_ClearITPendingBit(TIM14,TIM_IT_Update);  //清除中断标志位
}
