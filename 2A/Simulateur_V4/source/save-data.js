openRecentStrat();

function askForName(allowCancel, callback) {
    document.querySelector(".dialog-container").style = "display: flex;";
    dialogOpen = true;
    let input = document.querySelector(".dialog-container input")
    input.value =  "";
    input.focus()
    let createButton = $(".dialog-container .dialog .create.button");
    createButton.addClass("disabled");
    let cancelButton = $(".dialog-container .dialog .cancel.button");
    if (allowCancel) {
        cancelButton.removeClass("disabled");
    } else {
        cancelButton.addClass("disabled");
    }
    createButton.off("click");
    createButton.click(e => {
        if (e.currentTarget.classList.contains("disabled")) return;
        document.querySelector(".dialog-container").style = "display: none;";
        dialogOpen = false;
        callback(input.value);
    })
    cancelButton.off("click");
    cancelButton.click(e => {
        if (e.currentTarget.classList.contains("disabled")) return;
        document.querySelector(".dialog-container").style = "display: none;";
        dialogOpen = false;
        callback(null);
    })
}


function updateStrategyHTMLList() {
    $(".list.pane .list").empty()
    let jsonLocalData = localStorage.getItem("strats");
    let savedData = JSON.parse(jsonLocalData);
    for (let strat of savedData.strats) {
        $(".list.pane .list").append(`
        <div class="saved-item">
            <span class="name">${strat.name}</span>
            <span class="delete expand-button">Supprimer</span>
            <span class="duplicate expand-button">Dupliquer</span>
        </div>`)
    }
    $($(".list.pane .list .saved-item")[savedData.openedStategy]).addClass("selected")
    $(".list.pane .list .saved-item").each((i, item) => {
        $(item).click(e => {
            switchStrats(i)
        })
    })
    $(".list.pane .list .saved-item .delete.expand-button").each((i, item) => {
        $(item).click(e => {
            deleteStrat(i)
        })
    })
    $(".list.pane .list .saved-item .duplicate.expand-button").each((i, item)  => {
        $(item).click(e => {
            duplicateStrat(i);
        })
    })
}

function addNewStrategy(name) {
    let jsonLocalData = localStorage.getItem("strats");
    let savedData = JSON.parse(jsonLocalData);
    savedData.strats.push({
        name, 
        pathPoints: [[100, 100, 200, 100, 300, 100, 400, 100]],
        speeds: {},
        shouldReverse: {},
        onSiteActions: {},
        onMoveActions: {}
    })
    localStorage.setItem("strats", JSON.stringify(savedData));
    switchStrats();
}

function saveState() {
    let jsonLocalData = localStorage.getItem("strats");
    let savedData = JSON.parse(jsonLocalData);
    savedData.userSettings = userSettings;
    savedData.strats[savedData.openedStategy].pathPoints = path.map(b => 
        b.points.map(p => [p.x, p.y]).flat()
    );
    savedData.strats[savedData.openedStategy].speeds = speeds;
    savedData.strats[savedData.openedStategy].shouldReverse = shouldReverse;
    savedData.strats[savedData.openedStategy].onSiteActions = onSiteActions;
    savedData.strats[savedData.openedStategy].onMoveActions = onMoveActions;
    localStorage.setItem("strats", JSON.stringify(savedData));
}

setInterval(() => {
    saveState()
}, 500);

function openRecentStrat() {
    let jsonLocalData = localStorage.getItem("strats");
    let savedData = JSON.parse(jsonLocalData);
    if (savedData == null) {
        savedData = {
            strats: [{
                name: "Default",
                pathPoints: [[100, 100, 200, 100, 300, 100, 400, 100]],
                speeds: {},
                shouldReverse: {},
                onSiteActions: {},
                onMoveActions: {}
            }],
            openedStategy: 0
        }
        localStorage.setItem("strats", JSON.stringify(savedData));
    }
    switchStrats(savedData.openedStategy);
}

function switchStrats(n) {
    let jsonLocalData = localStorage.getItem("strats");
    let savedData = JSON.parse(jsonLocalData);
    if (n == null)
        n = savedData.strats.length - 1;
    let pathPoints = savedData.strats[n].pathPoints;
    path = [];
    for (let pp of pathPoints) {
        path.push(new Bezier(...pp))
    }
    savedData.openedStategy = n;
    speeds = savedData.strats[savedData.openedStategy].speeds ?? {};
    shouldReverse = savedData.strats[savedData.openedStategy].shouldReverse ?? {};
    onSiteActions = savedData.strats[savedData.openedStategy].onSiteActions ?? {};
    onMoveActions = savedData.strats[savedData.openedStategy].onMoveActions ?? {};
    document.querySelector(".title-bar .title").innerText = savedData.strats[savedData.openedStategy].name;
    localStorage.setItem("strats", JSON.stringify(savedData));
    updateStrategyHTMLList();
    updateHTMLList();
    selectionTool.pickUp();
}

function deleteStrat(n) {
    let jsonLocalData = localStorage.getItem("strats");
    let savedData = JSON.parse(jsonLocalData);
    savedData.strats.splice(n, 1);
    
    if (savedData.openedStategy <= n) {
        savedData.openedStategy = max(0, savedData.openedStategy - 1);
    }
    if (savedData.strats.length === 0) {
        askForName(false, name => {
            localStorage.setItem("strats", JSON.stringify(savedData));
            addNewStrategy(name);
        });
    } else {
        localStorage.setItem("strats", JSON.stringify(savedData));
        points = savedData.strats[savedData.openedStategy].points;
        updateStrategyHTMLList();
        selectionTool.pickUp();
    }
}

function duplicateStrat(n) {
    let jsonLocalData = localStorage.getItem("strats");
    let savedData = JSON.parse(jsonLocalData);
    
    askForName(false, name => {
        let item = JSON.parse(JSON.stringify(savedData.strats[n]));
        item.name = name;
        savedData.strats.splice(n+1, 0, item);
        localStorage.setItem("strats", JSON.stringify(savedData));
        updateStrategyHTMLList();
    });
}


