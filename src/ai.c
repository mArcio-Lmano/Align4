#include "include/ai.h"
#include "include/gameboard.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// NOTE: For Debuging
void printAi(Ai *ai) {
  printAiGameBoardScores(ai);
  printAiGameBoard(ai);
  printAiPossibleMoves(ai);
}
void printAiGameBoardScores(Ai *ai) {
  printf("Game Board Scores:\n");
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      printf(" %d ", ai->board_score[i][j]);
    }
    printf("\n");
  }
}
void printAiGameBoard(Ai *ai) {
  printf("Game Board: \n");
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      printf(" %d ", ai->board[i][j]);
    }
    printf("\n");
  }
}
void printAiPossibleMoves(Ai *ai) {
  printf("Possible Moves (%d):", ai->number_possible_moves);
  for (int i = 0; i < ai->number_possible_moves; i++) {
    printf(" %d ", ai->possible_moves[i]);
  }
  printf("\n");
}
void printAiBoardSum(Ai *ai) {
  printf("\nAi BoardSum: %d\n", ai->sum_board_scores);
}
//

Ai *initializeAi() {
  Ai *ai = (Ai *)malloc(sizeof(Ai));
  int values[ROWS][COLS] = {{1, 1, 1, 1, 1, 1, 1}, {1, 2, 2, 2, 2, 2, 1},
                            {1, 2, 3, 4, 3, 2, 1}, {1, 2, 3, 4, 3, 2, 1},
                            {1, 2, 2, 2, 2, 2, 1}, {1, 1, 1, 1, 1, 1, 1}};
  // ai->board = malloc(ROWS * sizeof(int *));
  ai->sum_board_scores = 0;
  for (int i = 0; i < ROWS; i++) {
    // ai->board[i] = malloc(COLS * sizeof(int));
    for (int j = 0; j < COLS; j++) {
      ai->board_score[i][j] = values[i][j];
      ai->sum_board_scores += values[i][j];
    }
  }
  for (int i = 0; i < COLS; i++) {
    ai->possible_moves[i] = i + 1;
  }
  ai->number_possible_moves = COLS;
  return ai;
}

int **copyBoard(int **board) {
  int **borad_copy = malloc(ROWS * sizeof(int *));
  for (int i = 0; i < ROWS; i++) {
    borad_copy[i] = malloc(COLS * sizeof(int));
    for (int j = 0; j < COLS; j++) {
      borad_copy[i][j] = board[i][j];
    }
  }
  return borad_copy;
}

void removePossiblePlay(Ai *ai, int play) {
  int size = ai->number_possible_moves;
  int index_possible_moves = -1;
  for (int i = 0; i < size; i++) {
    if (ai->possible_moves[i] == play) {
      index_possible_moves = i;
      break;
    }
  }
  if (index_possible_moves == -1) {
    return;
  }
  for (int i = index_possible_moves; i < size; i++) {
    ai->possible_moves[i] = ai->possible_moves[i + 1];
  }
  ai->number_possible_moves--;
}

// TODO: Make the minmax algorithm
//       Make a way to see if the colls are full, to check the possible moves
int minmax(Ai *ai, int depth, int player) {
  int scale = 1;

  if (depth <= 0) {
    return 0;
  }

  else {
    printf("MINMAX Algorithm\n");
    printAiPossibleMoves(ai);
    int **board = copyBoard(ai->board);
    int row = 0;
    printBoard(board, ROWS, COLS);
    for (int i = 0; i < ai->number_possible_moves; i++) {
      int move = ai->possible_moves[i];
      int *res = playPlayerOnBoard(board, ROWS - 1, move - 1, 1);
      if (res[0] != 0) {
        printf("Something Went Wrong");
      } else {
        printf("Move: %d\n", move);
        printBoard(board, ROWS, COLS);
      }
    }
  }
  return 0;
}
