#include "propulsion.h"


Robot robot;
float angleErrorIntegral = 0.0;
float angleErrorIntegral2 = 0.0;
float angleError0 = 0.0;
float correction = 0.0;
float error[3] = {0.0,0.0,0.0};
float error2[3] = {0.0,0.0,0.0};
float t0 = 0.0;
float slowDownFactor = 0;
float speed = 0;

void propulsion_initialize() {
    robot.leftMotor = (Stepper*) malloc(sizeof(Stepper));
    robot.rightMotor = (Stepper*) malloc(sizeof(Stepper));

    drv8825_initialize(
        robot.leftMotor,
        L_MOTOR_EN_Pin, L_MOTOR_EN_GPIO_Port,
        L_MOTOR_DIR_Pin, L_MOTOR_DIR_GPIO_Port,
        &L_MOTOR_TIMER, TIM_CHANNEL_1
    );
    drv8825_initialize(
        robot.rightMotor,
        R_MOTOR_EN_Pin, R_MOTOR_EN_GPIO_Port,
        R_MOTOR_DIR_Pin, R_MOTOR_DIR_GPIO_Port,
        &R_MOTOR_TIMER, TIM_CHANNEL_4
    );
}


void propulsion_enableMotors() {
    drv8825_enable(robot.leftMotor);
    drv8825_enable(robot.rightMotor);
}


void propulsion_disableMotors() {
    drv8825_disable(robot.leftMotor);
    drv8825_disable(robot.rightMotor);
}


void propulsion_setSpeeds(float left, float right, float k) {

	float max_speed = MAX_MOTOR_SPEED*(1-atan(1000*fabs(k))*2/M_PI);
	if ((max_speed < 400) && (MAX_MOTOR_SPEED >= 400))
		max_speed = 400;
	else if ((max_speed < 400) && (MAX_MOTOR_SPEED < 400))
		max_speed = MAX_MOTOR_SPEED;

    float greatestAbsoluteSpeed = fabs(fabs(left)>fabs(right)?left:right);

    if (greatestAbsoluteSpeed > max_speed) {
        left = left/greatestAbsoluteSpeed*max_speed;
        right = right/greatestAbsoluteSpeed*max_speed;
    }

    robot.leftSpeed = left;
    drv8825_setDirection(robot.leftMotor, (left < 0)?NEGATIVE:POSITIVE);
    drv8825_setRotationSpeed(robot.leftMotor, 60 * fabsf(left) / (2*M_PI*WHEEL_RADIUS));

    robot.rightSpeed = right;
    drv8825_setDirection(robot.rightMotor, (right < 0)?NEGATIVE:POSITIVE);
    drv8825_setRotationSpeed(robot.rightMotor, 60 * fabsf(right) / (2*M_PI*WHEEL_RADIUS));
}

/*void propulsion_setSpeeds2(float left, float right, Bezier* b, float t) {
	float k = bezier_curvature(b, t);
	float turnFactor =(1-fabs(100*k) > 0.5?1-fabs(100*k):0.5);
    float greatestAbsoluteSpeed = fabs(fabs(left)>fabs(right)?left:right);
    if (greatestAbsoluteSpeed > MAX_MOTOR_SPEED*turnFactor) {
        left = turnFactor*left/greatestAbsoluteSpeed*MAX_MOTOR_SPEED;
        right = turnFactor*right/greatestAbsoluteSpeed*MAX_MOTOR_SPEED;
    }

    robot.leftSpeed = left;
    drv8825_setDirection(robot.leftMotor, (left < 0)?NEGATIVE:POSITIVE);
    drv8825_setRotationSpeed(robot.leftMotor, 60 * fabsf(left) / (2*M_PI*WHEEL_RADIUS));

    robot.rightSpeed = right;
    drv8825_setDirection(robot.rightMotor, (right < 0)?NEGATIVE:POSITIVE);
    drv8825_setRotationSpeed(robot.rightMotor, 60 * fabsf(right) / (2*M_PI*WHEEL_RADIUS));
}*/


void propulsion_updatePosition(float dt) {
    float left = robot.leftSpeed * dt;
    float right = robot.rightSpeed * dt;

    float r =  (left + right)/2;
    float alpha = (right - left)/ENTRAXE_MOTOR;

    robot.position.x += r * cos(robot.angle + alpha/2);
    robot.position.y += r * sin(robot.angle + alpha/2);
    robot.angle += alpha;

    if (robot.angle > M_PI)
        robot.angle = robot.angle - M_TWOPI;
    else if (robot.angle < -M_PI)
        robot.angle = robot.angle + M_TWOPI;
}


float getAngleError(Bezier* b, float t, Vector2 p, Direction dir) {
    Vector2 tangent = bezier_deriv1(b, t);
    Vector2 displacement = vector2_diff(p, robot.position);

    float sign = vector2_cross(displacement, tangent); // (vaut -1, 0 ou 1)
    sign /= (sign != 0)?fabs(sign):1;
    float signedDistance = sign * vector2_norm(displacement);

    DEBUG_PROPULSION("dist: %.1fmm, ", signedDistance);

    float angleError = (vector2_angle(tangent) - atan(signedDistance / 200.0))
            - (robot.angle + (dir==BACKWARD?M_PI:0));
    angleError = standardAngle(angleError); // (entre -pi et pi)

    return angleError;
}


