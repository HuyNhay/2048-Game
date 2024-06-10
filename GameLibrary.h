#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <chrono>

#define LONG_TAB "\t\t\t       "
#define TAB "        "

#define COLOR_RED "\033[31m" 
#define COLOR_GREEN "\033[32m" 
#define COLOR_YELLOW "\033[33m" 
#define COLOR_BLUE "\033[34m" 
#define COLOR_MAGENTA "\033[35m" 
#define COLOR_CYAN "\033[36m" 
#define COLOR_ORANGE "\033[38;2;242;177;121m"
#define COLOR_RESET "\033[0m" 

using namespace std;
using namespace std::chrono;

const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int KEY_ESC = 27;
const int KEY_ENTER = 13;
const int KEY_SPACE = 32;
const char KEY_U = 'u';
const char KEY_N = 'n';
const char KEY_Y = 'y';
const char KEY_C = 'c';
const char KEY_R = 'r';
const char KEY_H = 'h';
const char KEY_S = 's';
const char KEY_G = 'g';
const char KEY_L = 'l';
const char KEY_M = 'm';
const char KEY_1 = '1';
const char KEY_2 = '2';
const char KEY_3 = '3';
const int CONTINUE = 111;
const int LOBBY = 222;
const int EXIT = 333;
const int CELL_LENGTH = 7;
const int NAME_LENGTH = 23;
const int SCORE_LENGTH = 16;
const int R = 12;
const int C = 13;
const int WIN_VALUE = 11;
const char ZERO[R][C] = {
	"************",
	"************",
	"**        **",
	"**        **",
	"**        **",
	"**        **",
	"**        **",
	"**        **",
	"**        **",
	"**        **",
	"************",
	"************"
};
const char TWO[R][C] = {
	"************",
	"************",
	"          **",
	"          **",
	"          **",
	"************",
	"************",
	"**          ",
	"**          ",
	"**          ",
	"************",
	"************"
};
const char FOUR[R][C] = {
	"**        **",
	"**        **",
	"**        **",
	"**        **",
	"**        **",
	"************",
	"************",
	"          **",
	"          **",
	"          **",
	"          **",
	"          **"
};
const char EIGHT[R][C] = {
	"************",
	"************",
	"**        **",
	"**        **",
	"**        **",
	"************",
	"************",
	"**        **",
	"**        **",
	"**        **",
	"************",
	"************"
};
const int POW2[] = {
	1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 
};
const int NUM_LENGTH[] = {
	0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4
};
const char BG_COLOR[][20] = {
	"",
	"\033[48;2;238;228;218m",
	"\033[48;2;237;224;200m",
	"\033[48;2;242;177;121m",
	"\033[48;2;245;150;100m",
	"\033[48;2;245;125;95m",
	"\033[48;2;245;95;60m",
	"\033[48;2;237;207;114m",
	"\033[48;2;237;204;97m",
	"\033[48;2;237;204;97m",
	"\033[48;2;237;204;97m",
	"\033[48;2;237;204;97m",
};
const char FONT_COLOR[][20] = {
	"\033[38;2;119;110;101m",
	"\033[38;2;119;110;101m",
	"\033[38;2;119;110;101m",
	"\033[38;2;255;255;255m",
	"\033[38;2;255;255;255m",
	"\033[38;2;255;255;255m",
	"\033[38;2;255;255;255m",
	"\033[38;2;255;255;255m",
	"\033[38;2;255;255;255m",
	"\033[38;2;255;255;255m",
	"\033[38;2;255;255;255m",
	"\033[38;2;255;255;255m"
};
const char RANK_COLOR[][20] = {
	"",
	"\033[38;2;231;29;67m",
	"\033[38;2;255;0;0m",
	"\033[38;2;255;55;0m",
	"\033[38;2;255;110;0m",
	"\033[38;2;255;165;0m",
	"\033[38;2;255;195;0m",
	"\033[38;2;255;225;0m",
	"\033[38;2;255;255;0m",
	"\033[38;2;170;213;0m",
	"\033[38;2;100;187;106m",

	"\033[38;2;85;170;0m",
	"\033[38;2;0;128;0m",
	"\033[38;2;22;138;173m",
	"\033[38;2;0;0;255m",
	"\033[38;2;25;0;200m",
	"\033[38;2;55;10;160m",
	"\033[38;2;129;43;166m",
	"\033[35m",
	"\033[38;2;184;87;202m",
	"\033[38;2;180;58;135m",

};

// User
struct User {
	string name;
	int bestScore;
	bool continuePlay;
	high_resolution_clock::time_point startTime;
	int addedTime;
	int playTime;

