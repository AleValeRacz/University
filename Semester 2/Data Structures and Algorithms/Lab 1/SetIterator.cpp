#include "SetIterator.h"
#include "Set.h"
#include <exception>
using namespace std;

SetIterator::SetIterator(const Set& m) : set(m){
	//TODO - Implementation
	this->current_position = 0;
}
//BC=WC=TC : Theta(1)

void SetIterator::first() {
	//TODO - Implementation
	this->current_position = 0;
}
//BC=WC=TC : Theta(1)

void SetIterator::next() {
	//TODO - Implementation
	if (this->current_position == this->set.set_size)
	{
		throw exception();

	}
	this->current_position++;
}
//BC=WC=TC : Theta(1)

TElem SetIterator::getCurrent()
{
	if (this->current_position == this->set.set_size)
	{
		throw exception();
	}
	return this->set.elements[this->current_position];
}
//BC=WC=TC : Theta(1)

bool SetIterator::valid() const {
	//TODO - Implementation

	return this->current_position < this->set.set_size;
}
//BC=WC=TC : Theta(1)

void SetIterator::previous()
{
	if (this->current_position == this->set.set_size)
	{
		throw exception();
	}
	if (this->current_position == 0)
		this->current_position = this->set.set_size;
	else
		this->current_position--;
}
//BC = WC = TC: Theta(1)




