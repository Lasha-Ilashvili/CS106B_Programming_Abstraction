
#include "Trie.h"

Trie::Trie() {
	root = NULL;
	words = 0;
}

//helper funqction syntax when it returns structure defined inside the class
//Trie::Node* Trie::helper(Node* node, string word);

void Trie::add(string w) {
	addNode(root, '0', w);
}

bool Trie::contains(string w) {
	return findNode(root, w);
}

int Trie::wordsWithPrefix(string pref) {
	if(pref == "") {
		return words;
	}
	Node* endPrefix = findPrefix(root, pref);

	if(!endPrefix) {
		return 0;
	}
	
	int res = endPrefix->isWord? 1 : 0;
	for(int i = 0; i < 26; i++) {
		countWords(endPrefix->letters[i], res);
	}

	return res;
}

bool Trie::remove(string w) {
	bool removed = false;
	removeNode(root, w, removed);
	words = removed? words - 1 : words;
	return removed;
}

int Trie::size() {
	return words;
}

/* PRIVATE */

void Trie::addNode(Node*& curr, char currCh, string w) {
	if(!curr) {
		curr = new Node;
		curr->ch = currCh;
		for(int i = 0; i < 26; i++) {
			curr->letters[i] = NULL;
		}
	}
	if(w.empty()) {
		words = curr->isWord? words : words + 1;
		curr->isWord = true;
		return;
	}

	char newCurr = w[0];
	addNode(curr->letters[newCurr - 'a'], newCurr, w.substr(1));
}

bool Trie::findNode(Node* curr, string w) {
	if(!curr) {
		return false;
	}
	if(w.empty()) {
		return curr->isWord;
	}

	return findNode(curr->letters[w[0] - 'a'], w.substr(1));
}

Trie::Node* Trie::findPrefix(Node* curr, string w) {
	if(!curr) {
		return NULL;
	}
	if(w.empty()) {
		return curr;
	}

	return findPrefix(curr->letters[w[0] - 'a'], w.substr(1));
}

void Trie::countWords(Node* curr, int& res) {
	if(!curr) {
		return;
	}
	if(curr->isWord) {
		res++;
	}
	
	for(int i = 0; i < 26; i++) {
		countWords(curr->letters[i], res);
	}	
}

void Trie::removeNode(Node*& curr, string w, bool& removed) {
	if(!curr) {
		removed = false;
		return;
	}
	if(w.empty()) {
		if(curr->isWord) {
			curr->isWord = false;
			removed = true;
			return;
		}
		removed = false;
		return;
	}

	removeNode(curr->letters[w[0] - 'a'], w.substr(1), removed);

	if(removed) {
		for(int i = 0; i < 26; i++) {
			curr->letters[i] != NULL;
			return;
		}
		delete curr;
		curr = NULL;
	}
}
