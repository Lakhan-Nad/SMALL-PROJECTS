var colorArr = [
    "white",
    "red",
    "blue",
    "black",
    "yellow",
    "green",
    "orange",
    "brown",
    "rebeccapurple",
];
var totalRow = 10;
var bothCorrect = "black";
var oneCorrect = "red";
var curGame = {
    active_row: 0,
    colorStates: [],
    cols: 0,
    isSpace: true,
    isRepeat: false
};
function putColor() {
    var row = this.parentNode.rowIndex;
    if (row == curGame.active_row) {
        var next = this.getAttribute("presentCol");
        next = (next + 1) % colorArr.length;
        // console.log(next);
        this.style.backgroundColor = colorArr[next];
        this.setAttribute("presentCol", next);
    }
}
function buildGuess() {
    var l = 1, r = colorArr.length;
    if (curGame.isSpace) {
        l = 0;
    }
    var states = [];
    var guess;
    while (states.length != curGame.cols) {
        guess = Math.floor(Math.random() * (r - l)) + l;
        if (!curGame.isRepeat) {
            if (states.indexOf(colorArr[guess]) != -1)
                continue;
        }
        states.push(colorArr[guess]);
    }
    return states;
}
function buildPin() {
    var pinMark = document.createElement("table");
    var rowObj;
    var colObj;
    for (var i = 0; i < 2; i++) {
        rowObj = document.createElement("tr");
        pinMark.append(rowObj);
        for (var j = 0; j < curGame.cols / 2; j++) {
            colObj = document.createElement("td");
            colObj.classList.add("pinColors");
            rowObj.append(colObj);
        }
    }
    return pinMark;
}
function buildBoard() {
    var table = document.getElementById("gameTable");
    table.innerHTML = "";
    var rowObj;
    var colObj;
    for (var i = 0; i < totalRow; i++) {
        rowObj = document.createElement("tr");
        table.append(rowObj);
        for (var j = 0; j < curGame.cols; j++) {
            colObj = document.createElement("td");
            colObj.classList.add("emptyColors");
            colObj.addEventListener("click", putColor);
            colObj.setAttribute("presentCol", "0");
            rowObj.append(colObj);
        }
        colObj = document.createElement("td");
        // colObj.classList.add("pinTable");
        colObj.append(buildPin());
        rowObj.append(colObj);
    }
    return;
}
function buildRevealed() {
    var table = document.getElementById("hiddenColors");
    table.innerHTML = "";
    var rowObj = document.createElement("tr");
    table.append(rowObj);
    var colObj;
    for (var i = 0; i < curGame.cols; i++) {
        colObj = document.createElement("td");
        colObj.classList.add("guessColors");
        colObj.style.backgroundColor = curGame.colorStates[i];
        colObj.innerText = "";
        rowObj.append(colObj);
    }
    return;
}
function buildHidden() {
    var table = document.getElementById("hiddenColors");
    table.innerHTML = "";
    var rowObj = document.createElement("tr");
    table.append(rowObj);
    var colObj;
    for (var i = 0; i < curGame.cols; i++) {
        colObj = document.createElement("td");
        colObj.classList.add("guessColors");
        colObj.style.backgroundColor = colorArr[0];
        colObj.innerText = "?";
        rowObj.append(colObj);
    }
    return;
}
function createColors() {
    var table = document.getElementById("colorPallete");
    table.innerHTML = "";
    var rowObj;
    var colObj;
    for (var i = 0; i < 2; i++) {
        rowObj = document.createElement("tr");
        table.append(rowObj);
        for (var j = 0; j < 4; j++) {
            colObj = document.createElement("td");
            colObj.classList.add("colorsSet");
            colObj.style.backgroundColor = colorArr[i * 4 + j + 1];
            rowObj.append(colObj);
        }
    }
}
function wonGame() {
    buildRevealed();
    return; // Add Game Won
}
function lostGame() {
    buildRevealed();
    return; // Add Game Lost
}
function upgrade() {
    curGame.active_row--;
    if (curGame.active_row < 0) {
        lostGame();
    }
    return;
}
function addPins(wCount, rCount) {
    var pinMark = document.getElementById("gameTable").rows[curGame.active_row].cells[curGame.cols]
        .firstChild;
    var objArray = [];
    var correct = rCount;
    for (var i = 0; i < 2; i++) {
        for (var j = 0; j < curGame.cols / 2; j++) {
            objArray.push(pinMark.rows[i].cells[j]);
        }
    }
    var x = 0;
    while (rCount--) {
        objArray[x].style.backgroundColor = bothCorrect;
        x++;
    }
    while (wCount--) {
        objArray[x].style.backgroundColor = oneCorrect;
        x++;
    }
    if (correct == curGame.cols) {
        wonGame();
    }
    else {
        upgrade();
    }
}
function countColors() {
    var colors = [];
    var temObj = document.getElementById("gameTable").rows[curGame.active_row];
    var temp;
    var rCount = 0;
    var wCount = 0;
    for (var i = 0; i < curGame.cols; i++) {
        temp = temObj.cells[i].style.backgroundColor;
        colors.push(temp);
    }
    for (var i = 0; i < curGame.cols; i++) {
        if (colors[i] == curGame.colorStates[i]) {
            colors[i] = undefined;
            rCount++;
        }
    }
    for (var i = 0; i < curGame.cols; i++) {
        if (colors[i] == undefined)
            continue;
        else {
            for (var j = 0; j < curGame.cols; j++) {
                if (colors[j] == curGame.colorStates[i]) {
                    colors[j] = colors[i];
                    colors[i] = undefined;
                    wCount++;
                }
            }
        }
    }
    addPins(wCount, rCount);
}
function correctOrNot() {
    var temObj = document.getElementById("gameTable").rows[curGame.active_row];
    var r = colorArr.length;
    var l = 1;
    var temp;
    if (curGame.isSpace) {
        l--;
    }
    for (var i = 0; i < curGame.cols; i++) {
        temp = colorArr.indexOf(temObj.cells[i].style.backgroundColor);
        if (temp < l || temp >= r) {
            return; // Add that rows not completely filled
        }
    }
    countColors();
}
function startNew() {
    curGame.isRepeat = document.getElementById("repeatAllowed").checked;
    curGame.isSpace = document.getElementById("spaceAllowed").checked;
    curGame.cols = document.getElementById("colsCount")
        .value;
    curGame.colorStates = buildGuess();
    curGame.active_row = totalRow - 1; // Initial Row;
    buildHidden();
    buildBoard();
    createColors();
    // console.log(curGame);
    return;
}
