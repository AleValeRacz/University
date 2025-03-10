#include "Repository.h"

void Repository::loadFile()
{
	ifstream fin("couriers.txt");
	string name, line, x, y, rad;
	while (getline(fin, line))
	{
		istringstream iss(line);
		getline(iss, name, '|');
		getline(iss, x, ' ');
		getline(iss, y, ' ');
		getline(iss, rad, '|');
		Courier cour(name, stod(x), stod(y), stod(rad));

		string streets;
		string str;
		while (getline(iss, streets, '|'))
		{
			istringstream isss(streets);
			getline(isss, str, '|');
			cour.addStreet(str);
		}
		this->couriers.push_back(cour);
	}

	fin.close();
	fin = ifstream("packages.txt");
	string recipient, street, nr, status;
	while (getline( fin, line))
	{
		istringstream iss(line);
		getline(iss, recipient, '|');
		getline(iss, street, ',');
		getline(iss, nr, '|');
		getline(iss, x, ',');
		getline(iss, y, '|');
		getline(iss, status, '|');
		bool st=0;
		if (status == "delivered")
			 st = 1;

		this->packages.push_back(Package(recipient, street, stoi(nr), stod(x), stod(y), st));
	}
}

void Repository::saveFile()
{
	ofstream fout("packages.txt");
	for (auto pack : this->packages)
		fout << pack.toString();

}

void Repository::AddPackage(string recipient, string street, int nr, double x, double y, bool status)
{

	this->packages.push_back(Package(recipient, street, nr, x, y, status));
}




