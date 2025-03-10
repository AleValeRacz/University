#include "Agancy.h"

vector <Client*> Agancy::addDwelling(double price, bool isProfi)
{
	vector<Client*> cl;
	Dwelling* d = new Dwelling(price, isProfi);
	dwellings.push_back(d);
	for (int i = 0; i < this->clients.size(); i++)
		if (clients[i]->isInterested(d))
			cl.push_back(clients[i]);
	return cl;
}

void Agancy::removeClient(std::string name) {
	auto predicate = [name](Client* c) {
		return c->get_name() == name;
		};

	clients.erase(std::remove_if(clients.begin(), clients.end(), predicate), clients.end());
}
void Agancy::initialinput()
{
	Person* p1 = new Person("Alex", 20); 
	Person* p2 = new Person("Marina", 8000);
	Company* c1 = new Company("altex", 12000, 400);
	Company* c2 = new Company("panemar", 1468, 8999);
	Dwelling* d = new Dwelling(30000, 1);
	this->clients.push_back(p1);
	this->clients.push_back(p2);
	this->clients.push_back(c1);
	this->clients.push_back(c2);
	this->dwellings.push_back(d);
}

void Agancy::writeToFile(string file_name)
{
	ofstream fout(file_name);
	for (int i = 0; i < clients.size(); i++)
		fout << clients[i]->toString();
}



