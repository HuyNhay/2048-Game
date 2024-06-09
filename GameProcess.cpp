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

int processVictory(
	GameBoard*& board, 
	States* states, 
	List<Player>* rankings,
	User* user
) {
	displayVictoryScreen(board, states, rankings, user);

	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_C:
			user->continuePlay = true;
			displayMainScreen(board, states, user);
			cout << "Pressed C, continue playing" << endl;
			return CONTINUE;
		case KEY_G:
			initGrid(board, states, user);
			cout << "Pressed G, start new game" << endl;
			return CONTINUE;
		case KEY_L:
			saveRankings(rankings, user);
			saveResumeGame(board, states, user);
			return LOBBY;
		case KEY_ESC:
			cout << "Pressed Esc" << endl;
			cout << COLOR_GREEN << "Exit successfully." << COLOR_RESET << endl;
			saveRankings(rankings, user);
			saveResumeGame(board, states, user);
			return EXIT;
		case KEY_U:
			if (!states->activePrev) break;
			processUndo(board, states, user);
			return CONTINUE;
		case KEY_H:
			rankings->update(*user);
			processShowRankings(rankings, user);
			displayMainScreen(board, states, user);
			return CONTINUE;
		}
	}
}

int processGameOver(
	GameBoard*& board,
	States* states,
	List<Player>* rankings,
	User* user
) {
	displayLossScreen(board, states, user);

	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_G:
			initGrid(board, states, user);
			cout << "Pressed G, start new game" << endl;
			return CONTINUE;
		case KEY_ESC:
			cout << "Pressed Esc" << endl;
			cout << COLOR_GREEN << "Exit successfully." << COLOR_RESET << endl;
			saveRankings(rankings, user);
			saveResumeGame(board, states, user);
			return EXIT;
		case KEY_L:
			saveRankings(rankings, user);
			saveResumeGame(board, states, user);
			return LOBBY;
		case KEY_H:
			rankings->update(*user);
			processShowRankings(rankings, user);
			displayMainScreen(board, states, user);
			return CONTINUE;
		case KEY_U: 
			if (!states->activePrev) break;
			processUndo(board, states, user);
			return CONTINUE;
		}
	}
}

void processUp(GameBoard* board, States* states, User* user) {
	// save this state
	if (states->activePrev) pushState(states->prev, board);

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
				updateScore(board, user, POW2[board->grid[row][col]]);
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
		displayMainScreen(board, states, user);

		// clear all next states
		if (states->activeNext) clearStates(states->next);

		cout << COLOR_YELLOW << "Moved up!" << COLOR_RESET << endl;
	}
	else { // if not
		displayMainScreen(board, states, user);
		cout << COLOR_YELLOW << "Unable to move up!" << COLOR_RESET << endl;

		if (states->activePrev) popState(states->prev);
	}
}

void processDown(GameBoard* board, States* states, User* user) {
	// save this state
	if (states->activePrev) pushState(states->prev, board);

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
				updateScore(board, user, POW2[board->grid[row][col]]);
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
		displayMainScreen(board, states, user);

		// clear all next states
		if (states->activeNext) clearStates(states->next);

		cout << COLOR_YELLOW << "Moved down!" << COLOR_RESET << endl;
	}
	else { // if not
		displayMainScreen(board, states, user);
		cout << COLOR_YELLOW << "Unable to move down!" << COLOR_RESET << endl;

		if (states->activePrev) popState(states->prev);
	}
}

void processLeft(GameBoard* board, States* states, User* user) {
	// save this state
	if (states->activePrev) pushState(states->prev, board);

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
				updateScore(board, user, POW2[board->grid[row][col]]);
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
		displayMainScreen(board, states, user);

		// clear all next states
		if (states->activeNext) clearStates(states->next);

		cout << COLOR_YELLOW << "Moved left!" << COLOR_RESET << endl;
	}
	else { // if not
		displayMainScreen(board, states, user);
		cout << COLOR_YELLOW << "Unable to move left!" << COLOR_RESET << endl;

		if (states->activePrev) popState(states->prev);
	}
}

void processRight(GameBoard* board, States* states, User* user) {
	// save this state
	if (states->activePrev) pushState(states->prev, board);

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
				updateScore(board, user, POW2[board->grid[row][col]]);
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
		displayMainScreen(board, states, user);

		// clear all next states
		if (states->activeNext) clearStates(states->next);

		cout << COLOR_YELLOW << "Moved right!" << COLOR_RESET << endl;
	}
	else { // if not
		displayMainScreen(board, states, user);
		cout << COLOR_YELLOW << "Unable to move right!" << COLOR_RESET << endl;

		if (states->activePrev) popState(states->prev);
	}
}

void processNewGame(GameBoard* board, States* states, User* user) {
	displayMainScreen(board, states, user);

	cout << "Pressed G" << endl;
	cout << "Do you want to start a new game? All progress will be lost." << endl;
	cout << "Press " <<
		COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " <<
		COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

	char userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_Y:
			initGrid(board, states, user);
			cout << "Pressed Y" << endl;
			return;
		case KEY_N:
			displayMainScreen(board, states, user);
			cout << "Pressed N" << endl;
			return;
		}
	}
}

