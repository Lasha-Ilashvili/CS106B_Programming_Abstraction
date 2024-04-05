#include "problem set20.h"
#include "error.h"


LLstring::LLstring(string other) {
	head = NULL;
	tail = NULL;

	for(int i = 0; i < other.length(); i++) {
		Cell* temp = new Cell;
		temp->ch = other[i];
		temp->next = NULL;

		if(head == NULL) {
			head = temp;
			tail = temp;
		} else {
			tail->next = temp;
			tail = temp;
		}
	}

}

LLstring& LLstring::operator= (const LLstring& other) {
	if(this != &other) {
		deallocate(head);
		head = NULL;
        tail = NULL;

		copy(other.head, head, tail);
	}
	return *this;
}

LLstring::~LLstring() {
	deallocate(head);
	head = NULL;
	tail = NULL;
}

string LLstring::toString() {
	string res = "";
	for(Cell* ptr = head; ptr != NULL; ptr = ptr->next) {
		res += ptr->ch;
	}
	return res;
}

LLstring LLstring::operator+ (LLstring& other) {
	LLstring* res = new LLstring();

	copy(head, res->head, res->tail);

	copy(other.head, res->head, res->tail);

	return *res;
}

void LLstring::copy(Cell* node, Cell*& h, Cell*& t) {
	if(node == NULL) {
		return;
	}
	//for(Cell* ptr = node; ptr != NULL; ptr = ptr->next) {
		Cell* temp = new Cell;
		temp->ch = node->ch; // node or ptr
		temp->next = NULL;
		if(h == NULL) {
			h = temp;
			t = temp;
		} else {
			t->next = temp;
			t = temp;
		}
	//}
	copy(node->next, h, t);
}

void LLstring::deallocate(Cell*& head) {
	if(head != NULL) {
		deallocate(head->next);
		delete head;
	}
}