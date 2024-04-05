#include "problem set18.h"
#include "error.h"

ResizableArray::ResizableArray(int size) {
	data = new double[size];
	currentSize = size;
}

ResizableArray::~ResizableArray() {
	delete[] data;
}

void ResizableArray::resize(int newSize) {
	double* newArr = new double[newSize];
	for(int i = 0; i < currentSize; i++) {
		newArr[i] = data[i];
	}
	delete[] data;
	data = newArr;
}

double ResizableArray::getAt(int index) {
	if(index < 0 || index > currentSize) {
		error("Exception: out of bounds");
	}
	return data[index];
}

void ResizableArray::setAt(int index, double value) {
	if(index < 0 || index > currentSize) {
		error("Exception: out of bounds");
	}

	data[index] = value;
}

int ResizableArray::size() {
	return currentSize;
}