#include "GameLibrary.h"

using namespace std;

int main() {
	srand((unsigned int)time(NULL));

	User* user = new User();

	GameBoard* board = new GameBoard();
	changeGridSizes(board, 4, 4);

	States* states = new States();

	List<Player>* rankings = new List<Player>();
	loadRankings(rankings);

	processLobby(board, user, states, rankings);
	
	return 0;
}

