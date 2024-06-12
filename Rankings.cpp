#include "GameLibrary.h"

bool List<Player>::removePlayer(User user) {
	bool isExist = false;
	Node<Player>* curNode = head;
	for (
		int i = 0;
		curNode != nullptr;
		curNode = curNode->next, i++
		) {
		if (curNode->data.name == user.name) {
			isExist = true;
			if (curNode->data.bestScore < user.bestScore) {
				removePos(i);
				return true;
			}
		}
	}
	return !isExist;
}

void List<Player>::addPlayer(User user) {
	Node<Player>* curNode = head;
	for (
		int i = 0;
		curNode != nullptr;
		curNode = curNode->next, i++
		) {
		if (curNode->data.bestScore > user.bestScore) continue;
		if (
			curNode->data.bestScore == user.bestScore &&
			curNode->data.playTime < user.playTime
			) continue;
		if (
			curNode->data.bestScore == user.bestScore &&
			curNode->data.playTime == user.playTime &&
			curNode->data.name < user.name
			) continue;
		addPos(i, new Node<Player>(Player(user)));
		return;
	}
	addTail(new Node<Player>(Player(user)));
}

void List<Player>::update(User user) {
	if (removePlayer(user))	addPlayer(user);
	while (size > 20) {
		removePos(size - 1);
	}
}

void List<Player>::saveToFile() {
	Encrypter encrypter("Ranks.bin");

	encrypter.writeInt(size);
	for (
		Node<Player>* curNode = head;
		curNode != nullptr;
		curNode = curNode->next
		) {
		saveRankPlayer(encrypter, curNode->data);
	}
}

bool List<Player>::isEmpty() const {
	return (size == 0);
}

void loadRankings(List<Player>* rankings) {
	Decrypter decrypter("Ranks.bin");

	if (!decrypter.input.is_open()) {
		return;
	}

	// read number of players
	int numPlayer = decrypter.readInt();

	string name = "";
	int score = 0;
	int playTime = 0;

	while (numPlayer--) {
		// read name
		name = decrypter.readString();

		// read score and time
		score = decrypter.readInt();
		playTime = decrypter.readInt();
		
		// add new player
		rankings->addTail(new Node<Player>(Player(name, score, playTime)));
	}
}

void saveRankings(List<Player>* rankings, User* user) {
	rankings->update(*user);
	rankings->saveToFile();
}

void processShowRankings(List<Player>* rankings, User* user) {
	system("CLS");

	displayRankings(rankings, user);

	cout << endl << endl;
	cout << " Press " << COLOR_YELLOW << "Space " << COLOR_RESET << "to continue game..." << endl;

	int userChoice = 0;
	while (true) {
		switch (userChoice = _getch()) {
		case KEY_SPACE:
			return;
		}
	}
}

int findUserRank(List<Player>* rankings, User* user) {
	rankings->update(*user);

	Node<Player>* curNode = rankings->head;
	for (
		int rank = 1;
		curNode != nullptr;
		curNode = curNode->next, rank++
		) {
		if (curNode->data.name == user->name) {
			return rank;
		}
	}
	
	return -1;
}