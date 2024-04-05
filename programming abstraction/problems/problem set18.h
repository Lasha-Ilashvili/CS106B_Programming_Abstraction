#ifndef _resizable_array_h
#define _resizable_array_h

class ResizableArray {
private:
	int currentSize;
	double* data;
public:
	ResizableArray(int size = 10);
	~ResizableArray();
	void resize(int newSize);
	double getAt(int index);
	void setAt(int index, double value);
	int size();
};

#endif