#ifndef INC_CONTROL_H_
#define INC_CONTROL_H_
#include "math.h"
#include <string.h>

float corrector(float * error, float correction, float Kp, float Ki, float Kd, float Kf, float dt, float Ilim, float * integral);
float Pcorr(float Kp, float error);
float Icorr(float Ki, float error, float * integral, float Ilim);
float Dcorr(float * error, float Kd, float dt);

void KalmanInit(float * stateInit, float * stateFin, float dt);
void Kalman(float * stateCurr, float * stateFin, float stateMes, float dt, float * coeff);

#endif
