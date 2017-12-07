#pragma once
#include <stdbool.h>
#include "board.h"

struct rule_result_t {
	bool valid = true;
	struct {
		bool valid = true;
		bool horizontalVertical;
	} neighbours;
	struct {
		bool valid = true;
		bool horizontalVertical;
	} half;
	struct {
		bool valid = true;
		bool rowCol;
		int index;
	} ident;
};

rule_result_t checkRules(const board_t *board, int x, int y, char value);
rule_result_t checkNeighboursRule(const board_t *board, int x, int y, char value);
rule_result_t checkHalfRule(const board_t *board, int x, int y, char value);
int countInRow(const board_t *board, int x, int y, char value);
int countInCol(const board_t *board, int x, int y, char value);
rule_result_t checkIdentRowColRule(const board_t *board, int x, int y, char value);