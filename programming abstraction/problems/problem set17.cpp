#include "problem set17.h"
#include <error.h>


Matrix::Matrix(int width, int height) {
	w = width;
	h = height;
	grid = new double[w*h];
}

Matrix::Matrix(const Matrix& other) {
	delete[] grid;

	w = other.w;
	h = other.h;

	grid = new double[w * h];

	for(int i = 0; i < w * h; i++) {
		grid[i] = other.grid[i];
	}
}

Matrix::~Matrix() {
	delete[] grid;
}

double Matrix::getAt(int row, int col) {
	return grid[row * w + col];
}

void Matrix::setAt(int row, int col, double val) {
	grid[row * w + col] = val;
}

void Matrix::addAt(int row, int col, double val) {
	grid[row * w + col] += val;
}

Matrix Matrix::add(Matrix& other) {
	Matrix res(w, h);
	for(int i = 0; i < w * h; i++) {
		res.grid[i] = grid[i] + other.grid[i];
	}
	return res;
}

Matrix Matrix::times(Matrix& other) {
	Matrix result(other.w, h);
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < other.w; col++) {
			for (int k = 0; k < w; k++) {
				result.addAt(row, col, getAt(row, k) * other.getAt(k, col));
			}
		}
	}
	return result;
}