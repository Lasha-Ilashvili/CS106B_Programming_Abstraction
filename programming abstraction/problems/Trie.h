

#ifndef _Trie_
#define _Trie_

#include "console.h"
#include <cstdlib>
using namespace std;

class Trie {

public:
	Trie();

	void add(string w);
	bool contains(string w);
	int wordsWithPrefix(string pref);
	bool remove(string w);
	int size();

private:
	struct Node {
		char ch;
		bool isWord;
		Node* letters[26];
		Node() {
			ch = ' ';
			isWord = false;
		}
	};
	
	//helper function definition example:
	//Node* helper(Node* node, string word);
	Node* root;
	int words;
	void addNode(Node*& curr, char currCh, string w);
	bool findNode(Node* curr, string w);
	Node* findPrefix(Node* curr, string w);
	void countWords(Node* curr, int& res);
	void removeNode(Node*& root, string w, bool& removed);

};

#endif

