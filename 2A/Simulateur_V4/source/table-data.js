function generateRobotVertices(w, h, r, N) {
    w = w || 160
    h = h || 250
    r = r || 40
    N = N || 10
    let robotVerts = [];
    robotVerts.push(Matter.Vector.create(w / 2, -h / 2))
    for (let i = N; i >= 0; i--) {
        let x = -r * Math.sin(i / N * Math.PI)
        let y = r * Math.cos(i / N * Math.PI)
        robotVerts.push(Matter.Vector.create(w / 2 + x, -h / 4 + y))
    }
    robotVerts.push(Matter.Vector.create(w / 2, 0))
    for (let i = N; i >= 0; i--) {
        let x = -r * Math.sin(i / N * Math.PI)
        let y = r * Math.cos(i / N * Math.PI)
        robotVerts.push(Matter.Vector.create(w / 2 + x, h / 4 + y))
    }
    robotVerts.push(Matter.Vector.create(w / 2, h / 2))
    robotVerts.push(Matter.Vector.create(-w / 2, h / 2))
    for (let i = N; i >= 0; i--) {
        let x = -r * Math.sin(i / N * Math.PI)
        let y = r * Math.cos(i / N * Math.PI)
        robotVerts.push(Matter.Vector.create(-w / 2 - x, h / 4 - y))
    }
    robotVerts.push(Matter.Vector.create(-w / 2, 0))
    for (let i = N; i >= 0; i--) {
        let x = -r * Math.sin(i / N * Math.PI)
        let y = r * Math.cos(i / N * Math.PI)
        robotVerts.push(Matter.Vector.create(-w / 2 - x, -h / 4 - y))
    }
    robotVerts.push(Matter.Vector.create(-w / 2, -h / 2))
    return robotVerts;
}

function extractRobotVertices(N, thresholdAngle) {
    N = N || 500
    let pathElement = $("#ID_159-7")[0]

    let points = []
    let l = pathElement.getTotalLength();
    for (let i = 0; i < N; i++) {
        let SVGPoint = pathElement.getPointAtLength(i / N * l)
        let p = { x: SVGPoint.x + 14.5, y: SVGPoint.y - 15.5 };
        points.push(p)
    }

    removeColinear(points, thresholdAngle)
    return points
}

function removeColinear(points, thresholdAngle) {
    for (let i = 0; i < points.length - 2; i++) {
        if (collinear(points[i], points[i + 1], points[i + 2], thresholdAngle)) {
            points.splice(i + 1, 1)
            i--
        }
    }
}

function collinear(a, b, c, thresholdAngle) {
    thresholdAngle = thresholdAngle || 0.01
    let ab = [b.x - a.x, b.y - a.y];
    let bc = [c.x - b.x, c.y - b.y];

    let dot = ab[0] * bc[0] + ab[1] * bc[1],
        magA = Math.sqrt(ab[0] * ab[0] + ab[1] * ab[1]),
        magB = Math.sqrt(bc[0] * bc[0] + bc[1] * bc[1]),
        angle = Math.acos(dot / (magA * magB));
    return angle <= thresholdAngle;
}