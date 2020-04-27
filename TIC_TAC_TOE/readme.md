## TIC_TAC_TOE

Contain a class named _Game_
Using this class any tic_tac_toe game can be stimulated
It has configured status code for each game status and various puvlic functions to control game flow

### Constructors

    - Game() : Initializes player1 with 'O' and player2 with 'X'
    - Game(int) : Let choose 'O' or 'X' for player1. 0 for 'O' and 1 for 'X'

### Public Functions

    - void reset() : To reset the board
    - int status() : Returns Current status of game
    - int move(int) : Plays the move for current player. Takes 0-8 denoting position in board. Returns status of game
    - int undo() : Undos last move. Return status after undo
    - void printCurrentBoard() : Print current board configuration
    - void availPos(int []) : copy array of empty positions [i if position i is empty -1 otherwise].
    - void currentBoard(char[3][3]) : return copy of current borad status

### Public Members

    - char icon1 : Contains icon value of player1
    - char icon2 : Contains icon value of player2

### Status Codes

    - START_GAME : 0
    - PLAYER_1_CHANCE : 1
    - PLAYER_2_CHANCE : 2
    - MOVE_PLAYED : 3
    - ILLEGAL_MOVE : 4
    - PLAYER_1_WINS : 5
    - PLAYER_2_WINS : 6
    - GAME_DRAWN : 7
    - GAME_OVER : 8

## ttt_comp

This files have stimulated TIC TAC TOE game using Game class

Minimax algo with alpha beta pruning is used to stimulate computers play.
