#include <iostream>
#include "console.h"
#include "set.h"
#include "vector.h"
using namespace std;

Vector<Set<int>> subSets(Set<int> set);
void betterSubSets(Set<int> soFar, Set<int> remaining);

int main()
{
	Set<int> set;
	set+=1,2,3;
	cout<<subSets(set)<<endl;

	//Set<int> soFar;
	//betterSubSets(soFar,set);
	return 0;
}

Vector<Set<int>> subSets(Set<int> set){
	Vector<Set<int>> res;
	if(set.isEmpty()){
		Set<int> empty;
		res+=empty;
		return res;
	}
	int x = set.first();
	Vector<Set<int>> withoutX = subSets(set-x);
	res=withoutX;
	foreach(Set<int> copy in withoutX){
		res+=(copy+x);
	}
	return res;
}

void betterSubSets(Set<int> soFar, Set<int> remaining){
	if(remaining.isEmpty()){
		cout<<soFar<<endl;
	} else {
		int x = remaining.first();
		betterSubSets(soFar+x, remaining-x);
		betterSubSets(soFar, remaining-x);
	}
}