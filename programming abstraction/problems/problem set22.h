#ifndef _mergesort_h
#define _mergesort_h

struct Cell {
	int val;
	Cell* next;
};

void mergeSort(Cell*& head);

#endif