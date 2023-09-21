#include "strategy.h"

Strategy* strategy_initialize() {
    Strategy* strategy = (Strategy*) malloc(sizeof(Strategy));
    strategy->length = 4;
    strategy->path = (Bezier**) malloc(sizeof(Bezier*) * strategy->length);

    strategy->directions = (Direction*) malloc(sizeof(Direction) * strategy->length);
    strategy->speeds = (float*) calloc(strategy->length+1, sizeof(float));

    strategy->onSiteActions = (uint8_t**) malloc(sizeof(uint8_t*) * (strategy->length+1));
    strategy->onSiteActionsLengths = (int*) calloc((strategy->length+1), sizeof(int));
    strategy->onMoveActions = (uint8_t**) malloc(sizeof(uint8_t*) * (strategy->length+1));
    strategy->onMoveActionsLengths = (int*) calloc((strategy->length+1), sizeof(int));

    strategy->path[0] = bezier_new(22.543, 929.527, 963.822, 910.623, 425.315, 1621.923, 1522.506, 1418.794, 30);
    strategy->path[1] = bezier_new(1522.506, 1418.794, 2619.698, 1215.664, 2440.330, 864.588, 2283.916, 734.412, 30);
    strategy->path[2] = bezier_new(2283.916, 734.412, 2097.725, 902.032, 781.762, 934.436, 612.901, 934.752, 30);
    strategy->path[3] = bezier_new(612.901, 934.752, 444.039, 935.068, 22.518, 926.546, 22.518, 926.546, 30);

    strategy->directions[0] = FORWARD;
    strategy->directions[1] = FORWARD;
    strategy->directions[2] = BACKWARD;
    strategy->directions[3] = BACKWARD;

    strategy->speeds[0] = 1000;
    strategy->speeds[1] = 1000;
    strategy->speeds[3] = 1000;



    return strategy;
}
