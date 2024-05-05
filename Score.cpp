#include "GameLibrary.h"

void displayScore(GameBoard* board, Player* player) {
	cout << COLOR_GREEN << "SCORE:   " << board->score << COLOR_RESET << endl;
	cout << COLOR_YELLOW << "BEST:    " << player->bestScore << COLOR_RESET << endl;
}

bool maximize(int& target, const int& cand) {
	if (target >= cand) return false;
	target = cand;
	return true;
}

void updateScore(
	GameBoard* board, 
	Player* player, 
	const int& value
) {
	board->score += value;
	maximize(player->bestScore, board->score);
}

