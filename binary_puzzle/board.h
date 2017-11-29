#pragma once
#include <stdio.h>
#include <stdbool.h>

struct field_t {
	bool modifiable = true;
	bool visible = true;
	char value = '.';
};

struct board_t {
	field_t **fields = NULL;
	int size = 0;
	struct {
		int x, y;
	} cursor_pos;
};

board_t createBoard(int size, FILE *prefill);
void clearBoard(board_t *board);
void destroyBoard(board_t *board);