#include "myusart.h"
#include "stdio.h"	
#include "stm32f4xx_conf.h"
//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif

/**********��ʼ��***********/
void USART_INIT(USART_x usart,u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	switch(usart)
	{
		case USART_1:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��GPIOAʱ��
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
			
			GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1); //GPIOA9����ΪUSART1
			GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1); //GPIOA10����ΪUSART1
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //GPIOA9��GPIOA10
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
			GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; //����
			GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ��PA9��PA10
		
			USART_InitStructure.USART_BaudRate = bound;//����������
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
			USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
			USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
		
			USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
			USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
			
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

			//Usart1 NVIC ����
			NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
			NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
			
			USART_ClearFlag(USART1, USART_FLAG_RXNE);
			break;
			
		case USART_2:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //ʹ��GPIOAʱ��
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
			
			GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2); //GPIOA2����ΪUSART1
			GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2); //GPIOA3����ΪUSART1
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
			GPIO_Init(GPIOD,&GPIO_InitStructure);
		
			USART_InitStructure.USART_BaudRate = bound;//����������
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
			USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
			USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
		
			USART_Init(USART2, &USART_InitStructure); //��ʼ������2
	
			USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2 
			
			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�

			//Usart1 NVIC ����
			NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����1�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�3
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�2
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
			NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
			
			USART_ClearFlag(USART2, USART_FLAG_RXNE);
			break;
			
		case USART_3:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��GPIOAʱ��
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART2ʱ��
			
			GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOA2����ΪUSART1
			GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOA3����ΪUSART1
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
			GPIO_Init(GPIOB,&GPIO_InitStructure);
		
			USART_InitStructure.USART_BaudRate = bound;//����������
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
			USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
			USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
		
			USART_Init(USART3, &USART_InitStructure); //��ʼ������2
	
			USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���3 
			
			USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������ж�

			//Usart1 NVIC ����
			NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����1�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�2
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
			NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
			
			USART_ClearFlag(USART3, USART_FLAG_RXNE);
			break;
			
		case USART_4:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //ʹ��GPIOAʱ��
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//ʹ��USART2ʱ��
			
			GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); //GPIOA2����ΪUSART1
			GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); //GPIOA3����ΪUSART1
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
			GPIO_Init(GPIOC,&GPIO_InitStructure);
		
			USART_InitStructure.USART_BaudRate = bound;					//����������
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//�ֳ�Ϊ8λ���ݸ�ʽ
			USART_InitStructure.USART_StopBits = USART_StopBits_1;		//һ��ֹͣλ
			USART_InitStructure.USART_Parity = USART_Parity_No;			//����żУ��λ
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
			USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;	//�շ�ģʽ
		
			USART_Init(UART4, &USART_InitStructure); 	//��ʼ������4
	
			USART_Cmd(UART4, ENABLE);  					//ʹ�ܴ���3 
			USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//��������ж�
			//Usart1 NVIC ����
			NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;//����1�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�2
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
			NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
			
			USART_ClearFlag(UART4, USART_FLAG_RXNE);
			break;
			
		case USART_5:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //ʹ��GPIOAʱ��
			//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//ʹ��USART2ʱ��
			
			GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5); //GPIOA2����ΪUSART1
			GPIO_PinAFConfig(GPIOC,GPIO_PinSource13,GPIO_AF_UART5); //GPIOA3����ΪUSART1
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
			GPIO_Init(GPIOC,&GPIO_InitStructure);
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����		
			GPIO_Init(GPIOC,&GPIO_InitStructure);
		
			USART_InitStructure.USART_BaudRate = bound;//����������
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
			USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
			USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
		
			USART_Init(UART5, &USART_InitStructure); //��ʼ������2
	
			USART_Cmd(UART5, ENABLE);  //ʹ�ܴ���3 
			
			USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//��������ж�

			//Usart1 NVIC ����
			NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;//����1�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�2
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
			NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
			
			USART_ClearFlag(UART5, USART_FLAG_RXNE);
			break;
			
		case USART_6:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE); //ʹ��GPIOAʱ��	
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//ʹ��USART2ʱ��
			
			GPIO_PinAFConfig(GPIOG,GPIO_PinSource9,GPIO_AF_USART6); //GPIOA2����ΪUSART1
			GPIO_PinAFConfig(GPIOG,GPIO_PinSource14,GPIO_AF_USART6); //GPIOA3����ΪUSART1
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
			GPIO_Init(GPIOG,&GPIO_InitStructure);
		
			USART_InitStructure.USART_BaudRate = bound;//����������
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
			USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
			USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
		
			USART_Init(USART6, &USART_InitStructure); //��ʼ������2
	
			USART_Cmd(USART6, ENABLE);  //ʹ�ܴ���3 
			
			USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);//��������ж�

			//Usart1 NVIC ����
			NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;//����1�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�2
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
			NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
			
			USART_ClearFlag(USART6, USART_FLAG_RXNE);
			break;
	}
		
}

