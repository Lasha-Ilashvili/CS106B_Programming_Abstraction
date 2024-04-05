#include <iostream>
#include <cmath>
#include "console.h"
#include "vector.h"
#include "grid.h"
#include "set.h"
using namespace std;

struct itemT {
	int weight;
	int value;

	itemT() {
		weight = 0;
		value = 0;
	}
};

int maxValueFromItems(Vector<itemT>& items, int maxWeight, Vector<itemT>& selectedItems);
int minValueTravel(Grid<int>& costs, Vector<int>& cities, Set<int>& visited);

int main12()
{
	cout<<"DONE"<<endl;
	return 0;
}

// problem 1
int maxValueFromItems(Vector<itemT>& items, int maxWeight, Vector<itemT>& selectedItems) {

	if(items.isEmpty() || maxWeight == 0) {
		int sum = 0;

		foreach(itemT val in selectedItems) {
			sum += val.value;
		}

		return sum;
	}

	itemT last = items[items.size()-1];

	items.remove(items.size()-1);

	int res = maxValueFromItems(items, maxWeight, selectedItems);

	if(last.weight <= maxWeight) {

		selectedItems += last;

		int op2 = maxValueFromItems(items, maxWeight - last.weight, selectedItems);

		selectedItems.remove(selectedItems.size()-1);
		
		res = max(res, op2);

	}

	items += last;

	return res;
}

// problem 2
int minValueTravel(Grid<int>& costs, Vector<int>& cities, Set<int>& visited) {

	if(cities.size() == costs.numCols()) {
		int cost = 0;
		for (int i = 0; i < cities.size(); i++) {
			cost += costs[cities[i]][cities[(i + 1) % cities.size()]];
		}
		return cost;
	}

	int res = INT_MAX;

	for(int city = 0; city < costs.numCols(); city++) {

		if(!visited.contains(city)) {
			cities += city;
			visited += city;

			int val = minValueTravel(costs, cities, visited);

			res = min(res, val);

			cities.remove(city);
			visited.remove(city);
		}
	}

	return res;	
}