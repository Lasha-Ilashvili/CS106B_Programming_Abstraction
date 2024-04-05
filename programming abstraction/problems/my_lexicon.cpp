#include "my_lexicon.h"	
#include <iostream>


MyLexicon::MyLexicon() {
	root = NULL;
	elements = 0;
}

MyLexicon::~MyLexicon() {
	deallocate(root);
	root = NULL;
}

/* Returns whether the lexicon is empty. */
bool MyLexicon::isEmpty() {
	return elements == 0;
}

/* Returns the number of words in the lexicon. */
int MyLexicon::size() {
	return elements;
}

/* Adds a word to the lexicon. */
void MyLexicon::addWord(string word) {
	addCell(root, word);
	elements++;
}

/* Returns whether the given word is contained in the lexicon. */
bool MyLexicon::containsWord(string word) {
	Cell* res = find(root, word);

	return res != NULL && res->isWord;
}

/* Returns whether the given prefix is contained in the lexicon. */
bool MyLexicon::containsPrefix(string word) {
	return find(root, word) != NULL;
}

/* Removes a word from the lexicon, if it exists. */
void MyLexicon::removeWord(string word) {
	removeCell(root, word);
	elements--;
}

/* PRIVATE */

void MyLexicon::addCell(Cell*& root, string word) {
	if(root == NULL) {
		root = new Cell;
		root->isWord = false;

		for(int i = 0; i < 26; i++) {
			root->next[i] = NULL;
		}
	}

	if(word == "") {
		root->isWord = true;
		return;
	}

	addCell(root->next[word[0] - 'a'], word.substr(1));
	
}

MyLexicon::Cell* MyLexicon::find(Cell* root, string word) {
	if(root == NULL || word == "") {
		return root;
	}

	return find(root->next[word[0] - 'a'], word.substr(1));
}

void MyLexicon::removeCell(Cell*& root, string word) {
	if(root == NULL) {
		return;
	}

	if(word == "") {
		root->isWord = false;
	} else {
		removeCell(root->next[word[0] - 'a'], word.substr(1));
	}

	for(int i = 0; i < 26; i++) {
		if(root->next[i] != NULL) {
			return;
		}
	}

	delete root;
	root = NULL;
}

void MyLexicon::deallocate(Cell*& root) {
	if(root == NULL) {
		return;
	}

	for(int i = 0; i < 26; i++) {
		deallocate(root->next[i]);
	}

	delete root;
}