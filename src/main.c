#include "include/ai.h"
#include "include/gameboard.h"
// #include "include/gameboard.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  GameBoard *gameBoard = initializeGameBoard();
  Ai *ai = initializeAi();

  printBoard(gameBoard->board, gameBoard->rows, gameBoard->columns);
  int winner = 0;
  while (1) {
    int res = playPlayer(gameBoard, ai, getUserInput);
    if (res != -1) {
      printBoard(gameBoard->board, gameBoard->rows, gameBoard->columns);
      int x = gameBoard->player_last_piece[1];
      int y = gameBoard->player_last_piece[0];
      winner = checkWin(x, y, gameBoard->board);
      // NOTE: Debug
      ai->board = copyBoard(gameBoard->board);
      if (gameBoard->player == 1) {
        ai->player1_number_stones++;
      } else {
        ai->player2_number_stones++;
      }
      gameBoard->player *= -1;
      int *best_move = (int *)malloc(sizeof(int));
      int score = minMax(ai, 1, gameBoard->player, best_move);
      printf("Score: %d\n", score);
      printf("Best Move: %d\n", *best_move);
      for (int i = 0; i < ROWS; ++i) {
        free(ai->board[i]);
      }
      free(ai->board);
      free(best_move);
    }
    if (winner != 0) {
      break;
    }
  }

  char piece = winner == 1 ? 'X' : (winner == -1 ? 'O' : ' ');
  printf("Player %c won\n", piece);

  for (int i = 0; i < gameBoard->rows; ++i) {
    free(gameBoard->board[i]);
  }
  free(gameBoard->board);
  free(gameBoard);
  free(ai);
  return 0;
}
