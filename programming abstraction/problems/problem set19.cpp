#include "problem set19.h"
#include "error.h"

template <typename T>
Deque<T>::Deque() {
	head = NULL;
	tail = NULL;
}

template <typename T>
Deque<T>::~Deque() {
	deallocate(head);
	head = NULL;
	tail = NULL;
}

template <typename T>
bool Deque<T>::isEmpty() {
	return head == tail;
}

template <typename T>
void Deque<T>::pushFront(T value) {
	Cell* newCell = new Cell;
	newCell->val = value;
	newCell->next = head;
	newCell->prev = NULL;
	if(head != NULL) {
		head->prev = newCell;
	} else {
		tail = newCell;
	}
	head = newCell;
}

template <typename T>
void Deque<T>::pushBack(T value) {
	Cell* newCell = new Cell;
	newCell->val = value;
	newCell->next = NULL;
	newCell->prev = tail;
	if(tail != NULL) {
		tail->next = newCell;
	} else {
		head = newCell;
	}
	tail = newCell;
}

template <typename T>
T Deque<T>::popFront() {
	if(isEmpty()) {
		error("Unexpected exception: out of range");
	}
	T res = head->val;
	Cell* previous = head;
	head = head->next;
	delete previous;
	return res;
}

template <typename T>
T Deque<T>::popBack() {
	if(isEmpty()) {
		error("Unexpected exception: out of range");
	}

	T res = tail->val;
	Cell* after = tail;
	tail = tail->prev;
	delete after;
	return res;
}

template <typename T>
void Deque<T>::deallocate(Cell*& head) {
	if(head != NULL) {
		deallocate(head->next);
		delete head;
	}
}

template class Deque<int>;
template class Deque<double>;