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


void TIM1_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 					//����Ƶ�� = 168M��psc+1   ��PWMƵ�� =  ����Ƶ�ʡ�arr ��
//void TIM2_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 					//����Ƶ�� = 84M��psc+1   ��PWMƵ�� =  ����Ƶ�ʡ�arr ��
//void TIM3_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 					//����Ƶ�� = 84M��psc+1   ��PWMƵ�� =  ����Ƶ�ʡ�arr ��
//void TIM4_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty) 					//����Ƶ�� = 84M��psc+1   ��PWMƵ�� =  ����Ƶ�ʡ�arr ��
//void TIM5_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 					//����Ƶ�� = 84M��psc+1   ��PWMƵ�� =  ����Ƶ�ʡ�arr ��
void TIM8_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 					//����Ƶ�� = 168M��psc+1   ��PWMƵ�� =  ����Ƶ�ʡ�arr ��
void TIM9_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 					//����Ƶ�� = 168M��psc+1   ��PWMƵ�� =  ����Ƶ�ʡ�arr ��
//void TIM10_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 				//����Ƶ�� = 168M��psc+1   ��PWMƵ�� =  ����Ƶ�ʡ�arr ��
//void TIM11_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 				//����Ƶ�� = 168M��psc+1   ��PWMƵ�� =  ����Ƶ�ʡ�arr ��
//void TIM12_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 				//����Ƶ�� = 84M��psc+1   ��PWMƵ�� =  ����Ƶ�ʡ�arr ��
//void TIM13_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 				//����Ƶ�� = 84M��psc+1   ��PWMƵ�� =  ����Ƶ�ʡ�arr ��
//void TIM14_PWM_Init(PWM_CH PWM_x,u32 arr,u32 psc,u32 duty); 				//����Ƶ�� = 84M��psc+1   ��PWMƵ�� =  ����Ƶ�ʡ�arr ��

void TIM1_PWM_charge_duty(PWM_CH PWM_x,u32 duty);    						//����ʵʱ�ı�ռ�ձ�
void TIM8_PWM_charge_duty(PWM_CH PWM_x,u32 duty);
void TIM9_PWM_charge_duty(PWM_CH PWM_x,u32 duty);
#endif

