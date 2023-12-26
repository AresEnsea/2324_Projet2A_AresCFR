var currentTool;
var hoveredItem;

class EraserTool extends Tool {
    constructor() {
        super("eraser");
        this.tempCurve = null;
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
            cursor('no-drop');
            let i = hoveredItem.curveIndex + 1;
            if (hoveredItem.curveIndex === 0 && hoveredItem.pointIndex === 0)
                i = 0;
            try {
                this.tempCurve = new Bezier(
                    path[i-1].points[0].x, path[i-1].points[0].y,
                    path[i-1].points[1].x, path[i-1].points[1].y,
                    path[i].points[2].x, path[i].points[2].y,
                    path[i].points[3].x, path[i].points[3].y
                );
            } catch (e) {
                this.tempCurve = null;
            } 
        } else {
            hoveredItem = { dist: Infinity, curveIndex: -1, pointIndex: -1 };
            cursor(ARROW);
            this.tempCurve = null;
        }
    }

    mousePressed(event) {
        let mouse = pixelsToMillis(event.offsetX, event.offsetY);
        let closestItem = hitTest(mouse);
        if (closestItem.dist < 30) {
            selectSingle(closestItem);
            this.shiftPathData(closestItem.curveIndex);
            deleteSelection();
        } else {
            selectNone();
        }
    }

    shiftPathData(start) {
        for (let i=start; i<path.length-1; i++) {
            speeds[i] = speeds[i+1];
            shouldReverse[i] = shouldReverse[i+1];
            onSiteActions[i] = onSiteActions[i+1];
            onMoveActions[i] = onMoveActions[i+1];
        }
        speeds[path.length-1] = 0;
        shouldReverse[path.length-1] = [];
        onSiteActions[path.length-1] = [];
        onMoveActions[path.length-1] = [];
    }

    drawInteraction() {
        if (this.tempCurve) {
            let k = cameraCurrent.k * windowTransform.k;
            drawBezier(this.tempCurve, k, true);
        }
    }
}