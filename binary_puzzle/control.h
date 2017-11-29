#pragma once
#include <stdbool.h>
#include "board.h"

enum ASCII_KEYS {
	ESC_KEY = 27,
	UP_ARROW_KEY = 0x48,
	DOWN_ARROW_KEY = 0x50,
	LEFT_ARROW_KEY = 0x4b,
	RIGHT_ARROW_KEY = 0x4d
};

enum direction_t {
	UP,
	RIGHT,
	DOWN,
	LEFT
};



void mainLoop(board_t *board);
bool parseInput(board_t *board);
void moveCursor(board_t *board, direction_t direction);
void updateValue(board_t *board, char value);