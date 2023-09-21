#include "symetry.h"

void switchTeam(Strategy* strategy) {
	robot.team = (robot.team == YELLOW)?PURPLE:YELLOW;

	for (int i=0; i<strategy->length; i++) {
		Bezier* b = strategy->path[i];
		bezier_set(
			b,
		    3000 - b->p1.x, b->p1.y,
			3000 - b->p2.x, b->p2.y,
			3000 - b->p3.x, b->p3.y,
			3000 - b->p4.x, b->p4.y,
			30
		);

		/*for (int j=0; j < strategy->onSiteActionsLengths[i]; j++) {
			if (strategy->onSiteActions[i][j] == 0xA1) {
				printf("%x\r\n", strategy->onSiteActions[i][j]);
				strategy->onSiteActions[i][j] = 0xA2;
				printf("%x\r\n", strategy->onSiteActions[i][j]);
			}

			if (strategy->onSiteActions[i][j] == 0xA2)
				strategy->onSiteActions[i][j] = 0xA1;

			if (strategy->onSiteActions[i][j] == 0xCA)
				strategy->onSiteActions[i][j] = 0xCB;

			if (strategy->onSiteActions[i][j] == 0xCB)
				strategy->onSiteActions[i][j] = 0xCA;
		}

		for (int j=0; j < strategy->onMoveActionsLengths[i]; j++) {
			if (strategy->onMoveActions[i][j] == 0xA1)
				strategy->onMoveActions[i][j] = 0xA2;

			if (strategy->onMoveActions[i][j] == 0xA2)
				strategy->onMoveActions[i][j] = 0xA1;

			if (strategy->onMoveActions[i][j] == 0xCA)
				strategy->onMoveActions[i][j] = 0xCB;

			if (strategy->onMoveActions[i][j] == 0xCB)
				strategy->onMoveActions[i][j] = 0xCA;
		}*/
	}
}
