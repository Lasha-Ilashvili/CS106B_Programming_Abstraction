#include <iostream>
#include <string>
#include "console.h"
#include "vector.h"
using namespace std;

Vector<string> perm(string& s);
void betterPerm(string s);
void doPerms(string& s, string& soFar);

int main()
{
	string s="laek";
	cout<<perm(s)<<endl;
	//betterPerm(s);
	return 0;
}

Vector<string> perm(string& s){
	Vector<string> res;
	if(s.empty()){
		return res+="";
	}
	for(int i=0; i<s.length(); i++){
		string copy=s;
		Vector<string> withoutChar=perm(copy.erase(i,1));
		foreach(string c in withoutChar){
			res+= (c+s[i]);
		}
	}
	return res;
}

void betterPerm(string s){
	string soFar="";
	doPerms(s,soFar);
	cout<<endl;
}

void doPerms(string& s, string& soFar){
	if(s.empty()){
		cout<<soFar<<" ";
	} else {
		for(int i=0; i<s.length(); i++){
			string copy=s;
			doPerms(copy.erase(i,1), soFar+copy[i]);
		}
	}
}
