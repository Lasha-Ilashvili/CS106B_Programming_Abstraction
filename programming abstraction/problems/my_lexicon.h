#ifndef _my_lexicon_h
#define _my_lexicon_h

#include <string>
using namespace std;

const int ENGLISH_ALPHABET = 26;
class MyLexicon {
	struct Cell {
		bool isWord;
		Cell* next[ENGLISH_ALPHABET];
	};

public:
	MyLexicon();
	~MyLexicon();
	
	/* Returns whether the lexicon is empty. */
	bool isEmpty();
	
	/* Returns the number of words in the lexicon. */
	int size();
	
	/* Adds a word to the lexicon. */
	void addWord(string word);
	
	/* Returns whether the given word is contained in the lexicon. */
	bool containsWord(string word);
	
	/* Returns whether the given prefix is contained in the lexicon. */
	bool containsPrefix(string word);
	
	/* Removes a word from the lexicon, if it exists. */
	void removeWord(string word);

private:
	Cell* root;
	int elements;

	void addCell(Cell*& root, string word);
	Cell* find(Cell* root, string word);
	void removeCell(Cell*& root, string word);
	void deallocate(Cell*& root);
};

#endif