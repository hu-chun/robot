#include "encode.h"
#include "delay.h"

void Encoder_Init2_TIM2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure); 						 //PA5
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&GPIO_InitStructure); 						   //PB3
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_TIM2);
	
	TIM2->ARR=(u16)(65535); //�趨�������Զ���װֵ
	TIM2->PSC=0; //Ԥ��Ƶ��
	TIM2->CCMR1 |= 1<<0; //����ģʽ��IC1FP1ӳ�䵽TI1��
	TIM2->CCMR1 |= 1<<8; //����ģʽ��IC2FP2ӳ�䵽TI2��
	TIM2->CCER |= 0<<1; //IC1������
	TIM2->CCER |= 0<<5; //IC2������
	TIM2->SMCR |= 3<<0; //����������������ػ��½�����Ч
	TIM2->CR1 |= 1<<0; //ʹ�ܼ�����
	
}

void Encoder_Init2_TIM3(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure); 						//PA7
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure); 							//PB4
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);
	
	TIM3->ARR=(u16)(65535); //�趨�������Զ���װֵ
	TIM3->PSC=0; //Ԥ��Ƶ��
	TIM3->CCMR1 |= 1<<0; //����ģʽ��IC1FP1ӳ�䵽TI1��
	TIM3->CCMR1 |= 1<<8; //����ģʽ��IC2FP2ӳ�䵽TI2��
	TIM3->CCER |= 0<<1; //IC1������
	TIM3->CCER |= 0<<5; //IC2������
	TIM3->SMCR |= 3<<0; //����������������ػ��½�����Ч
	TIM3->CR1 |= 1<<0; //ʹ�ܼ�����
	
}
void Encoder_Init2_TIM4(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//ʹ��PORTAʱ��	
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD,&GPIO_InitStructure); 						//PD13
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD,&GPIO_InitStructure); 						//PB6
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
	
	TIM4->ARR=(u16)(65535); //�趨�������Զ���װֵ
	TIM4->PSC=0; //Ԥ��Ƶ��
	TIM4->CCMR1 |= 1<<0; //����ģʽ��IC1FP1ӳ�䵽TI1��
	TIM4->CCMR1 |= 1<<8; //����ģʽ��IC2FP2ӳ�䵽TI2��
	TIM4->CCER |= 0<<1; //IC1������
	TIM4->CCER |= 0<<5; //IC2������
	TIM4->SMCR |= 3<<0; //����������������ػ��½�����Ч
	TIM4->CR1 |= 1<<0; //ʹ�ܼ�����
	
}

void Encoder_Init2_TIM5(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure); 						//PD13
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure); 						//PB6
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);
	
	TIM5->ARR=(u16)(65535); //�趨�������Զ���װֵ
	TIM5->PSC=0; //Ԥ��Ƶ��
	TIM5->CCMR1 |= 1<<0; //����ģʽ��IC1FP1ӳ�䵽TI1��
	TIM5->CCMR1 |= 1<<8; //����ģʽ��IC2FP2ӳ�䵽TI2��
	TIM5->CCER |= 0<<1; //IC1������
	TIM5->CCER |= 0<<5; //IC2������
	TIM5->SMCR |= 3<<0; //����������������ػ��½�����Ч
	TIM5->CR1 |= 1<<0; //ʹ�ܼ�����
}



void Encoder_Init_TIM2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,  ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure); 
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure); 
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);
	
	TIM_TimeBaseStructure.TIM_Prescaler=0;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=~(3<<5); 
	TIM_TimeBaseStructure.TIM_Period=(u16)(65535);   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;      //Ԥ��Ƶ
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	//Reset counter
	TIM_SetCounter(TIM2,0);
	TIM_Cmd(TIM2, ENABLE); 
}

void Encoder_Init_TIM3(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStructure); 						//PA7
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStructure); 							//PB4
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);
	
	TIM_TimeBaseStructure.TIM_Prescaler=0;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=~(3<<5); 
	TIM_TimeBaseStructure.TIM_Period=(u16)(65535);   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;      //Ԥ��Ƶ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	//Reset counter
	TIM_SetCounter(TIM3,0);
	TIM_Cmd(TIM3, ENABLE); 
}

void Encoder_Init_TIM4(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//ʹ��PORTAʱ��	
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD,&GPIO_InitStructure);  
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD,&GPIO_InitStructure); 
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
	
	TIM_TimeBaseStructure.TIM_Prescaler=0;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=~(3<<5); 
	TIM_TimeBaseStructure.TIM_Period=(u16)(65535);   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;      //Ԥ��Ƶ
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	//Reset counter
	TIM_SetCounter(TIM4,0);
	TIM_Cmd(TIM4, ENABLE); 
}

void Encoder_Init_TIM5(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure);   
	 
	/*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure); */
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);
	
	TIM_TimeBaseStructure.TIM_Prescaler=0;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=~(3<<5); 
	TIM_TimeBaseStructure.TIM_Period=0X0005FFFF;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;      //Ԥ��Ƶ
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM5, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	//Reset counter
	TIM_SetCounter(TIM5,0);
	TIM_Cmd(TIM5, ENABLE); 
}
//
//�����Ĵ�����ֵ
void TIM2_Encoder_Write(int data)
{
  TIM2->CNT = data;
}

void TIM3_Encoder_Write(int data)
{
  TIM3->CNT = data;
}
void TIM4_Encoder_Write(int data)
{
  TIM4->CNT = data;
}
void TIM5_Encoder_Write(int data)
{
  TIM5->CNT = data;
}

//������������,�����
int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;    
   switch(TIMX)
	 {
	   case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
		 case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		  case 5:  Encoder_TIM= (short)TIM5 -> CNT;  TIM5 -> CNT=0;break;	
		 default:  Encoder_TIM=0;
	 }
		return Encoder_TIM;
}

//
//����������
int TIM_Encoder_Read(u8 TIMX)
{
	int Encoder_TIM;
	switch(TIMX)
	{
		case 2:
			TIM2_Encoder_Write(0); 		//��������0
			delay_ms(10); 				//���ʱ�䣬�ɵ���
			Encoder_TIM = (int)((s16)(TIM2->CNT)); //��������ת��
			break;
		case 3:
			TIM3_Encoder_Write(0); 		//��������0
			delay_ms(10); 				//���ʱ�䣬�ɵ���
			Encoder_TIM = (int)((s16)(TIM3->CNT)); //��������ת��
			break;
		case 4:
			TIM4_Encoder_Write(0); 		//��������0
			delay_ms(10); 				//���ʱ�䣬�ɵ���
			Encoder_TIM = (int)((s16)(TIM4->CNT)); //��������ת��
			break;
		case 5:
			TIM5_Encoder_Write(0); 		//��������0
			delay_ms(10); 				//���ʱ�䣬�ɵ���
			Encoder_TIM = (int)((s16)(TIM5->CNT)); //��������ת��
			break;
		default:  Encoder_TIM=0;
		
	}	//��¼���ر仯������һ��դ�񱻼�¼4�Σ�
	return Encoder_TIM;
	
}

