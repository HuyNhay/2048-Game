#include "GameLibrary.h"

User::User() {
	name = "";
	bestScore = 0;
	continuePlay = false;
	addedTime = 0;
	playTime = 0;
}

User::User(string _name, int _bestScore, bool _continuePlay, int _addedTime, int _playTime) {
	name = _name;
	bestScore = _bestScore;
	continuePlay = _continuePlay;
	addedTime = _addedTime;
	playTime = _playTime;
}

User::~User() {
	name = "";
	bestScore = 0;
	continuePlay = false;
	addedTime = 0;
	playTime = 0;
}

void User::operator=(const User& other) {
	name = other.name;
	bestScore = other.bestScore;
	continuePlay = other.continuePlay;
	startTime = other.startTime;
	addedTime = other.addedTime;
	playTime = other.playTime;
}