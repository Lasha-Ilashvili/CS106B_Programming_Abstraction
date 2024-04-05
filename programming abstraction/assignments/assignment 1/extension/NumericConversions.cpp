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
int romanToInt(string s);
int convert(char ch);

/* Main program */

int main() {

	/* Just the test cases */
    cout<<stringToInt("-125135231")<<endl;
	cout<<intToString(0)<<endl;
	cout<<romanToInt("XIX")<<endl;
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

/* Converts string to int where roman numbers is written.
 * Note: program assumes passed string contains romanian number and doesn't error-check.
 */
int romanToInt(string s) {
    if(s.length()<1) return 0; // base case
	int index=0;
    char ch=s[index];
    int value=convert(ch); 

	//out of bound exception
    if(index+1==s.length()) return value;

    char nextCh=s[index+1];

	/* These conditions, considering romanian number nature, give appropriate value */
    if(ch=='I'&&(nextCh=='V'||nextCh=='X')) value=-value;
    if(ch=='X'&&(nextCh=='L'||nextCh=='C')) value=-value;
    if(ch=='C'&&(nextCh=='D'||nextCh=='M')) value=-value;

    return value + romanToInt(s.substr(1));
}

/* Justs assigns values to romanian numbers without considering any logic */
int convert(char ch){
    int sum=0;
    switch(ch){
		case 'I': sum=1; break;
		case 'V': sum=5; break;
		case 'X': sum=10; break;
		case 'L': sum=50; break;
		case 'C': sum=100; break;
		case 'D': sum=500; break;
		case 'M': sum=1000; break;
    }
    return sum;
}
