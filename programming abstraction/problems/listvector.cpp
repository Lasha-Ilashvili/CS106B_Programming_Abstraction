
#include "listvector.h"
#include <iostream>

ListVector::ListVector() {
	head = NULL;
	tail = NULL;
	length = 0;
}

int ListVector::size(){
	return length;
}

void ListVector::add(int val){
	Cell* temp = new Cell;
	temp->n = val;
	temp->next = NULL;

	if(head == NULL) {
		head = temp;
		tail = temp;
	} else {
		tail->next = temp;
		tail = temp;
	}

	length++;
}

int ListVector::get(int i){
	int res = 0, index = 0;

	for(Cell* ptr = head; ptr != NULL; ptr = ptr->next) {

		if(index == i) {
			res = ptr->n;
			break;
		}

		index++;
	} 

	return res;
}

void ListVector::insert(int i, int val){
	int index = 0;
	Cell* prev = NULL, *current = NULL;

	for(Cell* ptr = head; ptr != NULL; ptr = ptr->next) {

		if(index == i) {
			current = ptr;
			break;
		}

		index++;
		prev = ptr;
	}

	Cell* temp = new Cell;
	temp->n = val;
	temp->next = current;
	if(prev != NULL) {
		prev->next = temp;
	} else {
		head = temp;
	}

	if(current == NULL) {
		tail = temp;
	}

	length++;
}

void ListVector::remove(int i){
	int index = 0;
	Cell* prev = NULL, *current = head;

	for(Cell* ptr = head; ptr != NULL; ptr = ptr->next) {

		if(index == i) {
			current = ptr;
			break;
		}

		index++;
		prev = ptr;
	}

	if(current == head) {
		head = current->next;
	} else {
		if(current == tail) {
			tail = prev;
		}
		prev->next = current->next;
	}

	delete current;

	length--;
}