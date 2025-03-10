#include "Set.h"
#include "SetITerator.h"
#include <exception>

Set::Set() {

	this->capacity = 10;
	this->set_size = 0;
	this->elements = new TElem[this->capacity];

	
}
//BC=WC=TC : Theta(1)


bool Set::add(TElem elem) {
	//TODO - Implementation
	if (this->set_size == this->capacity)
		this->resize();

	int i = 0;
	while(i < this->set_size)
	{
		if (this->elements[i] == elem)
			return false;
		i++;
	}
	this->elements[this->set_size] = elem;
	this->set_size++;
	return true;
}
//BC: Theta(1)-when the first element in the set is equal with the element we want to add
//WC: Theta(set_size)-when the element is either on the last position or it's not in the set
//TC: O(set_size)


bool Set::remove(TElem elem) {
	int i=0;
	while (i < this->set_size)
	{
		if (this->elements[i] == elem)
		{
			for (int j = i; j < this->set_size - 1; j++)
				this->elements[j] = this->elements[j + 1];
			this->set_size--;
			return true;
		}
		i++;
	}
	return false;
}
//BC=WC=TC= Theta(set_size)-the element could be anywhere in the list, and  we would still need to shift all the following elements one position to the left


bool Set::search(TElem elem) const {
	int i=0;
	while (i < this->set_size)
	{
		if (this->elements[i] == elem)
			return true;
		i++;
	}
	return false;
}
//BC: Theta(1)-when the first element in the set is equal to the element we're looking for
//WC: Theta(set_size)-when the element is either on the last position or it's not in the set
//TC: O(set_size)



int Set::size() const {
	//TODO - Implementation
	return this->set_size;
}
//BC=WC=TC : Theta(1)


bool Set::isEmpty() const {
	//TODO - Implementation
	return this->set_size==0;
}
//BC=WC=TC : Theta(1)

Set::~Set() {
	//TODO - Implementation
	delete[] this->elements;
}
//BC=WC=TC : Theta(1)

SetIterator Set::iterator() const {
	return SetIterator(*this);
}
//BC=WC=TC : Theta(1)

void Set::resize()
{
	this->capacity *= 2;
	TElem* elms = new TElem[this->capacity];
	for (int i = 0; i < this->set_size; i++)
		elms[i] = this->elements[i];
	delete[]this->elements;
	this->elements = elms;

}
//BC=WC=TC= Theta(set_size)-all the elements are copied in all cases



