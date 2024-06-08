#include "GameLibrary.h"

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
	if (maximize(player->bestScore, board->score)) {
		auto stopTime = high_resolution_clock::now();
		player->playTime = duration_cast<seconds>(stopTime - player->startTime).count() + player->addedTime;
	}
}

