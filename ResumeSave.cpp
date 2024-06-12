#include "GameLibrary.h"

void saveUser(User* user) {
	ofstream output("User.bin", ios::binary);

	saveUserVitalInformation(user);
	saveUserOtherInformation(user);

	output.close();
}

void saveUserVitalInformation(User* user) {
	Encrypter encrypter("User.bin");

	// write name
	encrypter.writeString(user->name);

	// write score, resume
	encrypter.writeInt(user->bestScore);
	encrypter.writeBoolArray(user->usedAccount, NUM_ACCOUNT);
}

void saveUserOtherInformation(User* user) {
	char type = (char)(user->resumeAccount + '1');
	string fileName = "User";
	fileName += type;
	fileName += ".bin";

	Encrypter encrypter(fileName);

	// write continuePlay, time
	encrypter.writeBool(user->continuePlay);
	encrypter.writeInt(user->playTime);
	}

void saveStates(States* states, User* user) {
	char type = (char)(user->resumeAccount + '1');

	string fileName = "StatesActive";
	fileName += type;
	fileName += ".bin";

	Encrypter encrypter(fileName);

	encrypter.writeBool(states->activePrev);
	encrypter.writeBool(states->activeNext);

	if (states->activePrev) {
		fileName = "PreviousStates";
		fileName += type;
		fileName += ".bin";

		encrypter.openFile(fileName);

		int size = states->prev.getSize();
		encrypter.writeInt(size);

		GameBoard* board = nullptr;
		while (states->prev.getSize()) {
			board = states->prev.top();

			encrypter.writeInt(board->width);
			encrypter.writeInt(board->height);
			encrypter.writeInt(board->score);
			encrypter.writeBool(board->isWin);

			for (int i = 0; i < board->width; i++) {
				for (int j = 0; j < board->height; j++) {
					encrypter.writeInt(board->grid[i][j]);
				}
			}

			states->prev.pop();

			delete board;
		}
	}

	if (states->activeNext) {
		fileName = "NextStates";
		fileName += type;
		fileName += ".bin";

		encrypter.openFile(fileName);

		int size = states->next.getSize();
		encrypter.writeInt(size);

		GameBoard* board = nullptr;
		while (states->next.getSize()) {
			board = states->next.top();

			encrypter.writeInt(board->width);
			encrypter.writeInt(board->height);
			encrypter.writeInt(board->score);
			encrypter.writeBool(board->isWin);

			for (int i = 0; i < board->width; i++) {
				for (int j = 0; j < board->height; j++) {
					encrypter.writeInt(board->grid[i][j]);
				}
			}

			states->next.pop();

			delete board;
		}
	}
}

void saveGameBoard(GameBoard* board, User* user) {
	char type = (char)(user->resumeAccount + '1');
	string fileName = "Board";
	fileName += type;
	fileName += ".bin";

	Encrypter encrypter(fileName);

	encrypter.writeInt(board->width);
	encrypter.writeInt(board->height);
	encrypter.writeInt(board->score);
	encrypter.writeBool(board->isWin);

	for (int i = 0; i < board->width; i++) {
		for (int j = 0; j < board->height; j++) {
			encrypter.writeInt(board->grid[i][j]);
		}
	}
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
