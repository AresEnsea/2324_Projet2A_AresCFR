var currentTool;

class PenTool extends Tool {
    constructor() {
        super("pen");
        this.mouse = { x: 0, y: 0 };
        this.tempCurve = null;
        
    }

    mouseMoved(event) {
        this.mouse = pixelsToMillis(event.offsetX, event.offsetY);
        let lastCurve = path[path.length-1];
        let startTangent = createVector();
        keepSymetric(startTangent, lastCurve.points[3], lastCurve.points[2])
        this.tempCurve = new Bezier(
            lastCurve.points[3].x, lastCurve.points[3].y,
            startTangent.x, startTangent.y,
            this.mouse.x, this.mouse.y,
            this.mouse.x, this.mouse.y
        )
    }

    mouseDragged(event) {
        this.mouse = pixelsToMillis(event.offsetX, event.offsetY);
        this.tempCurve.points[3] = this.mouse;
    }

    mouseReleased(event) {
        console.log(path, this.tempCurve)
        path.push(this.tempCurve)
        //consolidatePath();
        selectNone();
        //this.tempCurve = null;
    }

    drawInteraction() {
        if (this.tempCurve) {
            let k = cameraCurrent.k * windowTransform.k;
            drawBezier(this.tempCurve, k, true);
            drawAnchor(this.tempCurve.points[3], this.tempCurve.points[2], k, false)
            fill(255, 255); noStroke();
            circle(this.tempCurve.points[3].x, this.tempCurve.points[3].y, 10/k);
        }
    }

    keyPressed(event) {
        if (event.key === "Backspace" && path.length !== 0) {
            selectLastPoint();
            deleteSelection();
            this.tempCurve = null;
        } else if (event.key === "Escape") {
            selectionTool.pickUp();
        }
    }
}