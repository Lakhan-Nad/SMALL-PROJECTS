/* Impot Tic Tac Toe Game Class */
#include "./tic_tac_toe.cpp"

Game curGame;  // A game instance
char board[3][3];
char max, min;

/* Constants */
#define maxi 100
#define mini -100
#define maxDepth 9
#define NINF -100000
#define INF 100000

/* Heruistic Function to return board status */
int evalBoard() {
  if (board[0][0] == board[0][1] && board[0][1] == board[0][2]) {
    return board[0][0] == max ? maxi : mini;
  }
  if (board[1][0] == board[1][1] && board[1][1] == board[1][2]) {
    return board[1][0] == max ? maxi : mini;
  }
  if (board[2][0] == board[2][1] && board[2][1] == board[2][2]) {
    return board[2][0] == max ? maxi : mini;
  }
  if (board[0][0] == board[1][0] && board[1][0] == board[2][0]) {
    return board[0][0] == max ? maxi : mini;
  }
  if (board[0][1] == board[1][1] && board[1][1] == board[2][1]) {
    return board[0][1] == max ? maxi : mini;
  }
  if (board[0][2] == board[1][2] && board[1][2] == board[2][2]) {
    return board[0][2] == max ? maxi : mini;
  }
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
    return board[0][0] == max ? maxi : mini;
  }
  if (board[2][0] == board[1][1] && board[1][1] == board[0][2]) {
    return board[2][0] == max ? maxi : mini;
  }
  return 0;
}

/*  Minimax to find optimal move */
int minimax(int depth, bool maximizer, int alpha, int beta) {
  int score = evalBoard();
  if (score == maxi) {
    return (maxi - depth);
  }
  if (score == mini) {
    return (mini + depth);
  }
  if (depth >= maxDepth) {
    return score;
  }
  int best = maximizer ? NINF : INF;
  for (int i = 0; i < 9; i++) {
    if (board[i / 3][i % 3] == (char)(i + '0')) {
      board[i / 3][i % 3] = maximizer ? max : min;
      int call = minimax(depth + 1, !maximizer, alpha, beta);
      if (maximizer) {
        best = best > call ? best : call;
        alpha = alpha > best ? alpha : best;
      } else {
        best = best < call ? best : call;
        beta = beta < best ? beta : best;
      }
      board[i / 3][i % 3] = (char)(i + '0');
    }
    if (alpha >= beta) break;
  }
  return best;
}

/* Initial Call to the Minimax function */
int compPlays() {
  curGame.currentBoard(board);
  int depth = 9;
  int best = -1000;
  int move;
  for (int i = 0; i < 9; i++)
    if (board[i / 3][i % 3] == (char)(i + '0')) depth--;
  for (int i = 0; i < 9; i++) {
    if (board[i / 3][i % 3] == (char)(i + '0')) {
      board[i / 3][i % 3] = max;
      int val = minimax(depth + 1, false, NINF, INF);
      if (val > best) {
        best = val;
        move = i;
      }
      board[i / 3][i % 3] = (char)(i + '0');
    }
  }
  return move;
}

/* Function to stimulate Game Flow */
void Play() {
  curGame.reset();
  max = curGame.icon2;
  min = curGame.icon1;
  int move;
  while (curGame.status() < 5) {
    curGame.printCurrentBoard();
    if (curGame.status() == 1) {
      std::printf("Enter move: ");
      std::scanf("%d", &move);
      curGame.move(move);
    } else {
      move = compPlays();
      std::printf("Computer Played: %d\n", move);
      curGame.move(move);
    }
  }
  curGame.printCurrentBoard();
}

/* Main Function */
int main() {
  Play();
  return 0;
}
