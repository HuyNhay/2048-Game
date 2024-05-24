// Pull newest version at: https://github.com/HuyNhay/2048-Game.git
#include "GameLibrary.h"

using namespace std;

int main() {
	srand((unsigned int)time(NULL));

	Player* player = new Player();

	GameBoard* board = new GameBoard();

	changeGridSizes(board, 4, 4);

	States* states = new States();

	processLobby(board, player, states);
	
	List<Player>* rankings = new List<Player>();

	rankings->loadFromFile(player);

	initGrid(board, states, player);

	processGamePlay(board, states, rankings, player);

	deallocateGame(board, states, rankings, player);

	return 0;
}

