#include "control.h"




float derivative[3] = {0.0,0.0,0.0};



float Pcorr(float Kp, float error)
{
	return Kp*error;
}

float Icorr(float Ki, float error, float * integral, float Ilim)
{
	*integral += error;
	return (fabs(*integral) > Ilim/Ki?(Ilim*(*integral)/(Ki*fabs(*integral))):(*integral));
}

float deriv(float a, float b, float dt)
{
	return (b-a)/dt;
}

float Dcorr(float * error, float Kd, float dt)
{
	dt = (dt == 0?0.0001:dt);
	/*derivative[2] = derivative[1];
	derivative[1] = derivative[0];
	derivative[0] = deriv(error[0],error[1],dt);
	return Kd*(derivative[0]+derivative[1]+derivative[2])/3;*/
	return Kd*(deriv(error[0],error[1],dt)+deriv(error[1],error[2],dt)+deriv(error[0],error[2],dt))/3;
	//return Kd*deriv(error[0],error[1],dt);
}





/* PID corrector function:
 * @params :
 * error : array containing the last 3 error measurements
 * Kp : Proportional correction coefficient
 * Ki : Integral correction coefficient
 * Kd : Derivative correction coefficient
 * Kf : feed-forward coefficient
 * dt : time interval
 * Ilim : Integral correction bounds
 * integral : integral value
 */

float corrector(float * error, float correction, float Kp, float Ki, float Kd, float Kf, float dt, float Ilim, float * integral)
{
	return -Pcorr(Kp, error[0]) - Icorr(Ki, error[0], integral, Ilim) - Dcorr(error,Kd,dt) + Kf*(correction);
}

/* State initialisation function for kalman filter :
 * stateInit = {x,v,a}: initial current state, strategy start point
 * stateFin = {x,v,a}: estimated future state (prior state for next iteration)
 * dt : time interval
 */
void KalmanInit(float * stateInit, float * stateFin, float dt)
{
	stateFin[0] = stateInit[0] + stateInit[1]*dt + stateInit[2]*pow(dt,2)/2;
	stateFin[1] = stateInit[1] + stateInit[2]*dt;
	stateFin[2] = stateInit[2];
}

/* alpha-beta-gamma Kalman filter, coeff = {alpha, beta, gamma}
 * stateCurr = {x,v,a}: estimated current state
 * stateFin = {x,v,a}: estimated future state (prior state for next iteration)
 * stateMes = {x,v,a}: measured current state
 * dt : time interval
 */

void Kalman(float * stateCurr, float * stateFin, float stateMes, float dt, float * coeff)
{
	//current state update

	stateCurr[0] = stateFin[0] + coeff[0]*(stateMes-stateFin[0]);
	stateCurr[1] = stateFin[1] + coeff[1]*(stateMes-stateFin[0])/dt;
	stateCurr[2] = stateFin[2] + 2*coeff[2]*(stateMes-stateFin[0])/pow(dt,2);

	//future state prediction
	stateFin[0] = stateCurr[0] + stateCurr[1]*dt + stateCurr[2]*pow(dt,2)/2;
	stateFin[1] = stateCurr[1] + stateCurr[2]*dt;
	stateFin[2] = stateCurr[2];
}

