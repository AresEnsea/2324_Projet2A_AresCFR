var currentTool;
var simulationRunning;

class SimulationTool extends Tool {
    constructor() {
        super("simulation");
    }

    pickUp() {
        currentTool?.putDown();
        $(`.${this.name}.tool`).addClass("selected");
        currentTool = this;

        $(".flip.button").addClass("disabled");
        $(".only-for-simulation").removeClass("hidden");
        $(".not-for-simulation").addClass("hidden");

        setupSimulation();
    }

    putDown() {
        $(`.${this.name}.tool`).removeClass("selected");

        $(".flip.button").removeClass("disabled");
        $(".only-for-simulation").addClass("hidden");
        $(".not-for-simulation").removeClass("hidden");

        simulationRunning = false;
    }
}