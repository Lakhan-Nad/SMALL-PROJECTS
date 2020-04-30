interface GameIf {
  active_row: number;
  colorStates: string[];
  cols: number;
  isSpace: boolean;
  isRepeat: boolean;
}

const colorArr: string[] = [
  "white", // Same as space color
  "red",
  "blue",
  "black",
  "yellow",
  "green",
  "orange",
  "brown",
  "rebeccapurple",
];

const totalRow: number = 10;
const bothCorrect: string = "black";
const oneCorrect: string = "red";

let curGame: GameIf = {
  active_row: 0,
  colorStates: [],
  cols: 0,
  isSpace: true,
  isRepeat: false,
};

function putColor() {
  let row: number = this.parentNode.rowIndex;
  if (row == curGame.active_row) {
    let next: number = (this.getAttribute("presentCol") as unknown) as number;
    next = (next + 1) % colorArr.length;
    // console.log(next);
    this.style.backgroundColor = colorArr[next];
    this.setAttribute("presentCol", <string>(next as unknown));
  }
}

function buildGuess(): string[] {
  let l: number = 1,
    r: number = colorArr.length;
  if (curGame.isSpace) {
    l = 0;
  }
  let states: string[] = [];
  let guess: number;
  while (states.length != curGame.cols) {
    guess = Math.floor(Math.random() * (r - l)) + l;
    if (!curGame.isRepeat) {
      if (states.indexOf(colorArr[guess]) != -1) continue;
    }
    states.push(colorArr[guess]);
  }
  return states;
}

function buildPin(): any {
  let pinMark: HTMLTableElement = document.createElement("table");
  let rowObj: HTMLTableRowElement;
  let colObj: HTMLTableDataCellElement;
  for (let i: number = 0; i < 2; i++) {
    rowObj = document.createElement("tr");
    pinMark.append(rowObj);
    for (let j: number = 0; j < curGame.cols / 2; j++) {
      colObj = document.createElement("td");
      colObj.classList.add("pinColors");
      rowObj.append(colObj);
    }
  }
  return pinMark;
}

function buildBoard(): void {
  let table: HTMLTableElement = document.getElementById(
    "gameTable"
  ) as HTMLTableElement;
  table.innerHTML = "";
  let rowObj: HTMLTableRowElement;
  let colObj: HTMLTableDataCellElement;
  for (let i: number = 0; i < totalRow; i++) {
    rowObj = document.createElement("tr");
    table.append(rowObj);
    for (let j: number = 0; j < curGame.cols; j++) {
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

function buildRevealed(): void {
  let table: HTMLTableElement = document.getElementById(
    "hiddenColors"
  ) as HTMLTableElement;
  table.innerHTML = "";
  let rowObj: HTMLTableRowElement = document.createElement("tr");
  table.append(rowObj);
  let colObj: HTMLTableDataCellElement;
  for (let i: number = 0; i < curGame.cols; i++) {
    colObj = document.createElement("td");
    colObj.classList.add("guessColors");
    colObj.style.backgroundColor = curGame.colorStates[i];
    colObj.innerText = "";
    rowObj.append(colObj);
  }
  return;
}

function buildHidden(): void {
  let table: HTMLTableElement = document.getElementById(
    "hiddenColors"
  ) as HTMLTableElement;
  table.innerHTML = "";
  let rowObj: HTMLTableRowElement = document.createElement("tr");
  table.append(rowObj);
  let colObj: HTMLTableDataCellElement;
  for (let i: number = 0; i < curGame.cols; i++) {
    colObj = document.createElement("td");
    colObj.classList.add("guessColors");
    colObj.style.backgroundColor = colorArr[0];
    colObj.innerText = "?";
    rowObj.append(colObj);
  }
  return;
}

function createColors() {
  let table: HTMLTableElement = document.getElementById(
    "colorPallete"
  ) as HTMLTableElement;
  table.innerHTML = "";
  let rowObj: HTMLTableRowElement;
  let colObj: HTMLTableDataCellElement;
  for (let i: number = 0; i < 2; i++) {
    rowObj = document.createElement("tr");
    table.append(rowObj);
    for (let j: number = 0; j < 4; j++) {
      colObj = document.createElement("td");
      colObj.classList.add("colorsSet");
      colObj.style.backgroundColor = colorArr[i * 4 + j + 1];
      rowObj.append(colObj);
    }
  }
}

function wonGame(): void {
  buildRevealed();
  return; // Add Game Won
}

function lostGame(): void {
  buildRevealed();
  return; // Add Game Lost
}
function upgrade(): void {
  curGame.active_row--;
  if (curGame.active_row < 0) {
    lostGame();
  }
  return;
}

function addPins(wCount: number, rCount: number): void {
  let pinMark: HTMLTableElement = (document.getElementById(
    "gameTable"
  ) as HTMLTableElement).rows[curGame.active_row].cells[curGame.cols]
    .firstChild as HTMLTableElement;
  let objArray: HTMLTableDataCellElement[] = [];
  let correct: number = rCount;
  for (let i: number = 0; i < 2; i++) {
    for (let j: number = 0; j < curGame.cols / 2; j++) {
      objArray.push(pinMark.rows[i].cells[j]);
    }
  }
  let x: number = 0;
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
  } else {
    upgrade();
  }
}

function countColors(): void {
  let colors: string[] = [];
  let temObj: HTMLTableRowElement = (document.getElementById(
    "gameTable"
  ) as HTMLTableElement).rows[curGame.active_row];
  let temp: string;
  let rCount: number = 0;
  let wCount: number = 0;
  for (let i: number = 0; i < curGame.cols; i++) {
    temp = temObj.cells[i].style.backgroundColor;
    colors.push(temp);
  }
  for (let i: number = 0; i < curGame.cols; i++) {
    if (colors[i] == curGame.colorStates[i]) {
      colors[i] = undefined;
      rCount++;
    }
  }
  for (let i: number = 0; i < curGame.cols; i++) {
    if (colors[i] == undefined) continue;
    else {
      for (let j: number = 0; j < curGame.cols; j++) {
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

function correctOrNot(): void {
  let temObj: HTMLTableRowElement = (document.getElementById(
    "gameTable"
  ) as HTMLTableElement).rows[curGame.active_row];
  let r: number = colorArr.length;
  let l: number = 1;
  let temp: number;
  if (curGame.isSpace) {
    l--;
  }
  for (let i: number = 0; i < curGame.cols; i++) {
    temp = colorArr.indexOf(temObj.cells[i].style.backgroundColor);
    if (temp < l || temp >= r) {
      return; // Add that rows not completely filled
    }
  }
  countColors();
}

function startNew(): void {
  curGame.isRepeat = (document.getElementById(
    "repeatAllowed"
  ) as HTMLInputElement).checked;
  curGame.isSpace = (document.getElementById(
    "spaceAllowed"
  ) as HTMLInputElement).checked;
  curGame.cols = ((document.getElementById("colsCount") as HTMLSelectElement)
    .value as unknown) as number;
  curGame.colorStates = buildGuess();
  curGame.active_row = totalRow - 1; // Initial Row;
  buildHidden();
  buildBoard();
  createColors();
  // console.log(curGame);
  return;
}
