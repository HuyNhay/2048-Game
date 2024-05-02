#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <conio.h>

#define LONG_TAB "\t\t\t       "

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
const int CELL_LENGTH = 7;
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
	//"\033[48;2;205;192;180m",
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
const char COLOR[][20] = {
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
const int WIN_VALUE = 11;

struct GameBoard {
	int **grid;
	int width;
	int height;
	int score;
	int bestScore;
	bool isWin;

	GameBoard();
};

template <typename T>
struct Node {
	T data;
	Node<T>* next;

	Node() {
		next = nullptr;
	}

	Node(T _data) {
		data = _data;
		next = nullptr;
	}

	~Node() {
		next = nullptr;
	}
};

template <typename T>
struct List {
	Node<T>* head;
	int size;

	List() {
		head = nullptr;
		size = 0;
	}

	~List() {
		while (head != nullptr) {
			removeHead();
		}
	}

	void addHead(Node<T>* node) {
		if (head == nullptr) {
			head = node;
			size++;
			return;
		}

		node->next = head;
		head = node;
		size++;
	}

	void removeHead() {
		if (head == nullptr) return;

		Node<T>* node = head;
		head = head->next;
		size--;
		delete node;
	}
};

template <typename T>
struct Stack {
	List<T>* st;

	Stack() {
		st = new List<T>();
	}

	~Stack() {
		delete st;
	}

	void push(T item) {
		st->addHead(new Node<T>(item));
	}

	T top() {
		return (*st->head).data;
	}

	void pop() {
		st->removeHead();
	}

	int getSize() {
		return st->size;
	}

	bool isEmpty() {
		return (st->size == 0);
	}
};

struct States {
	Stack<GameBoard*> prev;
	Stack<GameBoard*> next;

	States();

	~States();
};

void addRandomTile(GameBoard*);

void clearMemory(GameBoard*);

void deallocateGameBoard(GameBoard*);

void deallocateGame(GameBoard*, States*);

void changeDimension(GameBoard*, int, int);

void initGrid(GameBoard*, States*);

void insertLine(GameBoard*, char);

void displayLobby();

void displayInstruction();

void displayGame(GameBoard*);

void swap(int*, int*);

bool availableMove(GameBoard*);

void processGameOver(GameBoard*&, States*);

void processVictory(GameBoard*&, States*);

void processUp(GameBoard*, States*);

void processDown(GameBoard*, States*);

void processLeft(GameBoard*, States*);

void processRight(GameBoard*, States*);

void processNewGame(GameBoard*, States*);

void processQuitGame(GameBoard*, States*);

void processChangeDimension(GameBoard*, States*);

void processUndo(GameBoard*&, States*);

void processRedo(GameBoard*&, States*);

void processGamePlay(GameBoard*&, States*);

void displayScore(GameBoard*);

void updateScore(GameBoard*, const int&);

void maximize(int&, const int&);

GameBoard* copyState(GameBoard*);

void pushState(Stack<GameBoard*>&, GameBoard*);

void popState(Stack<GameBoard*>&);

void clearStates(Stack<GameBoard*>&);