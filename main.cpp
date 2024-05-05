#include "GameLibrary.h"

using namespace std;

int main() {
	srand((unsigned int)time(NULL));

	GameBoard* board = new GameBoard();

	States* states = new States();

	Player* player = new Player();

	List<Player>* rankings = new List<Player>();
	
	displayLobby(board, states, player, rankings);

	loadRankings(rankings, player);

	changeDimension(board, 4, 4);

	initGrid(board, states, player);

	processGamePlay(board, states, rankings, player);

	deallocateGame(board, states, rankings, player);

	return 0;
}