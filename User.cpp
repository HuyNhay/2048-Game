#include "GameLibrary.h"

User::User() {
	name = "";
	bestScore = 0;
	for (int i = 0; i < NUM_ACCOUNT; i++) {
		usedAccount[i] = false;
	}

	continuePlay = false;
	addedTime = 0;
	playTime = 0;
	resumeAccount = 0;
}

User::User(string _name, int _bestScore, bool _continuePlay, int _addedTime, int _playTime) {
	name = _name;
	bestScore = _bestScore;
	for (int i = 0; i < NUM_ACCOUNT; i++) {
		usedAccount[i] = false;
	}

	continuePlay = _continuePlay;
	addedTime = _addedTime;
	playTime = _playTime;
	resumeAccount = 0;
}

User::~User() {
	name = "";
	bestScore = 0;
	for (int i = 0; i < NUM_ACCOUNT; i++) {
		usedAccount[i] = false;
	}

	continuePlay = false;
	addedTime = 0;
	playTime = 0;
	resumeAccount = 0;
}

void User::operator=(const User& other) {
	name = other.name;
	bestScore = other.bestScore;
	for (int i = 0; i < NUM_ACCOUNT; i++) {
		usedAccount[i] = other.usedAccount[i];
	}

	continuePlay = other.continuePlay;
	startTime = other.startTime;
	addedTime = other.addedTime;
	playTime = other.playTime;
	resumeAccount = other.resumeAccount;
}