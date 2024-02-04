let path = [
    new Bezier(428+1, 869, 664, 870, 428+1, 1159+1, 656, 1159+1), 
    new Bezier(656, 1159+1, 883+1, 1159+1, 956, 1160+1, 1052+1, 1160), 
    new Bezier(1052+1, 1160, 1149, 1159+1, 1211+1, 1106+1, 1210, 972), 
    new Bezier(1210, 972, 1208+1, 837+1, 1209+1, 760+1, 1209+1, 605), 
    new Bezier(1209+1, 605, 1209+1, 449, 1119+1, 398+1, 983, 399+1), 
    new Bezier(983, 399+1, 847, 401, 769, 475+1, 769+1, 605), 
    new Bezier(769+1, 605, 769+1, 734+1, 770, 966, 770, 966)
]

let shouldReverse = {};
let speeds = {};
let onSiteActions = {};
let onMoveActions = {};

consolidatePath();

var hoveredItem;
resetHoveredItem();

function resetHoveredItem() {
    hoveredItem = {
        curveIndex: -1,
        pointIndex: -1,
        dist: Infinity
    };
}

function consolidatePath() {
    for (let i=0; i<path.length-1; i++) {
        path[i + 1].points[0] = {
            x: path[i].points[3].x,
            y: path[i].points[3].y
        }
    }
}

function drawPath() {
    let k = cameraCurrent.k * windowTransform.k;
    path.forEach((curve, i) => {
        drawCurve(curve, i, k)
    });
    if (hoveredItem.curveIndex >= 0) {
        let point = path[hoveredItem.curveIndex].points[hoveredItem.pointIndex]
        drawInteractionCircle(point.x, point.y, k, false)
    }
}

function drawAnchors() {
    let k = cameraCurrent.k * windowTransform.k;
    for (let i=0; i<path.length; i++) {
        if (path[i].selectedPoints[0] || path[i].selectedPoints[1] || path[i-1]?.selectedPoints[2])
            drawAnchor(path[i].points[0], path[i].points[1], k, path[i].selectedPoints[1])

        if (path[i].selectedPoints[2] || path[i].selectedPoints[3] || path[i+1]?.selectedPoints[1])
            drawAnchor(path[i].points[3], path[i].points[2], k, path[i].selectedPoints[2])
    }
}

function drawCurve(curve, i, k) {
    let point = curve.points[0]
    let showEndPoint = (i === path.length - 1);
    
    //circle(point.x, point.y, 10/k)
    
    if (curve.selectedPoints[0]) {
        drawInteractionCircle(point.x, point.y, k, true)
        fill(255, 255); noStroke();
    } else {
        fill(255, 100); noStroke();
    }
    if ((Number(speeds[i])??0) === 0)
        rect(point.x-5/k, point.y-5/k, 10/k, 10/k)
    else
        circle(point.x, point.y, 10/k)

    if (showEndPoint) {
        if (curve.selectedPoints[3]) {
            drawInteractionCircle(curve.points[3].x, curve.points[3].y, k, true)
            fill(255, 255); noStroke();
            circle(curve.points[3].x, curve.points[3].y, 10/k)
        } else {
            fill(255, 100); noStroke();
            circle(curve.points[3].x, curve.points[3].y, 10/k)
        }
        circle(curve.points[3].x, curve.points[3].y, 10/k);
    }

    drawBezier(curve, k)
}

function drawInteractionCircle(x, y, k, selected) {
    push()
    if (selected) {
        stroke(255)
        fill(255, 100)
        strokeWeight(1/k)
    } else {
        noStroke()
        fill(255, 50)
    }
    circle(x, y, 30/k)
    pop()
}

function drawAnchor(start, end, k, selected) {
    push()
    stroke(255, 255)
    noFill()
    strokeWeight(2/k)
    circle(end.x, end.y, 9/k)
    stroke(255, 50)
    strokeWeight(4/k)
    let r = createVector(end.x - start.x, end.y - start.y);
    r.setMag(4/k)
    line(start.x, start.y, end.x - r.x, end.y - r.y)
    if (selected)
        drawInteractionCircle(end.x, end.y, k, true)
    pop()
}

function drawBezier(curve, k, isTemp) {
    beginShape()
    let N = 5 + floor(curve.length()/30);
    curve.getLUT(N).forEach((point) => {
        vertex(point.x, point.y)
    })
    noFill()
    stroke(255, 150)
    if (isTemp != null)
        stroke(255, 255)
    strokeWeight(2/k)
    endShape()
    noStroke()
    curve.getLUT(N).forEach((point, i) => {
        let t = (i+1)/N;
        let kr = curve.curvature(t);
        if (abs(kr.r) < robot.wheelOffset && kr.r !== 0) {
            let f = (1 + sin(frameCount/3))/2;
            fill(255 * f, 100 * f, 0 * f)
            circle(point.x, point.y, 7/k)
        }
    })
}

function drawPassPoint(pos, anchor) {
    push()
    translate(pos.x, pos.y)
    circle(20, 20, 20)
    pop()
}

function deleteSelection() {
    if (path.length === 1) {
        selectionTool.pickUp();
        return;
    }
    let shouldSelectLast = false;
    for (let i=path.length-1; i>=0; i--) {
        if (path[i].selectedPoints[0] === true) {
            if (i === 0) {
                path.shift();
                resetHoveredItem();
                continue;
            }
            let newCurve = new Bezier(
                path[i-1].points[0].x, path[i-1].points[0].y,
                path[i-1].points[1].x, path[i-1].points[1].y,
                path[i].points[2].x, path[i].points[2].y,
                path[i].points[3].x, path[i].points[3].y
            )
            newCurve.selectedPoints = [false, false, false, false]
            path.splice(i-1, 2, newCurve)
            resetHoveredItem();
        }
        if (path[i].selectedPoints[3] === true && i === path.length-1) {
            path.splice(i, 1);
            resetHoveredItem();
            shouldSelectLast = currentTool.name === "selection";
        }
    }
    if (shouldSelectLast) {
        selectLastPoint();
    }
    if (path.length === 1) {
        selectionTool.pickUp()
    }
}

