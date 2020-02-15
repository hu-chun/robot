#include "PWM.h"

uint32_t TIM1_arr = 0;        //定义用来随时改变占空比的
uint32_t TIM8_arr = 0;
uint32_t TIM2_arr = 0;
uint32_t TIM3_arr = 0;
uint32_t TIM9_arr = 0;

void TIM1_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty)
{
	uint32_t  Duty_cycle = 0;
	uint32_t  JISU_freq = 0;
	uint32_t  PWM_freq = 0;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	JISU_freq  =  168000000/(psc + 1);
	Duty_cycle =  duty*(arr+1)/100;
	PWM_freq   =  JISU_freq/(arr+1);
	TIM1_arr   =  arr;
	switch(PWM_x)
	{
		case pwm_1:
			//GPIO_InitTypeDef GPIO_InitStructure;
			//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			//TIM_OCInitTypeDef  TIM_OCInitStructure;
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  			//TIM14时钟使能    
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 			//使能PORTF时钟	
			
			GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 			//GPIOF9复用为定时器14
			
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           			//GPIOF9
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        			//复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;				//速度100MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      			//推挽复用输出
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        			//上拉
			GPIO_Init(GPIOE,&GPIO_InitStructure);              				//初始化PF9
			  
			TIM_TimeBaseStructure.TIM_Prescaler=psc;  						//定时器分频
			TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		//向上计数模式
			TIM_TimeBaseStructure.TIM_Period=arr;   						//自动重装载值
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 				//重复计数
			TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
			TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);					//初始化定时器14
			
			//初始化TIM14 Channel1 PWM模式	 
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				//选择定时器模式:TIM脉冲宽度调制模式2
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		//输出极性:TIM输出比较极性低				
			TIM_OCInitStructure.TIM_Pulse = Duty_cycle;   					//给arr装初值
			
			TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  				//使能TIM14在CCR1上的预装载寄存器
			TIM_OC1Init(TIM1, &TIM_OCInitStructure);  						//根据T指定的参数初始化外设TIM1 4OC1
			TIM_ARRPreloadConfig(TIM1,ENABLE);								//ARPE使能 
			TIM_CtrlPWMOutputs(TIM1, ENABLE);
			TIM_Cmd(TIM1, ENABLE);  										//使能TIM14
		break;
		
		case pwm_2:
			//GPIO_InitTypeDef GPIO_InitStructure;
			//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			//TIM_OCInitTypeDef  TIM_OCInitStructure;
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  				//TIM14时钟使能    
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 				//使能PORTF时钟	
			
			GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1); 				//GPIOF9复用为定时器14
			
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;          				 //GPIOF9
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        				 //复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;					 //速度100MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;       				 //推挽复用输出
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        				 //上拉
			GPIO_Init(GPIOE,&GPIO_InitStructure);              					 //初始化PF9
			  
			TIM_TimeBaseStructure.TIM_Prescaler=psc;  							//定时器分频
			TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 			//向上计数模式
			TIM_TimeBaseStructure.TIM_Period=arr;   							//自动重装载值
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 					//重复计数
			TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
			
			TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);					//初始化定时器14
			
			//初始化TIM14 Channel1 PWM模式	 
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				//选择定时器模式:TIM脉冲宽度调制模式2
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		//输出极性:TIM输出比较极性低
			TIM_OCInitStructure.TIM_Pulse = Duty_cycle;   					//给arr装初值
			TIM_OC2Init(TIM1, &TIM_OCInitStructure);  						//根据T指定的参数初始化外设TIM1 4OC1			
			TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  				//使能TIM14在CCR1上的预装载寄存器
		 
			TIM_ARRPreloadConfig(TIM1,ENABLE);								//ARPE使能 
			TIM_CtrlPWMOutputs(TIM1, ENABLE);								//高级定时器才加
			TIM_Cmd(TIM1, ENABLE);  //使能TIM14
		break;
		
		case pwm_3:
			//GPIO_InitTypeDef GPIO_InitStructure;
			//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			//TIM_OCInitTypeDef  TIM_OCInitStructure;
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  				//TIM14时钟使能    
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 				//使能PORTF时钟	
			
			GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1); 				//GPIOF9复用为定时器14
			
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;          				 //GPIOF9
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        				 //复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;					 //速度100MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;       				 //推挽复用输出
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        				 //上拉
			GPIO_Init(GPIOE,&GPIO_InitStructure);              					 //初始化PF9
			  
			TIM_TimeBaseStructure.TIM_Prescaler=psc;  							//定时器分频
			TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 			//向上计数模式
			TIM_TimeBaseStructure.TIM_Period=arr;   							//自动重装载值
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 					//重复计数
			TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
			
			TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);					//初始化定时器14
			
			//初始化TIM14 Channel1 PWM模式	 
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				//选择定时器模式:TIM脉冲宽度调制模式2
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		//输出极性:TIM输出比较极性低
			TIM_OCInitStructure.TIM_Pulse = Duty_cycle;   					//给arr装初值
			
			TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  				//使能TIM14在CCR1上的预装载寄存器
			TIM_OC3Init(TIM1, &TIM_OCInitStructure);  						//根据T指定的参数初始化外设TIM1 4OC1
			TIM_ARRPreloadConfig(TIM1,ENABLE);								//ARPE使能 
			TIM_CtrlPWMOutputs(TIM1, ENABLE);								//高级定时器才加
			TIM_Cmd(TIM1, ENABLE);  //使能TIM14
		break;
		
		case pwm_4:
			//GPIO_InitTypeDef GPIO_InitStructure;
			//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			//TIM_OCInitTypeDef  TIM_OCInitStructure;
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  				//TIM14时钟使能    
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 				//使能PORTF时钟	
			
			GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1); 				//GPIOF9复用为定时器14
			
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;          				 //GPIOF9
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        				 //复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;					 //速度100MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;       				 //推挽复用输出
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        				 //上拉
			GPIO_Init(GPIOE,&GPIO_InitStructure);              					 //初始化PF9
			  
			TIM_TimeBaseStructure.TIM_Prescaler=psc;  							//定时器分频
			TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 			//向上计数模式
			TIM_TimeBaseStructure.TIM_Period=arr;   							//自动重装载值
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 					//重复计数
			TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
			
			TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);					//初始化定时器14
			
			//初始化TIM14 Channel1 PWM模式	 
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				//选择定时器模式:TIM脉冲宽度调制模式2
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		//输出极性:TIM输出比较极性低
			TIM_OCInitStructure.TIM_Pulse  = Duty_cycle;   					//给arr装初值
			TIM_OC4Init(TIM1, &TIM_OCInitStructure);  						//根据T指定的参数初始化外设TIM14OC1			
			TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  				//使能TIM14在CCR1上的预装载寄存器
		 
			TIM_ARRPreloadConfig(TIM1,ENABLE);								//ARPE使能 
			TIM_CtrlPWMOutputs(TIM1, ENABLE);								//高级定时器才加
			TIM_Cmd(TIM1, ENABLE);  										//使能TIM14
		break;
	}
		
	
}


