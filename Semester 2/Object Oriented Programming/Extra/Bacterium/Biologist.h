#pragma once
#include <string>
#include <vector>
using namespace std;

class Biologist
{
private:

	string  name;
	vector<string> speciesList;
public:
	Biologist(string name): name{name}{}
	~Biologist() {  }
	string getName() { return this->name; }
	vector<string>& getSpecies() { return this->speciesList; }
	void addSpecie(string specie) { this->speciesList.push_back(specie); }


};

