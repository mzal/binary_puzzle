#include <stdlib.h>
#include <stdio.h>
#include "board.h"


board_t createBoard(int size, FILE *prefill) {
	//initializes board of size size, filling it according to FILE *prefill
	//or filling with empty fields if prefill is nullptr or invalid
	board_t board;
	board.fields = (field_t **) malloc(size * sizeof(field_t*));
	for (int ii = 0; ii < size; ++ii)
		board.fields[ii] = (field_t *)malloc(size * sizeof(field_t));
	board.size = size;
	board.cursor_pos = { 0, 0 };

	if (prefill) {
		fseek(prefill, 0L, SEEK_END);
		if (ftell(prefill) >= size * (size + 1)) {
			fseek(prefill, 0L, SEEK_SET);
			//TODO: write field values from file to fields, set modifiable parameter
		}
	}
	else
		clearBoard(&board);
	return board;
}

void clearBoard(board_t *board) {
	for (int ii = 0; ii < board->size; ++ii) {
		for (int jj = 0; jj < board->size; ++jj) {
			board->fields[ii][jj].value = '.';
			board->fields[ii][jj].modifiable = true;
			board->fields[ii][jj].visible = true;
		}
	}
}

void destroyBoard(board_t *board) {
	for (int ii = 0; ii < board->size; ++ii)
		free(board->fields[ii]);
	free(board->fields);
}