void TIM9_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty)
{
	uint32_t  Duty_cycle = 0;
	uint32_t  JISU_freq = 0;
	uint32_t  PWM_freq = 0;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	JISU_freq  =  168000000/(psc + 1);
	Duty_cycle =  duty*(arr+1)/100;
	PWM_freq   =  JISU_freq/(arr+1);
	TIM9_arr   =  arr;
	switch(PWM_x)
	{
		case pwm_1:
			//GPIO_InitTypeDef GPIO_InitStructure;
			//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			//TIM_OCInitTypeDef  TIM_OCInitStructure;
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  			//TIM14时钟使能    
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 			//使能PORTF时钟	
			
			GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9); 			//GPIOF9复用为定时器14
			
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;           			//GPIOF9
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        			//复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;				//速度100MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      			//推挽复用输出
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        			//上拉
			GPIO_Init(GPIOE,&GPIO_InitStructure);              				//初始化PF9
			  
			TIM_TimeBaseStructure.TIM_Prescaler=psc;  						//定时器分频
			TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		//向上计数模式
			TIM_TimeBaseStructure.TIM_Period=arr;   						//自动重装载值
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 				//重复计数
			TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
			
			TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);					//初始化定时器14
			
			//初始化TIM14 Channel1 PWM模式	 
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				//选择定时器模式:TIM脉冲宽度调制模式2
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		//输出极性:TIM输出比较极性低
			TIM_OCInitStructure.TIM_Pulse = Duty_cycle;   					//给arr装初值
			TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);  				//使能TIM14在CCR1上的预装载寄存器
			TIM_OC1Init(TIM9, &TIM_OCInitStructure);  						//根据T指定的参数初始化外设TIM1 4OC1
			TIM_ARRPreloadConfig(TIM9,ENABLE);//ARPE使能 
			TIM_CtrlPWMOutputs(TIM9, ENABLE);
			TIM_Cmd(TIM9, ENABLE);  //使能TIM14
		break;
		
		case pwm_2:
			//GPIO_InitTypeDef GPIO_InitStructure;
			//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			//TIM_OCInitTypeDef  TIM_OCInitStructure;
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  				//TIM14时钟使能    
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 				//使能PORTF时钟	
			
			GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9); 				//GPIOF9复用为定时器14
			
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;          				 //GPIOF9
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        				 //复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;					 //速度100MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;       				 //推挽复用输出
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        				 //上拉
			GPIO_Init(GPIOE,&GPIO_InitStructure);              					 //初始化PF9
			  
			TIM_TimeBaseStructure.TIM_Prescaler=psc;  							//定时器分频
			TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 			//向上计数模式
			TIM_TimeBaseStructure.TIM_Period=arr;   							//自动重装载值
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 					//重复计数
			TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
			
			TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);					//初始化定时器14
			
			//初始化TIM14 Channel1 PWM模式	 
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				//选择定时器模式:TIM脉冲宽度调制模式2
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		//输出极性:TIM输出比较极性低
			TIM_OCInitStructure.TIM_Pulse = Duty_cycle;   					//给arr装初值
			TIM_OC2Init(TIM9, &TIM_OCInitStructure);  						//根据T指定的参数初始化外设TIM1 4OC1			
			TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);  				//使能TIM14在CCR1上的预装载寄存器
		 
			TIM_ARRPreloadConfig(TIM9,ENABLE);								//ARPE使能 
			TIM_CtrlPWMOutputs(TIM9, ENABLE);								//高级定时器才加
			TIM_Cmd(TIM9, ENABLE);  //使能TIM14
		break;
		
	}
	
}





