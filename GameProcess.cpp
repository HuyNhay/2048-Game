#include "GameLibrary.h"

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

bool availableMove(GameBoard* board) {
	// check is there exist a zero-valued cell
	for (int i = 0; i < board->width; i++) {
		for (int j = 0; j < board->height; j++) {
			if (board->grid[i][j] == 0) return true;
		}
	}

	// check is there exist two adjacent cell with equal values
	for (int i = 0; i < board->width; i++) {
		for (int j = 0; j < board->height; j++) {
			if (i < board->width - 1) {
				if (board->grid[i][j] == board->grid[i + 1][j]) {
					return true;
				}
			}

			if (j < board->height - 1) {
				if (board->grid[i][j] == board->grid[i][j + 1]) {
					return true;
				}
			}
		}
	}

	return false;
}

void processVictory(GameBoard*& board, States* states) {
	cout << "-------- VICTORY --------" << endl;
	cout << "Congratulations! You have reached " << POW2[WIN_VALUE] << "!" << endl;
	cout << "New game: " << COLOR_YELLOW << "N" << COLOR_RESET << endl;
	cout << "Exit:     " << COLOR_YELLOW << "Esc" << COLOR_RESET << endl;
	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_N:
			initGrid(board, states);
			return;
		case KEY_ESC:
			cout << endl << COLOR_GREEN << "Exit successfully." << COLOR_RESET << endl;
			deallocateGame(board, states);
			exit(0);
		case KEY_U: {
			processUndo(board, states);
			return;
		}
		}
	}
}

void processGameOver(GameBoard*& board, States* states) {
	cout << "-------- GAME OVER --------" << endl;
	cout << "You lose :(((" << endl;
	cout << "New game: " << COLOR_YELLOW << "N" << COLOR_RESET << endl;
	cout << "Exit:     " << COLOR_YELLOW << "Esc" << COLOR_RESET << endl;
	cout << "Undo:     " << COLOR_YELLOW << "U" << COLOR_RESET << endl;
	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_N:
			initGrid(board, states);
			return;
		case KEY_ESC: {
			cout << endl << COLOR_GREEN << "Exit successfully." << COLOR_RESET << endl;
			deallocateGame(board, states);
			exit(0);
		}
		case KEY_U: {
			processUndo(board, states);
			return;
		}
		}
	}
}

void processUp(GameBoard* board, States* states) {
	// save this state
	pushState(states->prev, board);

	// merge tiles
	bool flag = 0;
	for (int col = 0; col < board->height; col++) {
		// for each column, use two pointers technique to merge two "adjacent" tiles that are equal
		for (int row = 0, row2 = 0; row < board->width; row++) {
			if (board->grid[row][col] == 0) continue;

			while ((row2 < board->width) && (row2 <= row || board->grid[row2][col] == 0)) row2++;

			if (row2 < board->width && board->grid[row][col] == board->grid[row2][col]) {
				flag = 1;
				board->grid[row][col]++;
				board->grid[row2][col] = 0;
				updateScore(board, POW2[board->grid[row][col]]);
				if (board->grid[row][col] == WIN_VALUE) board->isWin = 1;
			}
		}
	}

	// push tiles up
	for (int col = 0; col < board->height; col++) {
		// for each column, use two pointers technique to push tiles to the top
		for (int row = 0, row2 = 0; row < board->width; row++) {
			if (board->grid[row][col]) continue;

			while ((row2 < board->width) && (row2 <= row || board->grid[row2][col] == 0)) row2++;

			if (row2 < board->width) {
				flag = 1;
				swap(&board->grid[row][col], &board->grid[row2][col]);
			}
		}
	}

	// if grid is modified
	if (flag) {
		// add 1 random tile
		addRandomTile(board);

		// redisplay
		displayGame(board);

		// clear all next states
		clearStates(states->next);
	}
	else { // if not
		popState(states->prev);
	}
}

