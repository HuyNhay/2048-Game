#include "GameLibrary.h"

void displayLobby(bool resumeAvailable) {
	system("CLS");

	cout << COLOR_MAGENTA << "Exit: Esc" << COLOR_RESET << endl;
	cout << endl;
	cout << endl << endl;

	for (int i = 0; i < R; i++) {
		cout << LONG_TAB << " ";
		cout << COLOR_YELLOW << TWO[i] << "\t";
		cout << COLOR_GREEN << ZERO[i] << "\t";
		cout << COLOR_RED << FOUR[i] << "\t";
		cout << COLOR_CYAN << EIGHT[i] << endl;
		cout << COLOR_RESET;
	}

	cout << endl;
	cout << LONG_TAB << LONG_TAB << "\t\t\t\t" << "--- Remade By HUYDEPTRAIVKL ---";
	cout << endl << endl << endl;

	cout << TAB << "       ";
	cout << COLOR_YELLOW << "New game: G" << COLOR_RESET;
	cout << TAB << "|" << TAB;
	cout << COLOR_GREEN << "Settings: S" << COLOR_RESET;
	cout << TAB << "|" << TAB;
	cout << COLOR_RED << "Rankings: H" << COLOR_RESET;
	cout << TAB << "|" << TAB;
	cout << COLOR_CYAN << "Resume: R ";
	if (!resumeAvailable) cout << "(Error)";
	cout << COLOR_RESET;
	cout << endl;
	cout << endl << endl;
}

void displaySettings(GameBoard* board, States* states) {
	system("CLS");

	cout << "      " << COLOR_ORANGE << "SETTINGS" << COLOR_RESET << endl;
	cout << endl;

	cout << COLOR_ORANGE << " Grid sizes: " << COLOR_RESET
		<< board->width << "x" << board->height << endl;
	cout << COLOR_ORANGE << " Game mode: " << COLOR_RESET;
	cout << "Undo: "
		<< COLOR_YELLOW << (states->activePrev ? "ON" : "OFF") << COLOR_RESET << ", ";
	cout << "Redo: "
		<< COLOR_YELLOW << (states->activeNext ? "ON" : "OFF") << COLOR_RESET << endl;
	cout << endl << endl;

	cout << " ----------------------------------------" << endl;
	cout << " Change grid sizes: " << COLOR_YELLOW << "C" << COLOR_RESET << endl;
	cout << " Change game mode:  " << COLOR_YELLOW << "M" << COLOR_RESET << endl;
	cout << " Back to lobby:     " << COLOR_YELLOW << "Space" << COLOR_RESET << endl;
	cout << endl << endl;
}

void displayGridBorder(GameBoard* board, char c) {
	cout << "+";
	for (int j = 0; j < board->height; j++) {
		for (int k = 0; k < CELL_LENGTH; k++) {
			cout << c;
		}
		cout << "+";
	}
	cout << endl;
}

void displayEmptyRow(GameBoard* board, int i) {
	cout << "|";
	for (int j = 0; j < board->height; j++) {
		cout << BG_COLOR[board->grid[i][j]];
		for (int k = 0; k < CELL_LENGTH; k++) {
			cout << " ";
		}
		cout << COLOR_RESET << "|";
	}
	cout << endl;
}

void displayScore(GameBoard* board, User* user) {
	cout << COLOR_GREEN << "SCORE:   " << board->score << COLOR_RESET << endl;
	cout << COLOR_YELLOW << "BEST:    " << user->bestScore << COLOR_RESET << endl;
	cout << endl;
}

void displayInstruction(States* states) {
	cout << "Use your " << COLOR_GREEN << "arrow keys " << COLOR_RESET << "to move the tiles." << endl;
	if (states->activePrev) cout << "Undo:      " << COLOR_YELLOW << "U" << COLOR_RESET << "     ";
	if (states->activeNext) cout << "Redo:         " << COLOR_YELLOW << "R" << COLOR_RESET << endl;
	else if (states->activePrev) cout << endl;
	cout << "Rankings:  " << COLOR_YELLOW << "H" << COLOR_RESET << "     ";
	cout << "Change sizes: " << COLOR_YELLOW << "C" << COLOR_RESET << endl;
	cout << "New game:  " << COLOR_YELLOW << "G" << COLOR_RESET << "     ";
	cout << "Exit:         " << COLOR_YELLOW << "Esc" << COLOR_RESET << endl;
	cout << "Remember to " << COLOR_RED << "exit game " << COLOR_RESET << "before closing the console!!!" << endl;
}

