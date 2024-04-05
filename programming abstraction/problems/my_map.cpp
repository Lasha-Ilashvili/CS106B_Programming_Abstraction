#include "my_map.h"


MyMap::MyMap() {
	root = NULL;
	elements = 0;
}

MyMap::~MyMap() {
	deallocate(root);
	root = NULL;
}
	
void MyMap::put(string key, int value) {
	addCell(root, key, value);
}

int MyMap::get(string key) {
	return getCell(root, key)->value;
}

bool MyMap::containsKey(string key) {
	return getCell(root, key) != NULL;
}

int MyMap::size() {
	return elements;
}

bool MyMap::isEmpty() {
	return elements == 0;
}

string MyMap::toString() {
	string tostring = "";

	printTree(root, tostring);

	return tostring;
}

/* Private */

void MyMap::addCell(Cell*& root, string key, int value) {
	if(root == NULL) {
		root = new Cell;
		root->key = key;
		root->value = value;
		root->left = root->right = NULL;

		elements++;
		return;
	}

	if(root->key == key) {
		root->value = value;
		return;
	}

	if(root->key < key) {
		addCell(root->right, key, value);
	} else {
		addCell(root->left, key, value);
	}
}

MyMap::Cell* MyMap::getCell(Cell* current, string key) {
	if(current == NULL) {
		return NULL;
	}

	if(current->key == key) {
		return current;
	}

	if(current->key < key) {
		return getCell(current->right, key);
	}

	return getCell(current->left, key);
}

void MyMap::printTree(Cell* current, string& tostring) {
	if(current != NULL) {
		printTree(current->left, tostring);

		tostring+= " [" + current->key + " : " + integerToString(current->value) + "] ";

		printTree(current->right, tostring);
	}
}

void MyMap::deallocate(Cell*& root) {
	if(root != NULL) {
		deallocate(root->left);
		deallocate(root->right);

		delete root;
	}
}