#include "GameLibrary.h"

template <typename T>
Node<T>::Node() {
	next = nullptr;
}

template <typename T>
Node<T>::Node(T _data) {
	data = _data;
	next = nullptr;
}

template <typename T>
Node<T>::~Node() {
	next = nullptr;
}

template struct Node<GameBoard*>; // explicit instantiate
template struct Node<Player>;

template <typename T>
ListBase<T>::ListBase() {
	head = nullptr;
	size = 0;
}

template <typename T>
ListBase<T>::~ListBase() {
	while (head != nullptr) {
		removeHead();
	}
}

template <typename T>
void ListBase<T>::addHead(Node<T>* node) {
	node->next = head;
	head = node;
	size++;
}

template <typename T>
void ListBase<T>::addTail(Node<T>* node) {
	if (head == nullptr) {
		head = node;
		size++;
		return;
	}

	Node<T>* curNode = head;
	while (curNode->next != nullptr) {
		curNode = curNode->next;
	}
	curNode->next = node;
	size++;
}

template <typename T>
void ListBase<T>::addPos(int pos, Node<T>* node) {
	if (pos == 0) {
		addHead(node);
		return;
	}

	Node<T>* preNode = head;
	for (int i = 1; i < pos; i++) {
		preNode = preNode->next;
	}
	node->next = preNode->next;
	preNode->next = node;
	size++;
}

template <typename T>
void ListBase<T>::removeHead() {
	if (head == nullptr) return;

	Node<T>* node = head;
	head = head->next;
	size--;
	delete node;
}

template <typename T>
void ListBase<T>::removePos(int pos) {
	if (pos == 0) {
		removeHead();
		return;
	}

	if (pos >= size) return;

	Node<T>* preNode = head;
	for (int i = 1; i < pos; i++) {
		preNode = preNode->next;
	}

	Node<T>* nodeAtPos = preNode->next;
	preNode->next = nodeAtPos->next;
	delete nodeAtPos;
	size--;
}

template struct ListBase<GameBoard*>;
template struct ListBase<Player>;

template struct List<GameBoard*>;
template struct List<Player>;