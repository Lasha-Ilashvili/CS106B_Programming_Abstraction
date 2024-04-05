#include "linkedSet.h"


LinkedSet::LinkedSet() {
	head = NULL;
	current = head;
	elements = 0;
}

void LinkedSet::add(int k) {
	if(contains(k)) {
		return;
	}	

	Cell* temp = new Cell;
	temp->n = k;
	temp->next = head;
	head = temp;

	elements++;
}

bool LinkedSet::contains(int k) {
	for(Cell* ptr = head; ptr != NULL; ptr = ptr->next) {
		if(ptr->n == k) {
			return true;
		}
	}
	return false;
}

int LinkedSet::size() {
	return elements;
}

void LinkedSet::remove(int k) {
	Cell* prev = head;
	for(Cell* ptr = head; ptr != NULL; ptr = ptr->next) {
		if(ptr->n == k) {
			prev->next = ptr->next;
			delete ptr;
			elements--;
			break;
		}
		prev = ptr;
	}
}

void LinkedSet::resetIterator() {
	current = head;
}

bool LinkedSet::hasNext() {
	return current != NULL;
}

int LinkedSet::next() {
	int res = current->n;
	current = current->next;
	return res;
}