#ifndef MY_STRING_INCL
#define MY_STRING_INCL
#include <cstdio>

using namespace std;

class MyString {
	

	public:
		MyString();
		~MyString();
		int length();
		void insert(int pos, char c);
		char get(int pos);
		void set(int pos, char c);
		MyString * substr(int start, int len);
		int find(MyString * s);

	private:
		struct Cell {
		char ch;
		Cell* next;
	};
		Cell* head;
		int size;
		void deallocate(Cell*& head);
};
#endif