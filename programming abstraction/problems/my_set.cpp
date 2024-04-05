#include "my_set.h"


MySet::MySet() {
	root = NULL;
	elements = 0;
}

MySet::~MySet() {
	deallocate(root);
	root = NULL;
}

int MySet::size() {
	return elements;
}

bool MySet::isEmpty() {
	return elements == 0;
}

void MySet::add(string value) {
	addCell(root, value);
}

bool MySet::contains(string value) {
	return getCell(root, value) != NULL;
}

string MySet::toString() {
	string tostring = "";

	printTree(root, tostring);

	return tostring;
}

void MySet::addCell(Cell*& root, string value) {
	if(root == NULL) {
		root = new Cell;
		root->s = value;
		root->left = root->right = NULL;

		elements++;

		return;
	}

	if(root->s == value) {
		return;
	}

	if(root->s < value) {
		addCell(root->right, value);
	} else {
		addCell(root->left, value);
	}
}

MySet::Cell* MySet::getCell(Cell* current, string value) {

	while(current != NULL) {

		if(current->s == value) {
			break;
		}

		if(current->s < value) {
			current = current->right;
		} else {
			current = current->left;
		}

	}
	
	return current;
}

void MySet::printTree(Cell* current, string& tostring) {
	if (current == NULL) return;
	
	printTree(current->left, tostring);
	tostring+= current->s + " ";
	printTree(current->right, tostring);
}

void MySet::deallocate(Cell*& root) {
	if(root != NULL) {
		deallocate(root->left);
		deallocate(root->right);

		delete root;
	}
}