#include "GameLibrary.h"

Player::Player() {
	name = "";
	bestScore = 0;
	addedTime = 0;
	playTime = 0;
}

Player::Player(string _name, int _bestScore, long long _playTime) {
	name = _name;
	bestScore = _bestScore;
	playTime = _playTime;
}

Player::~Player() {
	name = "";
	bestScore = 0;
	addedTime = 0;
	playTime = 0;
}

void Player::operator=(const Player& other) {
	name = other.name;
	bestScore = other.bestScore;
	startTime = other.startTime;
	addedTime = other.addedTime;
	playTime = other.playTime;
}

void Player::writeToFile(ofstream& output) const {
	output << name << endl;
	output << bestScore << endl;
	output << playTime << endl;
}

void Player::print() const {
	cout << name << endl << bestScore << endl;
}