void TIM8_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty)
{
	uint32_t  Duty_cycle = 0;
	uint32_t  JISU_freq = 0;
	uint32_t  PWM_freq = 0;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	JISU_freq  =  168000000/(psc + 1);
	Duty_cycle =  duty*(arr+1)/100;
	PWM_freq   =  JISU_freq/(arr+1);
	TIM8_arr   =  arr;
	switch(PWM_x)
	{
		case pwm_1:
			//GPIO_InitTypeDef GPIO_InitStructure;
			//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			//TIM_OCInitTypeDef  TIM_OCInitStructure;
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  			//TIM14时钟使能    
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 			//使能PORTF时钟	
			
			GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8); 			//GPIOF9复用为定时器14
			
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           			//GPIOF9
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        			//复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;				//速度100MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      			//推挽复用输出
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        			//上拉
			GPIO_Init(GPIOC,&GPIO_InitStructure);              				//初始化PF9
			  
			TIM_TimeBaseStructure.TIM_Prescaler=psc;  						//定时器分频
			TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		//向上计数模式
			TIM_TimeBaseStructure.TIM_Period=arr;   						//自动重装载值
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 				//重复计数
			TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
			
			TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);					//初始化定时器14
			
			//初始化TIM14 Channel1 PWM模式	 
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				//选择定时器模式:TIM脉冲宽度调制模式2
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		//输出极性:TIM输出比较极性低
			TIM_OCInitStructure.TIM_Pulse = Duty_cycle;   					//给arr装初值
			TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  				//使能TIM14在CCR1上的预装载寄存器
			TIM_OC1Init(TIM8, &TIM_OCInitStructure);  						//根据T指定的参数初始化外设TIM1 4OC1
			TIM_ARRPreloadConfig(TIM8,ENABLE);//ARPE使能 
			TIM_CtrlPWMOutputs(TIM8, ENABLE);
			TIM_Cmd(TIM8, ENABLE);  //使能TIM14
		break;
		
		case pwm_2:
			//GPIO_InitTypeDef GPIO_InitStructure;
			//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			//TIM_OCInitTypeDef  TIM_OCInitStructure;
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  				//TIM14时钟使能    
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 				//使能PORTF时钟	
			
			GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8); 				//GPIOF9复用为定时器14
			
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;          				 //GPIOF9
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        				 //复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;					 //速度100MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;       				 //推挽复用输出
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        				 //上拉
			GPIO_Init(GPIOC,&GPIO_InitStructure);              					 //初始化PF9
			  
			TIM_TimeBaseStructure.TIM_Prescaler=psc;  							//定时器分频
			TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 			//向上计数模式
			TIM_TimeBaseStructure.TIM_Period=arr;   							//自动重装载值
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 					//重复计数
			TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
			
			TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);					//初始化定时器14
			
			//初始化TIM14 Channel1 PWM模式	 
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				//选择定时器模式:TIM脉冲宽度调制模式2
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		//输出极性:TIM输出比较极性低
			TIM_OCInitStructure.TIM_Pulse = Duty_cycle;   					//给arr装初值
			TIM_OC2Init(TIM8, &TIM_OCInitStructure);  						//根据T指定的参数初始化外设TIM1 4OC1			
			TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  				//使能TIM14在CCR1上的预装载寄存器
		 
			TIM_ARRPreloadConfig(TIM8,ENABLE);								//ARPE使能 
			TIM_CtrlPWMOutputs(TIM8, ENABLE);								//高级定时器才加
			TIM_Cmd(TIM8, ENABLE);  //使能TIM14
		break;
		
		case pwm_3:
			//GPIO_InitTypeDef GPIO_InitStructure;
			//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			//TIM_OCInitTypeDef  TIM_OCInitStructure;
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  				//TIM14时钟使能    
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 				//使能PORTF时钟	
			
			GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8); 				//GPIOF9复用为定时器14
			
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;          				 //GPIOF9
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        				 //复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;					 //速度100MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;       				 //推挽复用输出
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        				 //上拉
			GPIO_Init(GPIOC,&GPIO_InitStructure);              					 //初始化PF9
			  
			TIM_TimeBaseStructure.TIM_Prescaler=psc;  							//定时器分频
			TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 			//向上计数模式
			TIM_TimeBaseStructure.TIM_Period=arr;   							//自动重装载值
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 					//重复计数
			TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
			
			TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);					//初始化定时器14
			
			//初始化TIM14 Channel1 PWM模式	 
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				//选择定时器模式:TIM脉冲宽度调制模式2
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		//输出极性:TIM输出比较极性低
			
			TIM_OCInitStructure.TIM_Pulse = Duty_cycle;   					//给arr装初值
			TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  				//使能TIM14在CCR1上的预装载寄存器
			TIM_OC3Init(TIM8, &TIM_OCInitStructure);  						//根据T指定的参数初始化外设TIM1 4OC1
			TIM_ARRPreloadConfig(TIM8,ENABLE);								//ARPE使能 
			TIM_CtrlPWMOutputs(TIM8, ENABLE);								//高级定时器才加
			TIM_Cmd(TIM8, ENABLE);  //使能TIM14
		break;
		
		case pwm_4:
			//GPIO_InitTypeDef GPIO_InitStructure;
			//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			//TIM_OCInitTypeDef  TIM_OCInitStructure;
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  				//TIM14时钟使能    
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 				//使能PORTF时钟	
			
			GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8); 				//GPIOF9复用为定时器14
			
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;          				 //GPIOF9
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        				 //复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;					 //速度100MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;       				 //推挽复用输出
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        				 //上拉
			GPIO_Init(GPIOC,&GPIO_InitStructure);              					 //初始化PF9
			  
			TIM_TimeBaseStructure.TIM_Prescaler=psc;  							//定时器分频
			TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 			//向上计数模式
			TIM_TimeBaseStructure.TIM_Period=arr;   							//自动重装载值
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 					//重复计数
			TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
			
			TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);					//初始化定时器14
			
			//初始化TIM14 Channel1 PWM模式	 
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				//选择定时器模式:TIM脉冲宽度调制模式2
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		//输出极性:TIM输出比较极性低
			TIM_OCInitStructure.TIM_Pulse  = Duty_cycle;   					//给arr装初值
			TIM_OC4Init(TIM8, &TIM_OCInitStructure);  						//根据T指定的参数初始化外设TIM14OC1			
			TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  				//使能TIM14在CCR1上的预装载寄存器
		 
			TIM_ARRPreloadConfig(TIM8,ENABLE);								//ARPE使能 
			TIM_CtrlPWMOutputs(TIM8, ENABLE);								//高级定时器才加
			TIM_Cmd(TIM8, ENABLE);  										//使能TIM14
			break;
	}
	
}


