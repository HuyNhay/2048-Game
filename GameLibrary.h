#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>

#define LONG_TAB "\t\t\t       "
#define TAB "        "

#define COLOR_RED "\033[31m" 
#define COLOR_GREEN "\033[32m" 
#define COLOR_YELLOW "\033[33m" 
#define COLOR_BLUE "\033[34m" 
#define COLOR_MAGENTA "\033[35m" 
#define COLOR_CYAN "\033[36m" 
#define COLOR_RESET "\033[0m" 

using namespace std;

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
const int CELL_LENGTH = 7;
const int NAME_LENGTH = 23;
const int R = 12;
const int C = 13;
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
	"\033[38;2;158;1;66m",
	"\033[38;2;213;62;79m",
	"\033[38;2;244;109;67m",
	"\033[38;2;253;174;97m",
	"\033[38;2;254;224;139m",
	"\033[38;2;230;245;152m",
	"\033[38;2;171;221;164m",
	"\033[38;2;102;194;165m",
	"\033[38;2;50;136;189m",
	"\033[38;2;94;79;162m",
};
const int WIN_VALUE = 11;

struct GameBoard {
	int **grid;
	int width;
	int height;
	int score;
	bool isWin;

	GameBoard();

	~GameBoard();
};

struct Player {
	string name;
	int bestScore;

	Player();

	Player(string, int);

	~Player();

	void operator=(const Player&);

	void writeToFile(ofstream&) const;

	void print() const;
};

template <typename T>
struct Node {
	T data;
	Node<T>* next;

	Node();

	Node(T);

	~Node();
};

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

template <>
struct List<Player> : ListBase<Player> {
	void removePlayer(Player);

	void addPlayer(Player);

	void update(Player);

	void loadFromFile(Player*);

	void saveToFile();

	void display() const;
};

template <typename T>
struct Stack {
	List<T>* st;

	Stack();

	~Stack();

	void push(T);

	T top();

	void pop();

	int getSize();

	bool isEmpty();
};

struct States {
	Stack<GameBoard*> prev;
	Stack<GameBoard*> next;

	States();

	~States();
};

// Lobby
void processLobby(GameBoard*, Player*);

void displayLobby();

void processEnterPlayerName(Player*);

void displaySettings(GameBoard*);

void processSettings(GameBoard*);

void processChangeGridSizesLobby(GameBoard*);
//
void removeSpaces(string&);

void addRandomTile(GameBoard*);

void clearMemory(GameBoard*);

void deallocateGame(GameBoard*, States*, List<Player>*, Player*);

void changeDimension(GameBoard*, int, int);

void initGrid(GameBoard*, States*, Player*);

void insertGridBorder(GameBoard*, char);

void displayInstruction();

void displayGame(GameBoard*, Player*);

void swap(int*, int*);

bool availableMove(GameBoard*);

bool processGameOver(GameBoard*&, States*, List<Player>*, Player*);

bool processVictory(GameBoard*&, States*, List<Player>*, Player*);

void processUp(GameBoard*, States*, Player*);

void processDown(GameBoard*, States*, Player*);

void processLeft(GameBoard*, States*, Player*);

void processRight(GameBoard*, States*, Player*);

void processNewGame(GameBoard*, States*, Player*);

bool processQuitGame(GameBoard*, States*, List<Player>*, Player*);

void processChangeGridSizesMain(GameBoard*, States*, Player*);

void processUndo(GameBoard*&, States*, Player*);

void processRedo(GameBoard*&, States*, Player*);

void processShowRankings(List<Player>*);

void processGamePlay(GameBoard*&, States*, List<Player>*, Player*);

void displayScore(GameBoard*, Player*);

void updateScore(GameBoard*, Player*, const int&);

bool maximize(int&, const int&);

GameBoard* copyState(GameBoard*);

void pushState(Stack<GameBoard*>&, GameBoard*);

void popState(Stack<GameBoard*>&);

void clearStates(Stack<GameBoard*>&);