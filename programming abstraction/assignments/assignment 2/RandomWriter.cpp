/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "hashmap.h"
#include "vector.h"
#include "random.h"
using namespace std;

const int NUMBER_OF_REPS = 2000;

/* Function prototypes */
int getOrder(string text, int lower, int upper);
void readAndFillUp(Vector<char>& allChars, istream& source);
void storeSeeds(Vector<char>& allChars, HashMap<string, Vector<char>>& data, HashMap<string, int>& seeds, int seedLength);
string randomOutput(HashMap<string, Vector<char>>& data, HashMap<string, int>& seeds, int num);
string getMostCommonSeed(HashMap<string, int>& seeds);

int main() {
	/* File opening */
	ifstream source;
	promptUserForFile(source,"Enter the source text: ");
	
	/* Getting the Markov order */
	int seedLength=getOrder("Enter the Markov order [1-10]: ",1,10);

	cout<<"Processing file..."<<endl;
	
	/* Setting up data structures */
	HashMap<string, Vector<char>> data; // Stores every following characters for individual seeds 
	HashMap<string, int> seeds; // Is used to determine which seed has the most occurrence
	Vector<char> allChars; // Stores all characters from the given file

	/* Reading */
	readAndFillUp(allChars, source);
	
	/* Storing */
	storeSeeds(allChars, data, seeds, seedLength);
	
	/* Printing ramdom text */
	cout<<randomOutput(data, seeds, NUMBER_OF_REPS)<<endl;

    return 0;
}

/* This function returns user's input if it's in range of given borders*/
int getOrder(string text, int lower, int upper){
	int input=0;
	while(true){	
		input=getInteger(text);
		if(input>=lower && input<=upper){
			break;
		}
	}
	return input;
}

/* For convenience, program stores all characters in the vector */
void readAndFillUp(Vector<char>& allChars, istream& source){
	char ch;
	while(source.get(ch)){
		allChars+=ch;
	}
}

/* This function uses Vector of characters
 * To form seeds, store them with following chars in one hashmap
 * and count them in another hashmap
 */
void storeSeeds(Vector<char>& allChars, HashMap<string, Vector<char>>& data, HashMap<string, int>& seeds, int seedLength){
	for(int i=0; i<allChars.size(); i++){
		int lastIndex = i+seedLength;

		if(lastIndex<allChars.size()){
			string seed="";

			for(int j=i; j<lastIndex; j++){
				seed+=allChars[j];
			}

			char nextCh=allChars[lastIndex];
			data[seed]+=nextCh;
			
			seeds[seed]++;
		}
	}
}

/* Function returns random output aka final result */
string randomOutput(HashMap<string, Vector<char>>& data, HashMap<string, int>& seeds, int num){
	string seed = getMostCommonSeed(seeds);
	string res = seed;

	for(int i=0; i<num; i++){
		Vector<char> chars=data[seed];
		if(!chars.isEmpty()){
			int randomIndex = randomInteger(0, chars.size()-1);
			res+=chars[randomIndex];
		} else {
			break;
		}
		/* Seed value is changed on every iteration */
		seed=res.substr(i+1);
	}

	return res;
}

/* Function returns the most frequent seed as a starter */
string getMostCommonSeed(HashMap<string, int>& seeds){
	string res="";
	int max=0;
	foreach(string seed in seeds){
		if(seeds[seed]>=max){
			max=seeds[seed];
			res=seed;
		}
	}
	return res;
}