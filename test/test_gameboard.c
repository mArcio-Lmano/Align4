#include "include/test_gameboard.h"

#include "../src/include/ai.h"
#include "../src/include/gameboard.h"

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

// NOTE: Util functions
int INDEX = 0;
int mockInput() {
  int inputs[] = {3, 6};
  return inputs[INDEX];
}

int ORIGINAL_STDOUT_FG = STDOUT_FILENO;
void suppressPrintf() {
  int devnull = open("/dev/null", O_WRONLY);
  if (devnull < 0) {
    return;
  }
  ORIGINAL_STDOUT_FG = dup(STDOUT_FILENO);
  dup2(devnull, STDOUT_FILENO);
  close(devnull);
}
void restorePrintf() {
  dup2(ORIGINAL_STDOUT_FG, STDOUT_FILENO);
  close(ORIGINAL_STDOUT_FG);
}

// NOTE: Test Functions
void test_initializeGameBoard() {
  GameBoard *game = initializeGameBoard();

  CU_ASSERT_PTR_NOT_NULL(game);

  CU_ASSERT_EQUAL(game->rows, ROWS);
  CU_ASSERT_EQUAL(game->columns, COLS);
  CU_ASSERT_EQUAL(game->player, 1);
  for (int i = 0; i < game->rows; ++i) {
    for (int j = 0; j < game->columns; ++j) {
      CU_ASSERT_EQUAL(game->board[i][j], 0)
      game->board[i][j] = 0;
    }
  }
  CU_ASSERT_EQUAL(game->positions_length, 0);

  for (int i = 0; i < game->rows; ++i) {
    free(game->board[i]);
  }
  free(game->board);
  free(game);
}

void test_playPlayer() {
  suppressPrintf();
  GameBoard *game = initializeGameBoard();
  Ai *ai = initializeAi();

  CU_ASSERT_PTR_NOT_NULL(game);
  CU_ASSERT_PTR_NOT_NULL(ai);

  int result_1 = playPlayer(game, ai, mockInput);
  CU_ASSERT_EQUAL(result_1, 0);
  CU_ASSERT_EQUAL(game->player_last_piece[0], 5);
  CU_ASSERT_EQUAL(game->player_last_piece[1], 2);

  int result_2 = playPlayer(game, ai, mockInput);
  CU_ASSERT_EQUAL(result_2, 0);
  CU_ASSERT_EQUAL(game->player_last_piece[0], 4);
  CU_ASSERT_EQUAL(game->player_last_piece[1], 2);

  INDEX++;
  int result_3 = playPlayer(game, ai, mockInput);
  CU_ASSERT_EQUAL(result_3, 0);
  CU_ASSERT_EQUAL(game->player_last_piece[0], 5);
  CU_ASSERT_EQUAL(game->player_last_piece[1], 5);

  restorePrintf();

  for (int i = 0; i < game->rows; ++i) {
    free(game->board[i]);
  }
  free(game->board);
  free(game);
  free(ai);
}

void test_checkWin() {
  // NOTE: CASE1
  int **board1 = (int **)malloc(ROWS * sizeof(int *));
  for (int i = 0; i < ROWS; ++i) {
    board1[i] = (int *)malloc(COLS * sizeof(int));
    for (int j = 0; j < COLS; ++j) {
      board1[i][j] = 0;
    }
  }

  board1[2][3] = -1;
  board1[3][2] = -1;
  board1[4][1] = -1;
  board1[5][0] = -1;
  int x1 = 1;
  int y1 = 4;
  int winner1 = checkWin(x1, y1, board1);
  CU_ASSERT_EQUAL(winner1, -1);

  for (int i = 0; i < ROWS; ++i) {
    free(board1[i]);
  }
  free(board1);

  // NOTE: CASE2
  int **board2 = (int **)malloc(ROWS * sizeof(int *));
  for (int i = 0; i < ROWS; ++i) {
    board2[i] = (int *)malloc(COLS * sizeof(int));
    for (int j = 0; j < COLS; ++j) {
      board2[i][j] = 0;
    }
  }

  board2[2][3] = 1;
  board2[3][2] = 1;
  board2[4][1] = 1;
  board2[5][0] = 1;
  int x2 = 1;
  int y2 = 4;
  int winner2 = checkWin(x2, y2, board2);
  CU_ASSERT_EQUAL(winner2, 1);

  for (int i = 0; i < ROWS; ++i) {
    free(board2[i]);
  }
  free(board2);

  // NOTE: CASE3
  int **board3 = (int **)malloc(ROWS * sizeof(int *));
  for (int i = 0; i < ROWS; ++i) {
    board3[i] = (int *)malloc(COLS * sizeof(int));
    for (int j = 0; j < COLS; ++j) {
      board3[i][j] = 0;
    }
  }

  board3[2][2] = 1;
  board3[3][2] = 1;
  board3[4][2] = 1;
  board3[5][2] = 1;
  int x3 = 2;
  int y3 = 4;
  int winner3 = checkWin(x3, y3, board3);
  CU_ASSERT_EQUAL(winner3, 1);

  for (int i = 0; i < ROWS; ++i) {
    free(board3[i]);
  }
  free(board3);

  // NOTE: CASE4
  int **board4 = (int **)malloc(ROWS * sizeof(int *));
  for (int i = 0; i < ROWS; ++i) {
    board4[i] = (int *)malloc(COLS * sizeof(int));
    for (int j = 0; j < COLS; ++j) {
      board4[i][j] = 0;
    }
  }

  board4[2][4] = 1;
  board4[3][3] = 1;
  board4[4][2] = 1;
  board4[5][1] = 1;
  int x4 = 3;
  int y4 = 3;
  int winner4 = checkWin(x4, y4, board4);
  CU_ASSERT_EQUAL(winner4, 1);

  for (int i = 0; i < ROWS; ++i) {
    free(board4[i]);
  }
  free(board4);

  // NOTE: CASE5
  int **board5 = (int **)malloc(ROWS * sizeof(int *));
  for (int i = 0; i < ROWS; ++i) {
    board5[i] = (int *)malloc(COLS * sizeof(int));
    for (int j = 0; j < COLS; ++j) {
      board5[i][j] = 0;
    }
  }

  board5[2][3] = 1;
  board5[3][4] = 1;
  board5[4][5] = 1;
  board5[5][6] = 1;
  int x5 = 5;
  int y5 = 4;
  int winner5 = checkWin(x5, y5, board5);
  CU_ASSERT_EQUAL(winner5, 1);

  for (int i = 0; i < ROWS; ++i) {
    free(board5[i]);
  }
  free(board5);
}
