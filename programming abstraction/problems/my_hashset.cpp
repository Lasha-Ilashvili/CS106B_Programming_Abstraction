#include "my_hashset.h"
#include "error.h"

const int kHashMask = 0x7FFFFFFF;
int hashCoded(string key) {
    int hashVal = 0;
    for (int x = 0; x < key.length(); ++x) {
        hashVal ^= (hashVal << 5) +
                   (hashVal >> 2) +
                   key[x];
    }
    return hashVal & kHashMask;
}

const int INITIAL_SIZE = 10;

MyHashSet::MyHashSet() {
	buckets = new Cell*[INITIAL_SIZE];
	numBuckets = INITIAL_SIZE;
	elements = 0;

	for(int i = 0; i < numBuckets; i++) {
		buckets[i] = NULL;
	}

}

MyHashSet::~MyHashSet() {
	for(int i = 0; i < numBuckets; i++) {
		deallocate(buckets[i]);
	}

	delete[] buckets;
}

int MyHashSet::size() {
	return elements;
}

bool MyHashSet::isEmpty() {
	return elements == 0;
}

void MyHashSet::add(string value) {
	if(elements / numBuckets > 2) {
		increaseBuckets();
	}

	if(contains(value)) {
		return;
	}

	Cell*& head = buckets[hashCoded(value) % numBuckets];	

	Cell* temp = new Cell;
	temp->s = value;
	temp->next = head;
	head = temp;

	elements++;
}

bool MyHashSet::contains(string value) {
	return findCell(value) != NULL;
}

MyHashSet::Cell* MyHashSet::findCell(string value) {
	Cell* head = buckets[hashCoded(value) % numBuckets];

	while(head != NULL) {
		if(head->s == value) {
			break;
		}
		head = head->next;
	}

	return head;
}

void MyHashSet::increaseBuckets() {
	int newSize = numBuckets * 2;
	Cell** newBuckets = new Cell*[newSize];

	for(int i = 0; i < newSize; i++) {
		newBuckets[i] = NULL;
	}

	for(int i = 0; i < numBuckets; i++) {
		Cell*& current = buckets[i];

		while(current != NULL) {
			Cell*& head = newBuckets[hashCoded(current->s) % newSize];
			
			Cell* next = current->next;

			current->next = head;
			head = current;

			current = next;
		}

	}

	delete[] buckets;

	buckets = newBuckets;
	numBuckets = newSize;
}

void MyHashSet::deallocate(Cell*& head) {
	if(head != NULL) {
		deallocate(head->next);
		delete head;
	}
}