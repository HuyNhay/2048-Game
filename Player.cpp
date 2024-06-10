#include "GameLibrary.h"

Player::Player() {
	name = "";
	bestScore = 0;
	playTime = 0;
}

Player::Player(string _name, int _bestScore, int _playTime) {
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

void saveRankPlayer(ofstream& output, Player player) {
	// write name
	int nameLength = (int)player.name.length();
	output.write((char*)&nameLength, sizeof(int));
	output.write(player.name.c_str(), nameLength);

	// write best score and time
	output.write((char*)&player.bestScore, sizeof(int));
	output.write((char*)&player.playTime, sizeof(int));
}