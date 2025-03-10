#pragma once
#include <string>
#include <vector>
using namespace std;
class Bacterium
{

private:
	string name, species;
	int size;
	vector<string> desieses;
public:
	Bacterium(string name, string species, int size): name{name}, species{species}, size{size}{}
	~Bacterium() {};
	string getName() { return this->name; }
	string getSpecies() { return this->species; }
	int getSize() { return this->size; }
	vector<string>& getDesises() { return this->desieses; }
	void addDesiese(string desiese) { this->desieses.push_back(desiese); }
	string toString() { string text = name + "|" + species + "|" + to_string(size); for (auto des : this->desieses) text += "|" + des; return text + "\n"; }
	void setName(string nam) { this->name = nam; }
	void setSpecies(string spe) { this->species = spe; }
	void setSize(int newSize) { this->size = newSize; }

};

