#include "avoidance.h"

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

	if (avoidanceState == PATH_OBSTRUCTED && distance < LIDAR_THRESHOLD) {
		avoidanceState = BACKTRACKING;
		printf("Backtracking...\r\n");
		backtrackingAim = t - 0.2;
		if (backtrackingAim < 0) {
			backtrackingAim = 0;
		}
	}

	if (avoidanceState == BACKTRACKING && t <= backtrackingAim + 0.01) {
		avoidanceState = PATH_CLEAR;
		printf("Trying again...\r\n");
	}
}
