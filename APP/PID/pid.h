/************************************************************************
绠�浠?浣嶇疆寮廝ID鎺у埗绋嬪簭
浣滆�咃細logic
鏃ユ湡锛?016骞?鏈?鏃?************************************************************************/
#ifndef PID_H
#define PID_H

typedef struct PID_Struct
{
	float P;
	float I;
	float D;
	float IThreshold;    //这是我加的一个参数积分离阀值当达到就停这是我加的一个
                             //参数积分离阀值当达到就停这是我加的一个参数积分离阀值当达到就停 
                             // 这是我加的一个参数，积分离阀值当达到就停止
        float rate_actual_output;

	float aim;
	float previous;
	float current;
	float error;
	
	float I_count;/*integral from n=0 to n=t*/

	float result;
}PID_Struct; //结构体变量

void PID_Init(PID_Struct *PID,float rate_actual_output,float P,float I,float D,float IThreshold);
void PID_SetAim(PID_Struct *PID,float aim);//used by user(asynchronous with PID_Out)
float PID_Out(PID_Struct *PID,float current);//used by system
#endif
