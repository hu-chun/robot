
#include "common.h"

void Peripherals_init(void)
{
	LED_Init();					//初始化LED
	KEY_Init();					//初始化按键  
	OLED_Init();				//OLed初始化
	#if Shou_or_Computer_uart
	USART_INIT(USART_1,115200);
	#else
	USART_INIT(USART_1,9600);
	#endif
	USART_INIT(USART_2,9600);	//定位通信
	//USART_INIT(USART_6,115200);	//遥控器通信
	#if Cmera_uart			 	//摄像头通信
	USART_INIT(USART_4,115200);
	#endif						
	#if TopBoard_uart			//顶板通信
	USART_INIT(USART_3,9600);
	#endif
	
	motor_encodeinit();			//电机硬件初始化
	motor_pid_runing();			//电机参数初始化
	EXTIX_Init();
	near_inint();
	My_RTC_Init();		 		//初始化RTC
	RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);		//配置WAKE UP中断,1秒钟中断一次
	//RTC_Set_Time(21,19,00,RTC_H12_AM);	//设置时间
	//RTC_Set_Date(18,9,19,2);		//设置日期
	BEEP_OFF;
	TIMERx_init(TIME_7,10000,840-1);   //运行时基10ms
	NRF24L01_Init();
	camear_cmd(OV_TARGET);				//目标识别模式
	//camear_color(TARGET_BLUE);			//识别蓝色
	Camear_control_init();           //图像控制的PID参数初始化
	while(NRF24L01_Check())
	{
		LED0=!LED0;	 
		delay_ms(200);
	}
	

	
	
	

}



