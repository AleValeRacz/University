#include "Map.h"
#include "MapIterator.h"

Map::Map() {
	this->head = nullptr;
	this->tail = nullptr;
	this->map_size = 0;
}
//Bc = Wc = Ac = Theta(1)


Map::~Map() {
	Node* current = this->head;
	while (current != nullptr)
	{
		Node* next = current->next;
		delete current;
		current = next;
	}
	delete current;
}
//Bc = Wc = Ac = Theta(map_size)

TValue Map::add(TKey c, TValue v){
	//for the first one added
	if (this->head == nullptr)
	{
		Node* new_node = new Node;
		new_node->elem = TElem(c, v);
		new_node->next = nullptr;
		new_node->previous = nullptr;
		this->head = new_node;
		this->tail = new_node;
		this->map_size++;
	}
	else
	{
		Node* current = this->head;
		while (current != nullptr)
		{
			if (current->elem.first == c)
			{
				TValue old_val = current->elem.second;
				current->elem.second = v;
				return old_val;
			}
			current = current->next;
			
		}

		Node* new_node = new Node;
		new_node->elem = TElem(c, v);
		new_node->next = nullptr;
		new_node->previous = this->tail;
		this->tail->next = new_node;
		this->tail = new_node;
		this->map_size++;
	}
	return NULL_TVALUE;	
}
//Bc: Theta(1)-when the first key is equal to c 
//Wc: Theta(map_size)-when the key c appears on the last position or not at all
//Ac: O(map_size)


TValue Map::search(TKey c) const{
	Node* current = this->head;
	while (current != nullptr)
	{
		if (current->elem.first == c)
			return current->elem.second;

		current = current->next;

	}
	return NULL_TVALUE;
}
//Bc: Theta(1)-when the element is on the first position
//Wc: Theta(map_size)-when the elem is on the last position or not in the array
//Ac: O(map_size)

TValue Map::remove(TKey c){
	if(this->head == nullptr)
		return NULL_TVALUE;
	Node* current = this->head;
	while (current != nullptr)
	{
		if (current->elem.first == c)
		{
			TValue val = current->elem.second;
			//If the element is the head
			if (current == this->head)
			{
				this->head = current->next;
				//if there was more than one element, we set the prev of the new head to null
				if (this->head != nullptr)
					this->head->previous = nullptr;
			}
			//if the element is the tail
			else if (current == this->tail)
			{
				this->tail = current->previous;
				//If there was more than one elemenent, we set the next of the new tail to null
				if (this->tail != nullptr)
					this->tail->next = nullptr;
			}
			else
			{
				current->previous->next = current->next;
				current->next->previous = current->previous;
			}
			delete current;
			this->map_size--;
			return val;

		}

		current = current->next;

	}
	return NULL_TVALUE;
}
//Bc: Theta(1)-when the element is on the first position
//Wc: Theta(map_size)-when the elem is on the last position or not in the array
//Ac: O(map_size)


int Map::size() const {
	
	return this->map_size;
}
//Bc = Wc = Ac = Theta(1)
bool Map::isEmpty() const{
	
	return this->map_size == 0;
}
//Bc = Wc = Ac = Theta(1)
MapIterator Map::iterator() {
	return MapIterator(*this);
}
//Bc = Wc = Ac = Theta(1)


