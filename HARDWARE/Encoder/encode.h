#ifndef __ENCODE_H__
#define __ENCODE_H__
#include "sys.h" 


//两种读编码器的方式
void Encoder_Init2_TIM2(void);
void Encoder_Init2_TIM3(void);
void Encoder_Init2_TIM4(void);
void Encoder_Init2_TIM5(void);

void Encoder_Init_TIM2(void);
void Encoder_Init_TIM3(void);
void Encoder_Init_TIM4(void);
void Encoder_Init_TIM5(void);

int TIM2_Encoder_Read(void);
int TIM3_Encoder_Read(void);
int TIM4_Encoder_Read(void);
int TIM5_Encoder_Read(void);

int TIM_Encoder_Read(u8 TIMX);

int Read_Encoder(u8 TIMX);

#endif


