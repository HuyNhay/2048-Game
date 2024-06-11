#include "GameLibrary.h"

void saveUser(User* user) {
	ofstream output("User.bin", ios::binary);
	
	saveUserVitalInformation(user);
	saveUserOtherInformation(user);

	output.close();
}

void saveUserVitalInformation(User* user) {
	ofstream output("User.bin", ios::binary);

	// write name
	int nameLength = (int)user->name.length();
	output.write((char*)&nameLength, sizeof(int));
	output.write(user->name.c_str(), nameLength);

	// write score, resume
	output.write((char*)&user->bestScore, sizeof(int));
	output.write((char*)user->usedAccount, NUM_ACCOUNT * sizeof(bool));

	output.close();
}

void loadUserVitalInformation(User* user) {
	ifstream input("User.bin", ios::binary);

	if (!input.is_open()) {
		return;
	}

	// read name
	int nameLength = 0;
	input.read((char*)&nameLength, sizeof(int));
	char* buffer = new char[nameLength];
	input.read(buffer, nameLength);
	user->name = "";
	user->name.append(buffer, nameLength);
	delete[] buffer;

	// read score, resume
	input.read((char*)&user->bestScore, sizeof(int));
	input.read((char*)user->usedAccount, NUM_ACCOUNT * sizeof(bool));

	input.close();
}

void saveUserOtherInformation(User* user) {
	char type = (char)(user->resumeAccount + '1');
	string fileName = "User";
	fileName += type;
	fileName += ".bin";

	ofstream output(fileName, ios::binary);

	// write continuePlay, time
	output.write((char*)&user->continuePlay, sizeof(bool));
	output.write((char*)&user->playTime, sizeof(int));

	output.close();
}

void loadUserOtherInformation(User* user) {
	char type = (char)(user->resumeAccount + '1');
	string fileName = "User";
	fileName += type;
	fileName += ".bin";

	ifstream input(fileName, ios::binary);

	// read continuePlay, time
	input.read((char*)&user->continuePlay, sizeof(bool));
	input.read((char*)&user->addedTime, sizeof(int));

	user->startTime = high_resolution_clock::now();
	user->playTime = user->addedTime;

	input.close();
}


//void loadUser(User* user) {
//	ifstream input("User.bin", ios::binary);
//	if (!input.is_open()) {
//		return;
//	}
//
//	// read name
//	int nameLength = 0;
//	input.read((char*)&nameLength, sizeof(int));
//	char* buffer = new char[nameLength];
//	input.read(buffer, nameLength);
//	user->name = "";
//	user->name.append(buffer, nameLength);
//	delete[] buffer;
//
//	// read score, continuePlay, time
//	input.read((char*)&user->bestScore, sizeof(int));
//	input.read((char*)&user->continuePlay, sizeof(bool));
//	input.read((char*)&user->addedTime, sizeof(int));
//
//	user->startTime = high_resolution_clock::now();
//	user->playTime = user->addedTime;
//
//	input.close();
//}

void saveStates(States* states, User* user) {
	char type = (char)(user->resumeAccount + '1');

	string fileName = "StatesActive";
	fileName += type;
	fileName += ".bin";

	ofstream output(fileName, ios::binary);
	
	output.write((char*)&states->activePrev, sizeof(bool));
	output.write((char*)&states->activeNext, sizeof(bool));

	output.close();

	if (states->activePrev) {
		fileName = "PreviousStates";
		fileName += type;
		fileName += ".bin";

		output.open(fileName, ios::binary);
		
		int size = states->prev.getSize();
		output.write((char*)&size, sizeof(int));

		GameBoard* board = nullptr;
		while (states->prev.getSize()) {
			board = states->prev.top();
			
			output.write((char*)&board->width, sizeof(int));
			output.write((char*)&board->height, sizeof(int));
			output.write((char*)&board->score, sizeof(int));
			output.write((char*)&board->isWin, sizeof(bool));

			for (int i = 0; i < board->width; i++) {
				for (int j = 0; j < board->height; j++) {
					output.write((char*)&board->grid[i][j], sizeof(int));
				}
			}

			states->prev.pop();

			delete board;
		}
		output.close();
	}

	if (states->activeNext) {
		fileName = "NextStates";
		fileName += type;
		fileName += ".bin";

		output.open(fileName, ios::binary);

		int size = states->next.getSize();
		output.write((char*)&size, sizeof(int));

		GameBoard* board = nullptr;
		while (states->next.getSize()) {
			board = states->next.top();

			output.write((char*)&board->width, sizeof(int));
			output.write((char*)&board->height, sizeof(int));
			output.write((char*)&board->score, sizeof(int));
			output.write((char*)&board->isWin, sizeof(bool));

			for (int i = 0; i < board->width; i++) {
				for (int j = 0; j < board->height; j++) {
					output.write((char*)&board->grid[i][j], sizeof(int));
				}
			}

			states->next.pop();

			delete board;
		}
		output.close();
	}
}

