#ifndef DRIVESYST_H
#define DRIVESYST_H

typedef enum
{
	e_CONSTANT, // setpoint from a constant
	e_BUTTON, // setpoint updated with a button
 	e_ACCELEROMETER, // setpoint updated from accelerometer atan2 value
	e_UART // setpoint updaded from UART
} setpoint_source_t;

typedef enum
{
	e_SPEED, // rad/s
	e_POSITION, // rad
	e_TORQUE // N.m = kg⋅m²/s²
} setpoint_physics_t;

typedef struct
{
	setpoint_source_t sp_source;
	setpoint_physics_t sp_physics;
} driveSyst_t;



void DriveSyst_Init(driveSyst_t *dsHandle);
void DriveSyst_Loop(driveSyst_t *dsHandle);


#endif
