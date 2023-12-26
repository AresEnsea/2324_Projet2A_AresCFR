var currentTool;
var hoveredItem;

class SelectionTool extends Tool {
    constructor() {
        super("selection");
        this.singlePointSelection = null;
    }

    putDown() {
        $(`.${this.name}.tool`).removeClass("selected");
        selectNone();
    }

    mouseMoved(event) {
        let mouse = pixelsToMillis(event.offsetX, event.offsetY);
        let closestItem = hitTest(mouse);
        let k = cameraCurrent.k * windowTransform.k;
        if (closestItem.dist < 15/k) {
            hoveredItem = closestItem;
            cursor('grab');
        } else {
            hoveredItem = { dist: Infinity, curveIndex: -1, pointIndex: -1 };
            cursor(ARROW);
        }
    }

    mousePressed(event) {
        let mouse = pixelsToMillis(event.offsetX, event.offsetY);
        let closestItem = hitTest(mouse);
        if (closestItem.dist < 30) {
            if (ctrlOrCommandPressed || isSelected(closestItem))
                addToSelection(closestItem);
            else
                selectSingle(closestItem);
        } else {
            selectNone();
        }
        if (countSelection() === 1) {
            this.singlePointSelection = getFirstSeelectedPoint();
        } else {
            this.singlePointSelection = null;
        }
    }

    mouseDragged(event) {
        let movement = linearPixelsToMillis(
            event.movementX,
            event.movementY,
        );
        if (ctrlOrCommand(event)) {
            editModeCameraAim.x -= movement.x;
            editModeCameraAim.y -= movement.y;
            updateCamera(true);
        } else {
            if (this.singlePointSelection && event.shiftKey) {
                if (this.singlePointSelection.pointIndex === 1) {
                    console.log("test")
                }
            }
            translateSelection(movement);
        }
    }

    keyPressed(event) {
        let amount = 1
        if (event.shiftKey) {
            amount = 50
        }
        if (event.key === "ArrowRight") {
            translateSelection({x: amount, y: 0});
        }
        else if (event.key === "ArrowLeft") {
            translateSelection({x: -amount, y: 0});
        }
        else if (event.key === "ArrowDown") {
            translateSelection({x: 0, y: amount});
        }
        else if (event.key === "ArrowUp") {
            translateSelection({x: 0, y: -amount});
        }
        else if (event.key === "Backspace" && path.length !== 0) {
            deleteSelection();
        }
    }
}