void displayGrid(GameBoard* board) {
	int& width = board->width;
	int& height = board->height;

	displayGridBorder(board, '-');

	for (int i = 0; i < width; i++) {
		if (width < 6) displayEmptyRow(board, i);

		// display row with value of the tiles
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

		if (width < 6) displayEmptyRow(board, i);

		displayGridBorder(board, '-');
	}

	cout << endl;
}

void displayMainScreen(GameBoard* board, States* states, User* user) {
	// clear screen
	system("CLS");

	// display score and best score
	displayScore(board, user);

	// display grid
	displayGrid(board);

	// display instruction
	displayInstruction(states);

	cout << endl;
}

void displayVictoryScreen(
	GameBoard* board, 
	States* states, 
	List<Player>* rankings,
	User* user
) {
	// clear screen
	system("CLS");

	// display score and best score
	displayScore(board, user);

	// display grid
	displayGrid(board);

	// display congratulations
	cout << "-------- VICTORY --------" << endl;
	cout << "Congratulations! You have reached " << POW2[WIN_VALUE] << endl;

	// display rank if player is in top 20
	int playerRank = findUserRank(rankings, user);
	if (playerRank != -1) {
		cout << "Your best rank is: " << playerRank << endl;
	}

	// display next possible buttons
	cout << "Continue:  " << COLOR_YELLOW << "C" << COLOR_RESET << endl;
	cout << "New game:  " << COLOR_YELLOW << "G" << COLOR_RESET << endl;
	cout << "Lobby:     " << COLOR_YELLOW << "L" << COLOR_RESET << endl;
	cout << "Exit:      " << COLOR_YELLOW << "Esc" << COLOR_RESET << endl;
	cout << "Rankings:  " << COLOR_YELLOW << "H" << COLOR_RESET << endl;
	if (states->activePrev) cout << "Undo:      " << COLOR_YELLOW << "U" << COLOR_RESET << endl;

	cout << endl;
}

void displayLossScreen(GameBoard* board, States* states, User* user) {
	// clear screen
	system("CLS");

	// display score and best score
	displayScore(board, user);

	// display grid
	displayGrid(board);

	// display next possible buttons
	cout << "-------- GAME OVER --------" << endl;
	cout << "New game:  " << COLOR_YELLOW << "G" << COLOR_RESET << endl;
	cout << "Exit:      " << COLOR_YELLOW << "Esc" << COLOR_RESET << endl;
	cout << "Lobby:     " << COLOR_YELLOW << "L" << COLOR_RESET << endl;
	cout << "Rankings:  " << COLOR_YELLOW << "H" << COLOR_RESET << endl;
	if (states->activePrev) cout << "Undo:      " << COLOR_YELLOW << "U" << COLOR_RESET << endl;

	cout << endl;
}

void displayRankings(List<Player>* rankings, User* user) {
	cout << "\t                 " << COLOR_GREEN << "RANKINGS" << COLOR_RESET << endl;
	cout << endl;

	cout << " Rank   ";

	cout << "Nickname";
	for (int i = 1; i < NAME_LENGTH - 1; i++) {
		cout << " ";
	}

	cout << "Best score     ";

	cout << "Played Time" << endl;

	int index = 1;
	for (
		Node<Player>* curNode = rankings->head;
		curNode != nullptr && index <= 20;
		curNode = curNode->next, index++
		) {
		Player& player = curNode->data;
		cout << RANK_COLOR[index];

		// print index
		cout << " " << index;
		if (index < 10) cout << "      ";
		else cout << "     ";

		// print name
		cout << player.name;
		for (
			int i = 1, length = (int)player.name.length();
			i < NAME_LENGTH - length;
			i++
			) {
			cout << " ";
		}
		cout << (player.name == user->name ? "(you)  " : "       ");

		// print best score
		cout << player.bestScore;
		for (
			int i = 1, length = numberLength(player.bestScore);
			i < SCORE_LENGTH - length;
			i++
			) {
			cout << " ";
		}

		// print played time
		cout << player.playTime << "s" << endl;

		cout << COLOR_RESET;
	}
}