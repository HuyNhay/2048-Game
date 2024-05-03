#include "GameLibrary.h"

int GameBoard::bestScore = 0;

void displayScore(GameBoard* board) {
	cout << COLOR_GREEN << "SCORE:   " << board->score << COLOR_RESET << endl;
	cout << COLOR_YELLOW << "BEST:    " << GameBoard::bestScore << COLOR_RESET << endl;
}

void maximize(int& target, const int& cand) {
	if (target >= cand) return;
	target = cand;
}

void updateScore(GameBoard* board, const int& value) {
	board->score += value;
	maximize(GameBoard::bestScore, board->score);
}

