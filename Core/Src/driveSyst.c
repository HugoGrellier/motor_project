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
	dsHandle->sp_source=e_BUTTON; //change the value to use another source 
	dsHandle->sp_physics=e_POSITION; //change the value to change mode
}



void DriveSyst_Loop(driveSyst_t *dsHandle){
	switch(dsHandle->sp_physics) {
		case e_SPEED:
						switch(dsHandle->sp_source){
								//Run the motor at a constant speed of 2pi rad/s
								case e_CONSTANT: 	pidHandleSpeed.input.order = 2*M_PI;
													pidHandleSpeed.input.feedback = Encoder_Read().d_angle;
													PID_Execute(&pidHandleSpeed);
													Motor_Pwm_Update(pidHandleSpeed.process.output);

												break;
								case e_BUTTON:
									;
												break;
								//the speed of the motor change with the angle
								case e_ACCELEROMETER: //Fonctionnalité inutile mais fonctionnelle
													Accel=MPU6050_Read_Accel();
													pidHandleSpeed.input.order = 12+3*(-atan2(Accel.x,Accel.z)); //ca marche
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
								//do 3 turn
								case e_CONSTANT: 	pidHandlePosition.input.order = 6*M_PI;
													pidHandlePosition.input.feedback = Encoder_Read().angle_abs;
													PID_Execute(&pidHandlePosition);
													Motor_Pwm_Update(pidHandlePosition.process.output);
												break;
								//for each time you press the button the motor will do a turn
								case e_BUTTON:
													if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)==1 && Button_pushed!=0){ 
														//check if the button as been released
														Button_pushed=0;
													}
													if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)==0 && Button_pushed==0){
														//on rising edge add 2pi to the order
														pidHandlePosition.input.order = pidHandlePosition.input.order+2*M_PI;
														Button_pushed=1;
													}
													pidHandlePosition.input.feedback = Encoder_Read().angle_abs;
													PID_Execute(&pidHandlePosition);
													Motor_Pwm_Update(pidHandlePosition.process.output);
												break;
								//Keep at the same value the angle between the ground and the axle
								case e_ACCELEROMETER:
													Accel=MPU6050_Read_Accel();
													pidHandlePosition.input.order = -atan2(Accel.x,Accel.z)-M_PI/2; //correct the angle of the accelerometer
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
								case e_CONSTANT:;
												break;
								case e_BUTTON:;
												break;
								case e_ACCELEROMETER:;
												break;
								case e_UART:;
												break;
								default: printf("error source");
						}
						break;
		default: printf("error physics");
	}


}
