#ifndef  __PWM_H
#define  __PWM_H
#include "sys.h"
typedef enum
{
	pwm_1,
	pwm_2,
	pwm_3,
	pwm_4,
	pwm_5,
	pwm_6,
	pwm_7,
		
}PWM_CH;


void TIM1_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 					//计数频率 = 168M÷psc+1   ，PWM频率 =  计数频率÷arr ，
//void TIM2_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 					//计数频率 = 84M÷psc+1   ，PWM频率 =  计数频率÷arr ，
//void TIM3_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 					//计数频率 = 84M÷psc+1   ，PWM频率 =  计数频率÷arr ，
//void TIM4_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty) 					//计数频率 = 84M÷psc+1   ，PWM频率 =  计数频率÷arr ，
//void TIM5_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 					//计数频率 = 84M÷psc+1   ，PWM频率 =  计数频率÷arr ，
void TIM8_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 					//计数频率 = 168M÷psc+1   ，PWM频率 =  计数频率÷arr ，
void TIM9_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 					//计数频率 = 168M÷psc+1   ，PWM频率 =  计数频率÷arr ，
//void TIM10_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 				//计数频率 = 168M÷psc+1   ，PWM频率 =  计数频率÷arr ，
//void TIM11_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 				//计数频率 = 168M÷psc+1   ，PWM频率 =  计数频率÷arr ，
//void TIM12_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 				//计数频率 = 84M÷psc+1   ，PWM频率 =  计数频率÷arr ，
//void TIM13_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 				//计数频率 = 84M÷psc+1   ，PWM频率 =  计数频率÷arr ，
//void TIM14_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 				//计数频率 = 84M÷psc+1   ，PWM频率 =  计数频率÷arr ，

void TIM1_PWM_charge_duty(PWM_CH PWM_x,u32 duty);    						//调用实时改变占空比
void TIM8_PWM_charge_duty(PWM_CH PWM_x,u32 duty);
void TIM9_PWM_charge_duty(PWM_CH PWM_x,u32 duty);
#endif

