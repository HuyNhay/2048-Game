#include "GameLibrary.h"

void savePlayer(Player* player) {
	ofstream output("Player.txt");
	
	output << player->name << endl;
	output << player->bestScore << endl;
	output << player->playTime << endl;

	output.close();
}

void loadPlayer(Player* player) {
	ifstream input("Player.txt");
	if (!input.is_open()) {
		return;
	}

	getline(input, player->name);
	input >> player->bestScore;
	input >> player->addedTime;
	player->startTime = player->startTime = high_resolution_clock::now();
	player->playTime = player->addedTime;

	input.close();
}

void saveStates(States* states) {
	ofstream output("StatesActive.txt");
	
	output << states->activePrev << endl;
	output << states->activeNext << endl;

	output.close();

	if (states->activePrev) {
		output.open("PreviousStates.txt");
		GameBoard* board = nullptr;
		while (states->prev.getSize()) {
			board = states->prev.top();
			
			output << board->width << endl;
			output << board->height << endl;
			output << board->score << endl;
			output << board->isWin << endl;

			for (int i = 0; i < board->width; i++) {
				for (int j = 0; j < board->height; j++) {
					output << board->grid[i][j] << " ";
				}
				//output << endl;
			}

			states->prev.pop();

			delete board;
		}
		output.close();
	}

	if (states->activeNext) {
		output.open("NextStates.txt");
		GameBoard* board = nullptr;
		while (states->next.getSize()) {
			board = states->next.top();

			output << board->width << endl;
			output << board->height << endl;
			output << board->score << endl;
			output << board->isWin << endl;

			for (int i = 0; i < board->width; i++) {
				for (int j = 0; j < board->height; j++) {
					output << board->grid[i][j] << " ";
				}
			}

			states->next.pop();

			delete board;
		}
		output.close();
	}
}

void loadStatesActiveStatus(States* states) {
	ifstream input("StatesActive.txt");
	if (!input.is_open()) {
		return;
	}

	input >> states->activePrev;
	input >> states->activeNext;

	input.close();
}

void saveGameBoard(GameBoard* board) {
	ofstream output("Board.txt");

	output << board->width << endl;
	output << board->height << endl;
	output << board->score << endl;
	output << board->isWin << endl;

	for (int i = 0; i < board->width; i++) {
		for (int j = 0; j < board->height; j++) {
			output << board->grid[i][j] << " ";
		}
		output << endl;
	}

	output.close();
}

void loadGameBoard(GameBoard* board) {
	ifstream input("Board.txt");
	if (!input.is_open()) {
		return;
	}

	clearMemory(board);

	input >> board->width;
	input >> board->height;
	input >> board->score;
	input >> board->isWin;

	board->grid = new int* [board->width];
	for (int i = 0; i < board->width; i++) {
		board->grid[i] = new int[board->height];
	}
	for (int i = 0; i < board->width; i++) {
		for (int j = 0; j < board->height; j++) {
			input >> board->grid[i][j];
		}
	}

	input.close();
}

void loadPrevStates(States* states) {
	ifstream input("PreviousStates.txt");
	if (!input.is_open()) {
		return;
	}

	while (true) {
		GameBoard* board = new GameBoard();
		if (
			input >> board->width &&
			input >> board->height && 
			input >> board->score &&
			input >> board->isWin
			) {

			board->grid = new int* [board->width];
			for (int i = 0; i < board->width; i++) {
				board->grid[i] = new int[board->height];
			}

			for (int i = 0; i < board->width; i++) {
				for (int j = 0; j < board->height; j++) {
					input >> board->grid[i][j];
				}
			}

			states->prev.pushTail(board);
		}
		else {
			delete board;
			break;
		}
	}
	input.close();
}

void loadNextStates(States* states) {
	ifstream input("NextStates.txt");
	if (!input.is_open()) {
		return;
	}

	while (true) {
		GameBoard* board = new GameBoard();
		if (
			input >> board->width &&
			input >> board->height &&
			input >> board->score &&
			input >> board->isWin
			) {

			board->grid = new int* [board->width];
			for (int i = 0; i < board->width; i++) {
				board->grid[i] = new int[board->height];
			}

			for (int i = 0; i < board->width; i++) {
				for (int j = 0; j < board->height; j++) {
					input >> board->grid[i][j];
				}
			}

			states->next.pushTail(board);
		}
		else {
			delete board;
			break;
		}
	}
	input.close();
}

void saveResumeGame(
	GameBoard* board,
	States* states,
	List<Player>* rankings,
	Player* player
) {
	savePlayer(player);
	saveStates(states);
	saveGameBoard(board);
}