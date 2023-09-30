/**
 * @file lidar.h
 */
#ifndef _AVOIDANCE_
#define _AVOIDANCE_

#include "propulsion.h"
#include "bezier.h"
#include "lidar.h"

/** État de la procédure d'évitement */
typedef enum {
	/** État nominal. */
	PATH_CLEAR=0,

	/** Ralentissement. */
	PATH_CROWDED=1,

	/** Réaction statique face à un obstacle. */
	PATH_OBSTRUCTED=2,

	/** Marche arrière face à un obstacle. */
	BACKTRACKING=3,

	/** Suivi d'une trajectoire d'évitement. */
	AVOIDANCE=4,

	/** Abandon du suivi de la trajectoire d'évitement en marche arrière. */
	AVOIDANCE_ABORT=5,
} AvoidanceState;


extern AvoidanceState avoidanceState;
extern Bezier* avoidanceCurve;
extern float backtrackingAim;
extern float avoidanceSpeedFactor;


void avoidance_initialize();

void avoidance_update(float t, Direction dir);

#endif
