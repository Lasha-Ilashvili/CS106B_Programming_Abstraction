#ifndef _my_hashmap_h
#define _my_hashmap_h

#include <string>
using namespace std;

class MyHashMap {
	
	struct Cell {
		string key;
		int value;
		Cell *next;
	};

public:
	MyHashMap();
	~MyHashMap();
	
	void put(string key, int value);
	bool containsKey(string key);
	int get(string key);
	
	int size();
	bool isEmpty();

private:
	Cell **buckets;
	int numBuckets;
	int numElems;

	Cell* findCell(string key);
	void increaseBuckets();
	void deallocate(Cell*& head);
};

#endif