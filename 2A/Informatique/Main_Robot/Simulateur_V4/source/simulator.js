// modules Matter.js (voir la documentation)
let Engine = Matter.Engine,
    World = Matter.World,
    Bodies = Matter.Bodies,
    Body = Matter.Body,
    Constraint = Matter.Constraint;

let engine;
let world;
let bodies = [];
let constraints;

let robot = {
    wheelOffset: 60,
    vertices: extractRobotVertices(1000, 0.08),
    aimPoint: 0,
    armPos: 0,
    armLength: 200,
    controlConstraint: null
}

let startFrame = 0
let startTimestamp = 0
let pauseTimestamp = 0

var simulationRunning = false
var simulationStopped = false


let currentCurve = 0

function setupSimulation() {
    currentCurve = 0
    startFrame = frameCount

    engine = Engine.create({
        positionIterations: 10,
        velocityIterations: 10
    });
    world = engine.world;
    world.gravity.y = 0;
    startTimestamp = engine.timing.timestamp


    // supprime les goblets
    bodies.length = 0;

    // frontières de la table
    bodies.push(Bodies.rectangle(1500, 2000 + 100, 3000 + 200, 200, { isStatic: true, restitution: 0 }))
    bodies.push(Bodies.rectangle(1500, -100, 3000 + 200, 200, { isStatic: true, restitution: 0 }))
    bodies.push(Bodies.rectangle(3000 + 100, 1000, 200, 2000 + 200, { isStatic: true, restitution: 0 }))
    bodies.push(Bodies.rectangle(-100, 1000, 200, 2000 + 200, { isStatic: true, restitution: 0 }))

    // bodies.push(Bodies.circle(1500, 1000, 20))

    let x = path[0].points[0].x
    let y = path[0].points[0].y

    robot.body = Bodies.fromVertices(x, y, extractRobotVertices(1000, 0.2), {
        label: "robot",
        density: 1,
        frictionAir: 0.1,
        restitution: 0,
    })
    bodies.push(robot.body)
    let r = createVector(path[0].points[1].x-path[0].points[0].x, path[0].points[1].y-path[0].points[0].y)
    let a = r.heading()
    //a += points[robot.aimPoint].r * PI
    Body.rotate(robot.body, a, robot.body.position)

    World.add(world, bodies)

    robot.controlConstraint = Constraint.create({
        pointA: { x, y },
        bodyB: robot.body,
        pointB: { x: 0, y: 0 },
        stiffness: 0.1,
        damping: 0.1,
        angularStiffness: 1,
        length: 0
    });

    World.add(world, [robot.controlConstraint]);
}

function updateSimulation() {
    let dt = 1000 / 60
    if (userSettings.simSpeed < 1)
        dt *= userSettings.simSpeed
    else {
        for (i = 1; i < userSettings.simSpeed; i++) {
            if (simulationRunning) {
                updateMotors()
                Engine.update(engine, dt)
            }
        }
    }
    if (simulationRunning) {
        updateMotors()
        Engine.update(engine, dt)
    }
}

function updateMotors() {
    let curve = path[currentCurve]

    let posOnCurve = curve.project(robot.body.position)
    let t = posOnCurve.t;
    let diff = curve.derivative(t);
    let angularError = robot.body.angle - atan2(diff.y, diff.x);

    if (t > 0.9999) {
        currentCurve++;
        if (currentCurve == path.length) {
            currentCurve = 0
            simulationRunning = false
        }
        return;
    }

    let k = curve.curvature(t).k
    let r = 1/k
    //let slow = 1/(1 + pow(abs(k), 2)*10000)
    let d = curve.derivative(t)
    let slow = 1 - max(0, sminCubic(1, 1/sqrt(d.x*d.x + d.y*d.y)*100, 1))
    let v = (20*t*(1-t) + 1*(1-t) + 1*t)/5// * slow 
    let e = robot.wheelOffset
    let v_g = v*(1-e*k)
    let v_d = v*(1+e*k)

    setRobotMotors(v_g, v_d)
}

function sminCubic(a, b, k) {
    let h = max( k-abs(a-b), 0.0 )/k;
    let m = h*h*h*0.5;
    let s = m*k*(1.0/3.0); 
    return (a<b) ? a-s : b-s;
}

function setRobotMotors(left, right) {
	let r =  (left + right)/2;
	let alpha = (right - left)/(robot.wheelOffset*2);

	let dx = r * cos(robot.body.angle + alpha/2);
	let dy = r * sin(robot.body.angle + alpha/2);

    robot.controlConstraint.pointA.x += dx;
    robot.controlConstraint.pointA.y += dy;
    Body.setAngle(robot.body, robot.body.angle + alpha)
}

function setRobotMotors_old(left, right) {
    let rbt = robot.body;
    let leftForcePos = { // position de la roue gauche
        x: rbt.position.x + robot.wheelOffset * Math.sin(rbt.angle),
        y: rbt.position.y - robot.wheelOffset * Math.cos(rbt.angle),
    }
    let leftForce = { // force exercée par la roue gauche
        x: left * Math.cos(rbt.angle),
        y: left * Math.sin(rbt.angle)
    }
    let rightForcePos = { // position de la roue droite
        x: rbt.position.x - robot.wheelOffset * Math.sin(rbt.angle),
        y: rbt.position.y + robot.wheelOffset * Math.cos(rbt.angle),
    }
    let rightForce = { // force exercée par la roue droite
        x: right * Math.cos(rbt.angle),
        y: right * Math.sin(rbt.angle)
    }

    // application des forces
    Body.applyForce(rbt, leftForcePos, leftForce)
    Body.applyForce(rbt, rightForcePos, rightForce)
}