#include "TCS3200.h"
#include "delay.h"
//u16 Rgena=1,Ggena=1,Bgena=1;//���ڵ��ڰ�ƽ��
u16 Ramount=0,Gamount=0,Bamount=0;//���ڴ�Ŷ�ȡ��RGBֵ
u16 amount=0;//�жϼ���
int HSV[4]={0};
_RGB RGB;

/*****************************************************************************
   Hָhue��ɫ�ࣩ��Sָsaturation�����Ͷȣ���Lָlightness�����ȣ���Vָvalue(ɫ��)��Bָbrightness�����ȣ���

  ɫ�ࣨH����ɫ�ʵĻ������ԣ�����ƽ����˵����ɫ���ƣ����ɫ����ɫ�ȡ� 
  ���Ͷȣ�S����ָɫ�ʵĴ��ȣ�Խ��ɫ��Խ���������𽥱�ң�ȡ0-100%����ֵ��
  ���ȣ�V�������ȣ�B����ȡ0-100%�� 	
  
   0��:   ��ɫ��RGB:(255, 0,  0 ), 255:R, 0:B��G+���� 
   60��:  ��ɫ��RGB:(255,255, 0 )��255:G, 0:B, R-����
   120��: ��ɫ��RGB:( 0, 255, 0 )��255:G, 0:R��B+����
   180��: ��ɫ��RGB:( 0, 255,255)��255:B, 0:R��G-����
   240��: ��ɫ��RGB:( 0,  0, 255)��255:B, 0:G��R+����
   300��: ��ɫ��RGB:(255, 0, 255)��255:R, 0:G��B-����
   360��: ��ɫ��RGB:(255, 0,  0 )��255:R, 0:B��G+	

  RGBת����HSV���㷨					        
������ max=max(R,G,B)
������ min=min(R,G,B)
����   if R = max, H = (G-B)/(max-min)
������ if G = max, H = 2 + (B-R)/(max-min)
������ if B = max, H = 4 + (R-G)/(max-min)
������ H = H * 60
������ if H < 0, H = H + 360
������ V=max(R,G,B)
������ S=(max-min)/max
******************************************************************************/

void TCS3200_Init(u8 s0,u8 s1)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF, ENABLE);	 
	//S0--->PE5		S1--->PE6		S2--->PF2		S3--->PF3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		 
	GPIO_Init(GPIOE, &GPIO_InitStructure);			

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		 
	GPIO_Init(GPIOF, &GPIO_InitStructure);	

	S0=s0;
	S1=s1;	
}

/*******************************************
*
*		  ��ƽ��
*
*******************************************/
void WhiteBalance(void)
{
	S2=0;S3=0;//��ɫͨ��
	amount=0;			 //��ʼ����
	delay_ms(10);
	RGB.Rgena = amount;   //�����ɫ����      
	amount=0;

	S2=1;S3=1;//��ɫͨ��
	amount=0;
	delay_ms(10);
	RGB.Ggena = amount;	 //�����ɫ����
	amount=0;

	S2=0;S3=1;//��ɫͨ��
	amount=0;
	delay_ms(10);
	RGB.Bgena = amount;	  //�����ɫ����
	amount=0;
	S2=1;S3=0;//�ر�ͨ��  	  
} 

/*******************************************
*
*		  RGB��ȡ
*
*******************************************/
u16 tcs3200_RED(void)
{
	S2=0;S3=0;
	amount=0;
	delay_ms(10);
	S2=1;S3=0;//�ر�ͨ�� 
	Ramount=(u32) amount*255/RGB.Rgena;	 //ȡRֵ
	if(Ramount>255) 
		Ramount = 255;
	return Ramount;
}

u16 tcs3200_GREEN(void)
{
	S2=1;S3=1;
	amount=0;
	delay_ms(10);
	S2=1;S3=0;							//�ر�ͨ�� 
	Gamount=(u32) amount*255/RGB.Ggena;	//ȡGֵ
	if(Gamount>255) 
		Gamount = 255;
	return Gamount;
}