	User();

	User(string, int, bool, int, int);

	~User();

	void operator=(const User&);
};


// Game board
struct GameBoard {
	int **grid;
	int width;
	int height;
	int score;
	bool isWin;

	GameBoard();

	~GameBoard();
};

// Node
template <typename T>
struct Node {
	T data;
	Node<T>* next;

	Node();

	Node(T);

	~Node();
};

// Player
struct Player {
	string name;
	int bestScore;
	int playTime;

	Player();

	Player(string, int, int);

	Player(const User&);

	~Player();

	void operator=(const Player&);
};
void saveRankPlayer(ofstream&, Player);

// Linked List
template <typename T>
struct ListBase {
	Node<T>* head;
	int size;

	ListBase();
	~ListBase();

	void addHead(Node<T>*);
	void addTail(Node<T>*);
	void addPos(int, Node<T>*);
	void removeHead();
	void removePos(int);
};
template <typename T>
struct List : ListBase<T> {
};

// Rankings
template <>
struct List<Player> : ListBase<Player> {
	void removePlayer(User);
	void addPlayer(User);
	void update(User);
	void saveToFile();
	bool isEmpty() const;
};
int numberLength(int);
void loadRankings(List<Player>*);
void processShowRankings(List<Player>*, User*);
void saveRankings(List<Player>*, User*);
int findUserRank(List<Player>*, User*);

// Stack
template <typename T>
struct Stack {
	List<T>* st;

	Stack();
	~Stack();

	void push(T);
	void pushTail(T);
	T top();
	void pop();
	int getSize();
	bool isEmpty();
};

// States
struct States {
	bool activePrev;
	bool activeNext;
	Stack<GameBoard*> prev;
	Stack<GameBoard*> next;

	States();
	~States();
};
GameBoard* copyState(GameBoard*);
void pushState(Stack<GameBoard*>&, GameBoard*);
void popState(Stack<GameBoard*>&);
void clearStates(Stack<GameBoard*>&);

// Lobby
void processLobby(GameBoard*, User*, States*, List<Player>*);
bool processEnterPlayerName(User*, List<Player>*);
bool checkNameExistence(List<Player>*, string);
void removeSpaces(string&);
void processSettings(GameBoard*, States*);
void processChangeGridSizesLobby(GameBoard*, States*);
void processChangeGameMode(GameBoard*, States*);
void changeGameMode(States*, int);
bool processResume(GameBoard*, States*, User*, bool);

// Resume
void saveResumeGame(GameBoard*, States*, User*);
void saveUser(User*);
void saveStates(States*);
void saveGameBoard(GameBoard*);
void loadUser(User*);
void loadStatesActiveStatus(States*);
void loadGameBoard(GameBoard*);
void loadPrevStates(States*);
void loadNextStates(States*);

// Grid
void changeGridSizes(GameBoard*, int, int);
void initGrid(GameBoard*, States*, User*);
void addRandomTile(GameBoard*);
void updateScore(GameBoard*, User*, const int&);
bool maximize(int&, const int&);
void clearMemory(GameBoard*);

// Display
void displayLobby(bool);
void displaySettings(GameBoard*, States*);
void displayGridBorder(GameBoard*, char);
void displayEmptyRow(GameBoard*, int);
void displayScore(GameBoard*, User*);
void displayGrid(GameBoard*);
void displayInstruction(States*);
void displayMainScreen(GameBoard*, States*, User*);
void displayVictoryScreen(GameBoard*, States*, List<Player>*, User*);
void displayLossScreen(GameBoard*, States*, User*);
void displayRankings(List<Player>*, User*);

// Game Process
void swap(int*, int*);
bool availableMove(GameBoard*);
int processGameOver(GameBoard*&, States*, List<Player>*, User*);
int processVictory(GameBoard*&, States*, List<Player>*, User*);
void processUp(GameBoard*, States*, User*);
void processDown(GameBoard*, States*, User*);
void processLeft(GameBoard*, States*, User*);
void processRight(GameBoard*, States*, User*);
void processNewGame(GameBoard*, States*, User*);
bool processQuitGame(GameBoard*, States*, List<Player>*, User*);
void processChangeGridSizesMain(GameBoard*, States*, User*);
void processUndo(GameBoard*&, States*, User*);
void processRedo(GameBoard*&, States*, User*);
int processGamePlay(GameBoard*&, States*, List<Player>*, User*);

// Deallocate
void deallocateGame(GameBoard*, States*, List<Player>*, User*);