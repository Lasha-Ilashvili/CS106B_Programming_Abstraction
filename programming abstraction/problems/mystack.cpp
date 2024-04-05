#include "mystack.h"
#include <error.h>

MyStack::MyStack() {
	elements = new int[INITIAL_CAPACITY];
	capacity = INITIAL_CAPACITY;
	count = 0;
}

MyStack& MyStack::operator=(const MyStack& other) {
	if (this != &other) {
		// Delete existing elements array
		delete[] elements;

		// Allocate new memory for elements array
		elements = new int[other.capacity];

		// Copy elements from other to current object
		for (int i = 0; i < other.count; i++) {
			elements[i] = other.elements[i];
		}

		// Copy other member variables
		capacity = other.capacity;
		count = other.count;
	}

	return *this;
}

MyStack::~MyStack() {
	delete[] elements;
}

bool MyStack::isEmpty() {
	return count == 0;
}

int MyStack::size() {
	return count;
}
void MyStack::push(int n) {
	if(count == capacity) {
		expand();
	}
	elements[count++] = n;
}

void MyStack::expand() {
	capacity *= 2;
	int *arr = new int[capacity];
	for(int i = 0; i < count; i++) {
		arr[i] = elements[i];
	}
	delete[] elements;
	elements = arr;
}

int MyStack::peek() {
	if(isEmpty()) {
		error("Out of bound exception");
	}
	return elements[count - 1];
}

int MyStack::pop() {
	int res = peek();
	count--;
	return res;
}

