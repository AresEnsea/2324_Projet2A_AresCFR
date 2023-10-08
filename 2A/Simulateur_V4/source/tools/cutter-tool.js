var currentTool;
var hoveredItem;

class CutterTool extends Tool {
    constructor() {
        super("cutter");
        this.closestCurveIndex = null;
        this.projection = null;
    }

    mouseMoved(event) {
        let mouse = pixelsToMillis(event.offsetX, event.offsetY);
        let minDist = Infinity;
        let minCurveIndex = null;
        let minProjection = null;

        for (let i=0; i<path.length; i++) {
            let curve = path[i];
            let projection = curve.project(mouse);
            if (projection.d < minDist && projection.d < 30) {
                minDist = projection.d;
                minCurveIndex = i;
                minProjection = projection;
            }
        }

        this.projection = minProjection;
        this.closestCurveIndex = minCurveIndex;
    }

    drawInteraction() {
        if (this.projection) {
            push()
            fill(255);
            noStroke();
            let k = cameraCurrent.k * windowTransform.k;

            translate(this.projection.x, this.projection.y);
            rectMode(CENTER);
            rect(0, 0, 15/k, 3/k);
            rect(0, 0, 3/k, 15/k);
            pop()
        }
    }

    mousePressed(event) {
        let mouse = pixelsToMillis(event.offsetX, event.offsetY);
        let closestItem = hitTest(mouse);
        if (this.projection) {
            let curve = path[this.closestCurveIndex];
            let splitResult = curve.split(this.projection.t);
            console.log(splitResult.left, splitResult.right);
            this.shiftPathData(this.closestCurveIndex);
            path.splice(this.closestCurveIndex, 1, splitResult.left, splitResult.right);
            selectNone();
        }
    }

    shiftPathData(start) {
        for (let i=path.length; i>=start; i--) {
            speeds[i+1] = speeds[i];
            shouldReverse[i+1] = shouldReverse[i];
            onSiteActions[i+1] = onSiteActions[i];
            onMoveActions[i+1] = onMoveActions[i];
        }
        onSiteActions[start+1] = [];
        onMoveActions[start+1] = [];
    }
}