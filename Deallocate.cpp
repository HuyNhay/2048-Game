#include "GameLibrary.h"

void clearMemory(GameBoard* board) {
	board->score = 0;
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

void deallocateGame(
	GameBoard* board, 
	States* states, 
	List<Player>* rankings, 
	Player* player
) {
	delete board;
	delete states;
	delete rankings;
	delete player;
}
