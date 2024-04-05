/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */

#include "pqueue-doublylinkedlist.h"
#include "error.h"

/* Constructor: Initializes an empty queue. */
DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	
	head = NULL;
	minCell = NULL;
	cells = 0;
}

/* Destructor: Deallocates the memory used by the queue. */
DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	
	deallocate(head);
	head = NULL;
	minCell = NULL;
}

/* Returns the number of cells in the queue. */
int DoublyLinkedListPriorityQueue::size() {
	
	return cells;
}

/* Checks if the queue is empty. */
bool DoublyLinkedListPriorityQueue::isEmpty() {
	
	return cells == 0;
}

/* Adds a cell to the front of the queue. */
void DoublyLinkedListPriorityQueue::enqueue(string value) {
	
	Cell* newCell = new Cell;

	if (head != NULL) {
		head->prev = newCell;
	}

	newCell->s = value;
	newCell->next = head;
	newCell->prev = NULL;

	head = newCell;
	cells++;
}

/* Returns the minimum element in the queue. */
string DoublyLinkedListPriorityQueue::peek() {
	
	if (isEmpty()) {
		error("Unexpected exception: out of range");
	}

	string min = head->s;
	minCell = head;
	Cell* current = head->next;

	while (current != NULL) {
		if (min > current->s) {
			min = current->s;
			minCell = current;
		}
		current = current->next;
	}

	return min;
}

/* Removes and returns the minimum element from the queue. */
string DoublyLinkedListPriorityQueue::dequeueMin() {
	
	string res = peek();

	if (minCell->prev != NULL) {
		minCell->prev->next = minCell->next;
	} else {
		head = minCell->next;
	}

	if (minCell->next != NULL) {
		minCell->next->prev = minCell->prev;
	}

	delete minCell;

	cells--;

	return res;
}

/* Recursively deallocates the memory used by the queue. */
void DoublyLinkedListPriorityQueue::deallocate(Cell*& head) {
	
	if (head != NULL) {
		deallocate(head->next);
		delete head;
	}
}