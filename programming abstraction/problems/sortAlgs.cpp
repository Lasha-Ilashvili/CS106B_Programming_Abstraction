#include <iostream>
#include "console.h"
#include "vector.h"
using namespace std;

void selectionSort(Vector<int>& v);
void insertionSort(Vector<int>& v);

int mainAlgs()
{
	Vector<int> v;
	v+=7,6,5,4,3,2,1;
	insertionSort(v);
	cout<<v<<endl;
	return 0;
}

void swap(Vector<int>& v, int current, int index) {
	if(index != current) {
		int temp = v[index];
		v[index] = v[current];
		v[current] = temp;
	}
} 

void replaceWithMin(Vector<int>& v, int current) {
	int min = current;

	for(int i = current + 1; i < v.size(); i++) {
		if(v[i] < v[min]) {
			min = i;
		}
	}

	swap(v, current, min);
}

void selectionSort(Vector<int>& v) {
	for(int i = 0; i < v.size(); i++) {
		replaceWithMin(v, i);
	}
}

void moveToStart(Vector<int>& v, int current) {
	for(int i = current - 1; i >= 0; i--) {
		if(v[i] > v[current]) {
			swap(v, current, i);
			current--;
		} else {
			break;
		}
	}
}

void insertionSort(Vector<int>& v) {
	for(int i = 1; i < v.size(); i++) {
		moveToStart(v, i);
	}
}
