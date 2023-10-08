let userSettings = {
    displayBackground: 1,
    displayPath: 1,
    gridType: 1,
    rotationType: 2,
    simSpeed: 1,
    translationType: 2,
    zoomAmount: 2,
    pixelDensity: 1,
    simQuality: 10
};

let dialogOpen = false;

let showSym = false;
let altPressed = false;
let shiftPressed = false;
let ctrlOrCommandPressed = false;

let simulationCameraAim = { x: 1500, y: 1000, k: 1, a: 0 }
let editModeCameraAim = { x: 1500, y: 1000, k: 1, a: 0 }
let cameraCurrent = { x: 1500, y: 1000, k: 0.5, a: 0.5 }
let cameraSpeed = { x: 0.1, y: 0.1, k: 0.01, a: 0.01 }
let windowTransform = {};

let robotPos = { x: 0, y: 0 };

let backgroundImage;
let faceUpRed;
let faceUpGreen;
let faceUpBlue;
let faceDown;

var currentTool = null;

let selectionTool = new SelectionTool();
let penTool = new PenTool();
let eraserTool = new EraserTool();
let cutterTool = new CutterTool();
//let simulationTool = new SimulationTool();

function preload() {
    backgroundImage = loadImage("graphics/table.jpg")
    faceUpRed = loadImage("graphics/elements/face-up-red.png")
    faceUpGreen = loadImage("graphics/elements/face-up-green.png")
    faceUpBlue = loadImage("graphics/elements/face-up-blue.png")
    faceDown = loadImage("graphics/elements/face-down.png")
} 

function setup() {
    var canvas = createCanvas(10, 10);
    canvas.parent("sketch-div");
    windowResized()

    frameRate(60)

    selectNone();

    selectionTool.pickUp();
}

function draw() {
    clear()
    //drawCredits()

    updateCameraSettings()
    updateCamera()

    push()

    translate(windowTransform.w/2 + windowTransform.x, windowTransform.h/2 + windowTransform.y)
    scale(windowTransform.k)
    scale(cameraCurrent.k)
    rotate(cameraCurrent.a)
    translate(-cameraCurrent.x, -cameraCurrent.y)

    if (currentTool.name === "simulation") {
        drawTable()
        drawBodies()
        drawPath()
        pop()

        updateSimulationIndicators() // stat interface

        updateSimulation()

    } else {
        drawTable();
        drawBodies();
        //image(faceUpRed, 836, 475, 150/faceUpRed.height*faceUpRed.width, 150)
        //image(faceUpGreen, 836 - 70, 475 + 124.5, 150/faceUpGreen.height*faceUpGreen.width, 150)
        //image(faceUpBlue, 836, 475 + 124.5 * 2, 150/faceUpBlue.height*faceUpBlue.width, 150)
        //image(faceUpRed, 3000-836-faceUpRed.width/2, 475, 150/faceUpRed.height*faceUpRed.width, 150)
        //image(faceUpGreen, 3000-836-faceUpGreen.width/2 + 70, 475 + 124.5, 150/faceUpGreen.height*faceUpGreen.width, 150)
        //image(faceUpBlue, 3000-836-faceUpBlue.width/2, 475 + 124.5 * 2, 150/faceUpBlue.height*faceUpBlue.width, 150)
        drawAnchors();
        drawPath();
        currentTool.drawInteraction();
        pop()
    }

    if (currentTool.name !== "simulation") {
        drawCursorCoordinates()
        if (showSym) drawSymetryLine()
    }
}

function drawBodies() {
    let blueSide = (points.length > 0) && (points[0].x < 1500);

    let red = () => {
        fill(255, 0, 0, 20)
        stroke(255, 0, 0)
    }, green = () => {
        fill(0, 255, 0, 20)
        stroke(0, 255, 0)
    }

    for (let obj of bodies) {
        strokeWeight(1.5 / cameraCurrent.k / windowTransform.k)
        if (obj.grabbed) {
            strokeWeight((3 + 1.5 * sin(frameCount / 8 * userSettings.simSpeed)) / cameraCurrent.k / windowTransform.k)
        } else if (obj.label === "robot") {
            push()
            noStroke()
            fill(255, 200)
            translate(obj.position.x, obj.position.y)
            robotPos = { x: obj.position.x, y: obj.position.y };
            rotate(obj.angle)
            drawRobot()
            pop()
        } else if (obj.label === "port") {
            if ((obj.portInfo.team === "blue") != (blueSide)) continue
            if (obj.portInfo.color === "red")
                red()
            else
                green()
            beginShape()
            for (let v of obj.vertices) {
                vertex(v.x, v.y)
            }
            endShape(CLOSE)
        } else if (obj.label === "wall") {
            noStroke()
            fill(255, 100)
            beginShape()
            for (let v of obj.vertices) {
                vertex(v.x, v.y)
            }
            endShape(CLOSE)
        }
    }
}

