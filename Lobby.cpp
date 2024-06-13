#include "GameLibrary.h"

int processEnterPlayerName(User* user, List<Player>* rankings) {
	bool resumeEnable = !rankings->isEmpty();

	displayLobby(resumeEnable);

	cout << LONG_TAB << "\t       " << "Pressed " << COLOR_YELLOW << "G" << COLOR_RESET
		<< ", enter your nickname." << endl;
	cout << LONG_TAB << "\t       " << COLOR_YELLOW << "Nickname (any unnecessary " << COLOR_RESET << endl;
	cout << LONG_TAB << "\t       " << COLOR_YELLOW << "spaces will be removed): " << COLOR_RESET;
	
	if (resumeEnable) loadUserVitalInformation(user);

	string name = "";
	cin >> ws; // remove all spaces in buffer
	for (int ntry = 3; ntry >= 0; ntry--) {
		getline(cin, name);
		removeSpaces(name);
		
		if (resumeEnable && name == user->name) { // new name is similar to resume name
			// find an empty account this new game
			for (int account = 0; account < NUM_ACCOUNT; account++) {
				if (user->usedAccount[account]) {
					continue;
				}

				displayLobby(resumeEnable);
				cout << LONG_TAB << "\t            " <<
					"Welcome back " << COLOR_ORANGE << user->name << COLOR_RESET << endl;
				cout << LONG_TAB << "\t  " <<
					"Your new game will be stored in " <<
					COLOR_GREEN << "Account " << account + 1 << COLOR_RESET << " in " <<
					COLOR_CYAN << "Resume" << COLOR_RESET << " mode" << endl << endl;

				cout << LONG_TAB << "\t            " <<
					"Press " << COLOR_YELLOW << "Space " << COLOR_RESET << "to start game..." << endl;
				int userChoice = 0;
				while (true) {
					switch (userChoice = _getch()) {
					case KEY_SPACE:
						user->resumeAccount = account;
						user->usedAccount[account] = true;
						return NEW_GAME;
					}
				}
			}

			// 5 accounts are used, ask client to choose 1 of 5 accounts to save the game
			displayLobby(resumeEnable);
			cout << LONG_TAB << "\t            " <<
				"Welcome back " << COLOR_ORANGE << user->name << COLOR_RESET << endl;
			cout << LONG_TAB << "\t            " <<
				"All your resume accounts are used" << endl;
			cout << LONG_TAB << "\t            " <<
				"Do you want to save new game in one of them?" << endl;
			cout << LONG_TAB << "\t            " <<
				"The old game will be removed" << endl;
			cout << LONG_TAB << "\t            " << "Press " <<
				COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " <<
				COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

			int userDecision = 0;
			while (true) {
				switch (userDecision = _getch()) {
				case KEY_Y: {
					displayLobby(resumeEnable);
					cout << LONG_TAB << " " <<
						"Pressed Y, choose an account to save the game" <<
						endl << endl;

					displayAccounts(user);

					int account = 0;
					while (true) {
						switch (account = _getch()) {
						case KEY_1:
						case KEY_2:
						case KEY_3:
						case KEY_4:
						case KEY_5: {
							account -= '1';

							displayLobby(resumeEnable);
							cout << LONG_TAB << "\t  " <<
								"Your new game will be stored in " <<
								COLOR_GREEN << "Account " << account + 1 << COLOR_RESET << " in " <<
								COLOR_CYAN << "Resume" << COLOR_RESET << " mode" << endl << endl;

							cout << LONG_TAB << "\t            " <<
								"Press " << COLOR_YELLOW << "Space " << COLOR_RESET << "to start game..." << endl;
							int userChoice = 0;
							while (true) {
								switch (userChoice = _getch()) {
								case KEY_SPACE:
									clearResumeGame(account);
									user->resumeAccount = account;
									user->usedAccount[account] = true;
									return NEW_GAME;
								}
							}
						}
						}
					}
				}
				case KEY_N: {
					displayLobby(resumeEnable);
					cout << LONG_TAB << "\t            " << "Pressed N" << endl;
					return CONTINUE;
				}
				}
			}

		}
		else if (
			(int)name.length() > 20 || 
			(int)name.length() == 0 || 
			checkInvalidCharacter(name) ||
			checkNameExistence(rankings, name)
			) { // invalid name
			if (ntry == 0) {
				cout << endl << COLOR_RED << "Too much wrong attempts, exit game automatically!" << COLOR_RESET;
				return EXIT;
			}
			cout << COLOR_RED;

			if ((int)name.length() > 20 || (int)name.length() == 0) {
				cout << "\t\t\t    " <<
					"Your nickname is invalid (NOT empty, NOT more than 20 characters) " << endl;
			}
			else if (checkInvalidCharacter(name)) {
				cout << "\t\t\t    " <<
					"Your nickname is invalid (ONLY contains letters, numbers and spaces) " << endl;
			}
			else {
				cout << "\t\t\t\t    " <<
					"Your nickname is invalid (already used in top 20) " << endl;
			}

			cout << LONG_TAB << "\t       " << "Please reenter (" << ntry << " more): ";
			cout << COLOR_RESET;
		}
		else { // valid name
			*user = User(name, 0, false, 0, 0);
			for (int account = 0; account < NUM_ACCOUNT; account++) {
				clearResumeGame(account);
			}
			user->resumeAccount = 0;
			user->usedAccount[0] = true;

			break;
		}
	}
	return NEW_GAME;
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
			cin.clear();
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

int processChooseResumeAccount(GameBoard* board, User* user, bool resumeEnable) {
	displayChooseResumeAccountScreen(user, resumeEnable);

	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_1:
		case KEY_2:
		case KEY_3:
		case KEY_4:
		case KEY_5: {
			int account = userChoice - '1';

			if (!user->usedAccount[account]) {
				displayChooseResumeAccountScreen(user, resumeEnable);
				cout << LONG_TAB << " " <<
					"Pressed " << COLOR_YELLOW << account + 1 << COLOR_RESET <<
					", this account hasn't been used" << endl;
				cout << LONG_TAB << " " <<
					"Do you want to start a new game? The game will be saved to this account" << endl;
				cout << LONG_TAB << " " << "Press " <<
					COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " <<
					COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

				int userDecision = 0;
				int running = true;
				while (running) {
					switch (userDecision = _getch()) {
					case KEY_Y:
						user->resumeAccount = account;
						user->usedAccount[account] = true;
						return NEW_GAME;
					case KEY_N:
						running = false;
						displayChooseResumeAccountScreen(user, resumeEnable);
						cout << LONG_TAB << "\t            " << "Pressed N" << endl;
						break;
					}
				}
			}
			else {
				user->resumeAccount = account;
				return CONTINUE;
			}
			break;
		}

		case KEY_G:
			displayLobby(resumeEnable);

			cout << LONG_TAB << " " <<
				"Pressed G, do you want to start a new game?" << endl;
			cout << LONG_TAB << " " << "Press " <<
				COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " <<
				COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

			int userDecision = 0;
			int running1 = true;
			while (running1) {
				switch (userDecision = _getch()) {
				case KEY_Y: {
					displayLobby(resumeEnable);
					cout << LONG_TAB << " " <<
						"Pressed Y, choose an account to save the game" <<
						endl << endl;

					displayAccounts(user);

					int account = 0;
					int running2 = true;
					while (running2) {
						switch (account = _getch()) {
						case KEY_1:
						case KEY_2:
						case KEY_3:
						case KEY_4:
						case KEY_5: {
							account -= '1';
							if (user->usedAccount[account]) {
								cout << endl;
								cout << LONG_TAB << " " <<
									"Pressed " << COLOR_YELLOW << account + 1 << COLOR_RESET <<
									", this account is already used" << endl;
								cout << LONG_TAB << " " <<
									"Do you want to delete the old game?" << endl;
								cout << LONG_TAB << " " << "Press " <<
									COLOR_YELLOW << "Y " << COLOR_RESET << "to confirm, " <<
									COLOR_YELLOW << "N " << COLOR_RESET << "to cancel." << endl;

								int d = 0;
								int running3 = true;
								while (running3) {
									switch (d = _getch()) {
									case KEY_Y:
										clearResumeGame(account);
										user->resumeAccount = account;
										user->usedAccount[account] = true;
										return NEW_GAME;
									case KEY_N:
										running3 = false;
										running2 = false;
										running1 = false;
										displayChooseResumeAccountScreen(user, resumeEnable);
										cout << LONG_TAB << "\t            " << "Pressed N" << endl;
										break;
									}
								}
							}
							else {
								user->resumeAccount = account;
								user->usedAccount[account] = true;
								return NEW_GAME;
							}
							break;
						}
						}
					}
				}

				case KEY_N:
					running1 = false;
					displayChooseResumeAccountScreen(user, resumeEnable);
					cout << LONG_TAB << "\t            " << "Pressed N" << endl;
					break;
				}
			}
			break;
		}
	}
}

