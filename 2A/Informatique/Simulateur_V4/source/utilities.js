function mod(x, d) {
    return (x % d + d) % d
}

function sgn(x) {
    return x ? (x / abs(x)) : 0
}

function isOnTable(x, y) {
    return (
        0 <= x && x <= 3000 &&
        0 <= y && y <= 2000
    )
}

function pixelsToMillis(x, y) {
    x -= windowTransform.x + windowTransform.w/2;
    y -= windowTransform.y + windowTransform.h/2;
    x /= windowTransform.k;
    y /= windowTransform.k;
    x /= cameraCurrent.k;
    y /= cameraCurrent.k;
    x += cameraCurrent.x;
    y += cameraCurrent.y;
    return { x, y }
}

function linearPixelsToMillis(x, y) {
    x /= windowTransform.k;
    y /= windowTransform.k;
    x /= cameraCurrent.k;
    y /= cameraCurrent.k;
    return { x, y }
}

function magni(vect) {
    return sqrt(vect.x*vect.x + vect.y*vect.y);
}

function ctrlOrCommand(event) {
    let isMac = navigator.platform.toUpperCase().indexOf('MAC')>=0;
    if (isMac) {
        return event.metaKey;
    } else {
        return event.ctrlKey;
    }
}

function arrow(x1, y1, x2, y2, r = 8) {
    push()
    line(x1, y1, x2, y2)
    noFill()
    let l = ((y2 - y1) ** 2 + (x2 - x1) ** 2) ** 0.5
    r = (1 - 1 / (1 + 0.8 * (l / r) ** 2)) * r
    theta = atan2((y2 - y1), (x2 - x1))
    arc(x2 + sin(theta) * r, y2 - cos(theta) * r, r * 2, r * 2, theta + HALF_PI, theta - PI)
    arc(x2 - sin(theta) * r, y2 + cos(theta) * r, r * 2, r * 2, theta + PI, theta - HALF_PI)
    pop()
}

function dottedLine(x1, y1, x2, y2, dl) {
    let position = createVector(x1, y1)
    let dv = createVector(x2 - x1, y2 - y1)
    let d = dv.mag()
    dv.setMag(dl)
    for (let i = 0; i < d / dl / 2; i++) {
        let lineEnd = p5.Vector.add(position, dv)
        line(position.x, position.y, lineEnd.x, lineEnd.y)
        position.add(dv)
        position.add(dv)
    }
}

// function togglePointInSelection(item) {
//     let found = false;
//     let newSelection = []
//     selection.forEach(el => {
//         if (el.curveIndex === item.curveIndex && el.pointIndex === item.pointIndex) {
//             found = true;
//         } else {
//             newSelection.push(el);
//         }
//     })
//     if (!found)
//         newSelection.push(item)
//     selection = newSelection;
// }