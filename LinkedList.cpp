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

template struct Node<GameBoard*>;

template <typename T>
List<T>::List() {
	head = nullptr;
	size = 0;
}

template <typename T>
List<T>::~List() {
	while (head != nullptr) {
		removeHead();
	}
}

template <typename T>
void List<T>::addHead(Node<T>* node) {
	if (head == nullptr) {
		head = node;
		size++;
		return;
	}

	node->next = head;
	head = node;
	size++;
}

template <typename T>
void List<T>::removeHead() {
	if (head == nullptr) return;

	Node<T>* node = head;
	head = head->next;
	size--;
	delete node;
}

template struct List<GameBoard*>;