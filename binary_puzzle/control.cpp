#include <stdio.h>
#include "control.h"
#include "graphics.h"
#include "rules.h"

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
			updateValue(board, '0');
			break;
		case '1':
			updateValue(board, '1');
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
	if ( board->fields[board->cursor_pos.y][board->cursor_pos.x].modifiable &&
		checkRules(board, board->cursor_pos.x, board->cursor_pos.y, value) )
		board->fields[board->cursor_pos.y][board->cursor_pos.x].value = value;
}