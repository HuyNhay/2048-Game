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

void saveRankPlayer(Encrypter& encrypter, Player player) {
	// write name
	encrypter.writeString(player.name);

	// write best score and time
	encrypter.writeInt(player.bestScore);
	encrypter.writeInt(player.playTime);
}