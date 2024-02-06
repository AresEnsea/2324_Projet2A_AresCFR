$(".pane .dialog .close-button").click(event => {
    $(event.target).parent().parent().hide()
})

$(".pane").click(event => {
    if ($(event.target).hasClass("pane"))
        $(event.target).hide()
})

function showSymetryLine() {
    showSym = true;
}

function hideSymetryLine() {
    showSym = false;
}

function setBodyColor(val) {
    $("body").css({ backgroundColor: "#" + val + val + val })
}

////////// Side Bar //////////

function updateHTMLList() {
    $(".positions").empty()
    $(".positions").append(`<tr class="noselect"><td></td><td>X (mm)</td><td>Y (mm)</td><td>Sens</td><td>Actionneurs</td></tr>`)
    for (let i = 0; i < points.length; i++) {
        let point = points[i]
        let x = point.x
        let y = point.y
        let line = ""
        line += `<tr class="noselect"><td>${i}</td><td>${x}</td><td>${y}</td>`
        if (i === 0)
            line += `<td>-</td><td>`
        else
            line += `<td>${point.r?"<span class='flip'>➜</span>":"<span>➜</span>"}</td><td>`
        let subline = ""
        for (let name in point.actions) {
            if (point.actions[name])
                subline += `<span class="smalltext">${name}</span>`
        }
        if (subline === "") subline = "-"
        line += subline
        line += `</tr>`
        $(".positions").append(line)
    }
    $(".positions tr").click(event => {
        if (tool != "eraser") {
            let target = $(event.target).parent();
            let n = target.index() - 1;
            if (n === -1) return;
            $(".positions tr").removeClass("preselected selected")
            target.addClass("selected")
            $($(".positions tr")[n]).addClass("preselected")
            setSelection(n);
        }
    }).on("mouseenter", event => {
        let target = $(event.target).parent();
        let n = target.index() - 1;
        if (n === -1) return;
        $(".positions tr").removeClass("hovered")
        target.addClass("hovered")
        hoveredIndex = n;
    }).on("mouseleave", event => {
        $(event.target).parent().removeClass("hovered")
        hoveredIndex = -1
    })
}

$(".simulation .reset.button").click(() => {
    setupSimulation()
    updateCamera(true)
})

$(".simulation .run.button").click(() => {
    simulationRunning = true;
    if (simulationStopped) {
        simulationStopped = false;
        startTimestamp = engine.timing.timestamp
    } else {
        startTimestamp += engine.timing.timestamp - pauseTimestamp
    }
})

$(".simulation .stop.button").click(() => {
    simulationRunning = false;
    simulationStopped = true;
    setupSimulation()
})

$(".simulation .pause.button").click(() => {
    simulationRunning = false;
    pauseTimestamp = engine.timing.timestamp
})

$(".side-bar-toggle.button").click(() => {
    $("body").toggleClass("side-bar-hidden")

    let start;
    function step(timestamp) {
        if (start === undefined)
            start = timestamp;
        const elapsed = timestamp - start;

        windowResized()

        if (elapsed < 500) { // Stop the animation after 2 seconds
            window.requestAnimationFrame(step);
        }
    }
    window.requestAnimationFrame(step)
})

$(".zoom-in.button").click(() => {
    editModeCameraAim.k *= 1.2
    $(".zoom-out.button").removeClass("disabled")
    if (editModeCameraAim.k > 10) {
        editModeCameraAim.k = 10;
        $(".zoom-in.button").addClass("disabled")
    }
})

$(".zoom-out.button").click(() => {
    editModeCameraAim.k /= 1.2
    $(".zoom-in.button").removeClass("disabled")
    if (editModeCameraAim.k < 0.5) {
        editModeCameraAim.k = 0.5; 
        $(".zoom-out.button").addClass("disabled")
    }
})

$(".home.button").click(() => {
    editModeCameraAim = { x: 1500, y: 1000, k: 1, a: 0 }
    $(".zoom-in.button").removeClass("disabled")
    $(".zoom-out.button").removeClass("disabled")
})

$(".button-list.options .button").click((e) => {
    let button = e.target
    if ($(button).hasClass("disabled")) return
    $(button).siblings().removeClass("selected")
    $(button).addClass("selected")
    let key = $(button).parent().attr("data-key")
    let value = parseFloat($(button).attr("data-value"));
    userSettings[key] = value;
    if (key === "pixelDensity") {
        pixelDensity(displayDensity() * userSettings[key])
    } else if (key === "translationType") {
        let rotButtons = $(".button-list[data-key='rotationType'] .button," +
            ".button-list[data-key='zoomAmount'] .button");
        if (value === 0)
            rotButtons.addClass("disabled")
        else
            rotButtons.removeClass("disabled")
    } else if (key === "displayBackground") {

    } else if (key === "simQuality") {

    }
})

function applyUserSettings() {
    $(".button-list.options").each((i, l) => {
        let key = $(l).attr("data-key");
        $(l).children(".button").removeClass("selected")
        let value = userSettings[key];
        $(l).children(`.button[data-value="${value}"]`).addClass("selected")
    })
}

function updateSimulationIndicators() {
    if (frameCount % 20 === 0) {
        $("#p5-fps .value").text(round(frameRate()) + " fps")
        $("#matter-fps .value").text(round(frameRate() * 20) + " Hz")
    }
    if (simulationRunning) {
        $("#time .value").text(round((engine.timing.timestamp - startTimestamp) / 1000, 2).toFixed(2) + " s")
    }
}

