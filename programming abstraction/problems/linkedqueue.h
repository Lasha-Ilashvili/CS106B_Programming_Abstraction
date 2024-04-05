#ifndef _linkedqueue_h
#define _linkedqueue_h

#include "error.h"


class LinkedQueue {

struct Cell{
	int n;
	Cell* link;
};

public:
	LinkedQueue();
	~LinkedQueue();
	int size();
	bool isEmpty();
	void enqueue(int n);
	int dequeue();
	int peek();

private:
	Cell* head;
	Cell* tail;
	int cells;
	void deallocate(Cell*& head);
};

#endif