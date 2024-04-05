/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
	string text = getLine("Enter a text: ");
	string subsequence = getLine("Enter a subsequence of a text: ");
	cout<<isSubsequence(text,subsequence)<<endl;

	// just an example
	cout<<isSubsequence("bakobakb", "kab")<<endl; // true
	cout<<isSubsequence("bakobak", "kab")<<endl; //  false
    return 0;
}

/* This function takes strings text and subsequence, 
 * Recursively checks if subsequence appear in text in the same order, 
 * But not necessarily consecutively and returns boolean 
 */
bool isSubsequence(string text, string subsequence){

	if(subsequence.empty()){
		return true;
	} else if(text.empty()){ //text is empty, but subsequence is not, returns false
		return false;
	}

	/* Removes character from subsequence if it matches text character */
	if(text[0]==subsequence[0]){
		return isSubsequence(text.substr(1), subsequence.substr(1));
	} else { /* Else subsequence is left unchanged */
		return isSubsequence(text.substr(1), subsequence);
	}
}
