#include "GameLibrary.h"

bool maximize(int& target, const int& cand) {
	if (target >= cand) return false;
	target = cand;
	return true;
}

void updateScore(
	GameBoard* board, 
	User* user, 
	const int& value
) {
	board->score += value;
	if (maximize(user->bestScore, board->score)) {
		auto stopTime = high_resolution_clock::now();
		user->playTime = duration_cast<seconds>(stopTime - user->startTime).count() + user->addedTime;
	}
}

