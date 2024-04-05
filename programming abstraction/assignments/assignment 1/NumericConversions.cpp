/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {

	/* Just the test cases */
    cout<<stringToInt("-125135231")<<endl;
	cout<<intToString(0)<<endl;

    return 0;
}

/* This function converts integer to string */
string intToString(int n){
	char lastDigit=char(n%10+'0'); 
	if(n/10==0){ // just before recursion, program checks whether n is 0 or will be 0 after division
		return string("")+lastDigit;
	}
	return intToString(n/10)+lastDigit;
}

/* This function converts string to integer */
int stringToInt(string str){
	int sign=1; // sign of final result, + or -
	//
	if(str.length()==0) return 0; // base case
	if(str[0]=='-'){ // checks if number in the string has negative sign and acts accordingly
		sign=-1;
		str=str.substr(1,str.length());
	}
	int last=str.length()-1;
	/* Conversion */
	int result=stringToInt(str.substr(0,last))*10 + str[last]-'0';
	return sign*result;
}
