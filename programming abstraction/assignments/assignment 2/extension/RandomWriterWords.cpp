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
void readAndFillUp(Vector<string>& allWords, istream& source);
void storeSeeds(Vector<string>& allWords, HashMap<string, Vector<string>>& data, HashMap<string, int>& seeds, int seedLength);
string randomOutput(HashMap<string, Vector<string>>& data, HashMap<string, int>& seeds, int num);
string getMostCommonSeed(HashMap<string, int>& seeds);

int main() {
	/* File opening */
	ifstream source;
	promptUserForFile(source,"Enter the source text: ");
	
	/* Getting the Markov order */
	int seedLength=getOrder("Enter the Markov order [1-10]: ",1,10);

	cout<<"Processing file..."<<endl;
	
	/* Setting up data structures */
	HashMap<string, Vector<string>> data; // Stores every following words for individual seeds 
	HashMap<string, int> seeds; // Is used to determine which seed has the most occurrence
	Vector<string> allWords; // Stores all words from the given file

	/* Reading */
	readAndFillUp(allWords, source);
	
	/* Storing */
	storeSeeds(allWords, data, seeds, seedLength);
	
	/* Printing ramdom text */
	cout<<randomOutput(data, seeds, NUMBER_OF_REPS)<<endl;

    return 0;
}


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


void readAndFillUp(Vector<string>& allWords, istream& source){
	string word;
	while(source>>word){
		allWords+=word;
	}
}


void storeSeeds(Vector<string>& allWords, HashMap<string, Vector<string>>& data, HashMap<string, int>& seeds, int seedLength){
	for(int i=0; i<allWords.size(); i++){
		int lastIndex = i+seedLength;

		if(lastIndex<allWords.size()){
			string seed="";

			for(int j=i; j<lastIndex; j++){
				seed+=allWords[j];
				seed+=" ";
			}

			data[seed]+=allWords[lastIndex];
			
			seeds[seed]++;
		}
	}
}


string randomOutput(HashMap<string, Vector<string>>& data, HashMap<string, int>& seeds, int num){
	string seed = getMostCommonSeed(seeds);
	string res = seed;

	for(int i=0; i<num; i++){
		if(!data[seed].isEmpty()){
			int randomIndex = randomInteger(0, data[seed].size()-1);
			res+=data[seed][randomIndex];
		} else {
			break;
		}
		/* Seed value is changed on every iteration */
		seed=res.substr(i+1);
	}

	return res;
}


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