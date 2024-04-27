#include "GameLibrary.h"

void addRandomTile(GameBoard* board) {
	int isFulfilled = 1; // use to check if grid is fulfilled of value greater than 0
	for (int i = 0; i < board->width; i++) {
		for (int j = 0; j < board->height; j++) {
			if (board->grid[i][j] == 0) isFulfilled = 0;
		}
	}
	if (isFulfilled) return;

	int i, j;
	while (true) {
		i = rand() % board->width;
		j = rand() % board->height;
		if (board->grid[i][j]) continue;
		board->grid[i][j] = (rand() % 10 < 9 ? 1 : 2);
		break;
	}
}