#include "GameLibrary.h"

GameBoard::GameBoard() {
	grid = nullptr;
	width = 0;
	height = 0;
	score = 0;
	isWin = false;
}

void initGrid(GameBoard* board, States* states) {
	clearStates(states->prev);
	clearStates(states->next);

	board->isWin = 0;
	for (int i = 0; i < board->width; i++) {
		for (int j = 0; j < board->height; j++) {
			board->grid[i][j] = 0;
		}
	}
	
	board->score = 0;

	addRandomTile(board);
	addRandomTile(board);

	displayGame(board);
}