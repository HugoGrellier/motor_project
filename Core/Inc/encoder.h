#ifndef ENCODER_H
#define ENCODER_H

typedef struct {
	float angle_rel;
	float angle_abs;
	float d_angle;
} Encoder_Feedback_t;

// public functions
void Encoder_Init (void);
Encoder_Feedback_t Encoder_Read (void);

#endif