float getRobotSpeed(Bezier* b,float t, float angleError, Direction dir, float initialSpeed, float finalSpeed) {
	slowDownFactor = 1 - fabs(Pcorr(10, error[0]))/M_PI;
    slowDownFactor = 1 - fabs(Icorr(5,error[0], &angleErrorIntegral2,0.5)+Pcorr(4,error[0])+Dcorr(error,0.4*fabs(speed/1000),t-t0)-0.1*(1-slowDownFactor))/M_PI;
    angleErrorIntegral2 = (angleErrorIntegral2 > 1?1: angleErrorIntegral2);
    slowDownFactor = slowDownFactor>0?slowDownFactor:0;

    /*float k = bezier_curvature(b,t);
    float turnFactor =(1-fabs(300*k) > 0.5?1-fabs(300*k):0.5);*/

    //speed = (dir==BACKWARD?-1:1) * slowDownFactor*turnFactor;
    speed = (dir==BACKWARD?-1:1) * slowDownFactor;
    if (initialSpeed < 1 && finalSpeed < 1)
        speed *= 600*(1-t) + 20;
    else
        speed *= initialSpeed*(1-t) + finalSpeed*t + 50;

    // Limite les accelerations brutales
    if (fabs(speed) > robot.measuredSpeed + K_ACCEL)
        speed = (robot.measuredSpeed + K_ACCEL) * fabs(speed) / speed;

    return speed;
}


void calculateMotorSpeeds(float* leftSpeed, float* rightSpeed, Bezier* b, float t, Direction dir, float speed) {
    float k = bezier_curvature(b, t);
    //float speed2 = speed*(1-atan(1000*fabs(k))/M_PI);
    //speed2 = speed>400?speed2:speed;
    float speed2 = speed;
    *leftSpeed = speed2 * (1 + dir*ENTRAXE_MOTOR*k/2);
    *rightSpeed = speed2 * (1 - dir*ENTRAXE_MOTOR*k/2);
}


void addCorrection(float* leftSpeed, float* rightSpeed, float angleError, float * angleErrorIntegral, float * angleError0, float * correction, float speed, float dt) {
	/**angleErrorIntegral += angleError;
	*angleErrorIntegral = (abs(*angleErrorIntegral) > MAX_INTEGRAL_CORR/KI_ANGLE?(MAX_INTEGRAL_CORR*(*angleErrorIntegral)/(KI_ANGLE*abs(*angleErrorIntegral))):(*angleErrorIntegral));

	*correction = -angleError*KP_ANGLE - (*angleErrorIntegral)*KI_ANGLE - KD_ANGLE*pow(fabs(speed/KD_SPEED),2)*(angleError-(*angleError0))/0.0001 + KC_ANGLE*(*correction); // contre réaction

	*angleError0 = angleError;*/
	error[2] = error[1];
	error[1] = error[0];
	error[0] = angleError;
	*correction = corrector(error, *correction, KP_ANGLE, KI_ANGLE, KD_ANGLE*sin(pow(fabs(speed/1000)*M_PI/2,1)), KC_ANGLE, dt,MAX_INTEGRAL_CORR,angleErrorIntegral);
    if (fabs(*correction) > MAX_CORRECTION) {
        *correction *= MAX_CORRECTION / fabs(*correction);
    }

    DEBUG_PROPULSION("ProportionnalCorr: %.1fmm, IntegralCorr: %.1fmm, corr: %.1fmm\r\n",angleError*KP_ANGLE, (*angleErrorIntegral)*KI_ANGLE, *correction);

    *leftSpeed -= *correction;
    *rightSpeed += *correction;
}


// C'est ici que la magie a lieu !
float propulsion_followBezier(Bezier* b, Direction dir, float initialSpeed, float finalSpeed, bool reverse) {
    float t = bezier_project(b, robot.position, 0.0001); // (entre 0 et 1)
    float dt = t-t0;
	float k = bezier_curvature(b,t);
    Vector2 p = bezier_eval(b, t); // Point de la courbe le plus proche du robot

    //DEBUG_PROPULSION("t: %.5f, x: %.1fmm, y: %.1fmm, a: %.1fdeg, ", t, robot.position.x, robot.position.y, robot.angle / M_PI / 2 * 360);

    // Erreur d'orientation
    float angleError = getAngleError(b, t, p, dir);
    DEBUG_PROPULSION("t: %.5f, x: %.1fmm, y: %.1fmm, speed: %.1fmm/s, a: %.1fdeg, a_err: %.1fdeg, k: %.10f ", t, robot.position.x, robot.position.y, robot.measuredSpeed, robot.angle / M_PI / 2 * 360, angleError / M_PI / 2 * 360, k);

    if (reverse) {
    	angleError = 0;
    }

    // Vitesse globale du robot
    float speed = getRobotSpeed(b, t, angleError, dir, initialSpeed, finalSpeed);

    if (reverse) {
    	speed *= -1;
    }

    float leftSpeed, rightSpeed;

    // Boucle ouverte
    calculateMotorSpeeds(&leftSpeed, &rightSpeed, b, t, dir, speed);

    // Boucle fermée
    addCorrection(&leftSpeed, &rightSpeed, angleError, &angleErrorIntegral, &angleError0, &correction, speed,dt);

    // Commande des moteurs
    propulsion_setSpeeds(leftSpeed, rightSpeed, k);
    t0 = t;
    return t;
}


float standardAngle(float angle) {
    return fmod(fmod(angle + M_PI, M_TWOPI) + M_TWOPI, M_TWOPI) - M_PI;
}
