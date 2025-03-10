#pragma once
#include "Bacterium.h"
#include "Biologist.h"
#include <sstream>
#include <fstream>
class Repository
{

private:
	vector<Bacterium> bacterias;
	vector<Biologist> biologists;
public:
	Repository() { this->loadFile(); }
	~Repository() { this->saveFile(); }
	void loadFile();
	void saveFile();
	vector<Bacterium>& getBacterias() {return this->bacterias;}
	vector<Biologist>& getBiologists() { return this->biologists; }
	void addBacterium(string name, string speices, int size, vector<string> desieses);

};

