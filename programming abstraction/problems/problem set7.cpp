#include <iostream>
#include <cmath>
#include "console.h"
#include "vector.h"
#include "simpio.h"
#include "grid.h"
#include "random.h"
#include "queue.h"
using namespace std;

struct Coordinates{
	int x;
	int y;
};

int fold(int, Vector<int>, int(int, int));
int add(int x, int y){ return x+y; }
int mult(int x, int y){ return x*y; }
int xor(int x, int y){ return x^y; }
bool routeExists(Grid<bool>& grid, Coordinates start, Coordinates end);
bool vecContains(Vector<Coordinates>& visited, Coordinates current);

int main7()
{
	cout<<"DONE"<<endl;
	return 0;
}

// problem 1
int fold(int startingValue, Vector<int> values, int(*combine)(int,int)){
	int res=startingValue;
	for(int i=0; i<values.size(); i++){
		res=combine(values[i], res);
	}
	return res;
}

// problem 2
bool routeExists(Grid<bool>& grid, Coordinates start, Coordinates end){
	if(grid[start.x][start.y] || grid[end.x][end.y]){
		return false;
	}
	Queue<Coordinates> q;
	Vector<Coordinates> visited;
	q.enqueue(start);

	while(!q.isEmpty()){
		Coordinates current = q.dequeue();
		if(current.x == end.x && current.y == end.y){
			return true;
		}

		for(int i=-1; i<=1; i++){
			for(int j=-1; j<=1; j++){
				Coordinates newPoint = {current.x+i, current.y+j};
				if(grid.inBounds(newPoint.x, newPoint.y) && !vecContains(visited, newPoint) && 
					!grid[newPoint.x][newPoint.y] && (abs(i)!=1 || abs(j)!=1)){
					visited+=newPoint;
					q.enqueue(newPoint);
				}
			}
		}
	}
	return false;
}

bool vecContains(Vector<Coordinates>& visited, Coordinates current){
	for(int i=0; i<visited.size(); i++){
		if(visited[i].x == current.x && visited[i].y == current.y){
			return true;
		}
	}
	return false;
}
