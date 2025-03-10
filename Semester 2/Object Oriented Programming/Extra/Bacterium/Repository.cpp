#include "Repository.h"

void Repository::loadFile()
{

	ifstream fin("biologists.txt");
	string line, name, species;
	while (getline(fin, line))
	{
		istringstream is(line);
		getline(is, name, '|');
		Biologist bio(name);
		while (getline(is,species,'|'))
		{
			string specie;
			istringstream iss(species);
			getline(iss, specie, '|');
			bio.addSpecie(specie);
		}
		this->biologists.push_back(bio);
	}

	fin.close();
	fin = ifstream("bacterium.txt");
	string size, specie, desieses;
	while (getline(fin, line))
	{
		istringstream is(line);
		getline(is, name, '|');
		getline(is, specie,'|');
		getline(is, size, '|');
		Bacterium bac(name, specie, stoi(size));
		while (getline(is, desieses,'|'))
		{
			string desiese;
			istringstream iss(desieses);
			getline(iss, desiese, '|');
			bac.addDesiese(desiese);
		}
		this->bacterias.push_back(bac);
	}


}

void Repository::saveFile()
{
	ofstream fout("bacterium.txt");
	for (auto bac : this->getBacterias())
		fout << bac.toString();
}

void Repository::addBacterium(string name, string speices, int size, vector<string> desieses)
{
	Bacterium bac(name, speices, size);
	for (auto des : desieses)
		bac.addDesiese(des);
	this->bacterias.push_back(bac);
}

