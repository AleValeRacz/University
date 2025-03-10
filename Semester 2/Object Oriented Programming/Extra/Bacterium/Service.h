#pragma once
#include "Repository.h"
class Service
{

private:
	Repository& repo;
public:
	Service(Repository& repo) : repo{ repo } {};
	~Service() {};
	vector<Bacterium>& getBacterias() { return this->repo.getBacterias(); }
	vector<Biologist>& getBiologists() { return this->repo.getBiologists(); }
	void addBacterium(string name, string speices, int size, vector<string> desieses);
	vector<Bacterium>& sortedBacterias();
	vector <Bacterium> filterBacterium(Biologist& bio);
	Bacterium& getBacteriumByName(string name);


};

