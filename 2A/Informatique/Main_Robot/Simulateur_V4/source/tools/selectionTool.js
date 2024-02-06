var currentTool;
var hoveredItem;

class SelectionTool extends Tool {
    constructor() {
        super("selection");
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
            this.dragSelection(movement);
        }
    }

    dragSelection(movement) {
        for (let curveIndex=0; curveIndex<curves.length; curveIndex++) {
            let prev = curves[curveIndex - 1], 
                curve = curves[curveIndex], 
                next = curves[curveIndex + 1];

            let selectionCount = curve.selectedPoints.reduce((el, cumm) => cumm + el, 0);

            for (let pointIndex=0; pointIndex<4; pointIndex++) {
                if (this.pointShouldBeDragged(pointIndex, curve)) {
                    curve.points[pointIndex].x += movement.x;
                    curve.points[pointIndex].y += movement.y;
                }
                if (curve.selectedPoints[1] && selectionCount === 1 && prev != null)
                    this.makeSymetric(prev.points[2], prev.points[3], curve.points[1]);
                
                if (curve.selectedPoints[2] && selectionCount === 1 && next != null)
                    this.makeSymetric(next.points[1], next.points[0], curve.points[2]);
            }
        }
    }

    pointShouldBeDragged(pointIndex, curve) {
        return (
            // the point is selected
            curve.selectedPoints[pointIndex] ||
            // or the anchor's parent is selected
            pointIndex === 1 && curve.selectedPoints[0] ||
            pointIndex === 2 && curve.selectedPoints[3]
        );
    }

    makeSymetric(target, center, reflection) {
        target.x = center.x - (reflection.x - center.x);
        target.y = center.y - (reflection.y - center.y);
    }
}