u16 tcs3200_BLUE(void)
{
	S2=0;S3=1;
	amount=0;
	delay_ms(10);
	S2=1;S3=0;							//�ر�ͨ�� 
	Bamount=(u32) amount*255/RGB.Bgena;//ȡBֵ	
	if(Bamount>255)
		Bamount = 255;
	return Bamount;
} 

u16 Actualcolor(u8 RED,u8 GREEN,u8 BLUE)
{
	u16 RGB_Color = 0x0000;
	RGB_Color |=(unsigned long) RED*1000/8225<<11;		//ת������Ļ��16λ��ɫֵ
	RGB_Color |=(unsigned long) GREEN*1000/4047<<5;	  
	RGB_Color |=(unsigned long) BLUE*1000/8225;
	return RGB_Color;
	
}
/*****************************************************************************
   Hָhue��ɫ�ࣩ��Sָsaturation�����Ͷȣ���Lָlightness�����ȣ���Vָvalue(ɫ��)��Bָbrightness�����ȣ���

  ɫ�ࣨH����ɫ�ʵĻ������ԣ�����ƽ����˵����ɫ���ƣ����ɫ����ɫ�ȡ� 
  ���Ͷȣ�S����ָɫ�ʵĴ��ȣ�Խ��ɫ��Խ���������𽥱�ң�ȡ0-100%����ֵ��
  ���ȣ�V�������ȣ�B����ȡ0-100%�� 	
  
   0��:   ��ɫ��RGB:(255, 0,  0 ), 255:R, 0:B��G+���� 
   60��:  ��ɫ��RGB:(255,255, 0 )��255:G, 0:B, R-����
   120��: ��ɫ��RGB:( 0, 255, 0 )��255:G, 0:R��B+����
   180��: ��ɫ��RGB:( 0, 255,255)��255:B, 0:R��G-����
   240��: ��ɫ��RGB:( 0,  0, 255)��255:B, 0:G��R+����
   300��: ��ɫ��RGB:(255, 0, 255)��255:R, 0:G��B-����
   360��: ��ɫ��RGB:(255, 0,  0 )��255:R, 0:B��G+	

  RGBת����HSV���㷨					        
������ max=max(R,G,B)
������ min=min(R,G,B)
����   if R = max, H = (G-B)/(max-min)
������ if G = max, H = 2 + (B-R)/(max-min)
������ if B = max, H = 4 + (R-G)/(max-min)
������ H = H * 60
������ if H < 0, H = H + 360
������ V=max(R,G,B)
������ S=(max-min)/max
******************************************************************************/
int *RGBtoHSV(u8 RED,u8 GREEN,u8 BLUE)
{
	float Max=0,Min=0;
	float Rhsv=0,Ghsv=0,Bhsv=0;
	float H=0,S=0,V=0;
	//int HSV[4]={0};
	Rhsv = (float) RED/25/10;	//RGBת����0��1.
	Ghsv = (float) GREEN/25/10;	 
	Bhsv = (float) BLUE/25/10;
	Max = (Rhsv>Ghsv)?Rhsv:Ghsv;	
	Max = (Max>Bhsv)?Max:Bhsv;		//ȡRGB���ֵ				  
	Min = (Rhsv<Ghsv)?Rhsv:Ghsv;								   
	Min = (Min<Bhsv)?Min:Bhsv;		//ȥRGB��Сֵ					 
							
	if(Rhsv==Max) H = (Ghsv-Bhsv)/(Max-Min);						  
	if(Ghsv==Max) H = 2+(Bhsv-Rhsv)/(Max-Min);		  					
	if(Bhsv==Max) H = 4+(Rhsv-Ghsv)/(Max-Min);							
	H =(int) (H*60);				//ȡH����ֵ									                  
	if(H<0) H = H+360;													  																		   	   
	V = (Rhsv>Ghsv)?Rhsv:Ghsv;												
	V = (V>Bhsv)?V:Bhsv;		//ȡV����ֵ									 																				  
	S = (Max-Min)/Max;			//ȡS����ֵ																													 	
	V = (int) (V*100);															 
	S = (int) (S*100);
	HSV[0] = H;
	HSV[1] = V;
	HSV[2] = S;
	
	return HSV;
}






















