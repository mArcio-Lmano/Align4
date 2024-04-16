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

int minmaxGetScore(Ai *ai, int **board) {
  int res = 0;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      res += ai->board_score[i][j] * board[i][j];
    }
  }
  return res;
}

// TODO: Make the minmax algorithm
//       Make a way to see if the colls are full, to check the possible moves
//       Find a better way to evaluate the score, rigth now it is bad.
int minmax(Ai *ai, int depth, int player, int **board, int *scr, int *bst_mv) {
  int scale = 1;
  int r = 0;
  // printf("Player %d Found at depth: %d, With a Score: %d\n", player, depth,
  //        *scr);
  if (depth <= 0) {
    return minmaxGetScore(ai, board);
  } else if (player == 1) {
    *scr = max(ai->sum_board_scores * -scale, *scr);
    // printBoard(board, ROWS, COLS);
    for (int i = 0; i < ai->number_possible_moves; i++) {
      int move = ai->possible_moves[i];
      int *res = playPlayerOnBoard(board, ROWS - 1, move - 1, player);
      if (res[0] != 0) {
        printf("Something Went Wrong\n");
      } else {
        r = minmax(ai, depth - 1, -1 * player, board, scr, bst_mv) * scale;
        if (r > *scr) {
          *scr = r;
          *bst_mv = res[2];
        }
        board[res[1]][res[2]] = 0;
        // printf("Move: %d, Row: %d, NewPiece: %d\n", move, res[1], res[2]);
        // printBoard(board, ROWS, COLS);
      }
    }
  } else {
    *scr = min(ai->sum_board_scores * scale, *scr);
    // printBoard(board, ROWS, COLS);
    for (int i = 0; i < ai->number_possible_moves; i++) {
      int move = ai->possible_moves[i];
      int *res = playPlayerOnBoard(board, ROWS - 1, move - 1, player);
      if (res[0] != 0) {
        printf("Something Went Wrong\n");
      } else {
        // printf("Move: %d, Row: %d, NewPiece: %d\n", move, res[1], res[2]);
        // printBoard(board, ROWS, COLS);
        r = minmax(ai, depth - 1, -1 * player, board, scr, bst_mv) * scale;
        // printf("R: %d, move: %d\n", r, move);
        if (r < *scr) {
          *scr = r;
          *bst_mv = res[2];
        }
        board[res[1]][res[2]] = 0;
      }
    }
  }
  // printf("Player %d  Score: %d\n", player, r);
  return *scr;
}
