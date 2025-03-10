#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator( Map& d) : map(d)
{
	this->current = d.head;
}
//Bc = Wc = Ac = Theta(1)

void MapIterator::first() {
	this->current = this->map.head;
}
//Bc = Wc = Ac = Theta(1)

void MapIterator::next() {
	if (this->current == nullptr)
		throw exception();
	this->current = this->current->next;
}
//Bc = Wc = Ac = Theta(1)

TElem MapIterator::getCurrent(){
	if (this->current == nullptr)
		throw exception();
	return this->current->elem;

}
//Bc = Wc = Ac = Theta(1)

bool MapIterator::valid() const {

	return this->current != nullptr;
}
//Bc = Wc = Ac = Theta(1)

TElem MapIterator::remove()
{
	if (this->current == nullptr)
		throw exception();
	Node* current_node = this->current;
	TElem element = current_node->elem;
	//if it is the head
	if (current_node == this->map.head)
	{
		this->map.head = current_node->next;
		if (this->map.head != nullptr)
			this->map.head->previous = nullptr;
	}
	//if it is the tail
	else if (current_node == this->map.tail)
	{
		this->map.tail = current_node->previous;
		if (this->map.tail != nullptr)
			this->map.tail->next = nullptr;
	}
	else
	{
		current_node->previous->next = current_node->next;
		current_node->next->previous = current_node->previous;
	}
	this->current = current_node->next;
	this->map.map_size--;
	delete current_node;
	return element;

}
//BC = WC = Ac = theta(1)



