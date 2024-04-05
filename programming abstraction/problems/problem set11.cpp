#include <iostream>
#include <string>
#include "console.h"
#include "grid.h"
#include "vector.h"
#include "set.h"
using namespace std;

bool hasHamiltonCycle(Grid<bool>& graph, Vector<int>& resultCycle);
bool canBeColored(Grid<bool>& graph, int colorCount, Vector<int>& coloringResult);

int main11() {
	cout<<"DONE"<<endl;
	return 0;
}

bool isCycle(Grid<bool>& graph, Vector<int>& resultCycle) {
	for(int i = 0; i < resultCycle.size(); i++) {
		int point1 = resultCycle[i];
		int point2 = resultCycle[(i+1) % resultCycle.size()];
		if(!graph[point1][point2]) {
			return false;
		}
	}
	return true;
}

bool containsHamiltonCycle(Grid<bool>& graph, Vector<int>& resultCycle, Set<int>& result) { 
	if(resultCycle.size() == graph.numCols()) {
		return isCycle(graph, resultCycle);
	}

	for(int i = 0; i < graph.numCols(); i++) {
		if(!result.contains(i)) {
			resultCycle += i;
			result.add(i);
			if(containsHamiltonCycle(graph, resultCycle, result)) {
				return true;
			}
			resultCycle.remove(result.size() - 1);
			result.remove(i);
		}
	}
	return false;
}

// problem 1
bool hasHamiltonCycle(Grid<bool>& graph, Vector<int>& resultCycle) {
	Set<int> result;
	return containsHamiltonCycle(graph, resultCycle, result);
}

bool isValid(Grid<bool>& graph, int color, Vector<int>& coloringResult) {
		
	for(int i = 0; i < coloringResult.size(); i++) {
		if(graph[i][coloringResult.size()] && coloringResult[i] == color) {
			return false;
		}
	}
	return true;
}

// problem 2
bool canBeColored(Grid<bool>& graph, int colorCount, Vector<int>& coloringResult) { 
	if(coloringResult.size() == graph.numCols()) {
		return true;
	}

	for(int i = 0; i < colorCount; i++) {
		if(isValid(graph, i, coloringResult)) {
			coloringResult += i;
			
			if(canBeColored(graph, colorCount, coloringResult) && isValid(graph, i, coloringResult)) {
				return true;
			}

			coloringResult.remove(coloringResult.size() - 1);
		}
	}
	return false;
}