#include "myusart.h"
#include "stdio.h"	
#include "stm32f4xx_conf.h"
//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif

/**********初始化***********/
void USART_INIT(USART_x usart,u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	switch(usart)
	{
		case USART_1:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //使能GPIOA时钟
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
			
			GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1); //GPIOA9复用为USART1
			GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1); //GPIOA10复用为USART1
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //GPIOA9与GPIOA10
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
			GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; //上拉
			GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化PA9，PA10
		
			USART_InitStructure.USART_BaudRate = bound;//波特率设置
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
			USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
			USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
		
			USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
			USART_Cmd(USART1, ENABLE);  //使能串口1 
			
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断

			//Usart1 NVIC 配置
			NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
			NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
			
			USART_ClearFlag(USART1, USART_FLAG_RXNE);
			break;
			
		case USART_2:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //使能GPIOA时钟
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
			
			GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2); //GPIOA2复用为USART1
			GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2); //GPIOA3复用为USART1
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
			GPIO_Init(GPIOD,&GPIO_InitStructure);
		
			USART_InitStructure.USART_BaudRate = bound;//波特率设置
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
			USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
			USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
		
			USART_Init(USART2, &USART_InitStructure); //初始化串口2
	
			USART_Cmd(USART2, ENABLE);  //使能串口2 
			
			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断

			//Usart1 NVIC 配置
			NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口1中断通道
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级3
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级2
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
			NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
			
			USART_ClearFlag(USART2, USART_FLAG_RXNE);
			break;
			
		case USART_3:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //使能GPIOA时钟
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART2时钟
			
			GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOA2复用为USART1
			GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOA3复用为USART1
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
			GPIO_Init(GPIOB,&GPIO_InitStructure);
		
			USART_InitStructure.USART_BaudRate = bound;//波特率设置
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
			USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
			USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
		
			USART_Init(USART3, &USART_InitStructure); //初始化串口2
	
			USART_Cmd(USART3, ENABLE);  //使能串口3 
			
			USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启相关中断

			//Usart1 NVIC 配置
			NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//串口1中断通道
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级2
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
			NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
			
			USART_ClearFlag(USART3, USART_FLAG_RXNE);
			break;
			
		case USART_4:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //使能GPIOA时钟
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//使能USART2时钟
			
			GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); //GPIOA2复用为USART1
			GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); //GPIOA3复用为USART1
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
			GPIO_Init(GPIOC,&GPIO_InitStructure);
		
			USART_InitStructure.USART_BaudRate = bound;					//波特率设置
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//字长为8位数据格式
			USART_InitStructure.USART_StopBits = USART_StopBits_1;		//一个停止位
			USART_InitStructure.USART_Parity = USART_Parity_No;			//无奇偶校验位
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
			USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;	//收发模式
		
			USART_Init(UART4, &USART_InitStructure); 	//初始化串口4
	
			USART_Cmd(UART4, ENABLE);  					//使能串口3 
			USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启相关中断
			//Usart1 NVIC 配置
			NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;//串口1中断通道
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级2
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
			NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
			
			USART_ClearFlag(UART4, USART_FLAG_RXNE);
			break;
			
		case USART_5:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //使能GPIOA时钟
			//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//使能USART2时钟
			
			GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5); //GPIOA2复用为USART1
			GPIO_PinAFConfig(GPIOC,GPIO_PinSource13,GPIO_AF_UART5); //GPIOA3复用为USART1
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
			GPIO_Init(GPIOC,&GPIO_InitStructure);
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉		
			GPIO_Init(GPIOC,&GPIO_InitStructure);
		
			USART_InitStructure.USART_BaudRate = bound;//波特率设置
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
			USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
			USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
		
			USART_Init(UART5, &USART_InitStructure); //初始化串口2
	
			USART_Cmd(UART5, ENABLE);  //使能串口3 
			
			USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启相关中断

			//Usart1 NVIC 配置
			NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;//串口1中断通道
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级2
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
			NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
			
			USART_ClearFlag(UART5, USART_FLAG_RXNE);
			break;
			
		case USART_6:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE); //使能GPIOA时钟	
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//使能USART2时钟
			
			GPIO_PinAFConfig(GPIOG,GPIO_PinSource9,GPIO_AF_USART6); //GPIOA2复用为USART1
			GPIO_PinAFConfig(GPIOG,GPIO_PinSource14,GPIO_AF_USART6); //GPIOA3复用为USART1
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
			GPIO_Init(GPIOG,&GPIO_InitStructure);
		
			USART_InitStructure.USART_BaudRate = bound;//波特率设置
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
			USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
			USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
		
			USART_Init(USART6, &USART_InitStructure); //初始化串口2
	
			USART_Cmd(USART6, ENABLE);  //使能串口3 
			
			USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);//开启相关中断

			//Usart1 NVIC 配置
			NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;//串口1中断通道
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级2
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
			NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
			
			USART_ClearFlag(USART6, USART_FLAG_RXNE);
			break;
	}
		
}

void USART_Send_Char(USART_x usart_x,u8 ch)//发一个字符串
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

/************发字符串***************/
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

/************发送指定长度的字符串********/

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
	uint8_t cmdf[2] = {CMD_WARE,~CMD_WARE};    				//串口调试 使用的前命令
	uint8_t cmdr[2] = {~CMD_WARE,CMD_WARE};    				//串口调试 使用的后命令
	USART_Send_Leng_String(USART_1,cmdf,sizeof(cmdf));    				//先发送前命令
	USART_Send_Leng_String(USART_1,(uint8_t *)wareaddr,waresize);//发送数据
	USART_Send_Leng_String(USART_1,cmdr,sizeof(cmdr));    				//发送后命令
}


/***************中断函数************/
void USART1_IRQHandler(void)   //接受中断函数示范             	
{
	unsigned char date;
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		date = USART_ReceiveData(USART1);
		USART_SendData(USART1, date);//把接受到的发送回去
	}
	
	USART_ClearFlag(USART1,USART_FLAG_RXNE);
}

/*void USART3_IRQHandler(void)                	
{
	unsigned char date;
	if(USART_GetITStatus(USART3,USART_IT_RXNE))
	{
		date = USART_ReceiveData(USART3);
		USART_SendData(USART3, date);//把接受到的发送回去
	}
	USART_ClearFlag(USART3,USART_FLAG_RXNE);
}*/
//void UART4_IRQHandler(void)                	
//{
//	unsigned char date;
//	if(USART_GetITStatus(UART4,USART_IT_RXNE))
//	{
//		date = USART_ReceiveData(UART4);
//		USART_SendData(UART4, date);//把接受到的发送回去
//	}
//	USART_ClearFlag(UART4,USART_FLAG_RXNE);
//}
//void UART5_IRQHandler(void)                	
//{
//	unsigned char date;
//	if(USART_GetITStatus(UART5,USART_IT_RXNE))
//	{
//		date = USART_ReceiveData(UART5);
//		USART_SendData(UART5, date);//把接受到的发送回去
//	}
//	USART_ClearFlag(UART5,USART_FLAG_RXNE);
//}
void USART6_IRQHandler(void)                	
{
	unsigned char date;
	if(USART_GetITStatus(USART6,USART_IT_RXNE))
	{
		date = USART_ReceiveData(USART6);
		USART_SendData(USART6, date);//把接受到的发送回去
	}
	USART_ClearFlag(USART6,USART_FLAG_RXNE);
}
