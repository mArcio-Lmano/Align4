#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#define ROWS 6
#define COLS 7
#define min(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a < _b ? _a : _b;                                                         \
  })
#define max(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a > _b ? _a : _b;                                                         \
  })

// Forward declaration of Ai header
typedef struct Ai Ai;
void removePossiblePlay(Ai *ai, int play);
void printAiPossibleMoves(Ai *ai);
void printAiPossibleMoves(Ai *ai);

// Define a struct to represent the game board
typedef struct {
  int rows;
  int columns;
  int **board;
  int player;
  int player_last_piece[2];
  int positions[ROWS * COLS];
  int positions_length;
  int player1_stones_played;
  int player2_stones_played;
} GameBoard;
typedef int (*InputFunction)();

GameBoard *initializeGameBoard();
void printBoard(int **board, int rows, int cols);
int getUserInput();
int playPlayer(GameBoard *game, Ai *ai, InputFunction getInput);
int *playPlayerOnBoard(int **board, int row, int new_piece, int player);
int checkWin(int x, int y, int **board);
#endif
