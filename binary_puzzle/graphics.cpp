#define _CRT_SECURE_NO_WARNINGS
#include "graphics.h"
#include <stdlib.h>
#include <string.h>

void draw(const board_t *board) {
#ifndef __cplusplus
	Conio2_Init();
#endif
	settitle("Michal Zalewski 171671");
	textbackground(TEXT_BACKGROUND);
	textcolor(TEXT_COLOR);
	clrscr();
	_setcursortype(_NOCURSOR);
	if (LAYOUT == 0) {
		drawLegend(board, 0, PADDING_TOP);
		drawBoard(board, LEGEND_WIDTH + 1, PADDING_TOP);
	}
	else {
		drawLegend(board, board->size + 3, PADDING_TOP);
		drawBoard(board, 0, PADDING_TOP);
	}

}

void drawLegend(const board_t *board, int positionX, int positionY) {
	int x = positionX + 2,
		y = positionY + 2,
		height = board->size + 2;
	gotoxy(x, y++);
	cputs("Michal Zalewski 171671");
	gotoxy(x, y++);
	cputs("abcd");
	gotoxy(x, y++);
	cputs("ESC\t\tquit");
	gotoxy(x, y++);
	cputs("ARROW KEYS\tmove");
	gotoxy(x, y++);
	cputs("01\t\tinsert number");
	gotoxy(x, y++);
	char cursorPositionString[20];
	sprintf(cursorPositionString, "POS %d:%d", board->cursor_pos.y, board->cursor_pos.x);
	cputs(cursorPositionString);
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

void drawCursor(int x, int y, char c, int positionX, int positionY) {
	textbackground(CURSOR_COLOR);
	gotoxy(positionX + x + 2, positionY + y + 2);
	putch(c);
	textbackground(TEXT_BACKGROUND);
}