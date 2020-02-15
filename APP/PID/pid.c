#include "pid.h"

void PID_Init(PID_Struct *PID,float rate_actual_output,float P,float I,float D,float IThreshold)
{
	PID->P=P;
	PID->I=I;
	PID->D=D;
	PID->IThreshold=IThreshold;
	PID->aim=0;
	PID->previous=0;
	PID->current=0;
	PID->error=0;
	PID->I_count=0;
	PID->result=0;
        PID->rate_actual_output=rate_actual_output;
}
void PID_SetAim(PID_Struct *PID,float aim)//used by user(asynchronous with Calc)
{
        if(PID->aim==aim)
            return;
	PID->aim=aim;
//	PID->I_count=0;//I think the integral should be reset when aim change.

}
float PID_Out(PID_Struct *PID,float current)//used by system
{
	/*declare for variables*/
	float P_result;
	float I_result;
	float D_result;
	/*calculate for error*/
	PID->previous=PID->current;
	PID->current=current;
	PID->error=PID->current-PID->aim;
	/*calculate for P,I,D's results separately*/
	//for P
	P_result=PID->P*PID->error;
	//for I
	PID->I_count+=PID->error;
	I_result=PID->I*PID->I_count;
	if(I_result>PID->IThreshold)
	{
		PID->I_count=PID->IThreshold/PID->I;
		I_result=PID->IThreshold;
	}
	else if(I_result<-PID->IThreshold)
	{
		PID->I_count=-PID->IThreshold/PID->I;
		I_result=-PID->IThreshold;
	}
	//for D
	D_result=PID->D*(PID->current-PID->previous);
	/*resulte*/
	PID->result=P_result+I_result+D_result;
	//return -PID->result+PID->aim/19.83;
        if(PID->rate_actual_output==0)
          return -PID->result;
        else
          return -PID->result+PID->aim/PID->rate_actual_output;
}