function drawRobot() {
    beginShape()
    for (let v of robot.vertices) {
        vertex(v.x, v.y)
    }
    endShape(CLOSE)
    push()
    fill(255)
    noStroke()
    textSize(20)
    text("NW", 115, -110)
    fill(0)
    circle(0, 0, 10)
    circle(0, robot.wheelOffset, 10)
    circle(0, -robot.wheelOffset, 10)
    pop()
    // for (let part of robot.body.parts.slice(1)) {
    //     beginShape()
    //     for (let v of part.vertices) {
    //         vertex(v.x, v.y)
    //     }
    //     endShape(CLOSE)
    // }
}

function drawRobotGhost(x, y, a, color) {
    push()
    noFill();
    stroke(color);
    strokeWeight(1);
    translate(x, y)
    rotate(a)
    beginShape();
    for (let v of robot.vertices) {
        vertex(v.x, v.y);
    }
    endShape(CLOSE);
    pop()
}

function drawGhostBounds(color) {
    push()
    noFill();
    stroke(color);
    strokeWeight(1);
    rect(0, 0, 3000, 2000);
    pop()
}

function drawCursorCoordinates() {
    let mouse = pixelsToMillis(mouseX, mouseY)
    if (isOnTable(mouse.x, mouse.y)) {
        textAlign(RIGHT, BOTTOM)
        textSize(15)
        fill(100)
        noStroke()
        text(`x: ${round(mouse.x)}, y: ${round(mouse.y)}`, width - 20, height - 15)
    }
}

let op = 100;

function drawTable() {  //Correction de la superposition image/grille
    let x = 0, y = 0;
    if (userSettings.displayBackground)
        image(backgroundImage, -x, -y, 3000 + x*2, 1975 + 25 + y*2)
    //let thickness = 22
    // noFill()
    // stroke(0, 100)
    // push()
    // //fill(0, 150)
    // noFill()
    // strokeWeight(thickness)
    // rect(0 - thickness / 2, 0 - thickness / 2, 3000 + thickness, 2000 + thickness)
    // pop()

    noStroke()
    fill(0, 100)
    rect(0, 0, 3000, 2000)
    

    if (userSettings.displayBackground) {
        image(backgroundImage, -x, -y, 3000 + x*2, 1975 + 25 + y*2)
        //image(backgroundImageOver, -x, -y, 3000 + x*2, 1830 + 25 + y*2)

    }
    
    drawGrid()

    

    // push()
    // noStroke()
    // translate(0, 2000)
    // rect(10, 22, 730, 22)
    // scale(-1, 1)
    // translate(-3000, 0)
    // rect(10, 22, 730, 22)
    // pop()
}

function drawGrid() {
    let val = 0
    if (currentTool.name !== "simulation" && !userSettings.displayBackground)
        val = 150
    if (userSettings.gridType === 0) return
    let space = userSettings.gridType * 10
    let N = 3000 / space
    strokeCap(SQUARE)
    let setStyle = function(i) {
        if (i % 100 === 0) {
            strokeWeight(2 / cameraCurrent.k / windowTransform.k)
            stroke(val, altPressed?100:50)
        } else {
            strokeWeight(2 / cameraCurrent.k / windowTransform.k)
            stroke(val, altPressed?50:20)
        }
    }
    for (let i = 1; i < N; i++) {
        setStyle(i * space)
        line(i * space, 0, i * space, 2000)
    }
    N = 2000 / space
    for (let i = 1; i < N; i++) {
        setStyle(i * space)
        line(0, i * space, 3000, i * space)
    }
}

function drawPreviewTrajectory() {
    stroke(255, 50)
    strokeWeight(6)
    let mouse = pixelsToMillis(mouseX, mouseY)
    if (tool === "pen" && points.length != 0 && hoveredIndex === -1 &&
        isOnTable(mouse.x, mouse.y)) {
        if (selectedIndex != -1 && selectedIndex < points.length - 1) {
            let p1 = points[selectedIndex]
            let p2 = points[selectedIndex + 1]
            dottedLine(p1.x, p1.y, mouse.x, mouse.y, 20)
            dottedLine(p2.x, p2.y, mouse.x, mouse.y, 20)
        }
        if (selectedIndex === points.length - 1) {
            let p1 = points[selectedIndex]
            dottedLine(p1.x, p1.y, mouse.x, mouse.y, 20)
        }
    } else if (tool === "eraser" && hoveredIndex > 0 && hoveredIndex != points.length - 1) {
        let p1 = points[hoveredIndex - 1]
        let p2 = points[hoveredIndex + 1]
        dottedLine(p1.x, p1.y, p2.x, p2.y, 20)
    }
}

