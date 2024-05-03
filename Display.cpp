#include "GameLibrary.h"
#include <string>

void displayLobby(GameBoard* board, States* states) {
	cout << endl << endl;
	cout << endl << endl;

	for (int i = 0; i < R; i++) {
		cout << LONG_TAB;
		cout << COLOR_YELLOW << TWO[i] << "\t";
		cout << COLOR_GREEN << ZERO[i] << "\t";
		cout << COLOR_RED << FOUR[i] << "\t";
		cout << COLOR_CYAN << EIGHT[i] << endl;
		cout << COLOR_RESET;
	}

	cout << endl;
	cout << LONG_TAB << LONG_TAB << "\t\t\t\t" << "--- Remade By HUYDEPTRAIVKL ---";
	
	cout << endl << endl;
	cout << LONG_TAB << "\t\t\t" << "Press " << COLOR_YELLOW << "Space " << COLOR_RESET << "to play...";

	int userChoice = 0;
	while (true) {
		userChoice = _getch();
		if (userChoice == KEY_SPACE) {
			cout << endl << endl << endl;
			processEnterPlayerName(board, states);
			return;
		}
	}
}

void insertGridBorder(GameBoard* board, char c) {
	cout << "|";
	for (int j = 0; j < board->height; j++) {
		for (int k = 0; k < CELL_LENGTH; k++) {
			cout << c;
		}
		cout << "|";
	}
	cout << endl;
}

void displayInstruction() {
	cout << "Use your " << COLOR_GREEN << "arrow keys " << COLOR_RESET << "to move the tiles." << endl;
	cout << "Undo:         " << COLOR_YELLOW << "U" << COLOR_RESET << endl;
	cout << "Redo:         " << COLOR_YELLOW << "R" << COLOR_RESET << endl;
	cout << "New game:     " << COLOR_YELLOW << "N" << COLOR_RESET << endl;
	cout << "Change sizes: " << COLOR_YELLOW << "C" << COLOR_RESET << endl;
	cout << "Exit:         " << COLOR_YELLOW << "Esc" << COLOR_RESET << endl;
	cout << "Remember to " << COLOR_RED << "exit game " << COLOR_RESET << "before closing the console!!!" << endl;
}

void displayGame(GameBoard* board) {
	int& width = board->width;
	int& height = board->height;

	// clear screen
	system("CLS");

	// display score and best score
	displayScore(board);

	cout << endl;

	// display grid

	insertGridBorder(board, '-');

	for (int i = 0; i < width; i++) {
		cout << "|";
		for (int j = 0; j < height; j++) {
			cout << BG_COLOR[board->grid[i][j]];
			for (int k = 0; k < CELL_LENGTH; k++) {
				cout << " ";
			}
			cout << COLOR_RESET << "|";
		}
		cout << endl;

		cout << "|";
		for (int j = 0; j < board->height; j++) {
			int& value = board->grid[i][j];

			cout << BG_COLOR[value] << COLOR[value];

			int len = NUM_LENGTH[value]; // length of number at row i, column j
			int leftPadding = (CELL_LENGTH - len + 1) / 2;
			for (int k = 0; k < leftPadding; k++) cout << " ";

			if (len) cout << POW2[value];
			
			int rightPadding = CELL_LENGTH - leftPadding - len;
			for (int k = 0; k < rightPadding; k++) cout << " ";
			
			cout << COLOR_RESET << "|";
		}
		cout << endl;

		cout << "|";
		for (int j = 0; j < height; j++) {
			cout << BG_COLOR[board->grid[i][j]];
			for (int k = 0; k < CELL_LENGTH; k++) {
				cout << " ";
			}
			cout << COLOR_RESET << "|";
		}
		cout << endl;

		insertGridBorder(board, '-');
	}

	// display instruction
	cout << endl;
	displayInstruction();

	cout << endl;
}