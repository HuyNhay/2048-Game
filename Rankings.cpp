#include "GameLibrary.h"

void List<Player>::removePlayer(User user) {
	Node<Player>* curNode = head;
	for (
		int i = 0;
		curNode != nullptr;
		curNode = curNode->next, i++
		) {
		if (curNode->data.name == user.name) {
			removePos(i);
			return;
		}
	}
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
	removePlayer(user);
	addPlayer(user);
	while (size > 20) {
		removePos(size - 1);
	}
}

void List<Player>::saveToFile() {
	ofstream output("Ranks.bin", ios::binary);
	output.write((char*)&size, sizeof(int));
	for (
		Node<Player>* curNode = head;
		curNode != nullptr;
		curNode = curNode->next
		) {
		saveRankPlayer(output, curNode->data);
	}
	output.close();

}

bool List<Player>::isEmpty() const {
	return (size == 0);
}

void loadRankings(List<Player>* rankings) {
	ifstream input("Ranks.bin", ios::binary);
	if (!input.is_open()) {
		return;
	}

	// read number of players
	int numPlayer = 0;
	input.read((char*)&numPlayer, sizeof(int));

	int nameLength = 0;
	string name = "";
	int score = 0;
	int playTime = 0;
	char* buffer = nullptr;

	while (numPlayer--) {
		// read name's length
		input.read((char*)&nameLength, sizeof(int));

		// read name
		buffer = new char[nameLength];
		input.read(buffer, nameLength);
		name = "";
		name.append(buffer, nameLength);
		delete[] buffer;

		// read score and time
		input.read((char*)&score, sizeof(int));
		input.read((char*)&playTime, sizeof(int));

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