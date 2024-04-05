#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

struct Cell {
	int n;
	Cell* next;
};

Cell* fillList();
void traverse(Cell* first);

int main13()
{
	Cell* first = fillList();

	traverse(first);

	return 0;
}

Cell* fillList() {
	Cell* res = NULL;
	Cell* tail = NULL;

	while(true) {
		int input = getInteger("? ");

		if(input == -1) {
			break;
		}

		Cell* temp = new Cell;
		temp->n = input;
		temp->next = NULL;

        if (res == NULL) {
            res = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
	}

	return res;
}

void traverse(Cell* first) {
	if(first!=NULL) {
		cout<<first->n<<endl;
		traverse(first->next);
	}
}