function updatePathInspector(reverse, speed, n) {
    document.querySelector(".indicator#speed .value").innerText = speed + " mm/s";
    document.querySelector("#speed-picker").disabled = false;
    document.querySelector("#speed-picker").value = speed;
    let buttons = document.querySelector(".button-list[data-key='direction']");
    buttons.querySelectorAll(".button").forEach(button => {
        button.classList.remove("disabled");
    });
    if (reverse) {
        buttons.querySelector("[data-value='forward']").classList.remove("selected");
        buttons.querySelector("[data-value='backward']").classList.add("selected");
    } else {
        buttons.querySelector("[data-value='forward']").classList.add("selected");
        buttons.querySelector("[data-value='backward']").classList.remove("selected");
    }
    document.querySelector(`.inspector.section[data-section-name="Parcours"]`).setAttribute("data-n", n);
}

function disablePathInspector() {
    document.querySelector(".indicator#speed .value").innerText = "";
    document.querySelector("#speed-picker").disabled = true;
    let buttons = document.querySelector(".button-list[data-key='direction']");
    buttons.querySelectorAll(".button").forEach(button => {
        button.classList.add("disabled");
    });
}

document.querySelector("#speed-picker").addEventListener("input", () => {
    let speed = document.querySelector("#speed-picker").value;
    document.querySelector(".indicator#speed .value").innerText = speed + " mm/s";
    let n = Number(document.querySelector(`.inspector.section[data-section-name="Parcours"]`).getAttribute("data-n"));
    speeds[n] = speed;
    if (speed != 0 && n > 0 && n < path.length) {
        makeSymetric(path[n-1].points[2], path[n-1].points[3], path[n].points[1])
    }
})

document.querySelectorAll(".button-list[data-key='direction'] .button").forEach(button => {
    button.addEventListener("click", () => {
        if (button.classList.contains("disabled")) return;
        let n = document.querySelector(`.inspector.section[data-section-name="Parcours"]`).getAttribute("data-n");
        shouldReverse[n] = button.getAttribute("data-value") === "backward";
    })
})

//////// robot svg interactivity ////////

$(document).ready(() => {
    for (let name of ["nw", "ne", "sw", "se", "bras"]) {
        $(`svg#robot rect#${name}-rect`).click(() => {
            $(`svg#robot rect#${name}-rect`).toggleClass("active")
            if (selectedIndex >= 0) {
                let point = points[selectedIndex]
                if (point.actions[name])
                    delete point.actions[name]
                else
                    point.actions[name] = true
                updateHTMLList()
            }
        })
    }
})

//////// p5 Events /////////

function windowResized() {
    resizeCanvas(windowWidth, windowHeight)
    windowTransform = getWindowTranform()
}

function mousePressed(event) {
    if ($(event.target).prop("tagName") != "CANVAS")
        return true
    currentTool.mousePressed(event);
}

function mouseDragged(event) {
    if ($(event.target).prop("tagName") != "CANVAS")
        return true
    currentTool.mouseDragged(event);
}

function mouseMoved(event) {
    if ($(event.target).prop("tagName") != "CANVAS")
        return true
    currentTool.mouseMoved(event);
}

function mouseReleased(event) {
    if ($(event.target).prop("tagName") != "CANVAS")
        return true
    currentTool.mouseReleased(event);
}

function mouseWheel(event) { 
    if (event.ctrlKey && currentTool.name !== "simulation") {
        editModeCameraAim.k /= pow(1.007, event.deltaY);
        if (editModeCameraAim.k >= 40) {
            editModeCameraAim.k = 40;
            $(".zoom-in.button").addClass("disabled")
        } else
            $(".zoom-in.button").removeClass("disabled")
        if (editModeCameraAim.k <= 0.5) {
            editModeCameraAim.k = 0.5; 
            $(".zoom-out.button").addClass("disabled")
        } else
            $(".zoom-out.button").removeClass("disabled")
    } else {
        let millis = linearPixelsToMillis(event.deltaX, event.deltaY);
        editModeCameraAim.x += millis.x;
        editModeCameraAim.y += millis.y;
        updateCamera(true)
    }

    return false;
}

function keyPressed(event) {
    if (dialogOpen) 
        return true;

    altPressed = event.altKey;
    shiftPressed = event.shiftKey;
    ctrlOrCommandPressed = ctrlOrCommand(event);

    // if (currentTool.name !== "simulation") {
    //     if (ctrlOrCommandPressed)
    //         cursor("grab")
    //     else {
    //         cursor(ARROW)
    //     }
    // }
    currentTool.keyPressed(event);
    if (event.key === " ") {
        if (currentTool.name !== "simulation") {
            if (path.length >= 1) {
                simulationTool.pickUp();
            }
        } else {
            simulationRunning = !simulationRunning;
        }
    }

    if (event.key.toLowerCase() === "s") {
        if (currentTool.name === "selection")
            simulationTool.pickUp();
        else {
            if (event.shiftKey) {
                editModeCameraAim.x = simulationCameraAim.x
                editModeCameraAim.y = simulationCameraAim.y
                editModeCameraAim.k = simulationCameraAim.k
            }
            selectionTool.pickUp();
        }
    }

    if (event.key === "Enter") {
        setupSimulation();
        updateCamera(true);
    }
    return false;
}

function keyReleased(event) {
    altPressed = event.altKey;
    shiftPressed = event.shiftKey;
    ctrlOrCommandPressed = ctrlOrCommand(event);
    if (currentTool.name !== "simulation" && !ctrlOrCommandPressed)
        cursor(ARROW)
}