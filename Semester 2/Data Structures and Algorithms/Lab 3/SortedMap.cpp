#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) {
	this->rel = r;
	this->head = -1;
	this->firstEmpty = 0;
	this->capacity = 2;
	this->map_size = 0;
	this->elements = new TElem[capacity];
	this->next = new int[capacity];
	for (int i = 0; i < capacity-1; i++)
	{
		this->next[i] = i + 1;
	}
	this->next[this->capacity-1] = -1;

}
//BC = WC = TC = Theta(capacity)
TValue SortedMap::add(TKey k, TValue v) {
	if (this->map_size == this->capacity) {
		resize();
	}

	int current = this->head;
	int prev = -1;
	while (current != -1 && rel(this->elements[current].first, k)) {
		if (this->elements[current].first == k) {
			TValue old_val = this->elements[current].second;
			this->elements[current].second = v;
			return old_val;
		}
		prev = current;
		current = this->next[current];
	}
	//if it needs to be added on the first position
	if (this->head == -1 || rel(k, this->elements[head].first)) {
		int new_pos = this->firstEmpty;
		this->firstEmpty = this->next[firstEmpty];

		this->elements[new_pos].first = k;
		this->elements[new_pos].second = v;
		this->next[new_pos] = head;
		this->head = new_pos;

		this->map_size++;
		return NULL_TVALUE;
	}
	// Insert the new element between prev and current
	int new_poz = this->firstEmpty;
	this->firstEmpty = this->next[firstEmpty];
	this->elements[new_poz].first = k;
	this->elements[new_poz].second = v;
	this->next[new_poz] = current;
	this->next[prev] = new_poz;

	this->map_size++;

	return NULL_TVALUE;
}
//BC = Theta(1)
//WC = Theta(map_size)
//TC = O(map_size)


TValue SortedMap::search(TKey k) const {
	int current = this->head;
	while (current != -1 && rel(this->elements[current].first, k))
	{
		if (elements[current].first == k)
			return elements[current].second;
		current = this->next[current];
	}
	return NULL_TVALUE;
}
//BC = Theta(1)
//WC = Theta(map_size)
//TC = O(map_size)


TValue SortedMap::remove(TKey k) {
	int current = this->head;
	int previous = -1;
	while (current != -1 && rel(this->elements[current].first, k))
	{
		if (this->elements[current].first == k)
		{
			TValue val = this->elements[current].second;
			if (previous == -1)
				this->head = this->next[current];
			else
			{
				this->next[previous] = this->next[current];
			}
			this->next[current] = this->firstEmpty;
			this->firstEmpty = current;
			this->map_size--;
			return val;
		}
		previous = current;
		current = this->next[current];
	}
	return NULL_TVALUE;
}
//BC = Theta(1)
//WC = Theta(map_size)
//TC = O(map_size)



int SortedMap::size() const {
	return this->map_size;
}
//BC = WC = TC = Theta(1)


bool SortedMap::isEmpty() const {

	return this->map_size == 0;
}
//BC = WC = TC = Theta(1)

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}
//BC = WC = TC = Theta(1)

SortedMap::~SortedMap() {
	delete[]elements;
	delete[]next;
}
//BC = WC = TC = Theta(1)

void SortedMap::resize()
{
	TElem* elms = new TElem[this->capacity * 2];
	int* new_next = new int[this->capacity * 2];
	for (int i = 0; i < this->capacity; i++)
	{
		elms[i] = this->elements[i];
		new_next[i] = this->next[i];
	} 
	for (int i = this->capacity; i < this->capacity * 2 - 1; i++)
		new_next[i] = i + 1;
	new_next[capacity * 2 - 1] = -1;
	delete[]this->elements;
	delete[]this->next;
	this->elements = elms;
	this->next = new_next;
	this->firstEmpty = this->capacity;
	this->capacity *= 2;

}
//BC = WC = TC = Theta(capacity*2)


int SortedMap::updateValues(SortedMap& sm)
{
	int i = 0;
	int current = this->head;
	while (current != -1)
	{
		TKey key = elements[current].first;
		TValue val = sm.search(key);
		if (val != NULL_TVALUE)
		{
			i++;
			this->elements[current].second = val;
			
		}
		current = this->next[current];
	}
	return i;

}
//BC = Theta(map_size) if all the keys in the other map don't pass the relation (search returns NULL every time)
//WC = Theta(map_size*map_size_of_other)
//TC = O(map_size*map_size of other)