$(".flip.button").on("mouseenter", showSymetryLine);
$(".flip.button").on("mouseleave", hideSymetryLine);
$(".flip.button").click(e => {
    let button = e.target;
    if (!$(button).hasClass("disabled"))
        applySymetry()
});

$(".export.button").click(() => {
    navigator.clipboard.writeText(generateStrategyCode());
})

$(".help.button").click(() => {
    $(".help.pane").show()
})

$(".load.button").click(() => {
    $(".list.pane").show()
})

$(".add.button").click(() => {
    askForName(true, name => {
        if (name)
            addNewStrategy(name);
        else
            console.log("User canceled.")
    })
})

$(".dialog-container .dialog input").on("input", (e) => {
    let createButton = $(".dialog-container .dialog .create.button");
    if (e.currentTarget.value) {
        createButton.removeClass("disabled");
    } else {
        createButton.addClass("disabled");
    }
})

$(".dialog-container .dialog input").on("keyup", e2 => {
    if (e2.keyCode === 13) {  // enter key
        let createButton = $(".dialog-container .dialog .create.button");
        e2.preventDefault()
        createButton.click();
    }
})