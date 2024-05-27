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

Player::~Player() {
	name = "";
	bestScore = 0;
	playTime = 0;
}

void Player::operator=(const Player& other) {
	name = other.name;
	bestScore = other.bestScore;
	startTime = other.startTime;
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

bool checkNameExistence(List<Player>* rankings, string name) {
	for (
		Node<Player>* curNode = rankings->head;
		curNode != nullptr;
		curNode = curNode->next
		) {
		if (curNode->data.name == name) {
			return true;
		}
	}
	return false;
}
