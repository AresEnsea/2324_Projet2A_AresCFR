
#include "strategy.h"

float xf, yf; //Points finaux de la trajectoire de Bezier

Strategy* strategy_initialize(int num) {
	if(num == 0 || num == 1)
	{
		Strategy* strategy = (Strategy*) malloc(sizeof(Strategy));
		    strategy->length = 15;
		    strategy->path = (Bezier**) malloc(sizeof(Bezier*) * strategy->length);

		    strategy->directions = (Direction*) malloc(sizeof(Direction) * strategy->length);
		    strategy->speeds = (float*) calloc(strategy->length+1, sizeof(float));

		    strategy->onSiteActions = (uint8_t**) malloc(sizeof(uint8_t*) * (strategy->length+1));
		    strategy->onSiteActionsLengths = (int*) calloc((strategy->length+1), sizeof(int));
		    strategy->onMoveActions = (uint8_t**) malloc(sizeof(uint8_t*) * (strategy->length+1));
		    strategy->onMoveActionsLengths = (int*) calloc((strategy->length+1), sizeof(int));

		    strategy->path[0] = bezier_new(224.435, 226.203, 474.001, 225.322, 490.976, 372.928, 753.802, 391.677, 30);
		    strategy->path[1] = bezier_new(753.802, 391.677, 1016.627, 410.425, 1074.374, 435.935, 1192.194, 453.608, 30);
		    strategy->path[2] = bezier_new(1192.194, 453.608, 1310.015, 471.281, 1595.729, 441.826, 1751.841, 515.464, 30);
		    strategy->path[3] = bezier_new(1751.841, 515.464, 1907.953, 589.102, 1937.408, 612.666, 2016.937, 745.214, 30);
		    strategy->path[4] = bezier_new(2016.937, 745.214, 2096.465, 877.761, 2093.520, 1027.982, 2037.555, 1192.931, 30);
		    strategy->path[5] = bezier_new(2037.555, 1192.931, 1981.591, 1357.879, 1952.135, 1407.953, 1796.024, 1475.700, 30);
		    strategy->path[6] = bezier_new(1796.024, 1475.700, 1639.912, 1543.446, 1616.348, 1540.501, 1457.290, 1522.828, 30);
		    strategy->path[7] = bezier_new(1457.290, 1522.828, 1298.233, 1505.155, 1256.996, 1540.501, 1097.938, 1422.680, 30);
		    strategy->path[8] = bezier_new(1097.938, 1422.680, 938.881, 1304.860, 932.990, 1328.424, 885.862, 1145.803, 30);
		    strategy->path[9] = bezier_new(885.862, 1145.803, 838.733, 963.181, 862.297, 995.582, 894.698, 795.287, 30);
		    strategy->path[10] = bezier_new(894.698, 795.287, 927.099, 594.993, 1086.156, 541.973, 1221.649, 521.355, 30);
		    strategy->path[11] = bezier_new(1221.649, 521.355, 1357.143, 500.736, 1330.633, 497.791, 1495.582, 500.736, 30);
		    strategy->path[12] = bezier_new(1495.582, 500.736, 1660.530, 503.682, 1664.948, 540.501, 1728.277, 600.884, 30);
		    strategy->path[13] = bezier_new(1728.277, 600.884, 1791.605, 782.032, 1539.764, 718.704, 1551.546, 857.143, 30);
		    strategy->path[14] = bezier_new(1551.546, 857.143, 1563.328, 995.582, 1525.037, 972.018, 1492.636, 1048.601, 30);

		    strategy->directions[0] = FORWARD;
		    strategy->directions[1] = FORWARD;
		    strategy->directions[2] = FORWARD;
		    strategy->directions[3] = FORWARD;
		    strategy->directions[4] = FORWARD;
		    strategy->directions[5] = FORWARD;
		    strategy->directions[6] = FORWARD;
		    strategy->directions[7] = FORWARD;
		    strategy->directions[8] = FORWARD;
		    strategy->directions[9] = FORWARD;
		    strategy->directions[10] = FORWARD;
		    strategy->directions[11] = FORWARD;
		    strategy->directions[12] = FORWARD;
		    strategy->directions[13] = FORWARD;
		    strategy->directions[14] = BACKWARD;

		    strategy->speeds[0] = 511;
		    strategy->speeds[1] = 501;
		    strategy->speeds[2] = 494;
		    strategy->speeds[3] = 494;
		    strategy->speeds[4] = 508;
		    strategy->speeds[5] = 455;
		    strategy->speeds[6] = 515;
		    strategy->speeds[7] = 596;
		    strategy->speeds[8] = 497;
		    strategy->speeds[9] = 504;
		    strategy->speeds[10] = 473;
		    strategy->speeds[11] = 529;
		    strategy->speeds[12] = 476;
		    strategy->speeds[14] = 452;



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

		    strategy->path[0] = bezier_new(243.093, 999.898, 615.141, 1000.610, 410.811, 999.848, 766.301, 1000.364, 30);
		    strategy->path[1] = bezier_new(766.301, 1000.364, 1121.792, 1000.880, 1107.183, 999.956, 1215.051, 1000.429, 30);
		    strategy->path[2] = bezier_new(1215.051, 1000.429, 1322.920, 1001.902, 1359.070, 1000.786, 1500.730, 999.927, 30);
		    strategy->path[3] = bezier_new(1500.730, 999.927, 1500.730, 999.927, 1752.155, 1000.387, 1852.106, 1000.387, 30);
		    strategy->path[4] = bezier_new(1852.106, 1000.387, 1952.057, 1000.387, 2484.680, 1000.565, 2546.088, 1000.471, 30);
		    strategy->path[5] = bezier_new(2546.088, 1000.471, 2607.496, 1000.378, 2782.705, 999.778, 2782.705, 999.778, 30);

		    strategy->directions[0] = FORWARD;
		    strategy->directions[1] = FORWARD;
		    strategy->directions[2] = FORWARD;
		    strategy->directions[3] = BACKWARD;
		    strategy->directions[4] = BACKWARD;
		    strategy->directions[5] = BACKWARD;

		    strategy->speeds[0] = 1000;
		    strategy->speeds[1] = 1000;
		    strategy->speeds[2] = 487;
		    strategy->speeds[4] = 1000;
		    strategy->speeds[5] = 473;



		    return strategy;
	}
	else if(num == 5 || num == 4)
	{
		Strategy* strategy = (Strategy*) malloc(sizeof(Strategy));
		    strategy->length = 9;
		    strategy->path = (Bezier**) malloc(sizeof(Bezier*) * strategy->length);

		    strategy->directions = (Direction*) malloc(sizeof(Direction) * strategy->length);
		    strategy->speeds = (float*) calloc(strategy->length+1, sizeof(float));

		    strategy->onSiteActions = (uint8_t**) malloc(sizeof(uint8_t*) * (strategy->length+1));
		    strategy->onSiteActionsLengths = (int*) calloc((strategy->length+1), sizeof(int));
		    strategy->onMoveActions = (uint8_t**) malloc(sizeof(uint8_t*) * (strategy->length+1));
		    strategy->onMoveActionsLengths = (int*) calloc((strategy->length+1), sizeof(int));

		    strategy->path[0] = bezier_new(287.633, 1703.093, 989.708, 1720.074, 824.506, 1464.675, 908.073, 1121.219, 30);
		    strategy->path[1] = bezier_new(908.073, 1121.219, 991.640, 777.763, 988.743, 825.609, 1087.315, 678.337, 30);
		    strategy->path[2] = bezier_new(1087.315, 678.337, 1185.886, 531.066, 1342.346, 464.826, 1508.465, 476.017, 30);
		    strategy->path[3] = bezier_new(1508.465, 476.017, 1674.585, 487.208, 1773.108, 450.058, 1982.294, 770.789, 30);
		    strategy->path[4] = bezier_new(1982.294, 770.789, 2191.479, 1091.519, 2481.320, 1428.523, 2566.459, 1523.094, 30);
		    strategy->path[5] = bezier_new(2566.459, 1523.094, 2651.597, 1617.666, 2600.551, 1550.088, 2735.351, 1734.857, 30);
		    strategy->path[6] = bezier_new(2735.351, 1734.857, 2296.090, 1738.343, 1774.692, 1741.337, 1774.692, 1741.337, 30);
		    strategy->path[7] = bezier_new(1774.692, 1741.337, 1774.692, 1741.337, 1126.641, 1736.689, 1126.641, 1736.689, 30);
		    strategy->path[8] = bezier_new(1126.641, 1736.689, 1126.641, 1736.689, 408.576, 1736.177, 287.981, 1738.175, 30);

		    strategy->directions[0] = FORWARD;
		    strategy->directions[1] = FORWARD;
		    strategy->directions[2] = FORWARD;
		    strategy->directions[3] = FORWARD;
		    strategy->directions[4] = FORWARD;
		    strategy->directions[5] = FORWARD;
		    strategy->directions[6] = BACKWARD;
		    strategy->directions[7] = BACKWARD;
		    strategy->directions[8] = BACKWARD;

		    strategy->speeds[0] = 1000;
		    strategy->speeds[1] = 1000;
		    strategy->speeds[2] = 487;
		    strategy->speeds[3] = 494;
		    strategy->speeds[4] = 1000;
		    strategy->speeds[5] = 473;
		    strategy->speeds[7] = 1000;
		    strategy->speeds[8] = 466;



		    return strategy;
	}
}

