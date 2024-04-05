#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "console.h"
#include "tokenscanner.h"
#include "stack.h"
#include "vector.h"
using namespace std;

void reverseFile();
void writeInOrderFile();
void countLatinLetters();

int main4()
{
	cout<<"DONE"<<endl;
	return 0;
}

// problem 1
void reverseFile(){
	ifstream reader("RosesAreRed.txt");

	TokenScanner scanner(reader);
	scanner.ignoreWhitespace();
	
	Stack<string> s;

	while(scanner.hasMoreTokens()){
		s.push(scanner.nextToken());
	}

	reader.close();

	ofstream writer("test1.txt");
	while(!s.isEmpty()){
		writer<<s.pop()<<" ";
	}
	writer<<endl;
	writer.close();
	
}
void writeInOrderFile(){
	ifstream reader("RosesAreRed.txt");

	TokenScanner scanner(reader);
	scanner.ignoreWhitespace();
	
	Vector<string> v;

	while(scanner.hasMoreTokens()){
		v.add(scanner.nextToken());
	}

	reader.close();

	ofstream writer("test1.txt");
	for(int i=0; i<v.size(); i++){
		if(i%2!=0) writer<<v.get(i)<<" ";
	}
	writer<<endl;
	for(int i=0; i<v.size(); i++){
		if(i%2==0) writer<<v.get(i)<<" ";
	}
	writer<<endl;
	writer.close();
}
// problem 2
void countLatinLetters(){
	ifstream reader("RosesAreRed.txt");
	Vector<int> v(26);

	char ch;
	while (reader.get(ch)){
		tolower(ch);
		if(ch>='a'&&ch<='z'){
			v[ch-'a']++;
		}
	}
	reader.close();

	for(int i=0; i<26; i++){
		cout<<"Letter \""<<char(i+'a')<<"\" is used "<<v[i]<<" time(s)."<<endl;
	}
}