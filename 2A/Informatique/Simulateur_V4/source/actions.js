function updateActionInspector(n) {
    let section = document.querySelector(".section[data-section-name='Actionneurs']");
    section.setAttribute("data-n", n);

    section.innerHTML = `<div class="label">Actions à l'arrêt</div>
    <div class="on-site action-list"></div>
    <div class="label">Actions en mouvement</div>
    <div class="on-move action-list"></div>`;

    let onSiteList = section.querySelector(".on-site.action-list");
    if (onSiteActions[n] == null) {
        onSiteActions[n] = [];
    }
    for (let action of onSiteActions[n]) {
        onSiteList.innerHTML += `<div class="on-site action">${action}</div>`
    }

    setTimeout(() => {
        section.querySelectorAll(".on-site.action").forEach((actionButton, i) => {
            actionButton.addEventListener("click", () => {
                onSiteActions[n] = onSiteActions[n].filter((el, j) => i != j);
                updateActionInspector(n);
            })
        })
    }, 0);

    let onMoveList = section.querySelector(".on-move.action-list");
    if (onMoveActions[n] == null) {
        onMoveActions[n] = [];
    }
    for (let action of onMoveActions[n]) {
        onMoveList.innerHTML += `<div class="on-move action">${action}</div>`
    }

    setTimeout(() => {
        section.querySelectorAll(".on-move.action").forEach((actionButton, i) => {
            actionButton.addEventListener("click", () => {
                onMoveActions[n] = onMoveActions[n].filter((el, j) => i != j);
                updateActionInspector(n);
            })
        })
    }, 0);

    section.querySelectorAll(".action-list").forEach((list) => {
        list.innerHTML += `<div class="add-action">+</div>`;
    });

    section.querySelector(".on-site.action-list .add-action").addEventListener("click", () => {
        let action = window.prompt("Action à ajouter :", "0x");
        if (action && action.trim()) {
            onSiteActions[n].push(action);
            updateActionInspector(n);
        }
    })

    section.querySelector(".on-move.action-list .add-action").addEventListener("click", () => {
        let action = window.prompt("Action à ajouter :", "0x");
        if (action && action.trim()) {
            onMoveActions[n].push(action);
            updateActionInspector(n);
        }
    })

    section.classList.remove("disabled");
}

function disableActionInspector() {
    let section = document.querySelector(".section[data-section-name='Actionneurs']");

    section.classList.add("disabled");
}