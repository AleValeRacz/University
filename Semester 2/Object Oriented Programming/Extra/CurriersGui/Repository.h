#pragma once
#include "Courier.h"
#include "Package.h"

#include <sstream>
#include <fstream>

typedef struct
{
	string name, text;
}msg;
class Repository
{
private:
	vector<Courier> couriers;
	vector<Package> packages;
	
public:
	Repository() { this->loadFile(); }
	~Repository(){this->saveFile();}
	void loadFile();
	void saveFile();
	vector<Courier>& GetCouriers() { return this->couriers; }
	vector<Package>& GetPackage() { return this->packages; }
	void AddPackage(string recipient, string street, int nr, double x, double y, bool status);
};

