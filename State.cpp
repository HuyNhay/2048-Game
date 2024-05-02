#include "GameLibrary.h"

States::States() {}

States::~States() {}

GameBoard* copyState(GameBoard* board) {
	GameBoard* copyBoard = new GameBoard;

	changeDimension(copyBoard, board->width, board->height);

	copyBoard->score = board->score;
	copyBoard->bestScore = board->bestScore;
	copyBoard->isWin = board->isWin;

	for (int i = 0, width = board->width; i < width; i++) {
		for (int j = 0, height = board->height; j < height; j++) {
			copyBoard->grid[i][j] = board->grid[i][j];
		}
	}

	return copyBoard;
}

void pushState(Stack<GameBoard*>& states, GameBoard* board) {
	states.push(copyState(board));
}

void popState(Stack<GameBoard*>& states) {
	GameBoard* board = states.top();
	states.pop();
	deallocateGameBoard(board);
}

void clearStates(Stack<GameBoard*>& states) {
	while (states.getSize()) {
		popState(states);
	}
}