#pragma once
#include <string>
using namespace std;

class Item
{
private:
	string category, name;
	int quantity;

public:
	Item(string category, string name, int quantity) :category{ category }, name{ name }, quantity{ quantity } {};
	~Item() {};
	string toString() { return category + " " + name + " " + to_string(quantity); }
	string getCategory() { return category; }
	string getName() { return name; }
	int getQuantity() { return quantity; }

};

