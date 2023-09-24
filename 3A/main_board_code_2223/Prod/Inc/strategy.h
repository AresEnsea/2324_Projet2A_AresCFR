#ifndef _STRATEGY_
#define _STRATEGY_

#include "propulsion.h"
#include "bezier.h"

typedef struct {
	int length;
	Bezier** path;
	Direction* directions;
	float* speeds;
	uint8_t** onSiteActions;
	uint8_t** onMoveActions;
	int* onSiteActionsLengths;
	int* onMoveActionsLengths;
} Strategy;

Strategy* strategy_initialize();

#endif
