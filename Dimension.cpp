#include "GameLibrary.h"

void changeDimension(GameBoard* board, int width, int height) {
	clearMemory(board);

	board->width = width;
	board->height = height;

	board->grid = new int* [board->width];
	for (int i = 0; i < board->width; i++) {
		board->grid[i] = new int[board->height];
	}
}