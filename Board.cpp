#include "GameLibrary.h"

GameBoard::GameBoard() {
	grid = nullptr;
	width = 0;
	height = 0;
	score = 0;
	isWin = false;
}

GameBoard::~GameBoard() {
	clearMemory(this);
}