#include <iostream>
#include <string>
#include "console.h"
using namespace std;

string swapFirstWithMin(string str);
bool isInteger(string str);
int stringToInt(string str);

int main2()
{
	cout<<"DONE"<<endl;
	return 0;
}

// problem 1
string swapFirstWithMin(string str){
	int index=0;
	for(int i=1; i<str.length();i++){
		if(str[i]<str[index]){
			index=i;
		}	
	}
	char temp=str[0];
	str[0]=str[index];
	str[index]=temp;

	return str;
}

// problem 2
bool isInteger(string str){
	if(str[0]=='-'||str.find('.')!=string::npos||str[0]=='0') return false;
	for(int i=0; i<str.length(); i++){
		if(str[i]<'0'||str[i]>'9')return false;
	}
	return true;
}

int stringToInt(string str){
	if(str.length()==0) return 0;
	return stringToInt(str.substr(0,str.size()-1))*10+str[str.size()-1]-'0';
}
// problem 3
int remainderMod7(string s) {
	if (s.length() == 1)
		return (s[0] - '0') % 7;
	return (remainderMod7(s.substr(0, s.length()-1))*3+(s[s.length()-1] - '0')) % 7;
}

