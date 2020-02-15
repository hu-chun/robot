
#include "EXIT.h"
#include "common.h"

extern u16 amount;
/**********��Ҫ�õ��ж�������������ӳ�ʼ��******/
void GPIO_PIN_INIT()
{
	  GPIO_InitTypeDef  GPIO_InitStructure;

	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOA,GPIOEʱ��
	 
	  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; //KEY0 KEY1 KEY2��Ӧ����
	  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;//��ͨ����ģʽ
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;//����
	  GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
}

/**************Ҫ�������ⲿ�ж��޸�****************/
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	GPIO_PIN_INIT(); 			//��ʼ����Ҫ�õ�������
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��,һ��Ҫʹ�ܣ���һ������
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource0);// ���ӵ��ж���0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource1);// ���ӵ��ж���1
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource2);// ���ӵ��ж���2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource3);// ���ӵ��ж���3

	/* ����EXTI_Line0,2,3,4 */
   EXTI_InitStructure.EXTI_Line 	= EXTI_Line0|EXTI_Line1 | EXTI_Line2 | EXTI_Line3;
   EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;//�ж��¼�
   EXTI_InitStructure.EXTI_Trigger  = EXTI_Trigger_Rising; //�½��ش���
   EXTI_InitStructure.EXTI_LineCmd  = ENABLE;//�ж���ʹ��
   EXTI_Init(&EXTI_InitStructure);//����
 
   NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�ⲿ�ж�0
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�0
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//�����ȼ�2
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
   NVIC_Init(&NVIC_InitStructure);//����
	
   NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//�ⲿ�ж�2
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�3
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//�����ȼ�2
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
   NVIC_Init(&NVIC_InitStructure);//����
	
   NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//�ⲿ�ж�3
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�2
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//�����ȼ�2
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
   NVIC_Init(&NVIC_InitStructure);//����
	
	
   NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//�ⲿ�ж�4
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�1
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//�����ȼ�2
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
   NVIC_Init(&NVIC_InitStructure);//����
}
extern u8 PLAN_flag;
//extern u8 RED_STEP;
//extern u8 GREED_STEP;
extern u8 MODE_CHOSE ;              // 1:�� 2���� 3:ң�� 4������
extern u8 KEY_CHOSE ;				//�췽�̷���Ӧ��ģʽ��ң�غͲ���û��
//�ⲿ�ж�0�������
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
	 EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
}	
//�ⲿ�ж�1�������
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
	 EXTI_ClearITPendingBit(EXTI_Line1);//���LINE4�ϵ��жϱ�־λ  
}
//�ⲿ�ж�2�������
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
	 EXTI_ClearITPendingBit(EXTI_Line2);//���LINE2�ϵ��жϱ�־λ 
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	 delay_ms(5);
	BEEP =!BEEP;
	 //BEEP=!BEEP;
     PLAN_flag = 1;	
	 EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}


