#pragma once
#include <string>
using namespace std;

class User
{
private:
	string name, type;
	int id;

public:
	User(string name, int id, string type) : name{ name }, id{ id }, type{ type } {};
	~User() {};
	string getName() { return name; }
	int getId() { return id; }
	string getType() { return type; }
	string toString() { return name + to_string(id) + type;}

};
