#ifndef _matrix_class_h
#define _matrix_class_h

class Matrix {

private:
	int w, h;
	double* grid;
public:

	Matrix(int width, int height);
	Matrix(const Matrix& other);
	~Matrix();
	double getAt(int row, int col);
	void setAt(int row, int col, double val);
	void addAt(int row, int col, double val);
	Matrix add(Matrix& other);
	Matrix times(Matrix& other);
};

#endif