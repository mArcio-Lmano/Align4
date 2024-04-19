#include "include/gameboard.h"
// #include "include/ai.h"
// #include "include/ai.h"

#include <stdio.h>
#include <stdlib.h>

GameBoard *initializeGameBoard() {
  GameBoard *game = (GameBoard *)malloc(sizeof(GameBoard));

  game->rows = ROWS;
  game->columns = COLS;
  game->player = 1;

  game->board = (int **)malloc(game->rows * sizeof(int *));
  for (int i = 0; i < game->rows; ++i) {
    game->board[i] = (int *)malloc(game->columns * sizeof(int));
    for (int j = 0; j < game->columns; ++j) {
      game->board[i][j] = 0;
    }
  }
  game->positions_length = 0;
  return game;
}

void printBoard(int **board, int rows, int cols) {
  printf("Game Board\n");
  for (int i = 0; i < rows; ++i) {
    printf("===============\n");
    for (int j = 0; j < cols; ++j) {
      char piece = board[i][j] == 1 ? 'X' : (board[i][j] == -1 ? 'O' : ' ');
      printf("|%c", piece);
    }
    printf("|\n");
  }
  printf("===============\n");
}

int getUserInput() {
  int input;
  scanf("%d", &input);
  return input;
}

int playPlayer(GameBoard *game, Ai *ai, InputFunction getInput) {
  char piece = game->player == 1 ? 'X' : (game->player == -1 ? 'O' : ' ');
  printf("Player '%c' Turn\n", piece);
  int new_piece = -1;
  while (new_piece < 1 || new_piece > 7) {
    printf("Where do you want to play?: ");
    new_piece = getInput();
  }
  int **board = game->board;
  int row = game->rows - 1;
  new_piece--;

  int *flags = playPlayerOnBoard(board, row, new_piece, game->player);
  int res = flags[0];
  row = flags[1];
  new_piece = flags[2];

  if (res == 0 && row >= 0) {
    game->player_last_piece[0] = row;
    game->player_last_piece[1] = new_piece;
    if (row == 0) {
      removePossiblePlay(ai, new_piece + 1);
      printAiPossibleMoves(ai);
    }
    game->positions[game->positions_length] = new_piece;
    game->positions_length++;
  }
  free(flags);
  return res;
}

int *playPlayerOnBoard(int **board, int row, int new_piece, int player) {
  // NOTE: r = [exit_status, row, new_piece]
  int *r = (int *)malloc(3 * sizeof(int));

  while (row >= 0 && board[row][new_piece] != 0) {
    row--;
  }
  if (row >= 0) {
    board[row][new_piece] = player;
    r[0] = 0;
    r[1] = row;
    r[2] = new_piece;
  } else {
    printf("Column is already filled. Please choose another column.\n");
    r[0] = -1;
    r[1] = -1;
    r[2] = -1;
  }
  return r;
}

// int checkWin(GameBoard *game_board) {
int checkWin(int x, int y, int **board) {
  int win = 0;
  int delta_plus_x, delta_minus_x, delta_plus_y, delta_minus_y;

  delta_plus_x = min(3, COLS - 1 - x);
  delta_minus_x = min(3, x);
  delta_plus_y = min(3, y);
  delta_minus_y = min(3, ROWS - 1 - y);

  // NOTE: Check Hoprizontal
  int x_minus = x - delta_minus_x;
  int x_plus = x + delta_plus_x;
  int *row = board[y];
  int row_sum = 0;
  for (int i = x_minus; i <= x_plus; i++) {
    row_sum += board[y][i];
  }

  if (row_sum == 4 || row_sum == -4) {
    win = row_sum / 4;
  }

  // NOTE: Check vertical
  int y_minus = y - delta_plus_y;
  int y_plus = y + delta_minus_y;
  int column_sum = 0;
  for (int i = y_minus; i <= y_plus; i++) {
    column_sum += board[i][x];
  }

  if (column_sum == 4 || column_sum == -4) {
    win = column_sum / 4;
  }

  // NOTE: Check diagonal
  // Diagonal 1
  int delta_diagonal1_minus, delta_diagonal1_plus;
  delta_diagonal1_minus = min(delta_minus_x, delta_minus_y);
  delta_diagonal1_plus = min(delta_plus_x, delta_plus_y);

  // printf("Diagonal1\n");
  int diagonal1_sum = 0;
  for (int i = -delta_diagonal1_minus; i <= delta_diagonal1_plus; i++) {
    int dig_x = x + i;
    int dig_y = y - i;
    // printf("Dig x: %d, y: %d\n", dig_x, dig_y);
    diagonal1_sum += board[dig_y][dig_x];
  }

  if (diagonal1_sum == 4 || diagonal1_sum == -4) {
    win = diagonal1_sum / 4;
  }

  // NOTE: Check diagonal
  // Diagonal 2
  int delta_diagonal2_minus, delta_diagonal2_plus;
  delta_diagonal2_minus = min(delta_plus_x, delta_minus_y);
  delta_diagonal2_plus = min(delta_minus_x, delta_plus_y);

  int diagonal2_sum = 0;
  for (int i = -delta_diagonal2_minus; i <= delta_diagonal2_plus; i++) {
    int dig_x = x - i;
    int dig_y = y - i;
    diagonal2_sum += board[dig_y][dig_x];
  }

  if (diagonal2_sum == 4 || diagonal2_sum == -4) {
    win = diagonal2_sum / 4;
  }
  return win;
}
