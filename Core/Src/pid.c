#include "pid.h"
#include "tim.h"





//
void PID_Init(PID_t* pidHandle, float Kp, float Ki, float Kd, float error_stop,float integ_sat)
{
	pidHandle->init.Kd = Kd;
	pidHandle->init.Kp = Kp;
	pidHandle->init.Ki = Ki;
	pidHandle->init.error_stop = error_stop;
	pidHandle->init.integ_sat = integ_sat;
	pidHandle->process.integ = 0;
	pidHandle->process.previous_error = 0;
	pidHandle->process.error = 0;
	pidHandle->process.deriv = 0;
	pidHandle->process.output = 0;
	pidHandle->input.order = 0;
	pidHandle->input.feedback = 0;
}

float PID_Execute(PID_t* pidHandle)
{
 // error
	pidHandle->process.previous_error = pidHandle->process.error;
	pidHandle->process.error = pidHandle->input.order-pidHandle->input.feedback;

 // derivate
	pidHandle->process.deriv = pidHandle->process.error - pidHandle->process.previous_error;

 // integer
	if (fabs(pidHandle->process.error) > pidHandle->init.error_stop){
		pidHandle->process.integ = pidHandle->process.integ + pidHandle->process.error;
	}

	if (fabs(pidHandle->process.integ) > pidHandle->init.integ_sat){
		pidHandle->process.integ = pidHandle->init.integ_sat;
	}
//command


pidHandle->process.output = pidHandle->init.Kp * pidHandle->process.error + pidHandle->init.Ki * pidHandle->process.integ + pidHandle->init.Kd * pidHandle->process.deriv;

return pidHandle->process.output;
}
