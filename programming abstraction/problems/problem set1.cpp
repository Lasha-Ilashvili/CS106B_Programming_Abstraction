#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

const int SENTINEL=-1;

void getMaxMinAndAverage();
void readInput(int& max, int& min, double& average);
bool isPowerOfTwo(int n);
void readTwoNonNegativeNums();
int gcd(int a, int b);

int main1()
{
	cout<<"DONE"<<endl;
	return 0;
}

//problem 1
void getMaxMinAndAverage(){
	int max=INT_MIN, min=INT_MAX;
	double average=0.0;
	readInput(max,min,average);
	cout<<"Max numbers is: "<<max<<endl;
	cout<<"Min numbers is: "<<min<<endl;
	cout<<"Average numbers is: "<<average<<endl;
}

void readInput(int& max, int& min, double& average){
	cout<<"Enter "<<SENTINEL<<" to see the results"<<endl;
	int sum=0;
	while(true){
		int input= getInteger("Enter a number: ");
		if(input==SENTINEL)break;
		if(input<min)min=input;
		if(input>max)max=input;
		sum++;
		average+=input;
	}
	average/=sum;
}
// problem 2
bool isPowerOfTwo(int n){
	if(n%2!=0) return n==1;
	return isPowerOfTwo(n/2);
}

// problem 3
void readTwoNonNegativeNums(){
	int a=getInteger("Enter first num: ");
	int b=getInteger("Enter second num: ");
	if(a>0&&b>0) cout<<gcd(a,b)<<endl;
}

int gcd(int a, int b){
	if(b==0) return a;
	return gcd(b,a%b);
}