bool processQuitGame(GameBoard* board, States* states, List<Player>* rankings, User* user) {
	displayMainScreen(board, states, user);

	cout << "Pressed Esc" << endl;
	cout << "Do you want to exit the game?" << endl;
	cout << "Press " <<
		COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " <<
		COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

	char userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_Y: {
			cout << "Pressed Y" << endl;
			cout << endl << COLOR_GREEN << "Exit successfully" << COLOR_RESET << endl;
			return true;
		}
		case KEY_N:
			displayMainScreen(board, states, user);
			cout << "Pressed N, continue playing" << endl;
			return false;
		}
	}
}

void processChangeGridSizesMain(GameBoard* board, States* states, User* user) {
	displayMainScreen(board, states, user);

	cout << "Pressed C" << endl;
	cout << "Do you want to change grid sizes?" << endl;
	cout << "Press " << 
		COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " << 
		COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl << endl;

	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_Y: {
			displayMainScreen(board, states, user);
			cout << "Pressed Y" << endl;
			int w;
			cout << COLOR_GREEN << "Enter number of rows: " << COLOR_RESET;
			while (true) {
				cin >> w;
				if (cin.fail() || w <= 0 || w > 10) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << COLOR_RED << "Your input is not incorrect (MUST be a positive number, recommend in range [2, 8]), please reenter: " << COLOR_RESET;
				}
				else break;
			}

			int h;
			cout << COLOR_GREEN << "Enter number of columns: " << COLOR_RESET;
			while (true) {
				cin >> h;
				if (cin.fail() || h <= 0 || h > 10) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << COLOR_RED << "Your input is incorrect (MUST be a positive number, in range [1, 10]), please reenter: " << COLOR_RESET;
				}
				else break;
			}

			changeGridSizes(board, w, h);

			initGrid(board, states, user);

			cout << COLOR_YELLOW << "Changed grid sizes!" << COLOR_RESET << endl;

			return;
		}
		case KEY_N:
			displayMainScreen(board, states, user);
			cout << "Pressed N, continue playing" << endl;
			return;
		}
	}
}

void processUndo(GameBoard*& board, States* states, User* user) {
	if (!states->activePrev) return;

	if (states->prev.isEmpty()) {
		displayMainScreen(board, states, user);
		cout << "Pressed U" << endl;
		cout << COLOR_YELLOW << "Unable to undo!" << COLOR_RESET << endl;
		return;
	}

	if (states->activeNext) states->next.push(board);
	else delete board;

	board = states->prev.top();
	states->prev.pop();

	displayMainScreen(board, states, user);

	cout << "Pressed U" << endl;
	cout << COLOR_YELLOW << "Undoed!" << COLOR_RESET << endl;
}

void processRedo(GameBoard*& board, States* states, User* user) {
	if (!states->activeNext) return;

	if (states->next.isEmpty()) {
		displayMainScreen(board, states, user);
		cout << "Pressed R" << endl;
		cout << COLOR_YELLOW << "Unable to redo!" << COLOR_RESET << endl;
		return;
	}

	states->prev.push(board);

	board = states->next.top();
	states->next.pop();

	displayMainScreen(board, states, user);

	cout << "Pressed R" << endl;
	cout << COLOR_YELLOW << "Redoed!" << COLOR_RESET << endl;
}

int processGamePlay(
	GameBoard*& board,
	States* states,
	List<Player>* rankings,
	User* user
) {
	int userChoice = 0;
	while (true) {
		if (!user->continuePlay && board->isWin) {
			switch (processVictory(board, states, rankings, user)) {
			case CONTINUE:
				continue;
			case EXIT:
				return EXIT;
			case LOBBY:
				*user = User("", 0, false, 0, 0);
				return CONTINUE;
			}
		}

		if (!availableMove(board)) {
			switch (processGameOver(board, states, rankings, user)) {
			case CONTINUE:
				continue;
			case EXIT:
				return EXIT;
			case LOBBY:
				*user = User("", 0, false, 0, 0);
				return CONTINUE;
			}

		}

		switch (userChoice = _getch()) {
		case KEY_UP:
			processUp(board, states, user);
			break;
		case KEY_DOWN:
			processDown(board, states, user);
			break;
		case KEY_LEFT:
			processLeft(board, states, user);
			break;
		case KEY_RIGHT:
			processRight(board, states, user);
			break;
		case KEY_G:
			processNewGame(board, states, user);
			break;
		case KEY_ESC:
			if (processQuitGame(board, states, rankings, user)) {
				saveRankings(rankings, user);
				saveResumeGame(board, states, user);
				return EXIT;
			}
			break;
		case KEY_C:
			processChangeGridSizesMain(board, states, user);
			break;
		case KEY_U:
			processUndo(board, states, user);
			break;
		case KEY_R:
			processRedo(board, states, user);
			break;
		case KEY_H:
			rankings->update(*user);
			processShowRankings(rankings, user);
			displayMainScreen(board, states, user);
			break;
		}
	}
}