#pragma once
#include <stdio.h>
#include <stdbool.h>

#define MAX_FILENAME_LENGTH 25
#define MIN_RANDOM 25
#define MAX_RANDOM 35
#define MAX_RANDOM_TRIES 4
#define MAX_BOARD_SIZE 20

typedef struct {
	bool modifiable = true;
	bool visible = true;
	char value = '.';
} field_t;

typedef struct {
	field_t **fields = NULL;
	int size = 0;
	struct {
		int x, y;
	} cursor_pos;
	struct {
		int x, y;
	} board_pos;
	struct {
		bool active = false,
			valid;
	} auto_mode;
} board_t;

board_t createBoard(int size, FILE *prefill);
void readBoardFromFile(board_t *board, FILE *str);
void clearBoard(board_t *board);
void destroyBoard(board_t *board);
void randomFillBoard(board_t *board);