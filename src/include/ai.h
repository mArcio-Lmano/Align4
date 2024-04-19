#ifndef AI_H
#define AI_H
#include "gameboard.h"
#include <stdbool.h>

// gameboard.h
int checkWin(int x, int y, int **board);
int *playPlayerOnBoard(int **board, int row, int new_piece, int player);

struct Ai {
  int **board;
  int possible_moves[COLS];
  int number_possible_moves;
  int player1_number_stones;
  int player2_number_stones;
  int board_full;
};

Ai *initializeAi();

void removePossiblePlay(Ai *ai, int play);
int **copyBoard(int **board);
int minMax(Ai *ai, int depth, int player, int *best_move);

// NOTE: For debugging
void printAi(Ai *ai);
#endif
