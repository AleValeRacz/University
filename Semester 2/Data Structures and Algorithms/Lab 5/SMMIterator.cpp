#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>

void SMMIterator::inorder_traversal(Node* node)
{
	if (node == nullptr)
		return;

	this->inorder_traversal(node->left);
	this->elements[this->nrElem++] = TElem(node->elem.first, node->elem.second);
	this->inorder_traversal(node->right);

}
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	this->elements = new TElem[map.size()];
	this->current = 0; 
	this->nrElem = 0;
	this->inorder_traversal(this->map.root);

}
// BC = WC = TC = Theta(mapSize)

void SMMIterator::first(){
	this->current = 0;
}

void SMMIterator::next(){
	if (!valid())
		throw exception();

	this->current++;
}

bool SMMIterator::valid() const{
	
	return this->current < this->nrElem;

}

TElem SMMIterator::getCurrent() const{
	if (!valid())
		throw exception();
	return this->elements[this->current];


}
SMMIterator::~SMMIterator()
{
	delete[] this->elements;
}






