#include <cstdio>
#include <cstring>

enum Messages {
  START_GAME,
  PLAYER_1_CHANCE,
  PLAYER_2_CHANCE,
  MOVE_PLAYED,
  ILLEGAL_MOVE,
  PLAYER_1_WINS,
  PLAYER_2_WINS,
  GAME_DRAWN,
  GAME_OVER,
};

struct Game {
 private:
  char board[3][3];
  char players[2];
  int chance;
  int current;
  int stack[9];
  bool isWin;
  void set(int);
  bool checkWin();
  int nextMove();

 public:
  char icon1, icon2;
  Game();
  Game(int);
  void reset();
  int status();
  int move(int);
  int undo();
  void printCurrentBoard();
  void availPos(int[]);
  void currentBoard(char[][3]);
  ~Game() {}
};  // End of Defination

/* Constructor */

Game::Game() { Game::set(0); }
Game::Game(int ch) { Game::set(ch); }

/* Private Functions */

void Game::set(int start_char) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      board[i][j] = 3 * i + j + '0';
    }
  }
  players[0] = 'O';
  players[1] = 'X';
  chance = 0;
  current = start_char % 2;
  icon1 = players[current];
  icon2 = players[current ^ 1];
  isWin = false;
}

bool Game::checkWin() {
  if (board[0][0] == board[0][1] && board[0][1] == board[0][2]) {
    return true;
  }
  if (board[1][0] == board[1][1] && board[1][1] == board[1][2]) {
    return true;
  }
  if (board[2][0] == board[2][1] && board[2][1] == board[2][2]) {
    return true;
  }
  if (board[0][0] == board[1][0] && board[1][0] == board[2][0]) {
    return true;
  }
  if (board[0][1] == board[1][1] && board[1][1] == board[2][1]) {
    return true;
  }
  if (board[0][2] == board[1][2] && board[1][2] == board[2][2]) {
    return true;
  }
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
    return true;
  }
  if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
    return true;
  }
  return false;
}

int Game::nextMove() {
  if (chance % 2 == 0)
    return Messages::PLAYER_1_CHANCE;
  else
    return Messages::PLAYER_2_CHANCE;
}

/* Public Functions */

void Game::reset() {
  for (int i = 0; i < chance; i++) {
    current ^= 1;
  }
  Game::set(current);
}

int Game::status() {
  if (chance < 5) {
    return Game::nextMove();
  } else {
    if (!Game::checkWin()) {
      isWin = false;
      if (chance < 9)
        return Game::nextMove();
      else
        return Messages::GAME_DRAWN;
    } else {
      isWin = true;
      if (chance % 2)
        return Messages::PLAYER_1_WINS;
      else
        return Messages::PLAYER_2_WINS;
    }
  }
}

int Game::move(int pos) {
  if (chance >= 9 || isWin) {
    return Messages::GAME_OVER;
  }
  pos = pos % 9;
  char boardPos = board[pos / 3][pos % 3];
  if (boardPos < '0' || boardPos >= '9') {
    return Messages::ILLEGAL_MOVE;
  }
  board[pos / 3][pos % 3] = players[current];
  stack[chance] = pos;
  chance++;
  current ^= 1;
  return Messages::MOVE_PLAYED;
}

int Game::undo() {
  if (chance == 0) {
    return Messages::START_GAME;
  } else {
    int pos = stack[chance - 1];
    board[pos / 3][pos % 3] = pos + '0';
    chance--;
    current ^= 1;
    return Game::status();
  }
}

void Game::printCurrentBoard() {
  std::printf("\n");
  for (int i = 0; i < 3; i++) {
    std::printf("%c %c %c", board[i][0], board[i][1], board[i][2]);
    std::printf("\n");
  }
  std::printf("\n");
}

void Game::availPos(int arr[9]) {
  int j = 0;
  for (int i = 0; i < 9; i++) {
    if (board[i / 3][i % 3] >= '0' && board[i / 3][i % 3] <= '9') {
      arr[i] = i;
    } else {
      arr[i] = -1;
    }
  }
}

void Game::currentBoard(char copyBoard[3][3]) {
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) copyBoard[i][j] = board[i][j];
}
