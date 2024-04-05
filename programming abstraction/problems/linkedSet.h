#ifndef _linkedset_h
#define _linkedset_h

#include <string>

using namespace std;


class LinkedSet {
	struct Cell {
		int n;
		Cell* next;
	};
public:	
	LinkedSet();
	void add(int k);
	bool contains(int k);
	int size();
	void remove(int k);
	void resetIterator();
	bool hasNext();
	int next();
private:
	Cell* head, *current;
	int elements;
};

#endif