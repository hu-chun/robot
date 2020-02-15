#include  "control.h"
#include "common.h"


void motor_en_init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOF时钟

	//GPIOF9,F10初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;		//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);				//初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;		//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);				//初始化
	GPIO_ResetBits(GPIOA,GPIO_Pin_8 | GPIO_Pin_9);		//至高，使能
	GPIO_ResetBits(GPIOE,GPIO_Pin_10 | GPIO_Pin_15);		//至高，使能
}
void motor_encodeinit(void)
{
	/* 编码器初始化*/
	Encoder_Init_TIM2();  			//A     
	Encoder_Init_TIM3();			//B
	Encoder_Init_TIM4();			//C
	/*电机初始化*/
	TIM1_PWM_Init(pwm_1,63,167,0);     	//15.625K A
	TIM1_PWM_Init(pwm_2,63,167,0);	   	//
	TIM1_PWM_Init(pwm_3,63,167,0);	   	//B
	TIM1_PWM_Init(pwm_4,63,167,0);	   	//
	TIM8_PWM_Init(pwm_1,63,167,0);	   	//C
	TIM8_PWM_Init(pwm_2,63,167,0);	   	//
	//TIM8_PWM_Init(pwm_3,74,167,0);
	//TIM8_PWM_Init(pwm_4,74,167,0);
	motor_en_init();         			//电机驱动EN端初始化
}
	
void MOTOR_A_runing(int pwm,Motor_EN motor_en)
{
	if(motor_en == enable)
	{
		A_EN;
		if(pwm>800)
		pwm=800;
		else if(pwm<= -800)
			pwm=-800; 
		if(pwm >= 0)
		{
			 TIM1_PWM_charge_duty(pwm_1,pwm);
			 TIM1_PWM_charge_duty(pwm_2,0);
		}
		else
		{ 
			 TIM1_PWM_charge_duty(pwm_1,0);
			 TIM1_PWM_charge_duty(pwm_2,-pwm);
		} 
	}
	else
	{
		A_DISEN;
		TIM1_PWM_charge_duty(pwm_1,0);
		TIM1_PWM_charge_duty(pwm_2,0);
	}
	
}

void MOTOR_B_runing(int pwm,Motor_EN motor_en)
{
	if(motor_en == enable)
	{
		B_EN;
		if(pwm>800)
		pwm=800;
		else if(pwm<= -800)
			pwm=-800; 
		if(pwm >= 0)
		{
			 TIM1_PWM_charge_duty(pwm_3,pwm);
			 TIM1_PWM_charge_duty(pwm_4,0);
		}
		else
		{ 
			 TIM1_PWM_charge_duty(pwm_3,0);
			 TIM1_PWM_charge_duty(pwm_4,-pwm);
		} 
	}
	else
	{
		B_DISEN;
		TIM1_PWM_charge_duty(pwm_3,0);
		TIM1_PWM_charge_duty(pwm_4,0);
	}
	
}
void MOTOR_C_runing(int pwm,Motor_EN motor_en)
{
	if(motor_en == enable)
	{
		C_EN;
		if(pwm>800)
		pwm=800;
		else if(pwm<= -800)
			pwm=-800; 
		if(pwm >= 0)
		{
			 TIM8_PWM_charge_duty(pwm_1,pwm);
			 TIM8_PWM_charge_duty(pwm_2,0);
		}
		else
		{ 
			 TIM8_PWM_charge_duty(pwm_1,0);
			 TIM8_PWM_charge_duty(pwm_2,-pwm);
		} 
	}
	else
	{
		C_DISEN;
		TIM8_PWM_charge_duty(pwm_1,0);
		TIM8_PWM_charge_duty(pwm_2,0);
	}
}
float P=0.39288;
float I=0.0678;//0.058;0.1384   0.0678
float D=0.035;//;.04200.032    0.035
u16 timea_A=0;
u16 timea_B=0;
u16 timea_C=0;
int16_t var[8]={0};
/*pid处理相关函数和中断*/
PID_Struct MOTORZ_A,MOTORZ_B,MOTORZ_C;
WHEEL_SPEED  EIT_ROBOT;						//机器人转态变量参数
Motor_EN ALL_MOTOR_EN;						//电机使能标志位
void motor_pid_runing()
{
	PID_Init(&MOTORZ_A,0,0.502,I,D,700);
	PID_Init(&MOTORZ_B,0,0.67,I,D,700);
	PID_Init(&MOTORZ_C,0,0.458,I,D,700);
	PID_SetAim(&MOTORZ_A,0);
	PID_SetAim(&MOTORZ_B,0);
	PID_SetAim(&MOTORZ_C,0);
	EIT_ROBOT.wheel_aim_A = 0;
	EIT_ROBOT.wheel_aim_B = 0;
	EIT_ROBOT.wheel_aim_C = 0;
	ALL_MOTOR_EN = enable;
	TIMERx_init(TIME_6,200-1,8400-1);
}

