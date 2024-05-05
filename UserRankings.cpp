#include "GameLibrary.h"

Player::Player() {
	name = "";
	bestScore = 0;
}

Player::Player(string _name, int _bestScore) {
	name = _name;
	bestScore = _bestScore;
}

Player::~Player() {
	name = "";
	bestScore = 0;
}

void Player::operator=(const Player& other) {
	name = other.name;
	bestScore = other.bestScore;
}

void Player::write(ofstream& output) const {
	output << name << endl;
	output << bestScore << endl;
}

void Player::print() const {
	cout << name << endl << bestScore << endl;
}

void loadRankings(List<Player>* rankings, Player* player) {
	ifstream input("Rankings.txt");
	if (!input.is_open()) {
		rankings->addTail(new Node<Player>(*player));
		return;
	}
	bool isNewPlayer = 1;
	string name = "";
	int score = 0;
	while (getline(input, name) && input >> score) {
		if (name == player->name) {
			player->bestScore = score;
			isNewPlayer = false;
		}

		rankings->addTail(new Node<Player>(Player(name, score)));
		
		input.ignore();
	}
	input.close();

	if (isNewPlayer) {
		rankings->addTail(new Node<Player>(*player));
	}
}

void saveRankings(List<Player>* rankings, Player* player) {
	ofstream output("Rankings.txt");
	rankings->update(player);
	rankings->writeDatas(output);
	output.close();
}