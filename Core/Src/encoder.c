#include "encoder.h"
#include "tim.h"


void Encoder_Init(void){
	MX_TIM2_Init();

	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_2);
	__HAL_TIM_SET_COUNTER(&htim2,32768);

}

Encoder_Feedback_t Encoder_Read(void){
	float pi= 3.14159;
	uint8_t MSG[50]={'\0'};
	Encoder_Feedback_t Encoder;
	float angle_abs_Prec=Encoder.angle_abs;
	float counter=__HAL_TIM_GET_COUNTER(&htim2);
	sprintf(MSG,"CNT: %f\n\r",counter);
	printf(MSG);
	Encoder.angle_abs=((counter-32768)/(75*8))*2*pi;
	Encoder.angle_rel=fmod(Encoder.angle_abs,2*pi);
	Encoder.d_angle=(angle_abs_Prec-Encoder.d_angle)*84000000;



	return Encoder;

}
