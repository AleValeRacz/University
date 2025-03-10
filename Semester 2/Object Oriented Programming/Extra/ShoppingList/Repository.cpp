#include "Repository.h"


void Repository::loadFile()
{
	ifstream file("items.txt");
	string line,category, name, quanS;
	int quantity;
	while (getline(file, line))
	{
		istringstream iss(line);
		getline(iss, category,'|');
		getline(iss, name, '|');
		getline(iss, quanS, '|');
		quantity = stoi(quanS);
		this->items.push_back(Item(category, name, quantity));

	}
}