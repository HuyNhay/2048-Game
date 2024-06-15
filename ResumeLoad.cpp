#include "GameLibrary.h"

void loadUserVitalInformation(User* user) {
	Decrypter decrypter("User.bin");

	if (!decrypter.input.is_open()) {
		return;
	}

	// read name
	user->name = decrypter.readString();

	// read score, resume
	user->bestScore = decrypter.readInt();
	decrypter.readBoolArray(user->usedAccount, NUM_ACCOUNT);
}

void loadUserOtherInformation(User* user) {
	char type = (char)(user->resumeAccount + '1');
	string fileName = "User";
	fileName += type;
	fileName += ".bin";

	Decrypter decrypter(fileName);

	if (!decrypter.input.is_open()) {
		return;
	}

	// read continuePlay, time
	user->continuePlay = decrypter.readBool();
	user->addedTime = decrypter.readInt();

	user->startTime = high_resolution_clock::now();
	user->playTime = user->addedTime;
}

void loadStatesActiveStatus(States* states, User* user) {
	char type = (char)(user->resumeAccount + '1');
	string fileName = "StatesActive";
	fileName += type;
	fileName += ".bin";

	Decrypter decrypter(fileName);

	if (!decrypter.input.is_open()) {
		return;
	}
	
	states->activePrev = decrypter.readBool();
	states->activeNext = decrypter.readBool();
}

void loadPrevStates(States* states, User* user) {
	char type = (char)(user->resumeAccount + '1');
	string fileName = "PreviousStates";
	fileName += type;
	fileName += ".bin";

	Decrypter decrypter(fileName);

	if (!decrypter.input.is_open()) {
		return;
	}

	// read size
	int size = decrypter.readInt();

	while (size--) {
		GameBoard* board = new GameBoard();

		board->width = decrypter.readInt();
		board->height = decrypter.readInt();
		board->score = decrypter.readInt();
		board->isWin = decrypter.readBool();

		board->grid = new int* [board->width];
		for (int i = 0; i < board->width; i++) {
			board->grid[i] = new int[board->height];
		}

		for (int i = 0; i < board->width; i++) {
			for (int j = 0; j < board->height; j++) {
				board->grid[i][j] = decrypter.readInt();
			}
		}

		states->prev.pushTail(board);
	}
}

void loadNextStates(States* states, User* user) {
	char type = (char)(user->resumeAccount + '1');
	string fileName = "NextStates";
	fileName += type;
	fileName += ".bin";

	Decrypter decrypter(fileName);

	if (!decrypter.input.is_open()) {
		return;
	}

	// read size
	int size = decrypter.readInt();

	while (size--) {
		GameBoard* board = new GameBoard();

		board->width = decrypter.readInt();
		board->height = decrypter.readInt();
		board->score = decrypter.readInt();
		board->isWin = decrypter.readBool();

		board->grid = new int* [board->width];
		for (int i = 0; i < board->width; i++) {
			board->grid[i] = new int[board->height];
		}

		for (int i = 0; i < board->width; i++) {
			for (int j = 0; j < board->height; j++) {
				board->grid[i][j] = decrypter.readInt();
			}
		}

		states->next.pushTail(board);
	}
}

void loadGameBoard(GameBoard* board, User* user) {
	char type = (char)(user->resumeAccount + '1');
	string fileName = "Board";
	fileName += type;
	fileName += ".bin";

	Decrypter decrypter(fileName);

	if (!decrypter.input.is_open()) {
		return;
	}

	clearMemory(board);

	board->width = decrypter.readInt();
	board->height = decrypter.readInt();
	board->score = decrypter.readInt();
	board->isWin = decrypter.readBool();

	board->grid = new int* [board->width];
	for (int i = 0; i < board->width; i++) {
		board->grid[i] = new int[board->height];
	}

	for (int i = 0; i < board->width; i++) {
		for (int j = 0; j < board->height; j++) {
			board->grid[i][j] = decrypter.readInt();
		}
	}
}

void loadResumeGame(
	GameBoard* board,
	States* states,
	User* user
) {
	loadUserOtherInformation(user);
	loadStatesActiveStatus(states, user);
	loadGameBoard(board, user);
	if (states->activePrev) {
		loadPrevStates(states, user);
	}
	if (states->activeNext) {
		loadNextStates(states, user);
	}

}

void clearResumeGame(int account) {
	char type = (char)(account + '1');
	string fileName = "";

	fileName = "Board";
	fileName += type;
	fileName += ".bin";
	ofstream output(fileName, ios::trunc);
	output.close();

	fileName = "Board";
	fileName += type;
	fileName += ".bin";
	output.open(fileName, ios::trunc);
	output.close();

	fileName = "NextStates";
	fileName += type;
	fileName += ".bin";
	output.open(fileName, ios::trunc);
	output.close();

	fileName = "PreviousStates";
	fileName += type;
	fileName += ".bin";
	output.open(fileName, ios::trunc);
	output.close();

	fileName = "StatesActive";
	fileName += type;
	fileName += ".bin";
	output.open(fileName, ios::trunc);
	output.close();

	fileName = "User";
	fileName += type;
	fileName += ".bin";
	output.open(fileName, ios::trunc);
	output.close();
}