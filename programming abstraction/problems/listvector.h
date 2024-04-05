
#ifndef ListVector_Included
#define ListVector_Included

#include "console.h"
#include "error.h"
#include <cstdlib>
using namespace std;

class ListVector {
	struct Cell{
		int n;
		Cell* next;
	};

	public:
		ListVector();
		int size();
		void add(int val);
		int get(int i);
		void insert(int i, int val);
		void remove(int i);

	private:
		Cell* head, *tail;
		int length;
};

#endif;