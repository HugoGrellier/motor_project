#ifndef PID_H
#define PID_H


typedef struct {
	struct{
		float Kp; // Proportional coefficient
		float Ki; // Integral coefficient
		float Kd; // Derivative coefficient
		float error_stop; // epsilon (error) tolerance -> goal considered as reached
		float integ_sat; // windup control with integral saturation
	} init;

	struct{
		float order; // order (what you want to reach)
		float feedback; // what you reached for now
	} input;

	struct{
		float error; // order - feedback
		float previous_error; // previous error... ^^
		float deriv; // i.e. output
		float integ; // i.e. output
		float output; // output = Ki*error + Ki*integ + Kd*deriv
	} process;
} PID_t;


// public functions
void PID_Init(PID_t* pidHandle, float Kp, float Ki, float Kd, float error_stop,float integ_sat);
float PID_Execute(PID_t* pidHandle);


#endif
