#pragma once
#include "Item.h"
#include <vector>
#include <sstream>
#include <fstream>
class Repository
{
private:
	vector <Item> items;
public:
	Repository() { this->loadFile(); }
	~Repository() {};
	vector <Item> getItems() { return this->items; }
	void loadFile();
};

