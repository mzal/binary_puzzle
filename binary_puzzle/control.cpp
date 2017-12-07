#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "control.h"
#include "graphics.h"
#include "rules.h"

void initializeGame() {
	FILE *defaultBoard = fopen("default.txt", "r");
	board_t board = createBoard(DEFAULT_BOARD_SIZE, defaultBoard);
	fclose(defaultBoard);
	mainLoop(&board);
	destroyBoard(&board);
}

void mainLoop(board_t *board) {
	draw(board);
	while (parseInput(board))
		draw(board);
}

bool parseInput(board_t *board) {
	char input = getch();
	switch (input) {
		case ESC_KEY:
			return 0;
		case 'n':
			clearScreen();
			destroyBoard(board);
			{
				FILE *boardFile = fopen(DEFAULT_BOARD_FILE, "r");
				*board = createBoard(DEFAULT_BOARD_SIZE, boardFile);
				fclose(boardFile);
			}
			break;
		case 'o':
			clearScreen();
			randomFillBoard(board);
			board->auto_mode.active = false;
			break;
		case 'p':
			drawPossible(board,
				checkRules(board, board->cursor_pos.x, board->cursor_pos.y, '0'),
				checkRules(board, board->cursor_pos.x, board->cursor_pos.y, '1'));
			break;
		case 'r':
			clearScreen();
			drawInputSize();
			{
				char sizeText[10];
				int ii = 0,
					size;
				fgets(sizeText, 10, stdin);
				size = atoi(sizeText);
				if (size % 2 == 0 && size <= MAX_BOARD_SIZE && size > 0) {
					char filename[25];
					sprintf(filename, "plansza%dx%d.txt", size, size);
					FILE *boardFile = fopen(filename, "r");
					destroyBoard(board);
					*board = createBoard(size, boardFile);
					if (boardFile)
						fclose(boardFile);
				}
				clearScreen();
			}
			break;
		case 'k':
			highlightInvalidFields(board);
			getch();
			break;
		case 'j':
			determinedFields(board);
			break;
		case 'a':
			board->auto_mode.active = !board->auto_mode.active;
			clearScreen();
			autoMode(board);
			break;
		case 0:
			input = getch();
			switch (input) {
				case UP_ARROW_KEY:
					moveCursor(board, UP);
					break;
				case DOWN_ARROW_KEY:
					moveCursor(board, DOWN);
					break;
				case LEFT_ARROW_KEY:
					moveCursor(board, LEFT);
					break;
				case RIGHT_ARROW_KEY:
					moveCursor(board, RIGHT);
					break;
			}
			break;
		case '0':
			clearScreen();
			updateValue(board, '0');
			if (board->auto_mode.active)
				autoMode(board);
			break;
		case '1':
			clearScreen();
			updateValue(board, '1');
			if (board->auto_mode.active)
				autoMode(board);
			break;
		case '.':
			clearScreen();
			updateValue(board, '.');
			if (board->auto_mode.active)
				autoMode(board);
			break;
	}
	return 1;
}

void moveCursor(board_t *board, direction_t direction) {
	switch (direction) {
		case UP:
			if (board->cursor_pos.y > 0)
				board->cursor_pos.y--;
			break;
		case DOWN:
			if (board->cursor_pos.y < board->size - 1)
				board->cursor_pos.y++;
			break;
		case LEFT:
			if (board->cursor_pos.x > 0)
				board->cursor_pos.x--;
			break;
		case RIGHT:
			if (board->cursor_pos.x < board->size - 1)
				board->cursor_pos.x++;
			break;
	}
}

void updateValue(board_t *board, char value) {
	rule_result_t ruleResult = checkRules(board, board->cursor_pos.x, board->cursor_pos.y, value);
	if ( board->fields[board->cursor_pos.y][board->cursor_pos.x].modifiable &&
		ruleResult.valid )
		board->fields[board->cursor_pos.y][board->cursor_pos.x].value = value;
}

void highlightInvalidFields(const board_t *board) {
	for (int ii = 0; ii < board->size; ++ii) {
		for (int jj = 0; jj < board->size; ++jj) {
			if (board->fields[ii][jj].value == '.') {
				rule_result_t rulesResult0 = checkRules(board, jj, ii, '0');
				rule_result_t rulesResult1 = checkRules(board, jj, ii, '1');
				if ((!rulesResult0.valid) && (!rulesResult1.valid))
					highlightField(board, jj, ii, HIGHLIGHT_INVALID);
			}
		}
	}
}

void determinedFields(board_t *board) {
	for (int ii = 0; ii < board->size; ++ii) {
		for (int jj = 0; jj < board->size; ++jj) {
			if (board->fields[ii][jj].value == '.') {
				rule_result_t rulesResult0 = checkRules(board, jj, ii, '0');
				rule_result_t rulesResult1 = checkRules(board, jj, ii, '1');
				if (rulesResult0.valid != rulesResult1.valid)
					highlightField(board, jj, ii, HIGHLIGHT_DETERMINED);
			}
		}
	}
	if (getch() == 'w') {
		fillDeterminedFields(board);
		autoMode(board);
	}
}

void fillDeterminedFields(board_t *board) {
	board_t board_copy = *board;
	for (int ii = 0; ii < board->size; ++ii) {
		for (int jj = 0; jj < board->size; ++jj) {
			if (board->fields[ii][jj].value == '.') {
				rule_result_t rulesResult0 = checkRules(&board_copy, jj, ii, '0');
				rule_result_t rulesResult1 = checkRules(&board_copy, jj, ii, '1');
				if (rulesResult0.valid != rulesResult1.valid) {
					if (rulesResult0.valid)
						board->fields[ii][jj].value = '0';
					else
						board->fields[ii][jj].value = '1';
				}
			}
		}
	}
}

void autoMode(board_t *board) {
	board->auto_mode.valid = true;
	for (int ii = 0; ii < board->size; ++ii) {
		for (int jj = 0; jj < board->size; ++jj) {
			if (board->fields[ii][jj].value == '.') {
				rule_result_t rulesResult0 = checkRules(board, jj, ii, '0');
				rule_result_t rulesResult1 = checkRules(board, jj, ii, '1');
				if ((!rulesResult0.valid) && (!rulesResult1.valid))
					board->auto_mode.valid = false;
			}
		}
	}
}