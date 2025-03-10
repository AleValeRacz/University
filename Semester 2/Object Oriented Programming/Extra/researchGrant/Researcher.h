#pragma once
#include <string>

using namespace std;
class Researcher
{
	private:
	string name, position;
public:
	 string getName() const { return this->name; }
	 string getPosition() const { return  this->position; }
	 Researcher(string name, string position): name{name}, position{position}{}
	 ~Researcher() {};
	 string toString() const { return name + " " + position; }



};

