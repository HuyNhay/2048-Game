#include "GameLibrary.h"

void saveUser(User* user) {
	ofstream output("User.bin", ios::binary);
	
	// write name
	int nameLength = (int)user->name.length();
	output.write((char*)&nameLength, sizeof(int));
	output.write(user->name.c_str(), nameLength);

	// write score, continuePlay, time
	output.write((char*)&user->bestScore, sizeof(int));
	output.write((char*)&user->continuePlay, sizeof(bool));
	output.write((char*)&user->playTime, sizeof(int));

	output.close();
}

void loadUser(User* user) {
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

	// read score, continuePlay, time
	input.read((char*)&user->bestScore, sizeof(int));
	input.read((char*)&user->continuePlay, sizeof(bool));
	input.read((char*)&user->addedTime, sizeof(int));

	user->startTime = high_resolution_clock::now();
	user->playTime = user->addedTime;

	input.close();
}

void saveStates(States* states) {
	ofstream output("StatesActive.bin", ios::binary);
	
	output.write((char*)&states->activePrev, sizeof(bool));
	output.write((char*)&states->activeNext, sizeof(bool));

	output.close();

	if (states->activePrev) {
		output.open("PreviousStates.bin", ios::binary);
		
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
		output.open("NextStates.bin", ios::binary);

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

void loadStatesActiveStatus(States* states) {
	ifstream input("StatesActive.bin", ios::binary);
	if (!input.is_open()) {
		return;
	}

	input.read((char*)&states->activePrev, sizeof(int));
	input.read((char*)&states->activeNext, sizeof(int));

	input.close();
}

void saveGameBoard(GameBoard* board) {
	ofstream output("Board.bin", ios::binary);

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

void loadGameBoard(GameBoard* board) {
	ifstream input("Board.bin", ios::binary);
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

void loadPrevStates(States* states) {
	ifstream input("PreviousStates.bin", ios::binary);
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

void loadNextStates(States* states) {
	ifstream input("NextStates.bin", ios::binary);
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
	saveStates(states);
	saveGameBoard(board);
}