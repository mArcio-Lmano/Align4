
#include "include/test_ai.h"
#include "../src/include/ai.h"

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdlib.h>

void test_initializeAi() {
  Ai *ai = initializeAi();

  CU_ASSERT_PTR_NOT_NULL(ai);

  for (int i = 0; i < COLS; i++) {
    CU_ASSERT_EQUAL(ai->possible_moves[i], i + 1);
  }
  CU_ASSERT_EQUAL(ai->number_possible_moves, COLS);
  CU_ASSERT_EQUAL(ai->player1_number_stones, 0);
  CU_ASSERT_EQUAL(ai->player2_number_stones, 0);
  CU_ASSERT_EQUAL(ai->board_full, 0);
  free(ai);
}

void test_copyBoard() {
  // NOTE: CASE1
  int **board_1 = (int **)malloc(ROWS * sizeof(int *));
  for (int i = 0; i < ROWS; ++i) {
    board_1[i] = (int *)malloc(COLS * sizeof(int));
    for (int j = 0; j < COLS; ++j) {
      board_1[i][j] = i * j;
    }
  }
  int **copy_board_1 = copyBoard(board_1);
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      CU_ASSERT_EQUAL(copy_board_1[i][j], i * j);
    }
  }

  for (int i = 0; i < ROWS; ++i) {
    free(board_1[i]);
  }
  free(board_1);
  for (int i = 0; i < ROWS; ++i) {
    free(copy_board_1[i]);
  }
  free(copy_board_1);

  // NOTE: CASE2
  int **board_2 = (int **)malloc(ROWS * sizeof(int *));
  for (int i = 0; i < ROWS; ++i) {
    board_2[i] = (int *)malloc(COLS * sizeof(int));
    for (int j = 0; j < COLS; ++j) {
      board_2[i][j] = i + j;
    }
  }
  int **copy_board_2 = copyBoard(board_2);
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      CU_ASSERT_EQUAL(copy_board_2[i][j], i + j);
    }
  }

  for (int i = 0; i < ROWS; ++i) {
    free(board_2[i]);
  }
  free(board_2);
  for (int i = 0; i < ROWS; ++i) {
    free(copy_board_2[i]);
  }
  free(copy_board_2);
}
