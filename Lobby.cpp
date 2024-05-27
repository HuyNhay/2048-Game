#include "GameLibrary.h"

void displayLobby() {
	system("CLS");

	cout << endl << endl;
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
	cout << COLOR_YELLOW << "New game: N" << COLOR_RESET;
	cout << TAB << "|" << TAB;
	cout << COLOR_GREEN << "Settings: S" << COLOR_RESET;
	cout << TAB << "|" << TAB;
	cout << COLOR_RED << "Rankings: H" << COLOR_RESET;
	cout << TAB << "|" << TAB;
	cout << COLOR_CYAN << "Resume: R" << COLOR_RESET;
	cout << endl;
}

void processEnterPlayerName(Player* player, List<Player>* rankings) {
	cout << endl << endl;
	cout << LONG_TAB << "\t       " << "Pressed " << COLOR_YELLOW << "N" << COLOR_RESET
		<< ", enter your nickname." << endl;
	cout << LONG_TAB << "\t       " << COLOR_YELLOW << "Nickname (any unnecessary " << COLOR_RESET << endl;
	cout << LONG_TAB << "\t       " << COLOR_YELLOW << "spaces will be removed) : " << COLOR_RESET;
	string name = "";
	for (int ntry = 3; ntry >= 0; ntry--) {
		getline(cin, name);
		removeSpaces(name);
		if ((int)name.length() > 20 || (int)name.length() == 0 || checkNameExistence(rankings, name)) { // invalid name
			if (ntry == 0) {
				cout << endl << COLOR_RED << "Too much wrong attempts, exit game automatically!" << COLOR_RESET;
				delete player;
				exit(0);
			}
			cout << COLOR_RED;

			if ((int)name.length() > 20 || (int)name.length() == 0) {
				cout << "\t\t\t    " <<
					"Your nickname is invalid (NOT empty, NOT more than 20 characters) " << endl;
			}
			else {
				cout << "\t\t\t    " <<
					"Your nickname is invalid (already used in top 20) " << endl;
			}

			cout << LONG_TAB << "\t\t\t" << "Please reenter (" << ntry << " more) : ";
			cout << COLOR_RESET;
		}
		else { // valid name
			player->name = name;
			return;
		}
	}
}

void processChangeGridSizesLobby(GameBoard* board, States* states) {
	displaySettings(board, states);

	cout << " ----------------------------------------" << endl;
	cout << " Do you want to change grid sizes?" << endl;
	cout << " Press " <<
		COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " <<
		COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_Y: {
			int w;
			cout << COLOR_GREEN << " Enter number of rows: " << COLOR_RESET;
			while (true) {
				cin >> w;
				if (cin.fail() || w <= 0 || w > 10) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << COLOR_RED << " Your input is not incorrect (MUST be a positive number, recommend in range [2, 8]), please reenter: " << COLOR_RESET;
				}
				else break;
			}

			int h;
			cout << COLOR_GREEN << " Enter number of columns: " << COLOR_RESET;
			while (true) {
				cin >> h;
				if (cin.fail() || h <= 0 || h > 10) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << COLOR_RED << " Your input is incorrect (MUST be a positive number, in range [1, 10]), please reenter: " << COLOR_RESET;
				}
				else break;
			}

			cin.ignore();

			changeGridSizes(board, w, h);

			displaySettings(board, states);

			cout << COLOR_YELLOW << " Changed grid sizes!" << COLOR_RESET << endl;

			return;
		}
		case KEY_N:
			displaySettings(board, states);
			return;
		}
	}
}

void displaySettings(GameBoard* board, States* states) {
	system("CLS");

	cout << "      " << COLOR_ORANGE << "SETTINGS" << COLOR_RESET << endl;
	cout << endl;

	cout << COLOR_ORANGE << " Grid sizes: " << COLOR_RESET 
		<< board->width << "x" << board->height << endl;
	cout << COLOR_ORANGE << " Game mode: " << COLOR_RESET;
		//<< "Undo + Redo" << endl;
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

void changeGameMode(States* states, int mode) {
	if (mode == KEY_1) {
		states->activePrev = false;
		states->activeNext = false;
	}
	else if (mode == KEY_2) {
		states->activePrev = true;
		states->activeNext = false;
	}
	else {
		states->activePrev = true;
		states->activeNext = true;
	}
}

void processChangeGameMode(GameBoard* board, States* states) {
	displaySettings(board, states);

	cout << " ----------------------------------------" << endl;
	cout << " Do you want to change game mode?" << endl;
	cout << " Press " <<
		COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " <<
		COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_Y: {
			displaySettings(board, states);

			cout << " Which mode do you want?" << endl;
			cout << " (" << COLOR_YELLOW << "1" << COLOR_RESET << ") " << 
				"Undo: " << COLOR_YELLOW << "OFF" << COLOR_RESET << ", " <<
				"Redo: " << COLOR_YELLOW << "OFF" << COLOR_RESET << endl;

			cout << " (" << COLOR_YELLOW << "2" << COLOR_RESET << ") " <<
				"Undo: " << COLOR_YELLOW << "ON" << COLOR_RESET << ", " <<
				"Redo: " << COLOR_YELLOW << "OFF" << COLOR_RESET << endl;

			cout << " (" << COLOR_YELLOW << "3" << COLOR_RESET << ") " <<
				"Undo: " << COLOR_YELLOW << "ON" << COLOR_RESET << ", " <<
				"Redo: " << COLOR_YELLOW << "ON" << COLOR_RESET << endl;


			int mode = 0;
			while (true) {
				switch (mode = _getch()) {
				case KEY_1: 
				case KEY_2:
				case KEY_3:
					changeGameMode(states, mode);
					displaySettings(board, states);
					
					cout << COLOR_YELLOW << " Changed game mode!" << COLOR_RESET << endl;
					return;
				}
			}
		}
		case KEY_N:
			displaySettings(board, states);
			return;
		}
	}
}

void processSettings(GameBoard* board, States* states) {
	displaySettings(board, states);

	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_C:
			processChangeGridSizesLobby(board, states);
			break;
		case KEY_M:
			processChangeGameMode(board, states);
			break;
		case KEY_SPACE:
			displayLobby();
			//cin.ignore();
			return;
		}
	}
}

void processLobby(GameBoard* board, Player* player, States* states, List<Player>* rankings) {
	displayLobby();

	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_N:
			processEnterPlayerName(player, rankings);
			return;
		case KEY_S:
			processSettings(board, states);
			break;
		case KEY_H:
			processShowRankings(rankings);
			displayLobby();
			break;
		case KEY_R:
			break;
		}
	}

}