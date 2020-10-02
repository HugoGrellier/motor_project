#include "driveSyst.h"
#include "encoder.h"
#include "tim.h"
#include "main.h"
#include "pid.h"
#include "gpio.h"
#include "stm32f4xx_hal.h"
#include <math.h>

Encoder_Feedback_t Feedback;

void DriveSyst_Init (driveSyst_t *dsHandle){
	dsHandle->sp_source=e_BUTTON;
	dsHandle->sp_physics=e_POSITION;
}


void DriveSyst_Loop(driveSyst_t *dsHandle){
	int in_movement=0;

	switch(dsHandle->sp_physics) {
		case e_SPEED:
						switch(dsHandle->sp_source){
								case e_CONSTANT: 	pidHandleSpeed.input.order = 6;
													pidHandleSpeed.input.feedback = Encoder_Read().d_angle;
													PID_Execute(&pidHandleSpeed);
													Motor_Pwm_Update(pidHandleSpeed.process.output);

												break;
								case e_BUTTON:;
												break;
								case e_ACCELEROMETER:;
												break;
								case e_UART:
												break;
								default: printf("error source");
							}
						break;



		case e_POSITION:
						switch(dsHandle->sp_source){
								case e_CONSTANT: 	pidHandlePosition.input.order = 18;
													pidHandlePosition.input.feedback = Encoder_Read().angle_abs;
													PID_Execute(&pidHandlePosition);
													Motor_Pwm_Update(pidHandlePosition.process.output);
												break;
									case e_BUTTON:
													if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)==0 && in_movement==0){
														pidHandlePosition.input.order = pidHandlePosition.input.feedback+2*M_PI;
														in_movement=1;
													}
													pidHandlePosition.input.feedback = Encoder_Read().angle_abs;
													PID_Execute(&pidHandlePosition);
													Motor_Pwm_Update(pidHandlePosition.process.output);
													if(pidHandlePosition.process.error<pidHandlePosition.init.error_stop){
															in_movement=0;
													}
												break;
								case e_ACCELEROMETER:;
												break;
								case e_UART:
												break;
								default: printf("error source");
								}
						break;


		case e_TORQUE:
						switch(dsHandle->sp_source){
								case e_CONSTANT: pidHandleSpeed.input.order = 6;
												break;
								case e_BUTTON:;
												break;
								case e_ACCELEROMETER:;
												break;
								case e_UART:
												break;
								default: printf("error source");
						}
						break;
		default: printf("error physics");
	}


}
