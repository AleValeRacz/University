#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	this->rel = r;
	this->mapSize = 0;
	this->root = nullptr;


}
//BC=WC=TC = Theta(1)

void SortedMultiMap:: initNode(Node* node, TKey c, TValue v)
{
	
	node->elem.first = c;
	node->elem.second = v;
	node->left = nullptr;
	node->right = nullptr;


}
//BC=WC=TC = Theta(1)

void SortedMultiMap::add(TKey c, TValue v) 
{
	if (this->root == nullptr)
	{
		this->root = new Node;
		this->initNode(root, c, v);
		this->mapSize++;
		return;
	}
	Node* current = this->root;
	while (true)
	{
		if (current->elem.first == c)
		{
			if (current->right == nullptr)
			{
				current->right = new Node;
				this->initNode(current->right, c, v);
				this->mapSize++;
				return;
			}
			else
				current = current->right;
		}

		else if (this->rel(c, current->elem.first))
		{
			if (current->left == nullptr)
			{
				//if left becomes null, we've reached the place where we need to insert the elem
				current->left = new Node;
				this->initNode(current->left, c, v);
				this->mapSize++;
				return;
			}
			else
				//otherwise, keep going left
				current = current->left;

		}
		else
		{
			if (current->right == nullptr)
			{
				current->right = new Node;
				this->initNode(current->right, c, v);
				this->mapSize++;
				return;
			}
			else
				current = current->right;


		}
	}
}

//BC = Theta(1)
//WC = Theta(mapSize)
//TC = O(mapSize)


void SortedMultiMap::search_rec(Node* node, TKey c, vector<TValue>& val)
{
	if (node == nullptr)
		return;
	if (node->elem.first == c)
	{
		val.push_back(node->elem.second);
		search_rec(node->left, c, val);
		search_rec(node->right, c, val);

	}
	else if (this->rel(c, node->elem.first))
		search_rec(node->left, c, val);
	else
		search_rec(node->right, c, val);

}

vector<TValue> SortedMultiMap::search(TKey c)  {
	
	vector <TValue> values;
	search_rec(this->root, c, values);
	return values;
}
//BC = Theta(height)
//WC = Theta(mapSize)
//TC = O(mapSize)


bool SortedMultiMap::remove(TKey c, TValue v) {
	
    return remove_rec(this->root, nullptr, c,v);
}

bool SortedMultiMap::remove_rec(Node* current, Node* parent, TKey c, TValue v)
{
	if (current == nullptr)
		return false;
	if (current->elem.first == c && current->elem.second == v)
	{
		if (current->left == nullptr && current->right == nullptr)
		{
			//no descendant
			if(parent == nullptr)
				this->root = nullptr; //for deleating the root
		
			else if (parent->left == current)
				parent->left = nullptr;
			else 
				parent->right = nullptr;
		
			delete current;
		}
		else if (current->left == nullptr || current->right == nullptr) 
		{
			// one descendant
			Node* child;
			if (current->left == nullptr)
				child = current->right;
			else
				child = current->left;

			if (parent == nullptr) 
				this->root = child; // The node to be deleted is the root

			else if (parent->left == current) 
				parent->left = child;
			else 
				parent->right = child;

			delete current;
		}
		else 
		{
			// Case 3: Two descendants
			Node* maxNode = current->left;
			while (maxNode->right != nullptr)
				maxNode = maxNode->right;

			current->elem = maxNode->elem;
			return remove_rec(current->left, current, maxNode->elem.first, maxNode->elem.second);
		}

		this->mapSize--;
		return true;
	}

	if (this->rel(c, current->elem.first))
		return remove_rec(current->left, current, c, v);

	else 
		return remove_rec(current->right, current, c, v);
	

	}

//BC = Theta(1) the element we need to delete is the root, and it has 0 or 1 descendants
// WC = Theta(mapSize)
//TC = O(mapSize)

int SortedMultiMap::size() const {

	return this->mapSize;
}

bool SortedMultiMap::isEmpty() const {

	return this->mapSize == 0;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap()
{
	this->destructor_rec(this->root);
}

void SortedMultiMap::destructor_rec(Node* node)
{
	if (node == nullptr)
		return;
	this->destructor_rec(node->left);
	this->destructor_rec(node->right);
	delete node;
}
// BC = WC = TC = Theta(mapSize)

int SortedMultiMap::diferentaCheieMaxMin() const
{
	
	Node* current = this->root;
	if (current == nullptr)
		return -1;
	Node* prev = nullptr;

	while (current != nullptr)
	{
		prev = current;
		current = current->left;
	}
	TKey min = prev->elem.first;
	current = this->root;
	prev = nullptr;
	while (current != nullptr)
	{
		prev = current;
		current = current->right;
	}
	TKey max = prev->elem.first;

	return max - min;
}
// BC = WC = TC = Theta(height)


