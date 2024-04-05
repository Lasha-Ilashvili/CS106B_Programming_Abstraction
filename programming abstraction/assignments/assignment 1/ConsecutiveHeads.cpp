/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;

int flips();

int main() {
	cout<<"It took "<<flips()<<" flips to get 3 consecutive heads."<<endl;
    return 0;
}

/*
 * This is a function that simulates flipping a coin repeatedly 
 * and continues until three consecutive heads are tossed.
 * Stores and returns number of flips.
 */
int flips() {
	int consecutiveHeads = 0, tries = 0;
	while (true) {
	  bool heads = randomChance(0.5); // one random coin flip with 50% chance of getting heads.
	  tries++; // stores number of flips
	  string result="";
	  // since bool value is either 1 or 0 we assume 1 is true
	  if (heads){
		result="heads";
		consecutiveHeads++; // adding 1 to consecutive count
	  } else {
		result="tails";
		consecutiveHeads = 0; // resets everytime coin simulation gives tails
	  }
	  cout<<result<<endl;
	  if (consecutiveHeads == 3) break; // program stops when 3 consecutive heads are tossed
	}
	return tries;
}