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
			curNode->data.name < user.name
			) continue;
		if (
			curNode->data.bestScore == user.bestScore &&
			curNode->data.name == user.name &&
			curNode->data.playTime < user.playTime
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
	ofstream output("Ranks.txt");
	for (
		Node<Player>* curNode = head;
		curNode != nullptr;
		curNode = curNode->next
		) {
		savePlayer(output, curNode->data);
	}
	output.close();

}

bool List<Player>::isEmpty() const {
	return (size == 0);
}

void loadRankings(List<Player>* rankings) {
	ifstream input("Ranks.txt");
	if (!input.is_open()) {
		return;
	}
	string name = "";
	int score = 0;
	long long playTime = 0;
	while (getline(input, name) && input >> score && input >> playTime) {
		rankings->addTail(new Node<Player>(Player(name, score, playTime)));
		input.ignore();
	}
	input.close();
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