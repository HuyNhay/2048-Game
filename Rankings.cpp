#include "GameLibrary.h"

void List<Player>::removePlayer(Player player) {
	Node<Player>* curNode = head;
	for (
		int i = 0;
		curNode != nullptr;
		curNode = curNode->next, i++
		) {
		if (curNode->data.name == player.name) {
			removePos(i);
			return;
		}
	}
}

void List<Player>::addPlayer(Player player) {
	Node<Player>* curNode = head;
	for (
		int i = 0;
		curNode != nullptr;
		curNode = curNode->next, i++
		) {
		if (curNode->data.bestScore > player.bestScore) continue;
		if (
			curNode->data.bestScore == player.bestScore &&
			curNode->data.name < player.name
			) continue;
		addPos(i, new Node<Player>(player));
		return;
	}
	addTail(new Node<Player>(player));
}

void List<Player>::update(Player player) {
	removePlayer(player);
	addPlayer(player);
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
		curNode->data.writeToFile(output);
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

void saveRankings(List<Player>* rankings, Player* player) {
	rankings->update(*player);
	rankings->saveToFile();
}

void processShowRankings(List<Player>* rankings, Player* player) {
	system("CLS");

	displayRankings(rankings, player);

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

int findPlayerRank(List<Player>* rankings, Player* player) {
	rankings->update(*player);

	Node<Player>* curNode = rankings->head;
	for (
		int rank = 1;
		curNode != nullptr;
		curNode = curNode->next, rank++
		) {
		if (curNode->data.name == player->name) {
			return rank;
		}
	}
	
	return -1;
}