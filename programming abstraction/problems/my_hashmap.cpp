#include "my_hashmap.h"
#include "error.h"

const int kHashMask = 0x7FFFFFFF;

int hashCode(string key) {
    int hashVal = 0;
    for (int x = 0; x < key.length(); ++x) {
        hashVal ^= (hashVal << 5) +
                   (hashVal >> 2) +
                   key[x];
    }
    return hashVal & kHashMask;
}



const int INITIAL_SIZE = 10;

MyHashMap::MyHashMap() {
	buckets = new Cell*[INITIAL_SIZE];
	numBuckets = INITIAL_SIZE;

	for(int i = 0; i < numBuckets; i++) {
		buckets[i] = NULL;
	}

	numElems = 0;
}

MyHashMap::~MyHashMap() {

	for(int i = 0; i < numBuckets; i++) {
		deallocate(buckets[i]);
	}

	delete[] buckets;
}

void MyHashMap::put(string key, int value) {
	if(numElems / numBuckets > 2) {
		increaseBuckets();
	}

	Cell* cell = findCell(key);

	if(cell != NULL) {
		cell->value = value;

		return;
	}

	Cell*& head = buckets[hashCode(key) % numBuckets];
	
	Cell* temp = new Cell;
	temp->key = key;
	temp->value = value;
	
	temp->next = head;
	head = temp;
	
	numElems++;
}

bool MyHashMap::containsKey(string key) {
	return findCell(key) != NULL;
}

int MyHashMap::get(string key) {
	Cell* cell = findCell(key);

	if(cell == NULL) {
		error("No specified key could be found!");
	}

	return cell->value;
}

int MyHashMap::size() {
	return numElems;
}

bool MyHashMap::isEmpty() {
	return numElems == 0;
}

MyHashMap::Cell* MyHashMap::findCell(string key) {
	Cell* head = buckets[hashCode(key) % numBuckets];

	while(head != NULL) {

		if(head->key == key) {
			break;
		}

		head = head->next;
	}

	return head;
}

void MyHashMap::increaseBuckets() {
	int newSize = numBuckets * 2;
	Cell **newBuckets = new Cell*[newSize];

	for (int i = 0; i < newSize; i++)
		newBuckets[i] = NULL;


	for(int i = 0; i < numBuckets; i++) {
		Cell*& current = buckets[i];

		while(current != NULL) {
			Cell*& head = newBuckets[hashCode(current->key) % newSize];

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

void MyHashMap::deallocate(Cell*& head) {
	if(head != NULL) {
		deallocate(head->next);
		delete head;
	}
}
