#include "GameLibrary.h"

void initGrid(GameBoard* board, States* states, Player* player) {
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

	displayGame(board, player);
}