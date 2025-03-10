#pragma once
#include <vector>
#include "domain.h"
#include <algorithm>
#include <fstream>
class Agancy
{
private:
	vector<Client*>  clients;
	vector<Dwelling*> dwellings;
public:
	Agancy() { initialinput(); };
	~Agancy() {};
	vector<Client*> addDwelling(double price, bool isProfitable);
	void removeClient(string name);
	//vector <Client*> getInterested(Dwelling d);
	void writeToFile(string filename);
	void initialinput();
	vector<Client*> get_clients() { return this->clients; }
	vector<Dwelling*> get_dwellings() { return this->dwellings; }

};


