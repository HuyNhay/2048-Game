#include "GameLibrary.h"

using namespace std;

int main() {
	srand((unsigned int)time(NULL));
	
	GameBoard* board = new GameBoard();

	States* states = new States();

	displayLobby();

	changeDimension(board, 4, 4);

	initGrid(board, states);

	processGamePlay(board, states);

	deallocateGame(board, states);

	return 0;
}