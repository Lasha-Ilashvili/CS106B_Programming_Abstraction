#include "myqueue.h"

int MyQueue::size() {
	return in.size() + out.size();
}

bool MyQueue::isEmpty() {
	return size() == 0;
}

void MyQueue::enqueue(int n) {
	in.push(n);
}

int MyQueue::peek() {
	if(out.isEmpty()) {
		copy();
	}
	return out.peek();
}

int MyQueue::dequeue() {
	int result = peek();
	out.pop();
	return result;
}



void MyQueue::copy() {
	while(!in.isEmpty()) {
		out.push(in.pop());
	}
}