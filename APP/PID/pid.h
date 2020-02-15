/************************************************************************
简�?位置式PID控制程序
作者：logic
日期�?016�?�?�?************************************************************************/
#ifndef PID_H
#define PID_H

typedef struct PID_Struct
{
	float P;
	float I;
	float D;
	float IThreshold;    //�����Ҽӵ�һ�����������뷧ֵ���ﵽ��ͣ�����Ҽӵ�һ��
                             //���������뷧ֵ���ﵽ��ͣ�����Ҽӵ�һ�����������뷧ֵ���ﵽ��ͣ 
                             // �����Ҽӵ�һ�������������뷧ֵ���ﵽ��ֹͣ
        float rate_actual_output;

	float aim;
	float previous;
	float current;
	float error;
	
	float I_count;/*integral from n=0 to n=t*/

	float result;
}PID_Struct; //�ṹ�����

void PID_Init(PID_Struct *PID,float rate_actual_output,float P,float I,float D,float IThreshold);
void PID_SetAim(PID_Struct *PID,float aim);//used by user(asynchronous with PID_Out)
float PID_Out(PID_Struct *PID,float current);//used by system
#endif