void USART_Send_Char(USART_x usart_x,u8 ch)//��һ���ַ���
{
	switch(usart_x)
	{
		case USART_1:
			USART_SendData(USART1,ch);
			while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));
		    break;
		case USART_2:
			USART_SendData(USART2,ch);
			while(!USART_GetFlagStatus(USART2,USART_FLAG_TXE));
		    break;
		case USART_3:
			USART_SendData(USART3,ch);
			while(!USART_GetFlagStatus(USART3,USART_FLAG_TXE));
		    break;
		case USART_4:
			USART_SendData(UART4,ch);
			while(!USART_GetFlagStatus(UART4,USART_FLAG_TXE));
		    break;
		case USART_5:
			USART_SendData(UART5,ch);
			while(!USART_GetFlagStatus(UART5,USART_FLAG_TXE));
		    break;
		case USART_6:
			USART_SendData(USART6,ch);
			while(!USART_GetFlagStatus(USART6,USART_FLAG_TXE));
		    break;
	}
}

/************���ַ���***************/
void USART_Send_String(USART_x usart_x,uint8_t *str)
{
	switch(usart_x)
	{
		case USART_1:
			while(*str != '\0')
			{
				USART_Send_Char(USART_1,*str);
				str++;
			}
			break;
		case USART_2:
			while(*str != '\0')
			{
				USART_Send_Char(USART_2,*str);
				str++;
			}
			break;
		case USART_3:
			while(*str != '\0')
			{
				USART_Send_Char(USART_3,*str);
				str++;
			}
			break;
		case USART_4:
			while(*str != '\0')
			{
				USART_Send_Char(USART_4,*str);
				str++;
			}
			break;
		case USART_5:
			while(*str != '\0')
			{
				USART_Send_Char(USART_5,*str);
				str++;
			}
			break;
		case USART_6:
			while(*str != '\0')
			{
				USART_Send_Char(USART_6,*str);
				str++;
			}
			break;
	}
}

/************����ָ�����ȵ��ַ���********/

void USART_Send_Leng_String(USART_x usart_x,uint8_t *str,u8 leng)
{
	switch(usart_x)
	{
		case USART_1:
			while(leng != 0)
			{
				USART_Send_Char(USART_1,*str);
				str++;
				leng--;
			}
			break;
		case USART_2:
			while(leng != 0)
			{
				USART_Send_Char(USART_2,*str);
				str++;
				leng--;
			}
			break;
		case USART_3:
			while(leng != 0)
			{
				USART_Send_Char(USART_3,*str);
				str++;
				leng--;
			}
			break;
		case USART_4:
			while(leng != 0)
			{
				USART_Send_Char(USART_4,*str);
				str++;
				leng--;
			}
			break;
		case USART_5:
			while(leng != 0)
			{
				USART_Send_Char(USART_5,*str);
				str++;
				leng--;
			}
			break;
		case USART_6:
			while(leng != 0)
			{
				USART_Send_Char(USART_6,*str);
				str++;
				leng--;
			}
			break;
	}
}

void USART_SendWare(void *wareaddr,uint32_t waresize)
{
#define CMD_WARE     3
	uint8_t cmdf[2] = {CMD_WARE,~CMD_WARE};    				//���ڵ��� ʹ�õ�ǰ����
	uint8_t cmdr[2] = {~CMD_WARE,CMD_WARE};    				//���ڵ��� ʹ�õĺ�����
	USART_Send_Leng_String(USART_1,cmdf,sizeof(cmdf));    				//�ȷ���ǰ����
	USART_Send_Leng_String(USART_1,(uint8_t *)wareaddr,waresize);//��������
	USART_Send_Leng_String(USART_1,cmdr,sizeof(cmdr));    				//���ͺ�����
}


/***************�жϺ���************/
void USART1_IRQHandler(void)   //�����жϺ���ʾ��             	
{
	unsigned char date;
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		date = USART_ReceiveData(USART1);
		USART_SendData(USART1, date);//�ѽ��ܵ��ķ��ͻ�ȥ
	}
	
	USART_ClearFlag(USART1,USART_FLAG_RXNE);
}

/*void USART3_IRQHandler(void)                	
{
	unsigned char date;
	if(USART_GetITStatus(USART3,USART_IT_RXNE))
	{
		date = USART_ReceiveData(USART3);
		USART_SendData(USART3, date);//�ѽ��ܵ��ķ��ͻ�ȥ
	}
	USART_ClearFlag(USART3,USART_FLAG_RXNE);
}*/
//void UART4_IRQHandler(void)                	
//{
//	unsigned char date;
//	if(USART_GetITStatus(UART4,USART_IT_RXNE))
//	{
//		date = USART_ReceiveData(UART4);
//		USART_SendData(UART4, date);//�ѽ��ܵ��ķ��ͻ�ȥ
//	}
//	USART_ClearFlag(UART4,USART_FLAG_RXNE);
//}
//void UART5_IRQHandler(void)                	
//{
//	unsigned char date;
//	if(USART_GetITStatus(UART5,USART_IT_RXNE))
//	{
//		date = USART_ReceiveData(UART5);
//		USART_SendData(UART5, date);//�ѽ��ܵ��ķ��ͻ�ȥ
//	}
//	USART_ClearFlag(UART5,USART_FLAG_RXNE);
//}
void USART6_IRQHandler(void)                	
{
	unsigned char date;
	if(USART_GetITStatus(USART6,USART_IT_RXNE))
	{
		date = USART_ReceiveData(USART6);
		USART_SendData(USART6, date);//�ѽ��ܵ��ķ��ͻ�ȥ
	}
	USART_ClearFlag(USART6,USART_FLAG_RXNE);
}
