#include "encoder.h"
#include "tim.h"
#include <math.h>
Encoder_Feedback_t Encoder;

void Encoder_Init(void){
	MX_TIM2_Init();//initialisation du timer 2 (utile pour l encoder)

	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1); // assignation des channels de lecture de l encoder
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_2);
	__HAL_TIM_SET_COUNTER(&htim2,32768); //compteur initialise a la valeure mediane du compteur 16 bits (65535 au maximum)

}

Encoder_Feedback_t Encoder_Read(void){

	float deltaT = 0.040; //delta temps necessaire pour l obtention de la vitesse angulaire 

	float counter=__HAL_TIM_GET_COUNTER(&htim2); //lecture valeure du compteur
	__HAL_TIM_SET_COUNTER(&htim2,32768); // remise a la valeure mediane du compteur

	//Calcul des differentes valeures d angle absolu, relatif et vitesse angulaire
	float delta = ((counter-32768.0F)*2.0F*M_PI)/(74.8F*8.0F); // Division par 74.8 (rapport d engrenage du moteur 75:1) et 8 (nombres de poles du moteur)
	Encoder.angle_abs += delta; //angle absolu
	Encoder.angle_rel = fmod(Encoder.angle_abs,2*M_PI); //angle relatif
	if (Encoder.angle_rel<0){
		Encoder.angle_rel = Encoder.angle_rel+2*M_PI; // changement de signe pour avoir un angle relatif entre 0 et 2*pi
	}

	Encoder.d_angle=delta/deltaT;// calcul vitesse angulaire

	return Encoder;

}