void processDown(GameBoard* board, States* states) {
	// save this state
	pushState(states->prev, board);

	// merge tiles
	bool flag = 0;
	for (int col = 0; col < board->height; col++) {
		// for each column, use two pointers technique to merge two "adjacent" tiles that are equal
		for (int row = board->width - 1, row2 = board->width - 1; row >= 0; row--) {
			if (board->grid[row][col] == 0) continue;

			while ((row2 >= 0) && (row2 >= row || board->grid[row2][col] == 0)) row2--;

			if (row2 >= 0 && board->grid[row][col] == board->grid[row2][col]) {
				flag = 1;
				board->grid[row][col]++;
				board->grid[row2][col] = 0;
				updateScore(board, POW2[board->grid[row][col]]);
				if (board->grid[row][col] == WIN_VALUE) board->isWin = 1;
			}
		}
	}

	// push tiles down
	for (int col = 0; col < board->height; col++) {
		// for each column, use two pointers technique to push tiles to the bottom
		for (int row = board->width - 1, row2 = board->width - 1; row >= 0; row--) {
			if (board->grid[row][col] > 0) continue;

			while ((row2 >= 0) && (row2 >= row || board->grid[row2][col] == 0)) row2--;

			if (row2 >= 0) {
				flag = 1;
				swap(&board->grid[row][col], &board->grid[row2][col]);
			}
		}
	}

	// if grid is modified
	if (flag) {
		// add 1 random tile
		addRandomTile(board);

		// redisplay
		displayGame(board);

		// clear all next states
		clearStates(states->next);
	}
	else { // if not
		popState(states->prev);
	}
}

void processLeft(GameBoard* board, States* states) {
	// save this state
	pushState(states->prev, board);

	// merge tiles
	bool flag = 0;
	for (int row = 0; row < board->width; row++) {
		// for each row, use two pointers technique to merge two "adjacent" tiles that are equal
		for (int col = 0, col2 = 0; col < board->height; col++) {
			if (board->grid[row][col] == 0) continue;

			while ((col2 < board->height) && (col2 <= col || board->grid[row][col2] == 0)) col2++;

			if (col2 < board->height && board->grid[row][col] == board->grid[row][col2]) {
				flag = 1;
				board->grid[row][col]++;
				board->grid[row][col2] = 0;
				updateScore(board, POW2[board->grid[row][col]]);
				if (board->grid[row][col] == WIN_VALUE) board->isWin = 1;
			}
		}
	}

	// push tiles down
	for (int row = 0; row < board->width; row++) {
		// for each column, use two pointers technique to push tiles to the left
		for (int col = 0, col2 = 0; col < board->height; col++) {
			if (board->grid[row][col] > 0) continue;

			while ((col2 < board->height) && (col2 <= col || board->grid[row][col2] == 0)) col2++;

			if (col2 < board->height) {
				flag = 1;
				swap(&board->grid[row][col], &board->grid[row][col2]);
			}
		}
	}

	// if grid is modified
	if (flag) {
		// add 1 random tile
		addRandomTile(board);

		// redisplay
		displayGame(board);

		// clear all next states
		clearStates(states->next);
	}
	else { // if not
		popState(states->prev);
	}
}

