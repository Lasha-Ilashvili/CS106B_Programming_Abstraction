/**********************************************
 * File: pqueue-heap.h
 *
 * A priority queue class backed by a binary
 * heap.
 */
#ifndef PQueue_Heap_Included
#define PQueue_Heap_Included

#include <string>
using namespace std;

/* A class representing a priority queue backed by an
 * binary heap.
 */
class HeapPriorityQueue {
public:
	/* Constructs a new, empty priority queue backed by a binary heap. */
	HeapPriorityQueue();
	
	/* Cleans up all memory allocated by this priority queue. */
	~HeapPriorityQueue();
	
	/* Returns the number of elements in the priority queue. */
	int size();
	
	/* Returns whether or not the priority queue is empty. */
	bool isEmpty();
	
	/* Enqueues a new string into the priority queue. */
	void enqueue(string value);
	
	/* Returns, but does not remove, the lexicographically first string in the
	 * priority queue.
	 */
	string peek();
	
	/* Returns and removes the lexicographically first string in the
	 * priority queue.
	 */
	string dequeueMin();

private:
	// TODO: Fill this in with the implementation of your binary heap
	// priority queue.  You can add any fields, types, or methods that you
	// wish.
	//
	// While you are free to implement this as you see fit, you *must* do
	// all of your own memory management and should not use the Vector.

	static const int INITIAL_CAPACITY = 100;
	string *elements;
	int capacity;
	int elemCount;
	void expand();
	void bubble_up(int child, int parent, int size);
	void bubble_down(int parent, int size);
	void swap(int n1, int n2);
};

#endif
