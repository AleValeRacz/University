#pragma once
#include "item.h"
#include "user.h"
#include <fstream>
#include <sstream>
class Repository
{
private:
	vector <Item> items;
	vector <User> users;
public:
	Repository() { this->loadRepo();}
	~Repository();
	void loadRepo();
	void addItem(string name, string category, int price);
	vector <Item>& getItems() { return this->items; }
	vector <User> getUsers() { return this->users; }

};