function selectNone() {
    for (let curve of path) {
        curve.selectedPoints = [false, false, false, false];
    }
    disablePathInspector();
    disableActionInspector();
}

function addToSelection(item) {
    let curve = path[item.curveIndex]
    curve.selectedPoints[item.pointIndex] = true;
    if (item.pointIndex === 0 && item.curveIndex > 0) {
        let previousCurve = path[item.curveIndex - 1]
        previousCurve.selectedPoints[3] = true;
    } else if (item.pointIndex === 3 && item.curveIndex < path.length - 1) {
        let nextCurve = path[item.curveIndex + 1]
        nextCurve.selectedPoints[0] = true;
    }
}

function selectSingle(item) {
    selectNone();
    let curve = path[item.curveIndex]
    curve.selectedPoints[item.pointIndex] = true;
    if (item.pointIndex === 0 && item.curveIndex > 0) {
        let previousCurve = path[item.curveIndex - 1]
        previousCurve.selectedPoints[3] = true;
    } else if (item.pointIndex === 3 && item.curveIndex < path.length - 1) {
        let nextCurve = path[item.curveIndex + 1]
        nextCurve.selectedPoints[0] = true;
    }
    if (item.pointIndex === 0 || item.pointIndex === 3) {
        let n = item.curveIndex;
        if (item.pointIndex === 3) {
            n += 1;
        }
        let reverse = !!shouldReverse[n];
        let speed = speeds[n] ?? 0;
        updatePathInspector(reverse, speed, n);
        updateActionInspector(n);
    }
}

function selectLastPoint() {
    path[path.length-1].selectedPoints[3] = true;
}

function isSelected(item) {
    let curve = path[item.curveIndex];
    return !!curve?.selectedPoints[item.pointIndex];
}

function countSelection() {
    let count = 0 + path[0].selectedPoints[0];
    for (let curve of path) {
        for (let i=1; i<4; i++) {
            count += curve.selectedPoints[i];
        }
    }
    return count;
}

function getFirstSeelectedPoint() {
    for (let j=0; j<path.length; j++) {
        for (let i=0; i<4; i++) {
            if (path[j].selectedPoints[i]) {
                return {
                    curveIndex: j,
                    pointIndex: i
                };
            }
        } 
    }
    return {
        curveIndex: -1,
        pointIndex: -1,
    };
}

function translateSelection(movement) {
    for (let curveIndex=0; curveIndex<path.length; curveIndex++) {
        let prev = path[curveIndex - 1], 
            curve = path[curveIndex], 
            next = path[curveIndex + 1];

        let selectionCount = curve.selectedPoints.reduce((el, cumm) => cumm + el, 0);

        for (let pointIndex=0; pointIndex<4; pointIndex++) {
            if (pointShouldBeDragged(pointIndex, curve)) {
                curve.points[pointIndex].x += movement.x;
                curve.points[pointIndex].y += movement.y;
            }
            if (curve.selectedPoints[1] && selectionCount === 1 && prev != null && (speeds[curveIndex]||0) != 0)
                keepSymetric(prev.points[2], prev.points[3], curve.points[1]);
            
            if (curve.selectedPoints[2] && selectionCount === 1 && next != null && (speeds[curveIndex+1]||0) != 0)
                keepSymetric(next.points[1], next.points[0], curve.points[2]);
        }
    }
}

function pointShouldBeDragged(pointIndex, curve) {
    return (
        // the point is selected
        curve.selectedPoints[pointIndex] ||
        // or the anchor's parent is selected
        pointIndex === 1 && curve.selectedPoints[0] ||
        pointIndex === 2 && curve.selectedPoints[3]
    );
}

function keepSymetric(target, center, reflection) {
    target.x = center.x - (reflection.x - center.x);
    target.y = center.y - (reflection.y - center.y);
}

function makeSymetric(target1, center, target2) {
    let target1Copy = { ...target1 };
    keepSymetric(target1Copy, center, target2);
    target1.x = target1.x/2 + target1Copy.x/2;
    target1.y = target1.y/2 + target1Copy.y/2;
    keepSymetric(target2, center, target1);
}

function hitTest(position) {
    let minDist = Infinity;
    let minIndex = 0;
    let minSubIndex = 0;
    for (let i = 0; i < path.length; i++) {
        let curve = path[i]
        let d;
        for (let j=0; j < curve.points.length; j++) {
            if (j === 1 && !curve.selectedPoints[0] && !curve.selectedPoints[1] && !curve.selectedPoints[2])
                continue;
            if (j === 2 && !curve.selectedPoints[3] && !curve.selectedPoints[1] && !curve.selectedPoints[2])
                continue;
            let point = curve.points[j]
            d = createVector(point.x - position.x, point.y - position.y).mag()
            if (d < minDist) {
                minDist = d;
                minIndex = i;
                minSubIndex = j;
            }
        }
    }
    return { dist: minDist, curveIndex: minIndex, pointIndex: minSubIndex }
}

function pprint() {
    let out = "";
    for (let b of path) {
        for (let p of b.points) {
            out += `${Math.round(p.x)}, ${Math.round(p.y)}, `
        }
        out += "\n"
    }
    console.log(out);
}