void TIM6_DAC_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==SET) //溢出中断
	{
		/**********************轮子A*************/
		PID_SetAim(&MOTORZ_A,EIT_ROBOT.wheel_aim_A);
		EIT_ROBOT.Speed_current_A = Read_Encoder(2);
		EIT_ROBOT.Speed_current_A = (EIT_ROBOT.Speed_after_A + EIT_ROBOT.Speed_current_A)/2; //采两次的值进行平均滤波
		var[0]=EIT_ROBOT.Speed_current_A;
		EIT_ROBOT.Speed_after_A = EIT_ROBOT.Speed_current_A;
		EIT_ROBOT.EN_A = ALL_MOTOR_EN;						//先使能，后做修改
		if(EIT_ROBOT.Speed_current_A>3000||EIT_ROBOT.Speed_current_A<-3000)				//防跑飞
		{
			timea_A++;						//计时
			if(timea_A == 3)
			{
				EIT_ROBOT.EN_A = disable;
			    EIT_ROBOT.baofu_flagA = 1;	
				timea_A	= 0;
			}
		}
		
		if((EIT_ROBOT.Speed_current_A<10||EIT_ROBOT.Speed_current_A>-10)&&(EIT_ROBOT.baofu_flagA == 1))
		{
			timea_A++;						//计时
			if(timea_A == 65000)
			{
				EIT_ROBOT.EN_A = enable;
				EIT_ROBOT.baofu_flagA = 0;
				timea_A = 0;
			}	
		}
		if(EIT_ROBOT.baofu_flagA == 1)
		{
			EIT_ROBOT.EN_A = disable;
		}
		EIT_ROBOT.Out_pwm_A = (int)PID_Out(&MOTORZ_A,EIT_ROBOT.Speed_current_A);		
		MOTOR_A_runing(EIT_ROBOT.Out_pwm_A,EIT_ROBOT.EN_A);
		/**********************轮子B*************/
		PID_SetAim(&MOTORZ_B,EIT_ROBOT.wheel_aim_B);
		EIT_ROBOT.Speed_current_B = Read_Encoder(3);
		EIT_ROBOT.Speed_current_B = (EIT_ROBOT.Speed_after_B + EIT_ROBOT.Speed_current_B)/2;	//采两次的值进行平均滤波
		var[1]=EIT_ROBOT.Speed_current_B;
		EIT_ROBOT.Speed_after_B = EIT_ROBOT.Speed_current_B;
		EIT_ROBOT.EN_B = ALL_MOTOR_EN;						//先使能，后做修改
		if(EIT_ROBOT.Speed_current_B>3000||EIT_ROBOT.Speed_current_B<-3000)
		{
			timea_B++;						//计时
			if(timea_B == 3)
			{
				EIT_ROBOT.EN_A = disable;
			    EIT_ROBOT.baofu_flagB = 1;	
				timea_B	= 0;
			}
		}
		if((EIT_ROBOT.Speed_current_B<10||EIT_ROBOT.Speed_current_B>-10)&&(EIT_ROBOT.baofu_flagB == 1))
		{
			timea_B++;						//计时
			if(timea_B == 65000)
			{
				EIT_ROBOT.EN_B = enable;
				EIT_ROBOT.baofu_flagB = 0;
				timea_B = 0;
			}	
		}
		EIT_ROBOT.Out_pwm_B = (int)PID_Out(&MOTORZ_B,EIT_ROBOT.Speed_current_B);
		MOTOR_B_runing(EIT_ROBOT.Out_pwm_B,EIT_ROBOT.EN_B);
		/**********************轮子C*************/
		PID_SetAim(&MOTORZ_C,EIT_ROBOT.wheel_aim_C);
		EIT_ROBOT.Speed_current_C = Read_Encoder(4);
		EIT_ROBOT.Speed_current_C = (EIT_ROBOT.Speed_after_C + EIT_ROBOT.Speed_current_C)/2;		//采两次的值进行平均滤波
		var[2]=EIT_ROBOT.Speed_current_C;
		EIT_ROBOT.Speed_after_C = EIT_ROBOT.Speed_current_C;
		EIT_ROBOT.EN_C = ALL_MOTOR_EN;						//先使能，后做修改
		if(EIT_ROBOT.Speed_current_C>3000||EIT_ROBOT.Speed_current_C<-3000)
		{
			timea_C++;						//计时
			if(timea_C == 3)
			{
				EIT_ROBOT.EN_C = disable;
			    EIT_ROBOT.baofu_flagB = 1;	
				timea_C	= 0;
			}
		}
		if((EIT_ROBOT.Speed_current_C<10||EIT_ROBOT.Speed_current_C>-10)&&(EIT_ROBOT.baofu_flagC == 1))
		{
			timea_C++;						//计时
			if(timea_C == 65000)
			{
				EIT_ROBOT.EN_C = enable;
				EIT_ROBOT.baofu_flagC = 0;
				timea_C = 0;
			}	
		}
		EIT_ROBOT.Out_pwm_C = (int)PID_Out(&MOTORZ_C,EIT_ROBOT.Speed_current_C);
		MOTOR_C_runing(EIT_ROBOT.Out_pwm_C,EIT_ROBOT.EN_C);
		
	}
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);  //清除中断标志位
}










