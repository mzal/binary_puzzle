#pragma once

#include <stdio.h>
#include "conio2.h"
#include "board.h"
#include "rules.h"

#define LAYOUT 0
#define PADDING_TOP 1
#define GAP 8
#define LEGEND_WIDTH 30
#define LEGEND_MAX_HEIGHT 20
#define MAX_ERROR_MESSAGE_LENGTH 40
#define CURSOR_COLOR CYAN
#define USER_INPUT_TEXT_COLOR LIGHTGREEN
#define TEXT_COLOR LIGHTGRAY
#define TEXT_BACKGROUND BLACK
#define INVALID_HIGHLIGHT LIGHTRED

enum highlight_color {
	HIGHLIGHT_DETERMINED = YELLOW,
	HIGHLIGHT_INVALID = LIGHTRED
};


void draw(board_t *board);
void drawLegend(const board_t *board, int positionX, int positionY);
void drawBoard(const board_t *board, int positionX, int positionY);
void drawBoardFrame(int size, int positionX, int positionY);
void drawNumbers(const board_t *board);
void drawCursor(int x, int y, char c, int positionX, int positionY);
void drawPossible(board_t *board, const rule_result_t ruleResult0, const rule_result_t ruleResult1);
int drawError(const board_t *board, const rule_result_t *ruleResult, int positionY);
void clearScreen();
void drawInputSize();
void highlightField(const board_t *board, int x, int y, int color);