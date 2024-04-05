/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "console.h"
#include "filelib.h"
#include "tokenscanner.h"
#include "string.h"
using namespace std;

/* Constants for FleschKincaid formula */
const double C0 = -15.59; 
const double C1 = 0.39;
const double C2 = 11.8;

/* Structure which stores variables as a data from the file */
struct DocumentInfo {
 int words;
 int syllables;
 int sentences;
 double grade;
};

/* Function declarations */
DocumentInfo getGrade(TokenScanner scanner, double C0, double C1, double C2);
void setUpScan(TokenScanner& scanner);
/* returns character on the specified index */
char index(string token, int end){return token[token.length()-end];}
int  vowels(string token);
bool isVowel(int ch);
void countSentences(string token, int& sentences);
void countEndings(char ch, int& sentences);
/* consideres edge cases(if either sentence, syllable or word counter is equal to zero) */
void edgeCase(int& sum){if(sum==0) sum=1;}

int main() 
{
	/* File opening and reading */
	ifstream reader;
	promptUserForFile(reader,"Enter input file name: ");
	
	/* setting up a TokenScanner type variable */
	TokenScanner scanner(reader);
	setUpScan(scanner);

   /* Getting all the necessary data form the file 
	* Passing constant values for better programming style */
	DocumentInfo info=getGrade(scanner, C0, C1, C2);
	
	/* Closing file reader */
	reader.close();

	/* Printing results */
	cout<<"Words: "<<info.words<<endl;
	cout<<"Syllables: "<<info.syllables<<endl;
	cout<<"Sentences: "<<info.sentences<<endl;
	cout<<"Grade level: "<<info.grade<<endl;

    return 0;
}

/* 
 * This function collects all the data needed for FleschKincaid formula
 * After that, computes and returns the grade
 */
DocumentInfo getGrade(TokenScanner scanner, double C0, double C1, double C2){
	/* Initializes values to 0 */
	DocumentInfo info={0,0,0};

	/* Loop to iterate through the file with TokenScanner */
	while(scanner.hasMoreTokens()){
		/* Converts string's characters to lowercase(only lowercase letters are checked throughout the program) */
		string token=toLowerCase(scanner.nextToken());
		
		/* Checks token's first letter. Only alphabetical characters (or words starting with " ) are allowed */
		if(isalpha(token[0])||token[0]=='"'){
			/* Counts words */
			info.words++;
			/* Counts syllables */
			info.syllables+=vowels(token);
		}
		/* Counts sentences */
		countSentences(token, info.sentences);
	}
	
	/* Edge cases */
	edgeCase(info.words);
	edgeCase(info.sentences);
	
	/* Computing grade and returning data */
	info.grade=C0+C1*(info.words/double(info.sentences))+C2*(info.syllables/double(info.words));

	return info;
}

/* Sets up a scanner to ignore whitespaces and adds characters which will not be considered as a delimiter */
void setUpScan(TokenScanner& scanner){
	scanner.ignoreWhitespace();
	/* Note: Because punctuations listed below aren't separated from the words(as handout suggested),
	 * word1-word2 and word1--word2 are treated as a single words.
	 * This is my subjective decision since no instructions on how to treat those cases were given whatsoever:).
	 */
	scanner.addWordCharacters("\'.,!?;_-\"()");
}

/* Function which counts vowels(specifically for counting syllables) */
int vowels(string token){
	int vows=0;
	/* Loop iterates through string.*/
	for(int i=0; i<token.length(); i++){
		/* Initializing two char type variables, current and previous */
		char ch= token[i], prevChar=' ';
		if(i!=0) prevChar= token[i-1];
		/* This statement makes sure that previous character wasn't a vowel */
		if(!isVowel(prevChar) && prevChar!='e'){
			/* If current char is vowel and 'e' isn't a last letter in a word, 1 is added to counter */
			if(ch=='e' && (i!=token.length()-1 && isalpha(token[i+1]))||isVowel(ch)) vows++;
		
		}
	}
	edgeCase(vows);

	return vows;
}

/* Function checks if given character is a vowel or not(except for the letter 'e', which is checked separately) */
bool isVowel(int ch){
	switch(ch){
		case 'a': case 'i': case 'o': case 'u': case 'y':
			return true;
	}
	return false;
}

/* Counts Sentences.  Note: character ';' is treated as an end of the sentence.
 * Also, i decided that sentences without punctuation symbols at the end doesn't count 
 * (no specifications were given here either).
 */
void countSentences(string token, int& sentences){
	/* Setting up last two characters variables in a string. For cases(word. and "word.") */
	char last=index(token,1), prev=' ';
	if(token.length()>1) prev=index(token,2);
	/* Checking both char values */
	countEndings(last, sentences);
	if(last!=prev && last!=' ') countEndings(prev, sentences);
}

/* This function is self-explanatory, adds 1 to int if ending is one og the specified punctuation marks */
void countEndings(char ch, int& sentences) {
	switch (ch){
		case '?': case '.': case '!': case ';':
			sentences++;
			break;
	}
}