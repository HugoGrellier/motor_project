#include "motor.h"
#include "tim.h"


void Motor_Init(void){
	MX_TIM3_Init();

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
};


void Motor_Pwm_Update(float in){

	TIM_OC_InitTypeDef sConfigOC1 = {0};
	sConfigOC1.OCMode = TIM_OCMODE_PWM1;
	sConfigOC1.Pulse = 0;
	sConfigOC1.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC1.OCFastMode = TIM_OCFAST_DISABLE;

	TIM_OC_InitTypeDef sConfigOC2 = {0};
	sConfigOC2.OCMode = TIM_OCMODE_PWM1;
	sConfigOC2.Pulse = 0;
	sConfigOC2.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC2.OCFastMode = TIM_OCFAST_DISABLE;


	if(in<-1.0){
		in=-1.0;
	}
	if(in>1.0){
			in=1.0;
		}
	if(in==0.0){
				sConfigOC1.Pulse = htim3.Init.Period;
				sConfigOC2.Pulse = htim3.Init.Period;
				}
	if(in<0.0){
		in=-1-in;
		sConfigOC1.Pulse = htim3.Init.Period*-in;
		sConfigOC2.Pulse = htim3.Init.Period;
	}
	if(in>0.0){
		in=1-in;
			sConfigOC1.Pulse = htim3.Init.Period;
			sConfigOC2.Pulse = htim3.Init.Period*in;
		}


	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC1, TIM_CHANNEL_1) != HAL_OK)
	  {
	    Error_Handler();
	  }

	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC2, TIM_CHANNEL_2) != HAL_OK)
	  {
	    Error_Handler();
	  }
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}
