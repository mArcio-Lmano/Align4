#include "include/ai.h"
#include "include/gameboard.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// NOTE: For Debuging
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
void printAi(Ai *ai) {
  printAiGameBoard(ai);
  printAiPossibleMoves(ai);
}
//

Ai *initializeAi() {
  Ai *ai = (Ai *)malloc(sizeof(Ai));
  for (int i = 0; i < COLS; i++) {
    ai->possible_moves[i] = i + 1;
  }
  ai->number_possible_moves = COLS;
  ai->board_full = 0;
  ai->player1_number_stones = 0;
  ai->player2_number_stones = 0;
  return ai;
}

int **copyBoard(int **board) {
  int **copy_board = (int **)malloc(ROWS * sizeof(int *));
  for (int i = 0; i < ROWS; ++i) {
    copy_board[i] = (int *)malloc(COLS * sizeof(int));
    for (int j = 0; j < COLS; ++j) {
      copy_board[i][j] = board[i][j];
    }
  }
  return copy_board;
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

Ai *copyAi(Ai *ai) {
  Ai *new_ai = (Ai *)malloc(sizeof(Ai));
  new_ai->board = copyBoard(ai->board);
  new_ai->number_possible_moves = ai->number_possible_moves;
  new_ai->player1_number_stones = ai->player1_number_stones;
  new_ai->player2_number_stones = ai->player2_number_stones;
  new_ai->board_full = ai->board_full;
  return new_ai;
}

int calculateMinMaxScore(Ai *ai, int player) {
  int number_stones;
  if (player == 1) {
    number_stones = ai->player1_number_stones;
  } else {
    number_stones = ai->player2_number_stones;
  }

  int r = player * (ROWS * COLS - number_stones);
  return r;
}

int minMax(Ai *ai, int depth, int player, int *best_move) {
  int score = 0;
  Ai *next_ai = copyAi(ai);
  if (depth == 0) {
    for (int i = 0; i < ROWS; ++i) {
      free(next_ai->board[i]);
    }
    free(next_ai->board);
    free(next_ai);
    return calculateMinMaxScore(ai, player);
  }

  else if (player == 1) {
    score = -(ROWS * COLS);
    next_ai->player1_number_stones++;
    for (int i = 0; i < next_ai->number_possible_moves; ++i) {
      int move = next_ai->possible_moves[i];
      int *res = playPlayerOnBoard(next_ai->board, ROWS - 1, move - 1, player);
      int flags[3];
      flags[0] = res[0];
      flags[1] = res[1];
      flags[2] = res[2];
      free(res);
      if (flags[0] == 0) {
        int winner = checkWin(flags[2], flags[1], next_ai->board);
        if (winner == 1) {
          *best_move = move;
          return calculateMinMaxScore(next_ai, player);
        }
        int r = minMax(next_ai, depth - 1, player * -1, best_move);
        next_ai->board[flags[1]][flags[2]] = 0;
        if (r > score) {
          *best_move = move;
          score = r;
        }
      } else {
        removePossiblePlay(next_ai, move);
      }
    }
  } else {
    score = (ROWS * COLS);
    next_ai->player2_number_stones++;
    for (int i = 0; i < next_ai->number_possible_moves; ++i) {
      int move = next_ai->possible_moves[i];
      int *res = playPlayerOnBoard(next_ai->board, ROWS - 1, move - 1, player);
      int flags[3];
      flags[0] = res[0];
      flags[1] = res[1];
      flags[2] = res[2];
      free(res);
      if (flags[0] == 0) {
        int winner = checkWin(flags[2], flags[1], next_ai->board);
        if (winner == -1) {
          *best_move = move;
          return calculateMinMaxScore(next_ai, player);
        }
        int r = minMax(next_ai, depth - 1, player * -1, best_move);
        next_ai->board[flags[1]][flags[2]] = 0;
        if (r < score) {
          *best_move = move;
          score = r;
        }
      } else {
        removePossiblePlay(next_ai, move);
      }
    }
  }

  for (int i = 0; i < ROWS; ++i) {
    free(next_ai->board[i]);
  }
  free(next_ai->board);
  free(next_ai);
  return score;
}