void TIM1_PWM_charge_duty(PWM_CH PWM_x,u32 duty)
{
	switch(PWM_x)
	{
		case pwm_1:
			TIM_SetCompare1(TIM1,duty*TIM1_arr/1000);break;
		case pwm_2:
			TIM_SetCompare2(TIM1,duty*TIM1_arr/1000);break;
		case pwm_3:
			TIM_SetCompare3(TIM1,duty*TIM1_arr/1000);break;
		case pwm_4:
			TIM_SetCompare4(TIM1,duty*TIM1_arr/1000);break;
	}
		
}

void TIM8_PWM_charge_duty(PWM_CH PWM_x,u32 duty)
{
	switch(PWM_x)
	{
		case pwm_1:
			TIM_SetCompare1(TIM8,duty*TIM8_arr/1000);break;
		case pwm_2:
			TIM_SetCompare2(TIM8,duty*TIM8_arr/1000);break;
		case pwm_3:
			TIM_SetCompare3(TIM8,duty*TIM8_arr/1000);break;
		case pwm_4:
			TIM_SetCompare4(TIM8,duty*TIM8_arr/1000);break;
	}
		
}


void TIM9_PWM_charge_duty(PWM_CH PWM_x,u32 duty)
{
	switch(PWM_x)
	{
		case pwm_1:
			TIM_SetCompare1(TIM9,duty*TIM9_arr/100);break;
		case pwm_2:
			TIM_SetCompare2(TIM9,duty*TIM9_arr/100);break;
		/*case pwm_3:
			TIM_SetCompare3(TIM4,duty*TIM4_arr/100);break;
		case pwm_4:
			TIM_SetCompare4(TIM4,duty*TIM4_arr/100);break;*/
	}
		
}


