/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	// TODO: Fill this in!
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
}

/* Returns the number of elements in the queue. */
int VectorPriorityQueue::size() {
	return v.size();
}

/* Checks if the queue is empty. */
bool VectorPriorityQueue::isEmpty() {
	
	return v.isEmpty();
}

/* Adds an element to the queue. */
void VectorPriorityQueue::enqueue(string value) {
	
	v += value;
}

/* Returns the minimum element (lexicographically smallest) in the queue without removing it.
 * Throws an error if the queue is empty.
 */
string VectorPriorityQueue::peek() {
	
	if (isEmpty()) {
		error("Unexpected exception: out of range");
	}

	return v[findMin()];
}

/* Removes and returns the minimum element (lexicographically smallest) in the queue.
 * Throws an error if the queue is empty. 
 */
string VectorPriorityQueue::dequeueMin() {
	
	if (isEmpty()) {
		error("Unexpected exception: out of range");
	}

	int index = findMin();
	string res = v[index];

	v.remove(index);

	return res;
}

/* Finds the index of the minimum element (lexicographically smallest) in the queue. */ 
int VectorPriorityQueue::findMin() {
	
	int min = 0;

	for (int i = 1; i < v.size(); i++) {
		if (v[i] < v[min]) {
			min = i;
		}
	}

	return min;
}