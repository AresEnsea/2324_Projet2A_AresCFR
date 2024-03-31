#include "avoidance.h"
#include "bezier.h"
#include "math.h"

AvoidanceState avoidanceState;
Bezier* avoidanceCurve;
float backtrackingAim;
float avoidanceSpeedFactor;

void avoidance_initialize() {
	avoidanceState = PATH_CLEAR;
	avoidanceCurve = bezier_newEmpty();
	backtrackingAim = 0;
	avoidanceSpeedFactor = 1;
}


void avoidance_update(float t, Direction dir) {
	int distance = lidar_getDistance(dir);
	if(distance == 0)
		distance = 1000;

	if ((avoidanceState == PATH_CLEAR || avoidanceState == PATH_CROWDED) && distance < LIDAR_THRESHOLD) {
		avoidanceState = PATH_OBSTRUCTED;
		printf("Obstacle detected. Waiting 2s...\r\n");
		propulsion_setSpeeds(0, 0, 0);
		HAL_Delay(2000);
	}

	if ((avoidanceState == PATH_CLEAR || avoidanceState == PATH_OBSTRUCTED) && distance > LIDAR_THRESHOLD && distance < LIDAR_MAX_DISTANCE) {
		avoidanceSpeedFactor = (distance - LIDAR_THRESHOLD) / (LIDAR_MAX_DISTANCE - LIDAR_THRESHOLD);
		avoidanceState = PATH_CROWDED;
	}

	if (avoidanceState == PATH_CROWDED && distance > LIDAR_MAX_DISTANCE) {
		avoidanceState = PATH_CLEAR;
	}

	if (avoidanceState == PATH_OBSTRUCTED && distance >= LIDAR_THRESHOLD) {
		avoidanceState = PATH_CLEAR;
		printf("Path cleared.\r\n");
	}

//	if (avoidanceState == PATH_OBSTRUCTED && distance < LIDAR_THRESHOLD) {
//		avoidanceState = BACKTRACKING;
//		printf("Backtracking...\r\n");
//		backtrackingAim = t - 0.2;
//		if (backtrackingAim < 0) {
//			backtrackingAim = 0;
//		}
//	}:

	if (avoidanceState == PATH_OBSTRUCTED && distance < LIDAR_THRESHOLD) {
		avoidanceState = BACKTRACKING;
		printf("Backtracking...\r\n");
		if (t >= 0.95) {
			avoidanceState = BACKTRACKING2;
		}
	}

	if (avoidanceState == BACKTRACKING2 && t >= 0.95){
		avoidanceState = PATH_CLEAR;
	}

	if (avoidanceState == BACKTRACKING && t <= backtrackingAim + 0.01) {
		avoidanceState = PATH_CLEAR;
		printf("Trying again...\r\n");
	}
}

//1re phase
Bezier * avoidance_path(float xr, float yr){
	float xn, yn, x2, y2, x3, y3;
	float k = 350;
	xn = xr + k*(cos(robot.angle+M_PI/2)-sin(robot.angle+M_PI/2));
	yn = yr + k*(cos(robot.angle+M_PI/2)+sin(robot.angle+M_PI/2));

	x2 = (xf - robot.position.x)/2;
	y2 = (yf - robot.position.y)/2;

	x3 = (xf - robot.position.x)/2;
	y3 = (yf - robot.position.y)/2;

	return bezier_new(xr, yr, x2, y2, x3, y3, xn, yn, 30);

}

//2nd phase
Bezier * avoidance_path_return(float xr, float yr){
	float x2, y2, x3, y3;

	x2 = (xf - robot.position.x)/2;
	y2 = (yf - robot.position.y)/2;

	x3 = (xf - robot.position.x)/2;
	y3 = (yf - robot.position.y)/2;

	return bezier_new(xr, yr, x2, y2, x3, y3, xf, yf, 30);

}





