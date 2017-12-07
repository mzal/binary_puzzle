#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "board.h"
#include "rules.h"

board_t createBoard(int size, FILE *customBoard) {
	//initializes board of size size, filling it according to FILE *prefill
	//or filling with empty fields if prefill is nullptr or invalid
	board_t board;
	board.fields = (field_t **) malloc(size * sizeof(field_t*));
	for (int ii = 0; ii < size; ++ii)
		board.fields[ii] = (field_t *)malloc(size * sizeof(field_t));
	board.size = size;
	board.cursor_pos = { 0, 0 };
	board.auto_mode.active = false;
	board.auto_mode.valid = true;

	if (customBoard) {
		readBoardFromFile(&board, customBoard);
	}
	else {
		/*
		
		*/
		randomFillBoard(&board);
	}
		
	return board;
}

void readBoardFromFile(board_t *board, FILE *str) {
	//TODO: check file length and crash on too short sometime
	char value = NULL;
	for (int ii = 0; ii < board->size; ++ii) {
		int jj = 0;
		while (jj < board->size) {
			char value = fgetc(str);
			switch (value)
			{
			case '0':
				board->fields[ii][jj].value = '0';
				board->fields[ii][jj].modifiable = false;
				board->fields[ii][jj].visible = true;
				break;
			case '1':
				board->fields[ii][jj].value = '1';
				board->fields[ii][jj].modifiable = false;
				board->fields[ii][jj].visible = true;
				break;
			case '.':
				board->fields[ii][jj].value = '.';
				board->fields[ii][jj].modifiable = true;
				board->fields[ii][jj].visible = true;
				break;
			default:
				break;
			}
			jj++;
		}
		fgetc(str);
	}
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

void randomFillBoard(board_t *board) {
	clearBoard(board);
	srand(time(NULL));
	int filled = 0,
		tries = 0,
		numOfFields = board->size * board->size,
		maximumTries = pow(board->size, MAX_RANDOM_TRIES);
	float minimumRatio = ( MIN_RANDOM + rand() % (MAX_RANDOM - MIN_RANDOM) ) / 100.0;
	
	while (float(filled) / numOfFields < minimumRatio && tries < maximumTries) {
		int x = rand() % board->size,
			y = rand() % board->size;
		char value = '0' + rand() % 2;
		if (board->fields[y][x].modifiable && checkRules(board, x, y, value).valid) {
			board->fields[y][x].value = value;
			board->fields[y][x].modifiable = false;
			filled++;
			tries = 0;
		}
		else
			tries++;
	}
}