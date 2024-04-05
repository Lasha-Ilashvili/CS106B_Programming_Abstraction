/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "vector.h"
#include "simpio.h"
using namespace std;

void wordLadder(Lexicon lex, Lexicon used,string startWord, string destination);
string getInput(string message);
Vector<string> getLadder(Queue<Vector<string>>& q, string destination,Lexicon lex, Lexicon used);
string replaceChar(int i, string current, char letter);
string printVector(Vector<string> ladder);

int main() {
	Lexicon lex("EnglishWords.dat");
	Lexicon used;
	
	while(true){
		string startWord=getLine("Enter the starting word (or nothing to quit): ");

		if(startWord=="") {
			break;
		} else {
			string destination=getLine("Enter the ending word: ");
			cout<<"Searching..."<<endl;
			wordLadder(lex,used,startWord,destination);
		}
	}

	cout<<"Goodbye!"<<endl;
    return 0;
}

/* This function finds a word ladder */
void wordLadder(Lexicon lex, Lexicon used, string startWord, string destination){
	Queue<Vector<string>> q;
	Vector<string> ladder;
	
	
	ladder+=startWord;
	q.enqueue(ladder);

	ladder=getLadder(q,destination,lex,used);
	
	if(!ladder.isEmpty()){
		cout<<"Ladder found: "<<printVector(ladder)<<endl;
		cout<<endl;
	} else {
		cout<<"No word ladder could be found."<<endl;
		cout<<endl;
	}
}

/* Using breadth-first search algorithm, function returns ladder */
Vector<string> getLadder(Queue<Vector<string>>& q, string destination, Lexicon lex, Lexicon used){
	Vector<string> currentV;
	while (!q.isEmpty()) {
		if(!lex.contains(destination)) break;
		currentV = q.dequeue();
		string current=currentV.get(currentV.size()-1);

		// this function takes current word, compares it to the destination word and returns ladder
		if (current == destination) return currentV;

		for(int i=0; i<current.length(); i++){
			for(char ch='a'; ch<='z'; ch++){
				string word = replaceChar(i, current, ch);
				if(!used.contains(word) && lex.contains(word)){
					used.add(word);
					Vector<string> currentCopy=currentV;
					currentCopy+=word;
					q.enqueue(currentCopy);
				}
			}
		}
	}
	currentV.clear();
	return currentV;
}

string replaceChar(const int i, string current, const char letter){
	current[i]=letter;
	return current;
}

/* Same as toString() method, but instead of commas " ->" are used */
string printVector(Vector<string> ladder){
	string toString="";
	for(int i=0; i<ladder.size(); i++){
		toString+=ladder[i];
		if(i<ladder.size()-1){
			toString+=" -> ";
		}
	}
	return toString;
}
