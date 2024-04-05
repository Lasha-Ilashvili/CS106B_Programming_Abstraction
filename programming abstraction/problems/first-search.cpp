#include <iostream>
#include "console.h"
#include "queue.h"
using namespace std;

void dfs(string s, int max){
	cout<<s<<endl;
	if(s.length()<max){
		for(char ch='1'; ch<='3'; ch++){
			dfs(s+ch,max);
		}
	}
}

void bfs(int max){
	Queue<string> q;
	q.enqueue("");
	while(!q.isEmpty()){
		string cur=q.dequeue();
		cout<<cur<<endl;
		if(cur.length()<max){
			for(char ch='1'; ch<='3'; ch++){
				q.enqueue(cur+ch);
			}
		}
	}
}

int main()
{
	cout<<"BFS vs DFS"<<endl;
	dfs("",3);
	return 0;
}