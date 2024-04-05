#ifndef _mystack_h
#define  _mystack_h

class MyStack {

public:
	MyStack();
	MyStack& operator=(const MyStack& other);
	~MyStack();
	void push(int n);
	int pop();	
	int peek();
	bool isEmpty();
	int size();
private:
	static const int INITIAL_CAPACITY = 100;
	int *elements;
	int capacity;
	int count;
	void expand();
};

#endif