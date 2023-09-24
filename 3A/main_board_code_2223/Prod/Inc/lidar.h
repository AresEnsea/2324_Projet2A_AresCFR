/**
 * @file lidar.h
 */
#ifndef _LIDAR_
#define _LIDAR_

#include "config.h"
#include "propulsion.h"
#include "serial.h"
#include "lidarReading.h"

extern uint8_t lidar_distances[16];
extern int lidar_timeSinceData[16];

void lidar_initialize();

void lidar_updateDistance(int index, uint8_t dist);
int lidar_getDistance(Direction dir);

bool lidar_pathIsClear(Direction dir);
bool lidar_frontIsClear();
bool lidar_backIsClear();

void lidar_incrementTime(int ms);

#endif
