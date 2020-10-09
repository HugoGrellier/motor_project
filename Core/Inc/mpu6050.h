#ifndef MPU6050_H
#define MPU6050_H

#include "i2c.h"

typedef struct Xyz {
 float x;
 float y;
 float z;
} Xyz;

// public functions
void MPU6050_Init (void);
Xyz MPU6050_Read_Accel (void);

#endif
