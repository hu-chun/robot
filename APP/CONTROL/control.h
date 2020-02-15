#ifndef  __CONTROL_H
#define  __CONTROL_H
#include "common.h"
#define  A_EN   	GPIO_SetBits(GPIOE,GPIO_Pin_10);
#define  A_DISEN   	GPIO_ResetBits(GPIOE,GPIO_Pin_10);
#define  B_EN  		GPIO_SetBits(GPIOE,GPIO_Pin_15);
#define  B_DISEN   	GPIO_ResetBits(GPIOE,GPIO_Pin_15);
#define  C_EN   	GPIO_SetBits(GPIOA,GPIO_Pin_8);
#define  C_DISEN   	GPIO_ResetBits(GPIOA,GPIO_Pin_8);

typedef enum
{
	enable = 1,
	disable = 0,
}Motor_EN;     //电机驱动en端，1使能输出才有效，0，反之，用于防止堵转


typedef struct WHEEL_SPEED
{
	int wheel_aim_A;
	int wheel_aim_B;
	int wheel_aim_C;
	int16_t Speed_current_A;
	int16_t Speed_current_B;
	int16_t Speed_current_C;
	int16_t Speed_after_A;
	int16_t Speed_after_B;
	int16_t Speed_after_C;
	int16_t Out_pwm_A;
	int16_t Out_pwm_B;
	int16_t Out_pwm_C;
	Motor_EN EN_A;
	Motor_EN EN_B;
	Motor_EN EN_C;
	u8 baofu_flagA;
	u8 baofu_flagB;
	u8 baofu_flagC;
}WHEEL_SPEED;

void motor_encodeinit(void);
void motor_pid_runing(void);

#endif

