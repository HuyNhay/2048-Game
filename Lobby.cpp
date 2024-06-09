#include "GameLibrary.h"

bool processEnterPlayerName(User* user, List<Player>* rankings) {
	cout << LONG_TAB << "\t       " << "Pressed " << COLOR_YELLOW << "G" << COLOR_RESET
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
				return false;
			}
			cout << COLOR_RED;

			if ((int)name.length() > 20 || (int)name.length() == 0) {
				cout << "\t\t\t    " <<
					"Your nickname is invalid (NOT empty, NOT more than 20 characters) " << endl;
			}
			else {
				cout << "\t\t\t\t    " <<
					"Your nickname is invalid (already used in top 20) " << endl;
			}

			cout << LONG_TAB << "\t       " << "Please reenter (" << ntry << " more) : ";
			cout << COLOR_RESET;
		}
		else { // valid name
			user->name = name;
			break;
		}
	}
	return true;
}

void processChangeGridSizesLobby(GameBoard* board, States* states) {
	displaySettings(board, states);

	cout << " Pressed C" << endl;
	cout << " Do you want to change grid sizes?" << endl;
	cout << " Press " <<
		COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " <<
		COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_Y: {
			displaySettings(board, states);
			cout << " Pressed Y" << endl;
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
			cout << " Pressed N" << endl;
			return;
		}
	}
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

	cout << " Pressed M" << endl;
	cout << " Do you want to change game mode?" << endl;
	cout << " Press " <<
		COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " <<
		COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_Y: {
			displaySettings(board, states);

			cout << " Pressed Y" << endl;
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

					cout << " Pressed " << mode - '0' << " " << endl;
					cout << COLOR_YELLOW << " Changed game mode!" << COLOR_RESET << endl;
					return;
				}
			}
		}
		case KEY_N:
			displaySettings(board, states);
			cout << " Pressed N" << endl;
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
			return;
		}
	}
}

bool processResume(GameBoard* board, States* states, User* user, bool resumeAvailable) {
	cout << LONG_TAB << "\t       " << "Pressed " << COLOR_CYAN << "R" <<COLOR_RESET << endl;

	if (!resumeAvailable) {
		cout << COLOR_YELLOW;
		cout << LONG_TAB << "\t       " << "Unable to resume! No players played before!" << endl;
		cout << COLOR_RESET;
		return false;
	}

	cout << LONG_TAB << "\t       " << "----------------------------------------" << endl;
	cout << LONG_TAB << "\t       " << "Do you want to resume?" << endl;
	cout << LONG_TAB << "\t       " << "Press " <<
		COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " <<
		COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_Y: {
			loadUser(user);
			loadStatesActiveStatus(states);
			loadGameBoard(board);
			if (states->activePrev) {
				loadPrevStates(states);
			}
			if (states->activeNext) {
				loadNextStates(states);
			}
			return true;
		}
		case KEY_N:
			displayLobby(resumeAvailable);
			cout << LONG_TAB << "\t       " << "Pressed N" << endl;
			return false;
		}
	}
}

void processLobby(GameBoard* board, User* user, States* states, List<Player>* rankings) {
	bool resumeEnable = !rankings->isEmpty();
	displayLobby(resumeEnable);

	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {

		case KEY_G:
			displayLobby(resumeEnable);
			if (processEnterPlayerName(user, rankings)) {
				initGrid(board, states, user);
				switch (processGamePlay(board, states, rankings, user)) {
				case CONTINUE:
					displayLobby(resumeEnable);
					break;
				case EXIT:
					deallocateGame(board, states, rankings, user);
					return;
				}
			}
			else {
				deallocateGame(board, states, rankings, user);
				return;
			}
			break;

		case KEY_S:
			processSettings(board, states);
			displayLobby(resumeEnable);
			break;

		case KEY_H:
			processShowRankings(rankings, user);
			displayLobby(resumeEnable);
			break;

		case KEY_R:
			displayLobby(resumeEnable);
			if (processResume(board, states, user, resumeEnable)) {
				displayMainScreen(board, states, user);
				switch (processGamePlay(board, states, rankings, user)) {
				case CONTINUE:
					displayLobby(resumeEnable);
					break;
				case EXIT:
					return;
				}
			}
			break;

		case KEY_ESC:
			displayLobby(resumeEnable);
			cout << LONG_TAB << "\t       " << "Press " <<
				COLOR_MAGENTA << "Esc" << COLOR_RESET << endl;
			cout << LONG_TAB << "\t       " << COLOR_GREEN << "Exit successfully" << COLOR_RESET << endl;
			deallocateGame(board, states, rankings, user);
			return;
		}
	}
}