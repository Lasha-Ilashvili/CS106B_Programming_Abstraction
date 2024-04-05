#include <iostream>
#include <cmath>
#include "console.h"
#include "vector.h"
using namespace std;

int findMin(Vector<int>& vec);
bool canComposeWith(int value, Vector<int>& units);
bool isTargetSum(Vector<int>& set, int target);

int main8()
{
	Vector<int> set;
	set+=2,4,8;
	cout<<isTargetSum(set, 14)<<endl;
	return 0;
}

// problem 1
int findMin(Vector<int>& vec){
	if(vec.size()==1){
		return vec[vec.size()-1];
	}
	int last = vec.size()-1;
	int x = vec[last];
	vec.remove(last);
	return min(x, findMin(vec));
}

// problem 2
bool canComposeWith(int value, Vector<int>& units){
	if(value==0){
		return true;
	} else if(value<0){
		return false;
	}
	bool res=false;
	for(int i=0; i<units.size(); i++){
		if(!res){
			res = res || canComposeWith(value-units[i], units);
		}
	}
	return res;
}

// problem 3
bool isTargetSum(Vector<int>& set, int target){
	if(set.isEmpty()){
		return target==0;
	}

	int last = set[set.size()-1];
	set.remove(set.size()-1);
	
	bool op1 = isTargetSum(set,target-last);
	bool op2 = false;
	if(!op1){
		op2 = isTargetSum(set,target);
	}
	set+=last;

	return op1 || op2;
}

