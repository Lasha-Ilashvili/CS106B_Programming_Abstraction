#ifndef _myqueue_h
#define _myqueue_h

#include "mystack.h"

class MyQueue {
public:
	int size();
	bool isEmpty();
	void enqueue(int n);
	int dequeue();
	int peek();
private:
	MyStack in, out;
	void copy();
};

#endif