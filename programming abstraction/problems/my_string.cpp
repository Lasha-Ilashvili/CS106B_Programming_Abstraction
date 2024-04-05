#include "my_string.h"


MyString::MyString() {
	head = NULL;
	size = 0;
}

MyString::~MyString() {
	deallocate(head);
	head = NULL;
}

int MyString::length() {
	return size;
}

void MyString::insert(int pos, char c) {
	int index = 0;
	Cell* current = head;
	Cell* prev = NULL;

	while(index != pos) {
		prev = current;
		current = current->next;
		index++;
	}

	Cell* temp = new Cell;
	temp->ch = c;
	temp->next = current;
	if(prev != NULL) {
		prev->next = temp;
	} else {
		head = temp;
	}

	size++;
}

char MyString::get(int indx) {
	int index = 0;
	Cell* ptr = head;

	while(index != indx) {
		ptr = ptr->next;
		index++;
	}

	return ptr->ch;

}

void MyString::set(int pos, char c) {
	int index = 0;
	Cell* ptr = head;
	while(index != pos) {
		ptr = ptr->next;
		index++;
	}
	ptr->ch = c;
}

MyString * MyString::substr(int start, int len) {
	MyString* res = new MyString();

	Cell* current = head;
	Cell* startHead = NULL;
	Cell* tail = NULL;
	
	for(int i = 0; i < size; i++) {
		if(i == start) {
			break;
		}

		current = current->next;
	}

	for(int i = 0; i < len; i++) {
		Cell* temp = new Cell;
		temp->ch = current->ch;
		temp->next = NULL;
		if(startHead == NULL) {
			startHead = temp;
			tail = temp;
		} else {
			tail->next = temp;
			tail = temp;
		}
	
		current = current->next;
	}

	res->size = len;
	res->head = startHead;
	

	return res;
}

int MyString::find(MyString * s) {
	int index = -1, currIndex = 0, sum = 0;
	Cell* ptr1 = head;
	Cell* ptr2 = s->head;
	while(true) {

		if(sum == s->size) {
			return currIndex - sum;
		}

		if(ptr1 == NULL || ptr2 == NULL) {
			break;
		}

		if(ptr1->ch == ptr2->ch) {
			sum++;
			ptr2 = ptr2->next;
		} else {
			sum = 0;
		}

		ptr1 = ptr1->next;
		currIndex++;
	}
	return index;
}

void MyString::deallocate(Cell*& head) {
	if(head != NULL) {
		deallocate(head->next);
		delete head;
	}
}
