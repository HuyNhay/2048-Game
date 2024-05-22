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
}

void List<Player>::loadFromFile(Player* player) {
	ifstream input("Rankings.txt");
	if (!input.is_open()) {
		return;
	}
	string name = "";
	int score = 0;
	while (getline(input, name) && input >> score) {
		if (name == player->name) {
			player->bestScore = score;
		}

		addTail(new Node<Player>(Player(name, score)));

		input.ignore();
	}
	input.close();
}

void List<Player>::saveToFile() {
	ofstream output("Rankings.txt");
	for (
		Node<Player>* curNode = head;
		curNode != nullptr;
		curNode = curNode->next
		) {
		curNode->data.writeToFile(output);
	}
	output.close();

}

void List<Player>::display() const {
	cout << "\t      " << COLOR_GREEN << "RANKINGS" << COLOR_RESET << endl;
	cout << endl;

	cout << " Rank   ";

	cout << "Nickname";
	for (int i = 1; i < NAME_LENGTH - 8; i++) {
		cout << " ";
	}

	cout << "Score" << endl;

	int index = 1;
	for (
		Node<Player>* curNode = head;
		curNode != nullptr && index <= 10;
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
			int i = 1;
			i < NAME_LENGTH - player.name.length();
			i++
			) {
			cout << " ";
		}

		// print best score
		cout << player.bestScore << endl;

		cout << COLOR_RESET;
	}
}