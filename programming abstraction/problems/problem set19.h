#ifndef _deque_h
#define _deque_h

template <typename T>

class Deque {
	struct Cell {
		T val;
		Cell* next;
		Cell* prev;
	};
public:
	Deque();
	~Deque();
	bool isEmpty();
	void pushFront(T value);
	void pushBack(T value);
	T popFront();
	T popBack();
private:
	Cell *head, *tail;
	void deallocate(Cell*& head);
};

#endif