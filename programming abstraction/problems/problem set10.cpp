#include <iostream>
#include <cmath>
#include "console.h"
#include "grid.h"
#include "vector.h"
using namespace std;

bool isClique(Grid<bool>& graph, Vector<int> indices);
int maxSizeClique(Grid<bool>& graph);

int main10()
{
	cout<<"DONE"<<endl;
	return 0;
}

bool isConnected(Grid<bool>& graph, int x, Vector<int> indices) {
	for(int i = 0; i<indices.size(); i++) {
		if(!graph[x][indices[i]]) {
			return false;
		}
	}
	return true;
}

// problem 1
bool isClique(Grid<bool>& graph, Vector<int> indices) {
	if(indices.size() < 2) {
		return true;
	}

	int x = indices[indices.size()-1];
	indices.remove(indices.size()-1);
	
	return isConnected(graph, x, indices) && isClique(graph, indices);
}

int maxSquare(Grid<bool>& graph, int x, Vector<int> square) {
	if(x == graph.numCols()) {
		if(isClique(graph, square)) {
			return square.size();
		} else {
			return -1;
		}
	}
	
	int op1 = maxSquare(graph, x+1, square);
	
	square+=x;

	int op2 = maxSquare(graph, x+1, square);

	square.remove(square.size()-1);
	
	return max(op1, op2);
}

// problem 2
int maxSizeClique(Grid<bool>& graph) {
	Vector<int> square;
	return maxSquare(graph, 0, square);
}
