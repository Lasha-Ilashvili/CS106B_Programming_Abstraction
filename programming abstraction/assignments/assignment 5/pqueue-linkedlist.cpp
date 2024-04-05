/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

/* Constructor: Initializes an empty queue. */
LinkedListPriorityQueue::LinkedListPriorityQueue() {
	
	head = NULL;
	elements = 0;
}

/* Destructor: Deallocates the memory used by the queue. */
LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	
	deallocate(head);
	head = NULL;
}

/* Returns the number of elements in the queue. */
int LinkedListPriorityQueue::size() {
	
	return elements;
}

/* Checks if the queue is empty. */
bool LinkedListPriorityQueue::isEmpty() {
	
	return elements == 0;
}

/* Adds an element to the queue in its sorted position. */
void LinkedListPriorityQueue::enqueue(string value) {
	
	Cell* temp = new Cell;
	temp->s = value;
	temp->next = NULL;

	elements++;

	if (head == NULL || head->s >= value) {
		temp->next = head;
		head = temp;
		return;
	}

	Cell* prev = NULL, *current = head;

	while (current != NULL && current->s <= value) {
		prev = current;
		current = current->next;
	}

	temp->next = current;
	prev->next = temp;
}

/* Returns the element with the highest priority (smallest value) in the queue. */
string LinkedListPriorityQueue::peek() {
	
	if (isEmpty()) {
		error("Unexpected exception: out of range");
	}
	return head->s;
}

/* Removes and returns the element with the highest priority (smallest value) from the queue. */
string LinkedListPriorityQueue::dequeueMin() {
	
	string res = peek();

	Cell* prev = head;
	head = head->next;
	delete prev;

	elements--;

	return res;
}

/* Recursively deallocates the memory used by the queue. */
void LinkedListPriorityQueue::deallocate(Cell*& head) {
	
	if (head != NULL) {
		deallocate(head->next);
		delete head;
	}
}