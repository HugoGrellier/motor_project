#include "encoder.h"
#include "tim.h"
#include <math.h>
Encoder_Feedback_t Encoder;

void Encoder_Init(void){
	MX_TIM2_Init();

	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_2);
	__HAL_TIM_SET_COUNTER(&htim2,32768);

}

Encoder_Feedback_t Encoder_Read(void){

	float deltaT = 0.040;

	float counter=__HAL_TIM_GET_COUNTER(&htim2);
	__HAL_TIM_SET_COUNTER(&htim2,32768);

	float delta = ((counter-32768.0F)*2.0F*M_PI)/(75.0F*8.0F);
	Encoder.angle_abs += delta;
	Encoder.angle_rel = fmod(Encoder.angle_abs,2*M_PI);
	if (Encoder.angle_rel<0){
		Encoder.angle_rel = Encoder.angle_rel+2*M_PI;
	}

	Encoder.d_angle=delta/deltaT;

	return Encoder;

}
