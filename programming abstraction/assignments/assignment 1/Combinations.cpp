/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
using namespace std;

int c(int n, int k);

int main() {
	/* Just a test case */
	cout<<c(7,4)<<endl;
	return 0;
}

/* Function starts from the bottom(vertical and horizonal index is passed as a parameter)
 * And builts its own way to the very top. 
 * If index is either vertically less than 2 or horizontally is an edge(beginning or the end)
 * Function returns 1 - that's the base case for this recursion.
 */
int c(int n, int k){
	if(n<2||(k==0||k==n)) return 1;
	return c(n-1,k-1)+c(n-1,k);
}

