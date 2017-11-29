#include "board.h"
#include "control.h"

int main() {
	board_t board = createBoard(4, NULL);
	mainLoop(&board);
	destroyBoard(&board);
	return 0;
}
