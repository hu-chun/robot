
#include "common.h"

void Peripherals_init(void)
{
	LED_Init();					//��ʼ��LED
	KEY_Init();					//��ʼ������  
	OLED_Init();				//OLed��ʼ��
	#if Shou_or_Computer_uart
	USART_INIT(USART_1,115200);
	#else
	USART_INIT(USART_1,9600);
	#endif
	USART_INIT(USART_2,9600);	//��λͨ��
	//USART_INIT(USART_6,115200);	//ң����ͨ��
	#if Cmera_uart			 	//����ͷͨ��
	USART_INIT(USART_4,115200);
	#endif						
	#if TopBoard_uart			//����ͨ��
	USART_INIT(USART_3,9600);
	#endif
	
	motor_encodeinit();			//���Ӳ����ʼ��
	motor_pid_runing();			//���������ʼ��
	EXTIX_Init();
	near_inint();
	My_RTC_Init();		 		//��ʼ��RTC
	RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);		//����WAKE UP�ж�,1�����ж�һ��
	//RTC_Set_Time(21,19,00,RTC_H12_AM);	//����ʱ��
	//RTC_Set_Date(18,9,19,2);		//��������
	BEEP_OFF;
	TIMERx_init(TIME_7,10000,840-1);   //����ʱ��10ms
	NRF24L01_Init();
	camear_cmd(OV_TARGET);				//Ŀ��ʶ��ģʽ
	//camear_color(TARGET_BLUE);			//ʶ����ɫ
	Camear_control_init();           //ͼ����Ƶ�PID������ʼ��
	while(NRF24L01_Check())
	{
		LED0=!LED0;	 
		delay_ms(200);
	}
	

	
	
	

}



