#include "GameLibrary.h"

Player::Player() {
	name = "";
	bestScore = 0;
	playTime = 0;
}

Player::Player(string _name, int _bestScore, long long _playTime) {
	name = _name;
	bestScore = _bestScore;
	playTime = _playTime;
}

Player::Player(const User& user) {
	name = user.name;
	bestScore = user.bestScore;
	playTime = user.playTime;
}

Player::~Player() {
	name = "";
	bestScore = 0;
	playTime = 0;
}

void Player::operator=(const Player& other) {
	name = other.name;
	bestScore = other.bestScore;
	playTime = other.playTime;
}

void savePlayer(ofstream& output, Player player) {
	output << player.name << endl;
	output << player.bestScore << endl;
	output << player.playTime << endl;

}
