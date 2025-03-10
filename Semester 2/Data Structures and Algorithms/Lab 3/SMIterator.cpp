#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	this->current = map.head;
}
//BC = WC = TC = Theta(1)
void SMIterator::first(){
	this->current = this->map.head;
}
//BC = WC = TC = Theta(1)
void SMIterator::next(){
	if (this->current == -1)
		throw exception();
	this->current = this->map.next[current];
}
//BC = WC = TC = Theta(1)
bool SMIterator::valid() const{
	
	return this->current != -1;
}
//BC = WC = TC = Theta(1)
TElem SMIterator::getCurrent() const
{
	if (this->current == -1)
		throw exception();
	return this->map.elements[current];
}
//BC = WC = TC = Theta(1)


