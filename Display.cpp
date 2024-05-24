#include "GameLibrary.h"
#include <string>

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

void displayInstruction(States* states) {
	cout << "Use your " << COLOR_GREEN << "arrow keys " << COLOR_RESET << "to move the tiles." << endl;
	if (states->activePrev) cout << "Undo:      " << COLOR_YELLOW << "U" << COLOR_RESET << "     ";
	if (states->activeNext) cout << "Redo:         " << COLOR_YELLOW << "R" << COLOR_RESET << endl;
	else if (states->activePrev) cout << endl;
	cout << "Rankings:  " << COLOR_YELLOW << "H" << COLOR_RESET << "     ";
	cout << "Change sizes: " << COLOR_YELLOW << "C" << COLOR_RESET << endl;
	cout << "New game:  " << COLOR_YELLOW << "N" << COLOR_RESET << "     ";
	cout << "Exit:         " << COLOR_YELLOW << "Esc" << COLOR_RESET << endl;
	cout << "Remember to " << COLOR_RED << "exit game " << COLOR_RESET << "before closing the console!!!" << endl;
}

void displayMainScreen(GameBoard* board, States* states, Player* player) {
	int& width = board->width;
	int& height = board->height;

	// clear screen
	system("CLS");

	// display score and best score
	displayScore(board, player);

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

			cout << BG_COLOR[value] << FONT_COLOR[value];

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
	displayInstruction(states);

	cout << endl;
}