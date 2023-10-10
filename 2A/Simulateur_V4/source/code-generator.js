function generateStrategyCode() {
    let out = `
    Strategy* strategy = (Strategy*) malloc(sizeof(Strategy));
    strategy->length = ${path.length};
    strategy->path = (Bezier**) malloc(sizeof(Bezier*) * strategy->length);

    strategy->directions = (Direction*) malloc(sizeof(Direction) * strategy->length);
    strategy->speeds = (float*) calloc(strategy->length+1, sizeof(float));

    strategy->onSiteActions = (uint8_t**) malloc(sizeof(uint8_t*) * (strategy->length+1));
    strategy->onSiteActionsLengths = (int*) calloc((strategy->length+1), sizeof(int));
    strategy->onMoveActions = (uint8_t**) malloc(sizeof(uint8_t*) * (strategy->length+1));
    strategy->onMoveActionsLengths = (int*) calloc((strategy->length+1), sizeof(int));\n\n`

    for (let i=0; i<path.length; i++) {
        out += `    strategy->path[${i}] = bezier_new(`
        for (let point of path[i].points) {
            out += `${point.x.toFixed(3)}, ${point.y.toFixed(3)}, `
        }
        out += `30);\n`
    }

    out += "\n"
    for (let i=0; i<path.length; i++) {
        out += `    strategy->directions[${i}] = `
        if (shouldReverse[i])
            out += `BACKWARD;\n`;
        else
            out += `FORWARD;\n`;
    }

    out += "\n"
    for (let i=0; i<path.length + 1; i++) {
        if ((speeds[i]||0) == 0) continue;
        out += `    strategy->speeds[${i}] = ${(speeds[i]||0)};\n`
    }

    out += "\n"
    for (let i=0; i<path.length + 1; i++) {
        if ((onSiteActions[i]?.length||0) == 0) continue;
        out += `    strategy->onSiteActionsLengths[${i}] = ${onSiteActions[i]?.length||0};\n`
        out += `    strategy->onSiteActions[${i}] = (uint8_t*) malloc(sizeof(uint8_t) * ${onSiteActions[i]?.length||0});\n`
        for (let j=0; j<onSiteActions[i]?.length||0; j++) {
            out += `    strategy->onSiteActions[${i}][${j}] = ${onSiteActions[i][j]};\n`
        }
    }

    out += "\n"
    for (let i=0; i<path.length + 1; i++) {
        if ((onMoveActions[i]?.length||0) == 0) continue;
        out += `    strategy->onMoveActionsLengths[${i}] = ${onMoveActions[i]?.length||0};\n`
        out += `    strategy->onMoveActions[${i}] = (uint8_t*) malloc(sizeof(uint8_t) * ${onMoveActions[i]?.length||0});\n`
        for (let j=0; j<onMoveActions[i]?.length||0; j++) {
            out += `    strategy->onMoveActions[${i}][${j}] = ${onMoveActions[i][j]};\n`
        }
    }

    out += `
    return strategy;`

    return out.trim();
}

`
#include "strategy.h"

Strategy* strategy_initialize() {
	Strategy* strategy = (Strategy*) malloc(sizeof(Strategy));
	strategy->length = 3;
	strategy->path = (Bezier**) malloc(sizeof(Bezier*) * strategy->length);
	strategy->directions = (Direction*) malloc(sizeof(Direction) * strategy->length);
	strategy->speeds = (float*) malloc(sizeof(float) * (strategy->length+1));

	strategy->path[0] = bezier_new(100, 100, 200, 100, 300, 100, 400, 100, 30);
	strategy->path[1] = bezier_new(400, 100, 400, 200, 400, 300, 400, 400, 30);
	strategy->path[2] = bezier_new(400, 400, 400, 500, 100, 500, 100, 400, 30);

	strategy->directions[0] = FORWARD;
	strategy->directions[1] = BACKWARD;
	strategy->directions[2] = BACKWARD;

	strategy->speeds[0] = 0;
	strategy->speeds[1] = 0;
	strategy->speeds[2] = 400;
	strategy->speeds[3] = 0;

	return strategy;
}
`