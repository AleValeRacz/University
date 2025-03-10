#include "Service.h"
#include<algorithm>
void Service::addBacterium(string name, string speices, int size, vector<string> desieses)
{

	this->repo.addBacterium(name, speices, size, desieses);

}
vector<Bacterium>& Service::sortedBacterias()
{
	vector<Bacterium>& sorted = this->getBacterias();
	sort(sorted.begin(), sorted.end(), [](Bacterium& a, Bacterium& b) {
		return a.getName() < b.getName();
		});
	return sorted;
}

vector<Bacterium> Service::filterBacterium(Biologist& bio)
{
	vector<Bacterium> filtered;
	for (auto &bac : this->sortedBacterias())
	{
		for (string spec : bio.getSpecies())
		{
			if (bac.getSpecies() == spec)
			{
				filtered.push_back(bac);
				break;
			}

		}
	}

	return filtered;
}

Bacterium& Service::getBacteriumByName(string name)
{
	for (auto &bac : this->getBacterias())
		if (bac.getName() == name)
			return bac;

}



