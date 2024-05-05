#include "GameLibrary.h"

Player::Player() {
	name = "";
	bestScore = 0;
}

Player::Player(string _name, int _bestScore) {
	name = _name;
	bestScore = _bestScore;
}

Player::~Player() {
	name = "";
	bestScore = 0;
}

void Player::operator=(const Player& other) {
	name = other.name;
	bestScore = other.bestScore;
}

void Player::writeToFile(ofstream& output) const {
	output << name << endl;
	output << bestScore << endl;
}

void Player::print() const {
	cout << name << endl << bestScore << endl;
}

