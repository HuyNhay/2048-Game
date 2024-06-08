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

void List<Player>::loadFromFile() {
	ifstream input("Ranks.txt");
	if (!input.is_open()) {
		return;
	}
	string name = "";
	int score = 0;
	long long playTime = 0;
	while (getline(input, name) && input >> score && input >> playTime) {
		addTail(new Node<Player>(Player(name, score, playTime)));
		input.ignore();
	}
	input.close();
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

void List<Player>::display(Player* user) const {
	cout << "\t                 " << COLOR_GREEN << "RANKINGS" << COLOR_RESET << endl;
	cout << endl;

	cout << " Rank   ";

	cout << "Nickname";
	for (int i = 1; i < NAME_LENGTH - 1; i++) {
		cout << " ";
	}

	cout << "Score          ";

	cout << "Played Time" << endl;

	int index = 1;
	for (
		Node<Player>* curNode = head;
		curNode != nullptr && index <= 20;
		curNode = curNode->next, index++
		) {
		Player& player = curNode->data;
		cout << RANK_COLOR[index];

		// print index
		cout << " " << index;
		if (index < 10) cout << "      ";
		else cout << "     ";
		
		// print name
		cout << player.name;
		for (
			int i = 1, length = player.name.length();
			i < NAME_LENGTH - length;
			i++
			) {
			cout << " ";
		}
		cout << (player.name == user->name ? "(you)  " : "       ");

		// print best score
		cout << player.bestScore;
		for (
			int i = 1, length = numberLength(player.bestScore);
			i < SCORE_LENGTH - length;
			i++
			) {
			cout << " ";
		}

		// print played time
		cout << player.playTime << "s" << endl;

		cout << COLOR_RESET;
	}
}

void saveRankings(List<Player>* rankings, Player* player) {
	rankings->update(*player);
	rankings->saveToFile();
}

void processShowRankings(List<Player>* rankings, Player* player) {
	system("CLS");

	rankings->display(player);

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