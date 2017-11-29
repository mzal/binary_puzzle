#pragma once

#include <stdio.h>
#include "conio2.h"
#include "board.h"

#define LAYOUT 0
#define PADDING_TOP 1
#define LEGEND_WIDTH 30
#define CURSOR_COLOR CYAN
#define USER_INPUT_TEXT_COLOR YELLOW
#define TEXT_COLOR LIGHTGRAY
#define TEXT_BACKGROUND BLACK


void draw(const board_t *board);
void drawLegend(const board_t *board, int positionX, int positionY);
void drawBoard(const board_t *board, int positionX, int positionY);
void drawBoardFrame(int size, int positionX, int positionY);
void drawCursor(int x, int y, char c, int positionX, int positionY);