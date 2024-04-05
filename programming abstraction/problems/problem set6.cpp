#include <iostream>
#include <fstream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "set.h"
#include "map.h"
#include "strlib.h"
using namespace std;

void twoStrings(string str1, string str2);
void fillSet(Set<char>& set, string str){foreach(char ch in toLowerCase(str)) set.add(ch);}
void countRepetitiveWords();
bool fourOperationStrings(string str1, string str2);
void combinationsOfString(Set<string>& set, string str);
string swap(string s, int start, int end);

int main6()
{
	cout<<"DONE"<<endl;
	return 0;
}

// problem 1
void twoStrings(string str1, string str2){
	Set<char> set1, set2;
	fillSet(set1, str1);
	fillSet(set2, str2);
	cout<<"Intersection of letters: "<<set1*set2<<endl;
	cout<<"Letters that are only presented in the first word: "<<set1-set2<<endl;
	cout<<"Letters that are only presented in the second word: "<<set2-set1<<endl;
}


// problem 2
void countRepetitiveWords(){
	Map<string,int> map;
	ifstream reader("RosesAreRed.txt");
	string word;
	while(reader>>word){
		map[word]++;
	}
	reader.close();
	cout<<map<<endl;
}
// problem 3
bool fourOperationStrings(string str1, string str2){
	Set<string> set1;
	Set<string> set2;
	combinationsOfString(set1, str1);
	combinationsOfString(set2, str2);
	return !(set1*set2).isEmpty();
}

void combinationsOfString(Set<string>& set, string str){
	for(int i=0; i<str.length(); i++){
		for(int j=i; j<=i+2; j++){
			if(j<str.length())
				set.add(swap(str, i, j));
		}	
	}
}

string swap(string s, int start, int end){
	char temp = s[start];
	s[start] = s[end];
	s[end] = temp;
	return s;
}