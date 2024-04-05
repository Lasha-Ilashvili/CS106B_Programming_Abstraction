#ifndef _ll_string_h
#define _ll_string_h

#include <string>
using namespace std;

class LLstring{
	struct Cell {
		char ch;
		Cell* next;
	};

public:
	LLstring(string other = "");
	LLstring& operator= (const LLstring& other);
	~LLstring();
	string toString();
	LLstring operator+ (LLstring& other);

private:
	Cell* head, *tail;
	void LLstring::copy(Cell* node, Cell*& h, Cell*& t);
	void deallocate(Cell*& head);
};

#endif