bool processResume(GameBoard* board, States* states, User* user, bool resumeEnable) {
	cout << LONG_TAB << "\t       " << "Pressed " << COLOR_CYAN << "R" <<COLOR_RESET << endl;

	if (!resumeEnable) {
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
		case KEY_Y:
			loadUserVitalInformation(user);
			switch (processChooseResumeAccount(board, user, resumeEnable)) {
			case NEW_GAME:
				initGrid(board, states, user);
				break;
			case CONTINUE:
				loadResumeGame(board, states, user);
				break;
			}
			return true;
		case KEY_N:
			displayLobby(resumeEnable);
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
			switch (processEnterPlayerName(user, rankings)) {
			case NEW_GAME:
				initGrid(board, states, user);
				switch (processGamePlay(board, states, rankings, user)) {
				case CONTINUE:
					resumeEnable = !rankings->isEmpty();
					displayLobby(resumeEnable);
					break;
				case EXIT:
					deallocateGame(board, states, rankings, user);
					return;
				}
			case CONTINUE:
				break;
			case EXIT:
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
				displayGamePlayScreen(board, states, user);
				switch (processGamePlay(board, states, rankings, user)) {
				case CONTINUE:
					resumeEnable = !rankings->isEmpty();
					displayLobby(resumeEnable);
					break;
				case EXIT:
					deallocateGame(board, states, rankings, user);
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