function drawSymetryLine() {
    stroke(255, 150)
    strokeWeight(2)
    dottedLine(width / 2, 0, width / 2, height, 15)
}

function drawCredits() {
    let sideBar = width - document.querySelector(".side-bar").offsetLeft;
    let s = `Simulateur et interface conçus\npar Pharoah Jardin`
    textSize(14)
    textAlign(CENTER)
    textFont("Rubik")
    fill(60)
    text(s, (width - sideBar + 50)/2, height/2)
}

function applySymetry() {
    for (let point of points) {
        point.x = 3000 - point.x
        point.r = 1 - point.r;
        let ne = point.actions.ne;
        point.actions.ne = point.actions.se;
        point.actions.se = ne;
        let nw = point.actions.nw;
        point.actions.nw = point.actions.sw;
        point.actions.sw = nw;
    }
    updateHTMLList()
}

function getWindowTranform() {
    let margin = 40
    let toolBar = 50
    let sideBar = width - document.querySelector(".side-bar").offsetLeft;

    let bg = { x: margin + 50, y: margin, k: 0.3, w: null, h: null }

    let w = width - toolBar - sideBar - margin*2
    let h = height - margin*2
    if (w / 3 < h / 2) {
        bg.h = w / 3 * 2
        bg.w = w
        bg.y = (h - bg.h) / 2 + margin
        bg.k = bg.w / 3000
    } else {
        bg.w = h / 2 * 3
        bg.h = h
        bg.x = (w - bg.w) / 2 + toolBar + margin
        bg.k = bg.h / 2000
    }
    bg.w
    return bg
}

function updateCamera(instant) {
    let aim = (currentTool.name === "simulation")?simulationCameraAim:editModeCameraAim;
    if (instant) {
        cameraCurrent.x = aim.x;
        cameraCurrent.y = aim.y;
        cameraCurrent.k = aim.k;
        cameraCurrent.a = aim.a;
    } else {
        cameraCurrent.x = lerp(cameraCurrent.x, aim.x, cameraSpeed.x);
        cameraCurrent.y = lerp(cameraCurrent.y, aim.y, cameraSpeed.y);
        if (cameraCurrent.k === NaN) cameraCurrent.k = 1
        cameraCurrent.k = lerp(cameraCurrent.k, aim.k, cameraSpeed.k);
        cameraCurrent.a = lerp(cameraCurrent.a, aim.a, cameraSpeed.a);
    }
}

function updateCameraSettings() {
    if (currentTool.name === "simulation") {
        simulationCameraAim = { x: 1500, y: 1000, k: 1, a: 0 }
        if (userSettings.translationType !== 0) {
            simulationCameraAim.x = robot.body.position.x
            simulationCameraAim.y = robot.body.position.y
            simulationCameraAim.k = userSettings.zoomAmount;
            if (userSettings.rotationType !== 0) {
                simulationCameraAim.a = -robot.body.angle - PI / 2;
            }
            cameraSpeed.a = (userSettings.rotationType === 1) ? 0.02 : 0.1
            cameraSpeed.k = (userSettings.zoomAmount === 1) ? 0.1 : 0.01
        } else {
            cameraSpeed = { x: 0.2, y: 0.2, k: 0.2, a: 0.2 }
        }
        if (userSettings.translationType === 1) {
            cameraSpeed.x = 0.01 * userSettings.zoomAmount;
            cameraSpeed.y = 0.01 * userSettings.zoomAmount;
        } else {
            cameraSpeed.x = 0.1;
            cameraSpeed.y = 0.1;
        }
    } else {
        // if (altPressed && selectedIndex >= 0) {
        //     let point = points[selectedIndex]
        //     cameraAim = { x: point.x, y: point.y, k: 3, a: 0 }
        cameraSpeed = { x: 0.2, y: 0.2, k: 0.1, a: 0.2 }
        // } else {
        //     cameraAim = { x: 1500, y: 1000, k: 1, a: 0 }
        //     cameraSpeed = { x: 0.2, y: 0.2, k: 0.2, a: 0.2 }
        // }
    }
}