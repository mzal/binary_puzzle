#pragma once
#include <stdbool.h>
#include "board.h"

bool checkRules(const board_t *board, int x, int y, char value);
bool checkNeighboursRule(const board_t *board, int x, int y, char value);
bool checkHalfRule(const board_t *board, int x, int y, char value);
int countInRow(const board_t *board, int x, int y, char value);
int countInCol(const board_t *board, int x, int y, char value);
//bool checkIdentRowColRule(const board_t *board, int x, int y, char value);