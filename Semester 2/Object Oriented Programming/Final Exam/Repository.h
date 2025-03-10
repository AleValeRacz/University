#pragma once
#include <Package.h>
#include <Courier.h>
#include <fstream>
#include <sstream>
class Repository
{
private:
	vector<Package> packages;
	vector<Courier> couriers;

public:
	Repository() { this->loadFile(); };
	~Repository() { this->saveFile(); }
	void loadFile();
	void saveFile();
	void addPackage(string recipient, string street, int number, double x, double y, bool status);
	 vector<Package>& getPackages() { return this->packages; }
	 vector<Courier>& getCourier() { return this->couriers; }
};

