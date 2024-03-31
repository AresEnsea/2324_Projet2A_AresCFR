#include "odometry.h"


int16_t getRightEncoderCount() {
	int16_t count = (int16_t) R_ENCODER.Instance->CNT;
	R_ENCODER.Instance->CNT = 0;
	return count;
}


int16_t getLeftEncoderCount() {
	int16_t count = (int16_t) L_ENCODER.Instance->CNT;
	L_ENCODER.Instance->CNT = 0;
	return count;
}

float XstateInit[3] = {0.0,0.0,0.0};
float YstateInit[3] = {0.0,0.0,0.0};
float XstateCurr[3] = {0.0,0.0,0.0};
float YstateCurr[3] = {0.0,0.0,0.0};
float XstateFin[3] = {0.0,0.0,0.0};
float YstateFin[3] = {0.0,0.0,0.0};
float XstateMes = 0;
float YstateMes = 0;
float rKalmanCoeff[3] = {0.8, 0.8, 0.005};
float alphaKalmanCoeff[3] = {0.8, 0.8, 0.2};

void odometry_updatePosition() {
	float coeff = M_TWOPI * ODOMETRY_RADIUS / TICKS_PER_REV;
	float leftMov = getLeftEncoderCount() * coeff;
	float rightMov = getRightEncoderCount() * coeff;
	float dt = ODOMETRY_REFRESH;
	float r =  (leftMov + rightMov)/2;
	float alpha = (leftMov - rightMov)/ENTRAXE_ODOMETRY;
	float previousRState = YstateCurr[0];
	float previousXState = XstateCurr[0];

	/*YstateMes += r;
	Kalman(YstateCurr, YstateFin, YstateMes, dt, rKalmanCoeff);
	r = YstateFin[0]- YstateCurr[0];
	//r = YstateCurr[0] - previousRState;


	XstateMes += alpha;
	Kalman(XstateCurr, XstateFin, XstateMes, dt, alphaKalmanCoeff);
	alpha = XstateFin[0] - XstateCurr[0];
	//alpha = XstateCurr[0] - previousXState;*/


	float deltaX = r * cos(robot.angle + alpha/2);
	float deltaY = r * sin(robot.angle + alpha/2);


	robot.position.x += deltaX;
	robot.position.y += deltaY;
	//robot.angle = XstateCurr[0];
	robot.angle += alpha;

	/*XstateMes += deltaX;

	YstateMes += deltaY;

	Kalman(XstateCurr, XstateFin, XstateMes, dt, KalmanCoeff);
	Kalman(YstateCurr, YstateFin, YstateMes, dt, KalmanCoeff);

	robot.position.x = XstateCurr[0];
	robot.position.y = YstateCurr[0];

	deltaX = XstateFin[0]-XstateCurr[0];
	deltaY = YstateFin[0]-YstateCurr[0];

	if((deltaX != 0) && (deltaY != 0))
	{
		robot.angle += atanf(deltaX/deltaY);
	}*/

	float currentSpeed = vector2_norm(vector2_new(deltaX, deltaY)) / dt;
	robot.measuredSpeed = robot.measuredSpeed*0.8 + currentSpeed*0.2;
	//robot.measuredSpeed = vector2_norm(vector2_new(deltaX, deltaY)) / dt;

	if (robot.angle > M_PI)
		robot.angle = robot.angle - M_TWOPI;
	else if (robot.angle < -M_PI)
		robot.angle = robot.angle + M_TWOPI;


	DEBUG_ODOMETRY("x: %.1fmm, y: %.1fmm, speed: %.1fmm, angle: %.1fdeg\r\n", robot.position.x, robot.position.y, robot.measuredSpeed, robot.angle/2/M_PI*360);
	//DEBUG_ODOMETRY("x: %.1fmm, y: %.1fmm, angle: %.1fdeg, vitesseY: %.2fmm, accelX: %.2fmm, accelY: %.2fmm\r\n", robot.position.x, robot.position.y, robot.angle/2/M_PI*360, XstateCurr[1], YstateCurr[1], XstateCurr[2], YstateCurr[2]);
}


void odometry_setPosition(float x, float y) {
	robot.position.x = x;
	robot.position.y = y;
}


void odometry_setAngle(float angle) {
	robot.angle = angle;
}

void odometry_startKalman()
{
	XstateInit[0] = robot.angle;

	KalmanInit(XstateInit,XstateFin,ODOMETRY_REFRESH);
	KalmanInit(YstateInit,YstateFin,ODOMETRY_REFRESH);
}

