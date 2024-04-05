#ifndef _my_set_h
#define _my_set_h

#include <string>
using namespace std;

class MySet{
	struct Cell {
		string s;
		Cell* left;
		Cell* right;
	};

public:
	MySet();
	~MySet();

	int size();
	bool isEmpty();
	void add(string value);
	bool contains(string value);
	string toString();

private:
	Cell* root;
	int elements;

	void addCell(Cell*& root, string value);
	Cell* getCell(Cell* current, string value);
	void printTree(Cell* current, string& tostring);
	void deallocate(Cell*& root);
};

#endif