void loadStatesActiveStatus(States* states, User* user) {
	char type = (char)(user->resumeAccount + '1');
	string fileName = "StatesActive";
	fileName += type;
	fileName += ".bin";

	ifstream input(fileName, ios::binary);

	if (!input.is_open()) {
		return;
	}

	input.read((char*)&states->activePrev, sizeof(int));
	input.read((char*)&states->activeNext, sizeof(int));

	input.close();
}

void saveGameBoard(GameBoard* board, User* user) {
	char type = (char)(user->resumeAccount + '1');
	string fileName = "Board";
	fileName += type;
	fileName += ".bin";

	ofstream output(fileName, ios::binary);

	output.write((char*)&board->width, sizeof(int));
	output.write((char*)&board->height, sizeof(int));
	output.write((char*)&board->score, sizeof(int));
	output.write((char*)&board->isWin, sizeof(bool));

	for (int i = 0; i < board->width; i++) {
		for (int j = 0; j < board->height; j++) {
			output.write((char*)&board->grid[i][j], sizeof(int));
		}
	}

	output.close();
}

void loadGameBoard(GameBoard* board, User* user) {
	char type = (char)(user->resumeAccount + '1');
	string fileName = "Board";
	fileName += type;
	fileName += ".bin";

	ifstream input(fileName, ios::binary);

	if (!input.is_open()) {
		return;
	}

	clearMemory(board);

	input.read((char*)&board->width, sizeof(int));
	input.read((char*)&board->height, sizeof(int));
	input.read((char*)&board->score, sizeof(int));
	input.read((char*)&board->isWin, sizeof(bool));

	board->grid = new int* [board->width];
	for (int i = 0; i < board->width; i++) {
		board->grid[i] = new int[board->height];
	}

	for (int i = 0; i < board->width; i++) {
		for (int j = 0; j < board->height; j++) {
			input.read((char*)&board->grid[i][j], sizeof(int));
		}
	}

	input.close();
}

void loadPrevStates(States* states, User* user) {
	char type = (char)(user->resumeAccount + '1');
	string fileName = "PreviousStates";
	fileName += type;
	fileName += ".bin";

	ifstream input(fileName, ios::binary);

	if (!input.is_open()) {
		return;
	}

	// read size
	int size = 0;
	input.read((char*)&size, sizeof(int));

	while (size--) {
		GameBoard* board = new GameBoard();

		input.read((char*)&board->width, sizeof(int));
		input.read((char*)&board->height, sizeof(int));
		input.read((char*)&board->score, sizeof(int));
		input.read((char*)&board->isWin, sizeof(bool));

		board->grid = new int* [board->width];
		for (int i = 0; i < board->width; i++) {
			board->grid[i] = new int[board->height];
		}

		for (int i = 0; i < board->width; i++) {
			for (int j = 0; j < board->height; j++) {
				input.read((char*)&board->grid[i][j], sizeof(int));
			}
		}
		
		states->prev.pushTail(board);
	}

	input.close();
}

void loadNextStates(States* states, User* user) {
	char type = (char)(user->resumeAccount + '1');
	string fileName = "NextStates";
	fileName += type;
	fileName += ".bin";

	ifstream input(fileName, ios::binary);

	if (!input.is_open()) {
		return;
	}

	// read size
	int size = 0;
	input.read((char*)&size, sizeof(int));

	while (size--) {
		GameBoard* board = new GameBoard();

		input.read((char*)&board->width, sizeof(int));
		input.read((char*)&board->height, sizeof(int));
		input.read((char*)&board->score, sizeof(int));
		input.read((char*)&board->isWin, sizeof(bool));

		board->grid = new int* [board->width];
		for (int i = 0; i < board->width; i++) {
			board->grid[i] = new int[board->height];
		}

		for (int i = 0; i < board->width; i++) {
			for (int j = 0; j < board->height; j++) {
				input.read((char*)&board->grid[i][j], sizeof(int));
			}
		}

		states->next.pushTail(board);
	}

	input.close();
}

void saveResumeGame(
	GameBoard* board,
	States* states,
	User* user
) {
	saveUser(user);
	saveStates(states, user);
	saveGameBoard(board, user);
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

	string fileName = "Board";
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