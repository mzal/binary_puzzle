#define _CRT_SECURE_NO_WARNINGS
#include "graphics.h"
#include <stdlib.h>
#include <string.h>

void draw(board_t *board) {
#ifndef __cplusplus
	Conio2_Init();
#endif
	settitle("Michal Zalewski 171671");
	textbackground(TEXT_BACKGROUND);
	textcolor(TEXT_COLOR);
	_setcursortype(_NOCURSOR);
	if (LAYOUT == 0) {
		board->board_pos.x = LEGEND_WIDTH + 1;
		board->board_pos.y = PADDING_TOP;
		drawLegend(board, 0, PADDING_TOP);
		drawBoard(board, board->board_pos.x, board->board_pos.y);
	}
	else {
		board->board_pos.x = 1;
		board->board_pos.y = PADDING_TOP;
		drawLegend(board, board->board_pos.x + board->size + GAP, PADDING_TOP);
		drawBoard(board, board->board_pos.x, board->board_pos.y);
	}

}

void drawLegend(const board_t *board, int positionX, int positionY) {
	int x = positionX + 2,
		y = positionY + 2,
		height = board->size + 2;
	gotoxy(x, y++);
	cputs("Michal Zalewski 171671");
	gotoxy(x, y++);
	cputs("abcdefghijklm");
	gotoxy(x, y++);
	cputs("ESC\tquit");
	gotoxy(x, y++);
	cputs("n\tnew game");
	gotoxy(x, y++);
	cputs("o\trandom game");
	gotoxy(x, y++);
	cputs("p\tvalid numbers");
	gotoxy(x, y++);
	cputs("r\tresize board");
	gotoxy(x, y++);
	cputs("k\tcheck invalid");
	gotoxy(x, y++);
	cputs("j\tcheck determined");
	gotoxy(x, y++);
	cputs("w\twrite determined");
	gotoxy(x, y++);
	cputs("a\tauto mode");
	gotoxy(x, y++);
	cputs("ARROWS\tmove");
	gotoxy(x, y++);
	cputs("01\tinsert number");
	gotoxy(x, y++);
	char cursorPositionString[20];
	sprintf(cursorPositionString, "POS %d:%d", board->cursor_pos.y, board->cursor_pos.x);
	cputs(cursorPositionString);
	if (board->auto_mode.active) {
		gotoxy(x, ++y);
		cputs("AUTO MODE");
		if (!board->auto_mode.valid) {
			gotoxy(x, ++y);
			cputs("game cannot be completed");
		}
	}
}

void drawBoard(const board_t *board, int positionX, int positionY) {
	drawBoardFrame(board->size, positionX, positionY);
	int x = positionX + 2,
		y = positionY + 2;
	for (int ii = 0; ii < board->size; ++ii) {
		for (int jj = 0; jj < board->size; ++jj) {
			if (board->fields[ii][jj].visible) {
				gotoxy(x + jj, y + ii);
				if (board->fields[ii][jj].modifiable && board->fields[ii][jj].value != '.')
					textcolor(USER_INPUT_TEXT_COLOR);
				putch(board->fields[ii][jj].value);
				textcolor(TEXT_COLOR);
			}
		}
	}
	drawNumbers(board);
	drawCursor(board->cursor_pos.x, board->cursor_pos.y, 
		board->fields[board->cursor_pos.y][board->cursor_pos.x].value,
		positionX, positionY);
}

void drawBoardFrame(int size, int positionX, int positionY) {
	for (int ii = 0; ii < size + 2; ++ii) {
		gotoxy(positionX + ii + 1, positionY + 1);
		putch('#');
		gotoxy(positionX + ii + 1, positionY + size + 2);
		putch('#');
	}
	for (int ii = 0; ii < size; ++ii) {
		gotoxy(positionX + 1, positionY + ii + 2);
		putch('#');
		gotoxy(positionX + size + 2, positionY + ii + 2);
		putch('#');
	}
}

void drawNumbers(const board_t *board) {
	int positionX = board->board_pos.x + board->size + 4,
		positionY = board->board_pos.y + 2;
	for (int ii = 0; ii < board->size; ++ii) {
		char numbers[10];
		sprintf(numbers, "%d %d", countInRow(board, -1, ii, '0'), countInRow(board, -1, ii, '1'));
		gotoxy(positionX, positionY++);
		cputs(numbers);
	}

	positionX = board->board_pos.x + 2;
	positionY = board->board_pos.y + board->size + 3;
	for (int ii = 0; ii < board->size; ++ii) {
		char numbers[10];
		sprintf(numbers, "%d %d", countInCol(board, ii, -1, '0'), countInCol(board, ii, -1, '1'));
		int jj = 0;
		while (numbers[jj]) {
			gotoxy(positionX, positionY + jj);
			putch(numbers[jj]);
			jj++;
		}
		positionX++;
	}
}

void drawCursor(int x, int y, char c, int positionX, int positionY) {
	textbackground(CURSOR_COLOR);
	gotoxy(positionX + x + 2, positionY + y + 2);
	putch(c);
	textbackground(TEXT_BACKGROUND);
}

void drawPossible(board_t *board,  const rule_result_t ruleResult0, const rule_result_t ruleResult1) {
	clearScreen();
	int positionY = board->size > LEGEND_MAX_HEIGHT ? board->size + 2 : LEGEND_MAX_HEIGHT + 2;
	gotoxy(2, positionY);
	if (board->fields[board->cursor_pos.y][board->cursor_pos.x].modifiable == false) {
		cputs("Field not modifiable");
	}
	else {
		puts("valid values: ");
		gotoxy(2, ++positionY);
		if (ruleResult0.valid)
			cputs("0");
		if (ruleResult1.valid)
			cputs("1");
		if (!ruleResult0.valid) {
			gotoxy(2, ++positionY);
			puts("0 cannot be inserted:");
			positionY = drawError(board, &ruleResult0, positionY + 1);
		}
		if (!ruleResult1.valid) {
			gotoxy(2, ++positionY);
			puts("1 cannot be inserted:");
			drawError(board, &ruleResult1, positionY + 1);
		}
	}
}

int drawError(const board_t *board, const rule_result_t *ruleResult, int positionY) {
	gotoxy(2, positionY);
	if (!ruleResult->neighbours.valid) {
		if (ruleResult->neighbours.horizontalVertical == 0)
			cputs("Cannot put 3 same values in a row");
		else 
			cputs("Cannot put 3 same values in one below the other");
		gotoxy(2, ++positionY);
	}
	if (!ruleResult->half.valid) {
		if (ruleResult->half.horizontalVertical == 0)
			cputs("Number of the same values in a row cannot be larger than half of its size");
		else
			cputs("Number of the same values in a column cannot be larger than half of its size");
		gotoxy(2, ++positionY);
	}
	if (!ruleResult->ident.valid) {
		char message[MAX_ERROR_MESSAGE_LENGTH];
		if (ruleResult->ident.rowCol == 0) {
			sprintf(message, "Row identical to row %d", ruleResult->ident.index);
		}
		else {
			sprintf(message, "Column identical to column %d", ruleResult->ident.index);
		}
		cputs(message);
		positionY++;
	}
	return positionY;
}

void clearScreen() {
	system("cls");
}

void drawInputSize() {
	gotoxy(2, PADDING_TOP + 2);
	cputs("input size: ");
}

void highlightField(const board_t *board, int x, int y, int color) {
	textbackground(color);
	gotoxy(board->board_pos.x + 2 + x, board->board_pos.y + 2 + y);
	putch(board->fields[y][x].value);
	textbackground(TEXT_BACKGROUND);
}