#include <iostream>
#include <cctype>
#include "console.h"
#include "simpio.h"
#include "stack.h"
using namespace std;

const int SENTINEL=-1;

void reverse();
int evaluateExpression(string expression);
pair<int,int> fib(int num);

int main3()
{
	cout<<"DONE"<<endl;
	return 0;
}

// problem 1
void reverse(){
	Stack<int> stack;
	cout<<"Enter "<<SENTINEL<<" to get results."<<endl;
	while(true){
		int n=getInteger("Enter a number: ");
		if(n==SENTINEL) break;
		stack.push(n);
	}
	while(!stack.isEmpty()){
		cout<<stack.pop()<<" ";
	}	
	cout<<endl;
}

// problem 2
int evaluateExpression(string expression){
	Stack<int> stack;
	int value;
	bool isFirst=true;
	for(int i=0; i<expression.length(); i++){
		char ch=expression[i];
		int num=ch-'0';
		if(isdigit(ch)){
			if(isFirst){
				value=num;
				isFirst=false;
			} else { 
				value-=num;
			}
		} else if(ch=='('){
			isFirst=true;
			stack.push(value);
		} else if(ch==')'){
			value=stack.pop()-value;
		}
	}
	return value;
}
// problem 3
pair<int,int> fib(int num){
	if(num==0) return make_pair(0,1);
	pair<int,int> pr= fib(num-1);
	return make_pair(pr.second, pr.first+pr.second);
}