void processRight(GameBoard* board, States* states) {
	// save this state
	pushState(states->prev, board);

	// merge tiles
	bool flag = 0;
	for (int row = 0; row < board->width; row++) {
		// for each row, use two pointers technique to merge two "adjacent" tiles that are equal
		for (int col = board->height - 1, col2 = board->height - 1; col >= 0; col--) {
			if (board->grid[row][col] == 0) continue;

			while ((col2 >= 0) && (col2 >= col || board->grid[row][col2] == 0)) col2--;

			if (col2 >= 0 && board->grid[row][col] == board->grid[row][col2]) {
				flag = 1;
				board->grid[row][col]++;
				board->grid[row][col2] = 0;
				updateScore(board, POW2[board->grid[row][col]]);
				if (board->grid[row][col] == WIN_VALUE) board->isWin = 1;
			}
		}
	}

	// push tiles down
	for (int row = 0; row < board->width; row++) {
		// for each column, use two pointers technique to push tiles to the left
		for (int col = board->height - 1, col2 = board->height - 1; col >= 0; col--) {
			if (board->grid[row][col] > 0) continue;

			while ((col2 >= 0) && (col2 >= col || board->grid[row][col2] == 0)) col2--;

			if (col2 >= 0) {
				flag = 1;
				swap(&board->grid[row][col], &board->grid[row][col2]);
			}
		}
	}

	// if grid is modified
	if (flag) {
		// add 1 random tile
		addRandomTile(board);

		// redisplay
		displayGame(board);

		// clear all next states
		clearStates(states->next);
	}
	else { // if not
		popState(states->prev);
	}
}

void processNewGame(GameBoard* board, States* states) {
	cout << "Do you want to start a new game? All progress will be lost." << endl;
	cout << "Press " <<
		COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " <<
		COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

	char userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_Y:
			initGrid(board, states);
			return;
		case KEY_N:
			displayGame(board);
			return;
		}
	}
}

void processQuitGame(GameBoard* board, States* states) {
	cout << "Do you want to exit the game?" << endl;
	cout << "Press " <<
		COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " <<
		COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

	char userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_Y: {
			cout << endl << COLOR_GREEN << "Exit successfully." << COLOR_RESET << endl;
			deallocateGame(board, states);
			exit(0);
		}
		case KEY_N:
			displayGame(board);
			return;
		}
	}
}

void processChangeDimension(GameBoard* board, States* states) {
	cout << "Do you want to change dimension?" << endl;
	cout << "Press " << 
		COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " << 
		COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_Y: {
			int w;
			cout << COLOR_GREEN << "Enter number of rows (MUST be a positive number, recommend in range [2, 8]): " << COLOR_RESET;
			while (true) {
				cin >> w;
				if (cin.fail() || w <= 0) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << COLOR_RED << "Your input is not incorrect, please reenter: " << COLOR_RESET;
				}
				else break;
			}

			int h;
			cout << COLOR_GREEN << "Enter number of columns (MUST be a positive number, recommend in range [2, 8]): " << COLOR_RESET;
			while (true) {
				cin >> h;
				if (cin.fail() || h <= 0) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << COLOR_RED << "Your input is incorrect, please reenter: " << COLOR_RESET;
				}
				else break;
			}

			changeDimension(board, w, h);
			initGrid(board, states);
			
			return;
		}
		case KEY_N:
			displayGame(board);
			return;
		}
	}
}

void processUndo(GameBoard*& board, States* states) {
	if (states->prev.empty()) return;

	states->next.push(board);

	board = states->prev.top();
	states->prev.pop();

	displayGame(board);
}

void processRedo(GameBoard*& board, States* states) {
	if (states->next.empty()) return;

	states->prev.push(board);

	board = states->next.top();
	states->next.pop();

	displayGame(board);
}

void processGamePlay(GameBoard*& board, States* states) {
	int userChoice = 0;
	while (true) {
		if (board->isWin) {
			processVictory(board, states);
		}

		if (!availableMove(board)) {
			processGameOver(board, states);
		}

		switch (userChoice = _getch()) {
		case KEY_UP:
			processUp(board, states);
			break;
		case KEY_DOWN:
			processDown(board, states);
			break;
		case KEY_LEFT:
			processLeft(board, states);
			break;
		case KEY_RIGHT:
			processRight(board, states);
			break;
		case KEY_N:
			processNewGame(board, states);
			break;
		case KEY_ESC:
			processQuitGame(board, states);
			break;
		case KEY_C:
			processChangeDimension(board, states);
			break;
		case KEY_U:
			processUndo(board, states);
			break;
		case KEY_R:
			processRedo(board, states);
			break;
		}
	}
}