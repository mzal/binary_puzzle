#include "rules.h"

rule_result_t checkRules(const board_t *board, int x, int y, char value) {
	rule_result_t result,
		neighboursResult = checkNeighboursRule(board, x, y, value),
		halfResult = checkHalfRule(board, x, y, value),
		identResult = checkIdentRowColRule(board, x, y, value);

	if (
		neighboursResult.valid &&
		halfResult.valid &&
		identResult.valid
		)
		return result;
	else if (value == '.')
		return result;
	else {
		result.valid = false;
		if (!neighboursResult.valid)
			result.neighbours = neighboursResult.neighbours;
		if (!halfResult.valid)
			result.half = halfResult.half;
		if (!identResult.valid)
			result.ident = identResult.ident;
	}
	return result;
}

rule_result_t checkNeighboursRule(const board_t *board, int x, int y, char value) {
	rule_result_t result;
	//horizontal check
	if (
		(x >= 2 && board->fields[y][x - 2].value == value && board->fields[y][x - 1].value == value) ||
		(x >= 1 && x < board->size - 1 && board->fields[y][x - 1].value == value && board->fields[y][x + 1].value == value) ||
		(x < board->size - 2 && board->fields[y][x + 1].value == value && board->fields[y][x + 2].value == value)
		) 
	{
		result.valid = false;
		result.neighbours.valid = false;
		result.neighbours.horizontalVertical = 0;
	}
	//vertical check
	if (
		(y >= 2 && board->fields[y - 2][x].value == value && board->fields[y - 1][x].value == value) ||
		(y >= 1 && y < board->size - 1 && board->fields[y - 1][x].value == value && board->fields[y + 1][x].value == value) ||
		(y < board->size - 2 && board->fields[y + 1][x].value == value && board->fields[y + 2][x].value == value)
		)
	{
		result.valid = false;
		result.neighbours.valid = false;
		result.neighbours.horizontalVertical = 1;
	}
	return result;
}

rule_result_t checkHalfRule(const board_t *board, int x, int y, char value) {
	rule_result_t result;
	if (countInRow(board, x, y, value) > board->size / 2) {
		result.valid = false;
		result.half.valid = false;
		result.half.horizontalVertical = 0;
		return result;
	}
	else if (countInCol(board, x, y, value) > board->size / 2) {
		result.valid = false;
		result.half.valid = false;
		result.half.horizontalVertical = 1;
		return result;
	}
	return result;
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

rule_result_t checkIdentRowColRule(const board_t *board, int x, int y, char value) {
	//checking rows
	rule_result_t result;
	for (int ii = 0; ii < board->size; ++ii) {
		if (ii == y)
			continue;
		else {
			if (board->fields[ii][x].value != value)
				continue;

			bool identical = 1;
			for (int jj = 0; jj < board->size; ++jj) {
				if (jj == x)
					continue;
				if (board->fields[ii][jj].value != board->fields[y][jj].value) {
					identical = 0;
					break;
				}
			}
			if (identical) {
				result.valid = false;
				result.ident.valid = false;
				result.ident.rowCol = 0;
				result.ident.index = ii;
				return result;
			}
		}
	}

	//checking columns
	for (int jj = 0; jj < board->size; ++jj) {
		if (jj == x)
			continue;
		else {
			if (board->fields[y][jj].value != value)
				continue;

			bool identical = 1;
			for (int ii = 0; ii < board->size; ++ii) {
				if (ii == y)
					continue;
				if (board->fields[ii][jj].value != board->fields[ii][x].value) {
					identical = 0;
					break;
				}
			}
			if (identical) {
				result.valid = false;
				result.ident.valid = false;
				result.ident.rowCol = 1;
				result.ident.index = jj;
				return result;
			}
		}
	}
	return result;	
}