#include "lidar.h"

int lidar_timeSinceData[16];
uint8_t lidar_distances[16];


// Le lidar est sur l'UART 4

void lidar_initialize() {
	for (int i=0; i<16; i++) {
		lidar_distances[i] = 255;
		lidar_timeSinceData[i] = LIDAR_TIMEOUT;
	}
}

void lidar_updateDistance(int index, uint8_t dist) {
	/*lidar_distances[index] = dist;
	lidar_timeSinceData[index] = 0;*/
	//printf("%d -> %dcm\r\n", index, dist);

}

int lidar_getDistance(Direction dir) {
	int minDist = 1000;
	readFrame();

	/* for(int j=0; j<=maxMesure; j++){
	 * if (dir == FORWARD) {
			for (int i=4; i<=8; i++) {
				if (lidar_timeSinceData[i] <= LIDAR_TIMEOUT && distanceList[j] < minDist && captorList[j] ) {
					minDist = distanceList[j];
				}
			}
		} else {
			int i=0;
			if (lidar_timeSinceData[i] <= LIDAR_TIMEOUT && distanceList[i] < minDist) {
				minDist = distanceList[j];
			}
			for (i=12; i<=15; i++) {
				if (lidar_timeSinceData[i] <= LIDAR_TIMEOUT && distanceList[i] < minDist) {
					minDist = distanceList[j];
				}
			}
		}
		}*/
	/* for(int j=0; j<=maxMesure; j++){
		 * if (dir == FORWARD) {
				for (int i=4; i<=8; i++) {
					if ( distanceList[j] < minDist && captorList[j] == i) {
						minDist = distanceList[j];
					}
				}
			} else {
				int i=0;
				if ( distanceList[j] < minDist && captorList[j] == i) {
					minDist = distanceList[j];
				}
				for (i=12; i<=15; i++) {
					if ( distanceList[j] < minDist && captorList[j] == i) {
						minDist = distanceList[j];
					}
				}
			}
			}*/


	for(int i = 0; i<maxMesure;i++){
		if((int)distanceList[i] < minDist){
			minDist = (int)distanceList[i];
		}
	}

	return minDist;
}

bool lidar_pathIsClear(Direction dir) {
	/*if (dir == FORWARD) {
		return lidar_frontIsClear();
	} else {
		return lidar_backIsClear();
	}*/
}

bool lidar_frontIsClear() {
	for (int i=4; i<=8; i++) {
		if (lidar_distances[i] < LIDAR_THRESHOLD && lidar_timeSinceData[i] <= LIDAR_TIMEOUT) {
			return false;
		}
	}
	return true;
	/*
	 * for(int j=0;j<maxMesure;j++){
	 * 	for(int i=4; i<8;i++){
	 * 		if(distanceList[j] < LIDAR_THRESHOLD && captorList[j] == i)
	 * 			return false;
	 * 	}
	 * }
	 *
	 * return true;
	 */
}

bool lidar_backIsClear() {
	for (int i=12; i<=15; i++) {
		if (lidar_distances[i] < LIDAR_THRESHOLD && lidar_timeSinceData[i] <= LIDAR_TIMEOUT) {
			return false;
		}
	}
	if (lidar_distances[0] < LIDAR_THRESHOLD && lidar_timeSinceData[0] <= LIDAR_TIMEOUT) {
		return false;
	}
	return true;
	/*
	 * for(int j=0;j<maxMesure;j++){
	 * 	for(int i=12; i<=15; i++){
	 * 		if(distanceList[j] < LIDAR_THRESHOLD && captorList[j] == i)
	 * 			return false;
	 * 	}
	 * 	if(distanceList[j] < LIDAR_THRESHOLD && captorList[j] == 0){
	 * 		return false;
	 * }
	 *
	 * return true;
	 */
}

void lidar_incrementTime(int ms) {
	for (int i=0; i<16; i++) {
		if (lidar_timeSinceData[i] <= LIDAR_TIMEOUT) {
			lidar_timeSinceData[i] += ms;
		}
	}
}
