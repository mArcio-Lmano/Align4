#ifndef AI_H
#define AI_H
#include "gameboard.h"
#include <stdbool.h>

struct Ai {
  int board_score[ROWS][COLS];
  int **board;
  int sum_board_scores;
  int possible_moves[COLS];
  int number_possible_moves;
};

Ai *initializeAi();

void removePossiblePlay(Ai *ai, int play);
int **copyBoard(int **board);
int *playPlayerOnBoard(int **board, int row, int new_piece, int player);
int minmax(Ai *ai, int depth, int player, int **board, int *scr, int *bst_mv);

// NOTE: For debugging
void printAi(Ai *ai);
void printAiGameBoardScores(Ai *ai);
void printAiGameBoard(Ai *ai);
void printAiPossibleMoves(Ai *ai);
void printAiBoardSum(Ai *ai);
#endif
