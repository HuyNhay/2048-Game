#include "GameLibrary.h"

using namespace std;

int main() {
	srand((unsigned int)time(NULL));

	Player* player = new Player();

	GameBoard* board = new GameBoard();
	changeGridSizes(board, 4, 4);

	States* states = new States();

	List<Player>* rankings = new List<Player>();
	rankings->loadFromFile();

	processLobby(board, player, states, rankings);
	
	processGamePlay(board, states, rankings, player);

	saveRankings(rankings, player);

	saveResumeGame(board, states, rankings, player);

	deallocateGame(board, states, rankings, player);

	return 0;
}

