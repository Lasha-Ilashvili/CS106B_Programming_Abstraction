#include "linkedqueue.h"
#include "queue.h"

LinkedQueue::LinkedQueue() {
	head = NULL;
	tail = NULL;
	cells = 0;
}

LinkedQueue::~LinkedQueue() {
	deallocate(head);
	head = NULL;
	tail = NULL;
}

int LinkedQueue::size() {
	return cells;
}

bool LinkedQueue::isEmpty() {
	return cells == 0;
}

void LinkedQueue::enqueue(int n) {
	Cell* temp = new Cell;
	temp->n = n;
	temp->link = NULL;

	if(head==NULL) {
		head = temp;
		tail = temp;
	} else {
		tail->link = temp;
		tail = temp;
	}

	cells++;
}

int LinkedQueue::peek() {
	if(head == NULL) {
		error("Unexpected exception: out of range");
	}
	return head->n;
}

int LinkedQueue::dequeue() {
	int res = peek();

	Cell* temp = head;
	head = head->link;
	delete temp;
	
	cells--;
	
	return res;
}

void LinkedQueue::deallocate(Cell*& head) {
	if(head != NULL) {
		deallocate(head->link);
		delete head;
	}
}