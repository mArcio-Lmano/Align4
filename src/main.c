#include "include/ai.h"
// #include "include/gameboard.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  GameBoard *gameBoard = initializeGameBoard();
  Ai *ai = initializeAi();
  // printAi(ai);

  printBoard(gameBoard->board, gameBoard->rows, gameBoard->columns);
  int winner = 0;
  while (1) {
    int res = playPlayer(gameBoard, ai);
    if (res != -1) {
      printBoard(gameBoard->board, gameBoard->rows, gameBoard->columns);
      winner = checkWin(gameBoard);
      gameBoard->player *= -1;
      // NOTE: Debug
      ai->board = copyBoard(gameBoard->board);
      int r = minmax(ai, 2, gameBoard->player);
      // printAi(ai);
      // printf("Number of Possible Moves: %d\n", ai->number_possible_moves);
    }
    if (winner != 0) {
      break;
    }
  }

  char piece = winner == 1 ? 'X' : (winner == -1 ? 'O' : ' ');
  printf("Player %c won\n", piece);

  // Free memory
  for (int i = 0; i < gameBoard->rows; ++i) {
    free(gameBoard->board[i]);
  }
  free(gameBoard->board);

  return 0;
}
