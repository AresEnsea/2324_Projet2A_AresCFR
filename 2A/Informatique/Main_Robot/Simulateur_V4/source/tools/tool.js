var currentTool;

class Tool {
    constructor (name) {
        this.name = name;

        $(`.${name}.tool`).click(() => this.pickUp());
    }

    pickUp() {
        currentTool?.putDown();
        $(`.${this.name}.tool`).addClass("selected");
        currentTool = this;
    }

    putDown() {
        $(`.${this.name}.tool`).removeClass("selected");
    }

    mousePressed(_event) {
        // override this
    }

    mouseDragged(_event) {
        // override this
    }

    mouseMoved(_event) {
        // override this
    }

    mouseReleased(_event) {
        // override this
    }

    keyPressed(_event) {
        // override this
    }

    keyReleased(_event) {
        // override this
    }

    drawInteraction() {
        // override this
    }
}