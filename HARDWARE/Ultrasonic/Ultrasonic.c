#include "Ultrasonic.h"
#include "myusart.h"
#include "common.h"
#include "delay.h"
u8 i=0;

volatile u16 distance_A;
volatile u16 distance_B;
volatile u16 distance_C;
volatile u16 distance_D;
u8 distance_A_flag = 0;
u8 DIS_buffa[2]={0};
u8 DIS_buffb[2]={0};
u8 DIS_buffc[2]={0};
u8 DIS_buffd[2]={0};
u8 D_A = 0;
u8 D_B = 0;
u8 D_C = 0;
u8 D_D = 0;
uint16_t CF[1] = {0x55};

volatile u32 TIME;	//输入捕获值	 记录TIM->CNT的值



/*超声波distance<100mm叫准，超声波distance>100mm不准*/
TIM_ICInitTypeDef  TIM9_ICInitStructure;
void ULTRASIONIC_INIT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
	GPIO_Init(GPIOE,&GPIO_InitStructure); //初始化PA0
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9); //PA0复用位定时器5
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	
	TIM_TimeBaseStructure.TIM_Prescaler=167;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=0XFFFFFFFF;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);
	
	
	
	TIM9_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
    TIM9_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
    TIM9_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
    TIM9_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
    TIM9_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
    TIM_ICInit(TIM9, &TIM9_ICInitStructure);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	TIM_ITConfig(TIM9,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断
	TIM_Cmd(TIM9,ENABLE ); 	//使能定时器5
		
}


void Ultragionic_init(ULTRASIONIC_X ult_x)
{
	switch(ult_x)
	{
		case ULT_A:
			USART_INIT(USART_2,9600);break;
		case ULT_B:
			USART_INIT(USART_4,9600);
			//TIM9_PWM_Init(pwm_1,2500,335,32); //舵机扫描200hz   28-36
			break;
			
		case ULT_C:
			USART_INIT(USART_5,9600);break;
		case ULT_D:
			USART_INIT(USART_6,9600);break;
	}

}

void USART2_IRQHandler(void)                	
{
	unsigned char date;
	if(USART_GetITStatus(USART2,USART_IT_RXNE))
	{
		date = USART_ReceiveData(USART2);
		//USART_SendData(USART3, date);//把接受到的发送回去
		DIS_buffa[D_A++] = date;
		if(D_A == 2)
			D_A = 0;
		distance_A = DIS_buffa[0]*256+DIS_buffa[1];
	}
	USART_ClearFlag(USART2,USART_FLAG_RXNE);
}

void UART4_IRQHandler(void)                	
{
	unsigned char date;
	if(USART_GetITStatus(UART4,USART_IT_RXNE))
	{
		date = USART_ReceiveData(UART4);
		//USART_SendData(UART4, date);//把接受到的发送回去
		DIS_buffb[D_B++] = date;
		if(D_B == 2)
			D_B = 0;
		distance_B = DIS_buffb[0]*256+DIS_buffb[1];
	}
	USART_ClearFlag(UART4,USART_FLAG_RXNE);

}

void UART5_IRQHandler(void)                	
{
	unsigned char date;
	if(USART_GetITStatus(UART5,USART_IT_RXNE))
	{
		date = USART_ReceiveData(UART5);
		//USART_SendData(UART5, date);//把接受到的发送回去
		DIS_buffc[D_C++] = date;
		if(D_C == 2)
			D_C = 0;
		distance_C = DIS_buffc[0]*256+DIS_buffc[1];
	}
	USART_ClearFlag(UART5,USART_FLAG_RXNE);

}

void USART6_IRQHandler(void)                	
{
	unsigned char date;
	if(USART_GetITStatus(USART6,USART_IT_RXNE))
	{
		date = USART_ReceiveData(USART6);
		//USART_SendData(USART6, date);//把接受到的发送回去
		DIS_buffd[D_D++] = date;
		if(D_D == 2)
			D_D = 0;
		distance_D = DIS_buffd[0]*256+DIS_buffd[1];
	}
	USART_ClearFlag(USART6,USART_FLAG_RXNE);

}

uint16_t read_distance(ULTRASIONIC_X ult_x)
{
	//u16 distance = 0;
	switch(ult_x)
	{
		case ULT_A:
			    USART_SendData(USART2,CF[0]);
				delay_ms(20);
				return distance_A ;
		case ULT_B:
				USART_SendData(UART4,CF[0]);
				delay_ms(20);
				return distance_B ;
		case ULT_C:
				USART_SendData(UART5,CF[0]);
				delay_ms(20);
				return distance_C ;
		case ULT_D:
				USART_SendData(USART6,CF[0]);
				delay_ms(20);
				return distance_D ;
	}
}




/*void TIM1_BRK_TIM9_IRQHandler(void)
{

	if (TIM_GetITStatus(TIM9, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{
			if(i==1)
			{
			   TIM_SetCounter(TIM9,0);									   //计数器清零
			   TIM_OC1PolarityConfig(TIM9,TIM_ICPolarity_Falling);		   //设置为下降沿触发
			   i=0;															   //标志上升沿到来
			}
			
			else
			{
				TIME=TIM_GetCounter(TIM9);					//获得捕获值
				if(TIME>65535)
				TIME = 65535;
				else;
				TIM_OC1PolarityConfig(TIM9,TIM_ICPolarity_Rising);			   //设置为上降沿触发
				i=1;												  			   //标志下降沿到来 			
			}		
		}
	
		
	TIM_ClearITPendingBit(TIM9, TIM_IT_CC1|TIM_IT_Update);                 //清除中断标志位
	
}*/

float get_distance(u32 TIME)			//超声波函数 调用时需定义外部变量extern u32	TIME;
{
		float distance; 
		TX_A; 	
		delay_us(20);
		UTX_A;	 		 				 //发出请求	
		distance=(float)TIME*340/20000;							 //得到距离
		return distance;	 
}



