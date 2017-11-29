#include "rules.h"

bool checkRules(const board_t *board, int x, int y, char value) {
	if (
		checkNeighboursRule(board, x, y, value) &&
		checkHalfRule(board, x, y, value)
		)
		return 1;
	return 0;
}

bool checkNeighboursRule(const board_t *board, int x, int y, char value) {
	//horizontal check
	if (
		(x >= 2 && board->fields[y][x - 2].value == value && board->fields[y][x - 1].value == value) ||
		(x >= 1 && x < board->size - 1 && board->fields[y][x - 1].value == value && board->fields[y][x + 1].value == value) ||
		(x < board->size - 2 && board->fields[y][x + 1].value == value && board->fields[y][x + 2].value == value)
		)
		return 0;
	//vertical check
	if (
		(y >= 2 && board->fields[y - 2][x].value == value && board->fields[y - 1][x].value == value) ||
		(y >= 1 && y < board->size - 1 && board->fields[y - 1][x].value == value && board->fields[y + 1][x].value == value) ||
		(y < board->size - 2 && board->fields[y + 1][x].value == value && board->fields[y + 2][x].value == value)
		)
		return 0;
	return 1;
}

bool checkHalfRule(const board_t *board, int x, int y, char value) {
	if (
		countInRow(board, x, y, value) > board->size / 2 ||
		countInCol(board, x, y, value) > board->size / 2
		)
		return 0;
	return 1;
}

int countInRow(const board_t *board, int x, int y, char value) {
	int c = 0;
	for (int ii = 0; ii < board->size; ++ii) {
		if (ii == x)
			c++;
		else if (board->fields[y][ii].value == value)
			c++;
	}
	return c;
}

int countInCol(const board_t *board, int x, int y, char value) {
	int c = 0;
	for (int ii = 0; ii < board->size; ++ii) {
		if (ii == y)
			c++;
		else if (board->fields[ii][x].value == value)
			c++;
	}
	return c;
}