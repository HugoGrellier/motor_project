#include "driveSyst.h"
#include "encoder.h"
#include "tim.h"
#include "main.h"
#include "pid.h"
#include "gpio.h"
#include "mpu6050.h"
#include "stm32f4xx_hal.h"
#include <math.h>
int Button_pushed=0;
Encoder_Feedback_t Feedback;
Xyz Accel;

void DriveSyst_Init (driveSyst_t *dsHandle){
	dsHandle->sp_source=e_BUTTON;
	dsHandle->sp_physics=e_POSITION;
}



void DriveSyst_Loop(driveSyst_t *dsHandle){

	switch(dsHandle->sp_physics) {
		case e_SPEED:
						switch(dsHandle->sp_source){
								case e_CONSTANT: 	pidHandleSpeed.input.order = 6;
													pidHandleSpeed.input.feedback = Encoder_Read().d_angle;
													PID_Execute(&pidHandleSpeed);
													Motor_Pwm_Update(pidHandleSpeed.process.output);

												break;
								case e_BUTTON:
									;
												break;
								case e_ACCELEROMETER:Accel=MPU6050_Read_Accel();
													pidHandleSpeed.input.order = 12+3*(-atan2(Accel.x,Accel.z));
													pidHandleSpeed.input.feedback = Encoder_Read().d_angle;
													PID_Execute(&pidHandleSpeed);
													Motor_Pwm_Update(pidHandleSpeed.process.output);
												break;
								case e_UART:
												break;
								default: printf("error source");
							}
						break;



		case e_POSITION:
						switch(dsHandle->sp_source){
								case e_CONSTANT: 	pidHandlePosition.input.order = 6*M_PI;
													pidHandlePosition.input.feedback = Encoder_Read().angle_abs;
													PID_Execute(&pidHandlePosition);
													Motor_Pwm_Update(pidHandlePosition.process.output);
												break;
								case e_BUTTON:
													if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)==1 && Button_pushed!=0){
														Button_pushed=0;
													}
													if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)==0 && Button_pushed==0){
														pidHandlePosition.input.order = pidHandlePosition.input.order+2*M_PI;
														printf("tour: %f \n\r",pidHandlePosition.input.order);
														Button_pushed=1;
													}

													pidHandlePosition.input.feedback = Encoder_Read().angle_abs;


												break;
								case e_ACCELEROMETER:
													Accel=MPU6050_Read_Accel();
													pidHandlePosition.input.order = -atan2(Accel.x,Accel.z)-M_PI/2;
													pidHandlePosition.input.feedback = Encoder_Read().angle_abs;
													PID_Execute(&pidHandlePosition);
													Motor_Pwm_Update(pidHandlePosition.process.output);
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
