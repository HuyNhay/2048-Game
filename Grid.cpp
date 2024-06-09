#include "GameLibrary.h"

void changeGridSizes(GameBoard* board, int width, int height) {
	clearMemory(board);

	board->width = width;
	board->height = height;

	board->grid = new int* [board->width];
	for (int i = 0; i < board->width; i++) {
		board->grid[i] = new int[board->height];
	}
}

void initGrid(GameBoard* board, States* states, User* user) {
	if (states->activePrev) clearStates(states->prev);
	if (states->activeNext) clearStates(states->next);

	user->startTime = high_resolution_clock::now();
	user->addedTime = 0;
	user->continuePlay = false;

	board->isWin = 0;
	for (int i = 0; i < board->width; i++) {
		for (int j = 0; j < board->height; j++) {
			board->grid[i][j] = 0;
		}
	}

	board->score = 0;

	addRandomTile(board);
	addRandomTile(board);

	displayMainScreen(board, states, user);
}

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