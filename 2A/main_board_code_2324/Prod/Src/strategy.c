
#include "strategy.h"

Strategy* strategy_initialize(int num) {
	if(num == 0 || num == 1)
	{
		Strategy* strategy = (Strategy*) malloc(sizeof(Strategy));
		    strategy->length = 6;
		    strategy->path = (Bezier**) malloc(sizeof(Bezier*) * strategy->length);

		    strategy->directions = (Direction*) malloc(sizeof(Direction) * strategy->length);
		    strategy->speeds = (float*) calloc(strategy->length+1, sizeof(float));

		    strategy->onSiteActions = (uint8_t**) malloc(sizeof(uint8_t*) * (strategy->length+1));
		    strategy->onSiteActionsLengths = (int*) calloc((strategy->length+1), sizeof(int));
		    strategy->onMoveActions = (uint8_t**) malloc(sizeof(uint8_t*) * (strategy->length+1));
		    strategy->onMoveActionsLengths = (int*) calloc((strategy->length+1), sizeof(int));

		    strategy->path[0] = bezier_new(240, 1000, 482.706, 1000, 889.093, 1000, 1101.350, 1000, 30);
		    strategy->path[1] = bezier_new(1101.350, 1000, 1313.608, 1000, 2073.478, 1000, 2073.478, 1000, 30);
		    strategy->path[2] = bezier_new(2073.478, 1000, 2073.478, 1000, 2619.905, 1000, 2760.723, 1000, 30);
		    strategy->path[3] = bezier_new(2760.723, 1000, 2619.720, 1000, 2157.587, 1000, 2074.928, 1000, 30);
		    strategy->path[4] = bezier_new(2074.928, 1000, 1992.270, 1000, 1192.385, 1000, 1100.334, 1000, 30);
		    strategy->path[5] = bezier_new(1100.334, 1000, 1008.283, 1000, 482.664, 1000, 240, 1000, 30);

		    strategy->directions[0] = FORWARD;
		    strategy->directions[1] = FORWARD;
		    strategy->directions[2] = FORWARD;
		    strategy->directions[3] = BACKWARD;
		    strategy->directions[4] = BACKWARD;
		    strategy->directions[5] = BACKWARD;

		    strategy->speeds[0] = 1000;
		    strategy->speeds[1] = 1000;
		    strategy->speeds[2] = 1000;
		    strategy->speeds[4] = 1000;
		    strategy->speeds[5] = 1000;



		    return strategy;

	}
	else if(num == 2 || num == 3)
	{
		Strategy* strategy = (Strategy*) malloc(sizeof(Strategy));
				    strategy->length = 6;
				    strategy->path = (Bezier**) malloc(sizeof(Bezier*) * strategy->length);

				    strategy->directions = (Direction*) malloc(sizeof(Direction) * strategy->length);
				    strategy->speeds = (float*) calloc(strategy->length+1, sizeof(float));

				    strategy->onSiteActions = (uint8_t**) malloc(sizeof(uint8_t*) * (strategy->length+1));
				    strategy->onSiteActionsLengths = (int*) calloc((strategy->length+1), sizeof(int));
				    strategy->onMoveActions = (uint8_t**) malloc(sizeof(uint8_t*) * (strategy->length+1));
				    strategy->onMoveActionsLengths = (int*) calloc((strategy->length+1), sizeof(int));

				    strategy->path[0] = bezier_new(240, 1000, 482.706, 1000, 889.093, 1000, 1101.350, 1000, 30);
				    strategy->path[1] = bezier_new(1101.350, 1000, 1313.608, 1000, 2073.478, 1000, 2073.478, 1000, 30);
				    strategy->path[2] = bezier_new(2073.478, 1000, 2073.478, 1000, 2619.905, 1000, 2760.723, 1000, 30);
				    strategy->path[3] = bezier_new(2760.723, 1000, 2619.720, 1000, 2157.587, 1000, 2074.928, 1000, 30);
				    strategy->path[4] = bezier_new(2074.928, 1000, 1992.270, 1000, 1192.385, 1000, 1100.334, 1000, 30);
				    strategy->path[5] = bezier_new(1100.334, 1000, 1008.283, 1000, 482.664, 1000, 240, 1000, 30);

				    strategy->directions[0] = FORWARD;
				    strategy->directions[1] = FORWARD;
				    strategy->directions[2] = FORWARD;
				    strategy->directions[3] = BACKWARD;
				    strategy->directions[4] = BACKWARD;
				    strategy->directions[5] = BACKWARD;

				    strategy->speeds[0] = 1000;
				    strategy->speeds[1] = 1000;
				    strategy->speeds[2] = 1000;
				    strategy->speeds[4] = 1000;
				    strategy->speeds[5] = 1000;



				    return strategy;
	}
	else if(num == 5 || num == 4)
	{	Strategy* strategy = (Strategy*) malloc(sizeof(Strategy));
    strategy->length = 2;
    strategy->path = (Bezier**) malloc(sizeof(Bezier*) * strategy->length);

    strategy->directions = (Direction*) malloc(sizeof(Direction) * strategy->length);
    strategy->speeds = (float*) calloc(strategy->length+1, sizeof(float));

    strategy->onSiteActions = (uint8_t**) malloc(sizeof(uint8_t*) * (strategy->length+1));
    strategy->onSiteActionsLengths = (int*) calloc((strategy->length+1), sizeof(int));
    strategy->onMoveActions = (uint8_t**) malloc(sizeof(uint8_t*) * (strategy->length+1));
    strategy->onMoveActionsLengths = (int*) calloc((strategy->length+1), sizeof(int));

    //strategy->path[0] = bezier_new(1095.392, 1841.935, 1098.577, 1678.371, 1099.549, 1671.753, 1105.089, 1399.884, 30);
    //strategy->path[1] = bezier_new(1105.089, 1399.884, 1110.630, 1128.015, 1407.093, 1071.997, 1407.093, 1071.997, 30);

    strategy->directions[0] = FORWARD;
    strategy->directions[1] = BACKWARD;

    strategy->speeds[0] = 496;
    strategy->speeds[1] = 496;



    return strategy;
	}
}

