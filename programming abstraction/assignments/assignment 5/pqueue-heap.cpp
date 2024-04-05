/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */

#include "pqueue-heap.h"
#include "error.h"

/* Constructor: Initializes an empty queue with initial capacity. */
HeapPriorityQueue::HeapPriorityQueue() {
	
	elements = new string[INITIAL_CAPACITY];
	capacity = INITIAL_CAPACITY;
	elemCount = 0;
}

/* Destructor: Deallocates the memory used by the queue. */
HeapPriorityQueue::~HeapPriorityQueue() {
	
	delete[] elements;
}

/* Returns the number of elements in the queue. */
int HeapPriorityQueue::size() {
	
	return elemCount;
}

/* Checks if the queue is empty. */
bool HeapPriorityQueue::isEmpty() {
	
	return elemCount == 0;
}

/* Adds a new element to the queue. */
void HeapPriorityQueue::enqueue(string value) {
	
	if (elemCount == capacity) {
		expand();
	}
	elements[elemCount] = value;
	int parent = (elemCount - 1) / 2;
	bubble_up(elemCount, parent, elemCount + 1);
	elemCount++;
}

/* Returns the minimum element in the queue without removing it. */
string HeapPriorityQueue::peek() {
	
	if (isEmpty()) {
		error("Unexpected exception: out of range");
	}
	return elements[0];
}

/* Removes and returns the minimum element from the queue. */
string HeapPriorityQueue::dequeueMin() {
	
	string res = peek();

	elemCount--;
	elements[0] = elements[elemCount];
	bubble_down(0, elemCount + 1);

	return res;
}

/* Doubles the capacity of the queue by creating a new array and copying the elements. */
void HeapPriorityQueue::expand() {
	
	capacity *= 2;
	string* arr = new string[capacity];
	for (int i = 0; i < elemCount; i++) {
		arr[i] = elements[i];
	}
	delete[] elements;
	elements = arr;
}

/* Bubbles up the element at the given child index until it satisfies the queue property. */
void HeapPriorityQueue::bubble_up(int child, int parent, int size) {
	
	while (parent >= 0 && parent < size && elements[child] < elements[parent]) {
		swap(child, parent);

		child = parent;
		parent = (child - 1) / 2;
	}
}

/* Bubbles down the element at the given parent index until it satisfies the queue property. */
void HeapPriorityQueue::bubble_down(int parent, int size) {
	
	int leftChild = parent * 2 + 1;
	int rightChild = parent * 2 + 2;
	int min = parent;

	if (leftChild < size && elements[leftChild] < elements[min]) {
		min = leftChild;
	}

	if (rightChild < size && elements[rightChild] < elements[min]) {
		min = rightChild;
	}

	if (min != parent) {
		swap(parent, min);
		bubble_down(min, size);
	}
}

/* Swaps the elements at the given indices. */
void HeapPriorityQueue::swap(int n1, int n2) {
	
	string temp = elements[n1];
	elements[n1] = elements[n2];
	elements[n2] = temp;
}
