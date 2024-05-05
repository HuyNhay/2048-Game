// Pull newest version at: https://github.com/HuyNhay/2048-Game.git
#include "GameLibrary.h"

using namespace std;

int main() {
	srand((unsigned int)time(NULL));

	Player* player = new Player();
	
	displayLobby();

	processEnterPlayerName(player);

	GameBoard* board = new GameBoard();

	States* states = new States();

	List<Player>* rankings = new List<Player>();

	rankings->loadFromFile(player);

	changeDimension(board, 4, 4);

	initGrid(board, states, player);

	processGamePlay(board, states, rankings, player);

	deallocateGame(board, states, rankings, player);

	return 0;
}