#pragma once
#include "Repository.h"
#include <algorithm>
class Service
{
private:
	Repository repo;
public:
	Service() {};
	~Service() {};
	vector <Item> getItemsSorted();
	vector <Item> SearchNameCategory(string name);
	vector <Item> FilterByCategory(string category);

};

