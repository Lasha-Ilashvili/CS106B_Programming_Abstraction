#ifndef _my_map_h
#define _my_map_h

#include <string>
#include "strlib.h"
using namespace std;

class MyMap {
	struct Cell {
		string key;
		int value;
		Cell* left;
		Cell* right;
	};

public:
	MyMap();
	~MyMap();
	
	void put(string key, int value);
	int get(string key);
	bool containsKey(string key);

	int size();
	bool isEmpty();
	string toString();

private:
	Cell* root;
	int elements;

	void deallocate(Cell*& root);
	void addCell(Cell*& root, string key, int value);
	Cell* getCell(Cell* current, string key);
	void printTree(Cell* current, string& tostring);
};

#endif