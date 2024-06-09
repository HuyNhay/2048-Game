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

bool processVictory(
	GameBoard*& board, 
	States* states, 
	List<Player>* rankings,
	Player* player
) {
	displayMainScreen(board, states, player);

	// display congratulations
	cout << "-------- VICTORY --------" << endl;
	cout << "Congratulations! You have reached " << POW2[WIN_VALUE] << endl;

	// display rank if player is in top 20
	int playerRank = findPlayerRank(rankings, player);
	if (playerRank != -1) {
		cout << "Your rank is: " << playerRank << endl;
	}

	// display and process next possible buttons
<<<<<<< HEAD
	cout << "New game:  " << COLOR_YELLOW << "G" << COLOR_RESET << endl;
	cout << "Exit:      " << COLOR_YELLOW << "Esc" << COLOR_RESET << endl;
	cout << "Rankings:  " << COLOR_YELLOW << "H" << COLOR_RESET << endl;
=======
	cout << "New game: " << COLOR_YELLOW << "G" << COLOR_RESET << endl;
	cout << "Exit:     " << COLOR_YELLOW << "Esc" << COLOR_RESET << endl;
	cout << "Rankings: " << COLOR_YELLOW << "H" << COLOR_RESET << endl;
>>>>>>> 84ea47a8914b1ecb315c7d414b31355a0c5014d0
	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_G:
			initGrid(board, states, player);
			return false;
		case KEY_ESC:
			cout << endl << COLOR_GREEN << "Exit successfully." << COLOR_RESET << endl;
			return true;
		case KEY_U:
			processUndo(board, states, player);
			return false;
		case KEY_H:
			rankings->update(*player);
			processShowRankings(rankings, player);
			displayMainScreen(board, states, player);
			return false;
		}
	}
}

bool processGameOver(
	GameBoard*& board,
	States* states,
	List<Player>* rankings,
	Player* player
) {
	displayMainScreen(board, states, player);

	cout << "-------- GAME OVER --------" << endl;
	cout << "New game: " << COLOR_YELLOW << "N" << COLOR_RESET << endl;
	cout << "Exit:     " << COLOR_YELLOW << "Esc" << COLOR_RESET << endl;
	if (states->activePrev) cout << "Undo:     " << COLOR_YELLOW << "U" << COLOR_RESET << endl;
	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_N:
			initGrid(board, states, player);
			return false;
		case KEY_ESC: {
			cout << endl << COLOR_GREEN << "Exit successfully." << COLOR_RESET << endl;
			return true;
		}
		case KEY_U: {
			if (!states->activePrev) break;
			processUndo(board, states, player);
			return false;
		}
		}
	}
}

void processUp(GameBoard* board, States* states, Player* player) {
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
				updateScore(board, player, POW2[board->grid[row][col]]);
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
		displayMainScreen(board, states, player);

		// clear all next states
		if (states->activeNext) clearStates(states->next);

		cout << COLOR_YELLOW << "Moved up!" << COLOR_RESET << endl;
	}
	else { // if not
		displayMainScreen(board, states, player);
		cout << COLOR_YELLOW << "Unable to move up!" << COLOR_RESET << endl;

		if (states->activePrev) popState(states->prev);
	}
}

void processDown(GameBoard* board, States* states, Player* player) {
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
				updateScore(board, player, POW2[board->grid[row][col]]);
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
		displayMainScreen(board, states, player);

		// clear all next states
		if (states->activeNext) clearStates(states->next);

		cout << COLOR_YELLOW << "Moved down!" << COLOR_RESET << endl;
	}
	else { // if not
		displayMainScreen(board, states, player);
		cout << COLOR_YELLOW << "Unable to move down!" << COLOR_RESET << endl;

		if (states->activePrev) popState(states->prev);
	}
}

void processLeft(GameBoard* board, States* states, Player* player) {
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
				updateScore(board, player, POW2[board->grid[row][col]]);
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
		displayMainScreen(board, states, player);

		// clear all next states
		if (states->activeNext) clearStates(states->next);

		cout << COLOR_YELLOW << "Moved left!" << COLOR_RESET << endl;
	}
	else { // if not
		displayMainScreen(board, states, player);
		cout << COLOR_YELLOW << "Unable to move left!" << COLOR_RESET << endl;

		if (states->activePrev) popState(states->prev);
	}
}

