#include "GameLibrary.h"

template <typename T>
Stack<T>::Stack() {
	st = new List<T>();
}

template <typename T>
Stack<T>::~Stack() {
	delete st;
}

template <typename T>
void Stack<T>::push(T item) {
	st->addHead(new Node<T>(item));
}

template <typename T>
T Stack<T>::top() {
	return (*st->head).data;
}

template <typename T>
void Stack<T>::pop() {
	st->removeHead();
}

template <typename T>
int Stack<T>::getSize() {
	return st->size;
}

template <typename T>
bool Stack<T>::isEmpty() {
	return (st->size == 0);
}

template struct Stack<GameBoard*>; // explicit instantiate