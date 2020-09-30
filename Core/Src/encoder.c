#include "encoder.h"
#include "tim.h"


void Encoder_Init(void){
	MX_TIM2_Init();

	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_2);
	__HAL_TIM_SET_COUNTER(&htim2,0);

}

Encoder_Feedback_t Encoder_Read(void){
//	counter=__HAL_TIM_GET_COUNTER(&htim2);
	//Encoder_Feedback_t.angle_abs=0;
}
