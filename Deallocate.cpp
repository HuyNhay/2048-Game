#include "GameLibrary.h"

void clearMemory(GameBoard* board) {
	board->score = 0;
	board->bestScore = 0;
	board->isWin = 0;

	if (board->grid == nullptr) return;
	if (board->width == 0) return;
	for (int i = 0; i < board->width; i++) {
		delete[] board->grid[i];
	}
	delete[] board->grid;

	board->grid = nullptr;

	board->width = 0;
	board->height = 0;
}

void deallocateGameBoard(GameBoard* board) {
	clearMemory(board);
	delete board;
}

void deallocateGame(GameBoard* board, States* states) {
	deallocateGameBoard(board);
	clearStates(states->prev);
	clearStates(states->next);
	delete states;
}