void processRight(GameBoard* board, States* states, Player* player) {
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
				updateScore(board, player, POW2[board->grid[row][col]]);
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
		displayMainScreen(board, states, player);

		// clear all next states
		if (states->activeNext) clearStates(states->next);

		cout << COLOR_YELLOW << "Moved right!" << COLOR_RESET << endl;
	}
	else { // if not
		displayMainScreen(board, states, player);
		cout << COLOR_YELLOW << "Unable to move right!" << COLOR_RESET << endl;

		if (states->activePrev) popState(states->prev);
	}
}

void processNewGame(GameBoard* board, States* states, Player* player) {
	displayMainScreen(board, states, player);

	cout << "Do you want to start a new game? All progress will be lost." << endl;
	cout << "Press " <<
		COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " <<
		COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

	char userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_Y:
			initGrid(board, states, player);
			return;
		case KEY_N:
			displayMainScreen(board, states, player);
			return;
		}
	}
}

bool processQuitGame(GameBoard* board, States* states, List<Player>* rankings, Player* player) {
	displayMainScreen(board, states, player);

	cout << "Do you want to exit the game?" << endl;
	cout << "Press " <<
		COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " <<
		COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

	char userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_Y: {
			cout << endl << COLOR_GREEN << "Exit successfully" << COLOR_RESET << endl;
			return true;
		}
		case KEY_N:
			displayMainScreen(board, states, player);
			return false;
		}
	}
}

void processChangeGridSizesMain(GameBoard* board, States* states, Player* player) {
	displayMainScreen(board, states, player);

	cout << "Do you want to change dimension?" << endl;
	cout << "Press " << 
		COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " << 
		COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_Y: {
			int w;
			cout << COLOR_GREEN << "Enter number of rows: " << COLOR_RESET;
			while (true) {
				cin >> w;
				if (cin.fail() || w <= 0) {
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
				if (cin.fail() || h <= 0) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << COLOR_RED << "Your input is incorrect (MUST be a positive number, recommend in range [2, 8]), please reenter: " << COLOR_RESET;
				}
				else break;
			}

			changeGridSizes(board, w, h);
			initGrid(board, states, player);
			
			return;
		}
		case KEY_N:
			displayMainScreen(board, states, player);
			return;
		}
	}
}

void processUndo(GameBoard*& board, States* states, Player* player) {
	if (!states->activePrev) return;

	if (states->prev.isEmpty()) {
		displayMainScreen(board, states, player);
		cout << COLOR_YELLOW << "Unable to undo!" << COLOR_RESET << endl;
		return;
	}

	if (states->activeNext) states->next.push(board);
	else delete board;

	board = states->prev.top();
	states->prev.pop();

	displayMainScreen(board, states, player);

	cout << COLOR_YELLOW << "Undoed!" << COLOR_RESET << endl;
}

void processRedo(GameBoard*& board, States* states, Player* player) {
	if (!states->activeNext) return;

	if (states->next.isEmpty()) {
		displayMainScreen(board, states, player);
		cout << COLOR_YELLOW << "Unable to redo!" << COLOR_RESET << endl;
		return;
	}

	states->prev.push(board);

	board = states->next.top();
	states->next.pop();

	displayMainScreen(board, states, player);

	cout << COLOR_YELLOW << "Redoed!" << COLOR_RESET << endl;
}

void processGamePlay(
	GameBoard*& board,
	States* states,
	List<Player>* rankings,
	Player* player
) {
	int userChoice = 0;
	while (true) {
		if (board->isWin) {
			if (processVictory(board, states, rankings, player)) {
				return;
			}
			else {
				continue;
			}
		}

		if (!availableMove(board)) {
			if (processGameOver(board, states, rankings, player)) {
				return;
			}
		}

		switch (userChoice = _getch()) {
		case KEY_UP:
			processUp(board, states, player);
			break;
		case KEY_DOWN:
			processDown(board, states, player);
			break;
		case KEY_LEFT:
			processLeft(board, states, player);
			break;
		case KEY_RIGHT:
			processRight(board, states, player);
			break;
		case KEY_G:
			processNewGame(board, states, player);
			break;
		case KEY_ESC:
			if (processQuitGame(board, states, rankings, player)) {
				return;
			}
			break;
		case KEY_C:
			processChangeGridSizesMain(board, states, player);
			break;
		case KEY_U:
			processUndo(board, states, player);
			break;
		case KEY_R:
			processRedo(board, states, player);
			break;
		case KEY_H:
			rankings->update(*player);
			processShowRankings(rankings, player);
			displayMainScreen(board, states, player);
			break;
		}
	}
}