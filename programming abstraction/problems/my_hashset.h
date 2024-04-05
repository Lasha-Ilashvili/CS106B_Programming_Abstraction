#ifndef _my_hashset_h
#define _my_hashset_h

#include <string>
using namespace std;

class MyHashSet {
	struct Cell{
		string s;
		Cell* next;
	};
public:
	MyHashSet();
	~MyHashSet();

	int size();
	bool isEmpty();
	void add(string value);
	bool contains(string value);

private:
	Cell** buckets;
	int numBuckets;
	int elements;

	Cell* findCell(string value);
	void increaseBuckets();
	void deallocate(Cell*& head);
};

#endif